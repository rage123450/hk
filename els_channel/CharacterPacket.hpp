#pragma once
#include "PacketBuilder.hpp"
#include "Player.hpp"

namespace els {

	namespace CharacterPacket {

		PacketBuilder playerDataAck(Player* player);
		PacketBuilder unknown_0x2B(Player* player);
		PacketBuilder unknown_0x2C();
		PacketBuilder unknown_0x2D(Player* player);
		PacketBuilder unknown_0x2E();
		PacketBuilder unknown_0x29();
		PacketBuilder unknown_0x136();
		PacketBuilder unknown_0x2D8();
		PacketBuilder unknown_0x223();
		PacketBuilder unknown_0x26F();
		PacketBuilder unknown_0xF5(int number);
		PacketBuilder unknown_0x1DB();
		PacketBuilder unknown_0xF6(Player* player, int number);
		PacketBuilder unknown_0x3A0();

	}


}