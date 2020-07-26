#pragma once
#include <map>
#include "Player.hpp"

namespace els {

	class Party {

		private:
			// does it need id?
			std::map<int, Player*> m_members;
			Player* m_leader;
			long long m_partyid;
			int m_dungeonid;

		public:
			Party() { }
			~Party() { }
			void setLeader(Player* player);
			Player* getLeader();
			int getSize();
			void addMember(Player* player);
			void kickMember(int chrid);
			bool hasMember(int chrid);
			std::map<int, Player*>* getMembers();
			void setID(long long id);
			long long getID();
			void setDungeonID(int dID);
			int getDungeonID();
	};

}