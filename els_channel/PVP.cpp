#include "PVP.hpp"

namespace els {

	int PVP::getID() {
		return m_id;
	}

	void PVP::setID(int id) {
		m_id = id;
	}

	int PVP::getMode() {
		return m_mode;
	}

	void PVP::setMode(int mode) {
		m_mode = mode;
	}

	void PVP::addPlayer(int team, Player* player) {
		switch (team) {
			case 1:
				m_red.push_back(player);
				break;
			case 2:
				m_blue.push_back(player);
				break;
		}
	}

	std::vector<Player*>& PVP::getTeam(int team) {
		switch (team) {
			case 1:
				return m_red;
				break;
			case 2:
				return m_blue;
				break;
		}
	}

	void PVP::approvePVP() {
		m_approvals++;
	}

	int PVP::getApprovals() {
		return m_approvals;
	}

	void PVP::doneLoad() {
		m_load++;
	}

	int PVP::getLoaded() {
		return m_load;
	}


}