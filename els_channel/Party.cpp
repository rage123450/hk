#include "Party.hpp"

namespace els {

	void Party::setLeader(Player* player) {
		m_leader = player;
	}

	Player* Party::getLeader() {
		return m_leader;
	}

	int Party::getSize() {
		return m_members.size() + 1; // +1 for leader
	}

	void Party::addMember(Player* player) {
		m_members.insert(std::make_pair(player->getPlayerID(), player));
	}

	void Party::kickMember(int chrid) {
		if (m_members.find(chrid) != m_members.end()) {
			m_members.erase(chrid);
		}
	}

	bool Party::hasMember(int chrid) {
		if (m_members.find(chrid) != m_members.end()) {
			return true;
		}
		return false;
	}

	std::map<int, Player*>* Party::getMembers() {
		return &m_members;
	}

	void Party::setID(long long id) {
		m_partyid = id;
	}

	long long Party::getID() {
		return m_partyid;
	}

	void Party::setDungeonID(int dungeonid) {
		m_dungeonid = dungeonid;
	}

	int Party::getDungeonID() {
		return m_dungeonid;
	}
}