#pragma once

#include "PacketBuilder.hpp"

namespace els {

	namespace QuestPacket {

		PacketBuilder OpenNPCAck(int npcid);
		PacketBuilder QuestAcceptAck();
		PacketBuilder QuestAccept(int npcid, int questid);

	}


}