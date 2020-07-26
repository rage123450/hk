#pragma once

#include "PacketBuilder.hpp"

namespace els {

	namespace SkillPacket {
		
		PacketBuilder distributeSPAck(int remSP, std::vector<std::pair<int, std::pair<int, int> > >* skills);
		PacketBuilder modifySkillSlotsAck(int dstIndex, int dstSkill, int srcIndex, int srcSkill);

	}



}