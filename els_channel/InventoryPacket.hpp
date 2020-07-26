#pragma once

#include "PacketBuilder.hpp"
#include "Player.hpp"
#include <vector>

namespace els {

	namespace InventoryPacket {

		void addItemData(PacketBuilder* pb, Item* item, int invtype, int invpos);
		PacketBuilder invDataEnd();
		PacketBuilder invData(Player* player, int invtype);
		PacketBuilder moveItem(Player* player, int srcInv, int srcSlot, int dstInv, int dstSlot);
		PacketBuilder discardItem(Player* player, int invtype, int invpos);
		PacketBuilder openShop(int shopid);
		PacketBuilder upgradeEquipOK();
		PacketBuilder upgradeEquip(Player* player, int result, Item* equip, Item* stone, int stonepos);
		PacketBuilder enchantItem(Player* player, Item* item, int slot, int enc, std::vector<std::pair<int, Item*> > shardSlots);
		PacketBuilder repairEquip(Player* player, std::vector<Item*> repaired);

	}


}