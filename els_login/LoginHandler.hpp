#pragma once
#include "PacketReader.hpp"
#include "Connection.hpp"

namespace els {

	namespace LoginHandler {

		void userLogin(PacketReader pr, Connection* conn);
		void checkSerial(PacketReader pr, Connection* conn, std::string user, std::string serial);
		void serverListReq(Connection* conn);
		void channelListReq(Connection* conn);
		void terminateConnection(Connection* conn);

	}


}