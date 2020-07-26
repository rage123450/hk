#pragma once
#include "PacketReader.hpp"

namespace els {

	class Connection;
	class GameConnection;

	namespace ChannelServerHandler {

		void handlePacket(PacketReader pr, Connection* c);
		void handlePacket(PacketReader pr, GameConnection* c);

	}

}