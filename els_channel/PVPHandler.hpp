#pragma once
#include "PacketReader.hpp"
#include "Connection.hpp"

namespace els {

	namespace PVPHandler {

		void pvpQueueReq(PacketReader pr, Connection* conn);
		void pvpQueueCancel(Connection* conn);
		void pvpApproveReq(PacketReader pr, Connection* conn);
		void pvpLoadReq(PacketReader pr, Connection* conn);

	}

}