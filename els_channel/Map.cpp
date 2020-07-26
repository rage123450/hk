#include "Map.hpp"
#include "Converter.hpp"
#include <cassert>
#include <iostream>

namespace els {

	Map::Map(int id) : m_id(id) { }

	int Map::getID() {
		return m_id;
	}

	std::map<int, Player*>* Map::getPlayers() {
		return &m_players;
	}

	void Map::addPlayer(Player* player) {
		std::cout << "MID: " << std::dec << m_id << std::endl;
//		std::cout << player->getName() << std::endl;
		m_players.insert(std::make_pair(player->getPlayerID(), player));
	}

	void Map::removePlayer(int id) {
		if (m_players.find(id) != m_players.end())
			m_players.erase(id);
	}

	void Map::addParty(Party* party) {
		m_parties.insert(std::make_pair(party->getID(), party));
	}

	void Map::delParty(long long pid) {
		if (m_parties.find(pid) != m_parties.end()) {
			m_parties.erase(pid);
		}
	}

	std::map<long long, Party*>* Map::getParties() {
		return &m_parties;
	}

}