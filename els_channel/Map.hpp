#pragma once

#include "Player.hpp"
#include "Party.hpp"
#include <set>

namespace els {

	class Map {

		private:
			int m_id;
			std::map<int, Player*> m_players;
			std::map<long long, Party*> m_parties;

		public:
			Map(int id);
			Map() { }
			~Map() { }
			int getID();
			std::map<int, Player*>* getPlayers();
			void addPlayer(Player* player);
			void removePlayer(int id);
			void addParty(Party* party);
			void delParty(long long pid);
			std::map<long long, Party*>* getParties();


	};


}