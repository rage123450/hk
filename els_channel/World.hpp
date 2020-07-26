#pragma once
#include <deque>
#include "Map.hpp"
#include "Party.hpp"
#include "PVP.hpp"
#include "PVPRoom.hpp"

namespace els {
	
	class Player;
	class Connection;
	class GameConnection;

	namespace World {
		
		// Clients
		static std::map<std::string, std::pair<Connection*, GameConnection*> > m_clients;
		bool hasClient(std::string ip);
		std::pair<Connection*, GameConnection*>* getClient(std::string ip);
		void addClient(std::string ip, Connection* conn);

		// World
		static std::map<int, Map> m_world;
		void addMap(Map map);
		Map* getMap(int mapid);

		// ²Õ¶¤
		static long long m_partyCount = 0;
		static std::map<long long, Party> m_parties;
		long long addParty(Party* party);
		void delParty(long long pid);
		Party* getParty(long long pid);

		// PVP ©Ð¶¡
		static std::map<int, PVPRoom> m_pvproom;
		void addPVPRoom(PVPRoom room);
		void removePVPRoom(PVPRoom room);
		int getPVPRoomSize();
		PVPRoom* getPVPRoom(int roomid);
		std::map<int, PVPRoom>* getPVPRooms();

		// PVP
		static std::map<int, Player*> m_pvpQueue[3];
		void pvpQueue(int mode, Player* player);
		void pvpUnqueue(int mode, int id);
		std::map<int, Player*>& getPVPQueue(int mode);
		
		static int m_pvpID = 1;
		static std::map<int, PVP> m_pvpMatch[3];
		int addPVPMatch(int mode, PVP match);
		PVP* getPVPMatch(int id);

		// Dungeons
		
		// Fields

	}

}