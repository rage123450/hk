#pragma once
#include <map>

namespace els {

	class SkillInventory {

		private:
			
			std::map<int, int> m_skillInv;
			int m_skillSlots[8];
			int m_remSP;

		public:
			
			SkillInventory();
			~SkillInventory() { }
			void setSP(int amount);
			void addSP(int amount);
			void setSkillLevel(int skill, int level);
			void addSkill(int skill, int level);
			int getSkillLevel(int skill);
			bool hasSkill(int skillID);
			std::map<int, int>* getSkillInventory(); // skillid, level
			int getRemainingSP();
			int* getEquippedSkills();


	};


}