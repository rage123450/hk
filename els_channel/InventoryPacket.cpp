#include "InventoryPacket.hpp"
#include "World.hpp"
#include "ItemDataProvider.hpp"
#include "Time.hpp"

namespace els {

	namespace InventoryPacket {

		void addItemData(PacketBuilder* pb, Item* item, int invtype, int invpos) {
			
			if (item == nullptr) {
				pb
					->writeLong(0)
					.writeByte(invtype)
					.writeByte/*Short*/(invpos)
					.writeInt(0)
					.writeByte(0)
					.writeInt(1) // ¼Æ¶q
					.writeShort(0)
					.writeByte(0)
					.writeByte(0)

					.writeByte(0)
					.writeByte(0)
					.writeByte(0)

					.writeInt(0)
					.writeShort(0)
					.writeElsString("")
					;
			}
			else {
				pb
					->writeLong(item->getUniqueID())
					.writeByte(invtype)
					.writeByte/*Short*/(invpos)
					.writeInt(item->getItemID());

				if (invtype == 7 || ItemDataProvider::isDecorative(item->getItemID())) { // decoratives
					pb->writeByte(0);
				}
				else {
					pb->writeByte(1);
				}

				pb	
					->writeInt(item->getQuantity())
					.writeShort(item->getEndurance());

				if (item->isSealed()) pb->writeByte(100);
				else pb->writeByte(0);
				
				pb->writeByte(item->getUpgrades());

				pb->writeByte(item->getAttribute(0));
				std::cout << "ATTR1: " << item->getAttribute(0) << std::endl;
				pb->writeByte(item->getAttribute(1));
				std::cout << "ATTR2: " << item->getAttribute(1) << std::endl;
				pb->writeByte(item->getAttribute(2));
				std::cout << "ATTR3: " << item->getAttribute(2) << std::endl;

				pb->writeInt(0);	// size -> short (socket data)
//				pb->writeInt(0);	// additional effects
//				pb->writeByte(item->getStatus());
					
				if (ItemDataProvider::isDecorative(item->getItemID())) {
					pb->writeShort(7);
				}
				else {
					pb->writeShort(0);
				}
				if (item->getExpiry() != "0000-00-00 00:00:00") {
					pb->writeElsString(item->getExpiry());
				}
				else {
					pb->writeElsString("");
				}
			}
		}

		PacketBuilder invDataEnd() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writebool(true)
//				.writebool(true)
				.finishPacket(0x1B);

			return pb;
		}

		PacketBuilder invData(Player* player, int invtype) {

			PacketBuilder pb;
			pb
				.writeInt(invtype)
				.writeInt(player->getInv()->getQuantity(invtype));

			for (int i = 0; i < player->getInv()->getMaxSlots(invtype); i++) {
				int uid = (*player->getInv()->getInventory(invtype))[i];
				if (uid == -1) continue;
				auto item = player->getInv()->getItem(uid);
				pb
					.writeLong(item->getUniqueID());
				addItemData(&pb, item, invtype, i);
					
			}

			pb.finishPacket(0x1C);

			return pb;

		}

		PacketBuilder moveItem(Player* player, int srcInv, int srcSlot, int dstInv, int dstSlot) {

			PacketBuilder pb;
			pb
				.writeInt(2);
			auto srcItem = player->getInv()->getItem((*player->getInv()->getInventory(srcInv))[srcSlot]);
			auto dstItem = player->getInv()->getItem((*player->getInv()->getInventory(dstInv))[dstSlot]);
			addItemData(&pb, srcItem, srcInv, srcSlot);
			addItemData(&pb, dstItem, dstInv, dstSlot);
			pb
				.writeLong(0)
				.writeByte(0)
				.finishPacket(0xEC/*0x10B*/);

			return pb;
		}

		PacketBuilder discardItem(Player* player, int invtype, int invpos) {

			PacketBuilder pb;
			pb
				.writeInt(0);

			auto item = player->getInv()->getItem((*player->getInv()->getInventory(invtype))[invpos]);
			addItemData(&pb, item, invtype, invpos);

			pb.finishPacket(0x111);

			return pb;
		}

		PacketBuilder openShop(int shopid) {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writeInt(shopid)
				.writeLong(1)
				.writeInt(Time::timestamp_now())
				.writeLong(0)
				.finishPacket(0x563);

			return pb;
		}

		PacketBuilder upgradeEquipOK() {

			PacketBuilder pb;
			pb
				.writeByte(0)
				.finishPacket(0x3D1);

			return pb;

		}

		PacketBuilder upgradeEquip(Player* player, int result, Item* equip, Item* stone, int stonepos) {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writeInt(player->getED()) // free upgrades!
				.writeInt(result)
				.writeLong(equip->getUniqueID())
				.writeInt(equip->getItemID())
				.writeInt(2); // just make it 2 for simplicity

			addItemData(&pb, equip, 1, equip->getPosition());
			if (stone != nullptr)
				addItemData(&pb, stone, 4, stonepos);
			else
				addItemData(&pb, nullptr, 4, stonepos);
			
			pb.finishPacket(0x1D0);

			return pb;
		}

		PacketBuilder enchantItem(Player* player, Item* item, int slot, int enc, std::vector<std::pair<int, Item*> > shardSlots) {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writeInt(player->getED()) // free enchantments!
				.writeLong(item->getUniqueID())
				.writeInt(item->getItemID())
				.writeByte(slot)
				.writeByte(enc);
			
			pb.writeInt(shardSlots.size() + 1);

			std::cout << "POS: " << item->getPosition() << std::endl;

			for (int i = 0; i < shardSlots.size(); i++) {
				addItemData(&pb, shardSlots[i].second, 4, shardSlots[i].first);
			}
			addItemData(&pb, item, 1, item->getPosition());
			pb.finishPacket(0x212);

			return pb;

		}

		PacketBuilder repairEquip(Player* player, std::vector<Item*> repaired) {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writeInt(player->getED())
				.writeInt(player->getAP())
				.writeInt(repaired.size());

			for (int i = 0; i < repaired.size(); i++) {
				addItemData(&pb, repaired[i], 1, repaired[i]->getPosition());
			}

			pb.finishPacket(0x194);

			return pb;

		}

	}


}