#pragma once
#include <string>
#include <vector>
#include "Constants.hpp"

namespace els {
	
	class Skill {

		private:

			int m_id;										// skill id: a unique identifier for the skill
			Constants::skillType m_type;					// skill type: indicates the type of the skill (eg. special active)
			std::string m_name;								// skill name: the name of the skill
			short m_reqLearnSP;								// skill reqLearnSP: indicates the amount of SP required the learn the skill
			short m_reqUpgradeSP;							// skill reqUpgradeSP: indicates amount of SP needed to raise level of skill
			std::vector<short> m_reqCharLevel;				// skill reqCharLevel: indicates the level required to raise level of skill
			std::vector<short> m_cooldown;					// skill cooldown: the cooldown of the skill
			std::vector<short> m_reqMP;						// skill reqMP: indicates the amount of MP required to use the skill

			Constants::unitClass m_unitClass;				// skill unitClass: indicates the unit class that the skill belongs to
			short m_masterLevel;							// skill masterLevel: indicates the max level of the skill

		public:

			Skill();										// constructor
			~Skill();										// destructor

			// no set methods, skills are pretty rigid

			int getSkillID();								// returns the unique identifier of the skill
			Constants::skillType getSkillType();			// returns the type of the skill (eg. special active)
			std::string getSkillName();						// returns the name of the skill
			short getReqLearnSP();							// returns the amount of SP required the learn the skill
			short getReqUpgradeSP();						// returns the amount of SP needed to raise the level the skill
			short getReqCharLevel(short curLevel);			// returns the level required to raise level of skill. curLevel: current level of skill
			short getCooldown(short curLevel);				// returns the cooldown of the skill. curLevel: current level of the skill
			short getReqMP(short curLevel);					// returns the amount of SP needed to use the skill. curLevel: current level of the skill
			Constants::unitClass getSkillUnitClass();		// returns the unit class that the skill belongs to
			short getMasterLevel();							// returns the master level of the skill

	};

}