#include "SkillHandler.hpp"
#include "SkillPacket.hpp"

namespace els {

	namespace SkillHandler {

		void distributeSP(PacketReader pr, Connection* conn) {

/*			int newSkills = pr.readInt();

			// for each new skill get id
			for (int i = 0; i < newSkills; i++) {
				pr.skipBytes(4);
			}

			pr.skipBytes(4);*/

			int size = 1/*pr.readInt()*/;
			int skillid, curlevel, level;
			// curlevel is the skill level before the player adds SP to it

			std::vector<std::pair<int, std::pair<int, int> > > changedSkills;

			for (int i = 0; i < pr.getLength(); i++) {
				std::cout << static_cast<int>(pr.getPacket()[i]) << " ";
			}

			for (int i = 0; i < size; i++) {

				skillid = pr.readInt();
				std::cout << "SKILL ID: " << skillid << std::endl;
//				pr.skipBytes(4);
				curlevel = conn->getPlayer()->getSkillInv()->getSkillLevel(skillid)/*pr.readInt()*/;
				level = (conn->getPlayer()->getSkillInv()->getSkillLevel(skillid) + 1)/*pr.readInt()*/;
				std::cout << "SKILL LEVEL: " << level << std::endl;
//				pr.skipBytes(4);

				conn->getPlayer()->getSkillInv()->setSkillLevel(skillid, level);
				changedSkills.push_back(std::make_pair(skillid, std::make_pair(curlevel, level)));

			}
			int rsp = (conn->getPlayer()->getSkillInv()->getRemainingSP() - 1);
			conn->getPlayer()->getSkillInv()->setSP(rsp);
			conn->sendPacket(SkillPacket::distributeSPAck(rsp, &changedSkills).getPacket());

		}

		void modifySkillSlots(PacketReader pr, Connection* conn) {

			int slot = pr.readInt();
			int skillid = pr.readInt();
			int* slots = conn->getPlayer()->getSkillInv()->getEquippedSkills();

			bool equipped = false;
			int equippedSlot = -1;
			bool slotTaken = false;
			int takenSlot = -1;
			int srcSkill = 0;

			for (int i = 0; i < 8; i++) {
				if (slots[i] == skillid) {
					equipped = true;
					equippedSlot = i;
				}
				if (i == slot && slots[i] != -1) {
					slotTaken = true;
					takenSlot = i;
				}
			}

			if (equipped) {
				if (slotTaken) {
					std::swap(slots[equippedSlot], slots[slotTaken]);
					srcSkill = slots[equippedSlot];
				}
				else {
					slots[slot] = skillid;
					slots[equippedSlot] = -1;
				}
			}
			else {
				slots[slot] = skillid;
			}

			conn->sendPacket(SkillPacket::modifySkillSlotsAck(slot, skillid, equippedSlot, srcSkill).getPacket());

		}

	}


}