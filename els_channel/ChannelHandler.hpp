#pragma once
#include "Connection.hpp"
#include "GameConnection.hpp"
#include "PacketReader.hpp"

namespace els {

	namespace ChannelHandler {

		void unknown_0x232(PacketReader pr, Connection* conn);
		void unknown_0x234(Connection* conn);
		void packetError(PacketReader pr, Connection* conn);
		void useCoBoExpress(PacketReader pr, Connection* conn);
		void gameConnStartReq(PacketReader pr, GameConnection* conn);
		void mapMovement(PacketReader pr, Connection* conn);

	}

}