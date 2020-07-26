#pragma once

#include "Connection.hpp"
#include "PacketReader.hpp"

namespace els {

	namespace SkillHandler {

		void distributeSP(PacketReader pr, Connection* conn);
		void modifySkillSlots(PacketReader pr, Connection* conn);

	}


}