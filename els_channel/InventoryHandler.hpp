#pragma once
#include "Connection.hpp"
#include "PacketReader.hpp"

namespace els {

	namespace InventoryHandler {

		void invDataReq(Connection* conn);
		void moveItemReq(PacketReader pr, Connection* conn);
		void discardItemReq(PacketReader pr, Connection* conn);
		void openShopReq(PacketReader pr, Connection* conn);
		void upgradeEquipEnq(Connection* conn);
		void upgradeEquipReq(PacketReader pr, Connection* conn);
		void enchantEquipReq(PacketReader pr, Connection* conn);
		void repairEquipReq(PacketReader pr, Connection* conn);
		void buyItemReq(PacketReader pr, Connection* conn);

	}


}