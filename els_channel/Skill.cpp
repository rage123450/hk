#include "Skill.hpp"

namespace els {

	Skill::Skill() {

		m_id = 0;
		m_type = Constants::skillType::ST_NONE;
		m_name = "";
		m_reqLearnSP = 0;
		m_reqUpgradeSP = 0;
		m_unitClass = Constants::unitClass::UC_NONE;
		m_masterLevel = 0;
	}

	Skill::~Skill() { }

	int Skill::getSkillID() {
		return m_id;
	}

	Constants::skillType Skill::getSkillType() {
		return m_type;
	}

	std::string Skill::getSkillName() {
		return m_name;
	}

	short Skill::getReqLearnSP() {
		return m_reqLearnSP;
	}

	short Skill::getReqUpgradeSP() {
		return m_reqUpgradeSP;
	}

	short Skill::getReqCharLevel(short curLevel) {
		return m_reqCharLevel[curLevel];
	}

	short Skill::getCooldown(short curLevel) {
		return m_cooldown[curLevel];
	}

	short Skill::getReqMP(short curLevel) {
		return m_reqMP[curLevel];
	}

	Constants::unitClass Skill::getSkillUnitClass() {
		return m_unitClass;
	}

	short Skill::getMasterLevel() {
		return m_masterLevel;
	}

}