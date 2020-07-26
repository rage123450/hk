#pragma once
#include "PacketReader.hpp"
#include "Connection.hpp"

namespace els {

	namespace AuthHandler {

		void userLogin(PacketReader pr, Connection* conn);
		void checkSerial(PacketReader pr, Connection* conn, std::string user, std::string serial);
		void serverListReq(Connection* conn);
		void channelListReq(Connection* conn);
		void verCheckReq(PacketReader pr, Connection* conn);
		void channelLoginReq(PacketReader pr, Connection* conn);
		void unknown_0x33(Connection* conn);
		void dateReq(Connection* conn);
		void channelIPReq(Connection* conn);
		void charlistReq(Connection* conn);
		void channelApproveReq(Connection* conn);
		void unknown_0x48D(Connection* conn);
		void checkCharNameReq(PacketReader pr, Connection* conn);
		void createCharReq(PacketReader pr, Connection* conn);
		void terminateConnection(Connection* conn);

	}


}