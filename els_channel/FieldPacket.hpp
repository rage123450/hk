#pragma once

#include "PacketBuilder.hpp"
#include "Player.hpp"

namespace els {

	namespace FieldPacket {

		PacketBuilder playerList(Player* player);
		PacketBuilder CashShopInfo();
		PacketBuilder CashShopUnk();
		PacketBuilder SquareInfo();
		PacketBuilder SquareEnter(Player* player);
		PacketBuilder OpenPersonalShopAck(int playerid);

	}


}