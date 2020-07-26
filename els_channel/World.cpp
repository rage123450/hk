#include "World.hpp"
#include <thread>
#include <mutex>

namespace els {

	namespace World {

		bool hasClient(std::string ip) {
			if (m_clients.find(ip) != m_clients.end()) return true;
			else return false;
		}

		std::pair<Connection*, GameConnection*>* getClient(std::string ip) {
			return &m_clients[ip];
		}

		void addClient(std::string ip, Connection* conn) {
			m_clients.insert(make_pair(ip, std::make_pair(conn, nullptr)));
		}

		void addMap(Map map) {
			m_world.insert(std::make_pair(map.getID(), map));
		}

		Map* getMap(int mapid) {
			auto it = m_world.find(mapid);
			if (it != m_world.end()) return &it->second;
			else return nullptr;
		}

		std::mutex pmtx;

		long long addParty(Party* party) {
			pmtx.lock();
			m_partyCount++;
			long long a = m_partyCount;
			m_parties.insert(std::make_pair(m_partyCount, *party));
			m_parties[a].setID(m_partyCount);
			pmtx.unlock();
			return a;
		}

		void delParty(long long pid) {
			m_parties.erase(pid);
		}

		Party* getParty(long long pid) {
			return &m_parties[pid];
		}

		void addPVPRoom(PVPRoom room) {
			m_pvproom.insert(std::make_pair(room.getID(), room));
		}

		void removePVPRoom(PVPRoom room) {
			if (m_pvproom.find(room.getID()) != m_pvproom.end()) {
				m_pvproom.erase(room.getID());
		    }
		}

		int getPVPRoomSize() {
			return m_pvproom.size();
		}

		PVPRoom* getPVPRoom(int roomid) {
			auto it = m_pvproom.find(roomid);
			if (it != m_pvproom.end()) return &it->second;
			else return nullptr;
		}

		std::map<int, PVPRoom>* World::getPVPRooms() {
			return &m_pvproom;
		}

		void pvpQueue(int mode, Player* player) {
			m_pvpQueue[mode].insert(std::make_pair(player->getPlayerID(), player));
		}

		void pvpUnqueue(int mode, int id) {
			if (m_pvpQueue[mode].find(id) != m_pvpQueue[mode].end())
				m_pvpQueue[mode].erase(id);
		}

		std::map<int, Player*>& getPVPQueue(int mode) {
			return m_pvpQueue[mode];
		}

		std::mutex pvpmtx;

		int addPVPMatch(int mode, PVP match) {
			pvpmtx.lock();
			match.setID(m_pvpID + (mode + 1) * 1000000);
			m_pvpMatch[mode].insert(std::make_pair(m_pvpID+(mode+1)*1000000, match));
			int ret = m_pvpID + (mode + 1) * 1000000;
			m_pvpID++;
			pvpmtx.unlock();
			
			return ret;
		}

		PVP* getPVPMatch(int id) {
			if (m_pvpMatch[id%1000000].find(id) != m_pvpMatch[id%1000000].end()) {
				return &m_pvpMatch[id % 1000000][id];
			}
		}

	}


}