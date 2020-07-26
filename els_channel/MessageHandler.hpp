#pragma once

#include "Connection.hpp"
#include "PacketReader.hpp"

namespace els {

	namespace MessageHandler {

		void generalChatReq(PacketReader pr, Connection* conn);

	}


}