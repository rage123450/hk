#pragma once
#include "PacketBuilder.hpp"
#include "PacketReader.hpp"
#include "Player.hpp"
#include "Party.hpp"

namespace els {

	namespace ChannelPacket {

		PacketBuilder unknown_0x2EB();
		PacketBuilder unknown_0x102(int number);
		PacketBuilder unknown_0x429();
		PacketBuilder unknown_0x1B9();
		PacketBuilder unknown_0x233();
		PacketBuilder unknown_0x23F();
		PacketBuilder unknown_0x235();
		PacketBuilder useCoBoExpressAck(Player* player);
		PacketBuilder mapPartyData(Party* party);
		PacketBuilder mapPlayerData(Player* player);
		PacketBuilder mapMovementData(Player* player, PacketReader* pr);

	}


}