#include "SkillPacket.hpp"

namespace els {

	namespace SkillPacket {

		PacketBuilder distributeSPAck(int remSP, std::vector<std::pair<int, std::pair<int, int> > >* skills) {

			PacketBuilder pb;
			pb
				.writeInt(0)

//				.writeInt(1)
//				.writeInt(skills->size())
                ;

			for (auto skill : *skills) {
				
				pb
					.writeInt(skill.first)
//					.writeInt(skill.first)
//					.writeInt(skill.second.first) // original skill level
					.writeInt(skill.second.second) // current skill level
					.writeInt(0);

			}

			pb
				.writeInt(remSP)
				.writeInt(0)
				.finishPacket(0x10B);

			return pb;

		}

		PacketBuilder modifySkillSlotsAck(int dstIndex, int dstSkill, int srcIndex, int srcSkill) {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writeInt(dstIndex)
				.writeInt(dstSkill)
				.writeInt(srcIndex)
				.writeInt(srcSkill)
				.finishPacket(0x10D);

			return pb;
		}

	}



}