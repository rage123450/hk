#pragma once
#include <vector>
#include "Player.hpp"

namespace els {

	class PVP {

		private:
			int m_id;
			int m_mode;
			int m_approvals;
			int m_load;
			std::vector<Player*> m_red;
			std::vector<Player*> m_blue;

		public:
			PVP() { m_approvals = 0; m_load = 0; }
			~PVP() { }
			int getID();
			void setID(int id);
			int getMode();
			void setMode(int mode);
			void addPlayer(int team, Player* player);
			void approvePVP();
			int getApprovals();
			void doneLoad();
			int getLoaded();
			std::vector<Player*>& getTeam(int team);

	};

}