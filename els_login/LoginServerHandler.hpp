#pragma once
#include "PacketReader.hpp"

namespace els {

	class Connection;

	namespace LoginServerHandler {
		
		void handlePacket(PacketReader pr, Connection* c);

	}
}