#include "SkillInventory.hpp"
#include <cstring>

namespace els {

	SkillInventory::SkillInventory() {
		m_remSP = 0;
		memset(m_skillSlots, 0, sizeof(m_skillSlots));
	}

	void SkillInventory::setSP(int amount) {
		m_remSP = amount;
	}

	void SkillInventory::addSP(int amount) {
		m_remSP += amount;
	}

	void SkillInventory::setSkillLevel(int skill, int level) {
		//if (hasSkill(skill) && level <= m_remSP) { // make sure have enough sp to inc level
			m_skillInv[skill] = level;
			//addSP(-sp); // deduct sp used
		//}
	}

	void SkillInventory::addSkill(int skill, int level) { // used for loading ONLY.
		m_skillInv[skill] = level;
	}

	int SkillInventory::getSkillLevel(int skill) {
		if (hasSkill(skill)) {
			return m_skillInv[skill];
		}
		else {
			return 0;
		}
	}

	bool SkillInventory::hasSkill(int skill) {
		if (m_skillInv.find(skill) != m_skillInv.end()) {
			return true;
		}
		return false;
	}

	std::map<int, int>* SkillInventory::getSkillInventory() {
		return &m_skillInv;
	}

	int SkillInventory::getRemainingSP() {
		return m_remSP;
	}

	int* SkillInventory::getEquippedSkills() {
		return &m_skillSlots[0];
	}

}