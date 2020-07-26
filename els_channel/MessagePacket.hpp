#pragma once

#include "PacketBuilder.hpp"

namespace els {

	namespace MessagePacket {

		PacketBuilder generalChatAck();
		PacketBuilder generalChat(int playerid, int channel, long unk, std::wstring message);

	}


}