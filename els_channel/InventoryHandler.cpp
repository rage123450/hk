#include "InventoryHandler.hpp"
#include "InventoryPacket.hpp"
#include "ItemDataProvider.hpp"
#include "Random.hpp"

namespace els {

	namespace InventoryHandler {

		void invDataReq(Connection* conn) {

			// 0x32 to send inv data
			for (int i = 1; i < 8; i++) {
				if (conn->getPlayer()->getInv()->getQuantity(i) != 0)
					conn->sendPacket(InventoryPacket::invData(conn->getPlayer(), i).getPacket());
			}
			// end with 0x31
			conn->sendPacket(InventoryPacket::invDataEnd().getPacket());

		}

		void moveItemReq(PacketReader pr, Connection* conn) {

			int srcInv = pr.readByte();
			int srcSlot = pr.readInt();
			int dstInv = pr.readByte();
			int dstSlot = pr.readInt();
			
			// checks if necessary, skipping first
			// set new pos of src item
			conn->getPlayer()->getInv()->getItem((*conn->getPlayer()->getInv()->getInventory(srcInv))[srcSlot])
				->setPosition(dstSlot);
			// get src and dst items
			auto srcItem = conn->getPlayer()->getInv()->getItem((*conn->getPlayer()->getInv()->getInventory(srcInv))[srcSlot]);
			auto dstItem = conn->getPlayer()->getInv()->getItem((*conn->getPlayer()->getInv()->getInventory(dstInv))[dstSlot]);
			
			//see if we have to change pos of dst item 
			if (dstItem != nullptr) {
				dstItem->setPosition(srcSlot);
			}

			// check if it is swapping with an equipped item! if it is, change the equipped flags
			// unequipping
			if (srcInv == 9) {
				srcItem->setEquipped(false);
			}
			// equipping
			if (dstInv == 9) {
				srcItem->setEquipped(true);
				// check if any item is unequipped in the process, and change flag
				if (dstItem != nullptr) {
					dstItem->setEquipped(false);
				}
			}

			std::swap((*conn->getPlayer()->getInv()->getInventory(srcInv))[srcSlot],
				(*conn->getPlayer()->getInv()->getInventory(dstInv))[dstSlot]);

			conn->sendPacket(InventoryPacket::moveItem(conn->getPlayer(), srcInv, srcSlot, dstInv, dstSlot).getPacket());

		}

		void discardItemReq(PacketReader pr, Connection* conn) {

			int uid = pr.readLong();
			int quantity = pr.readInt();

			conn->getPlayer()->getInv()->getItem(uid)->changeQuantity(-quantity);

			bool decorative = ItemDataProvider::isDecorative(conn->getPlayer()->getInv()->getItem(uid)->getItemID());
			int invtype = ItemDataProvider::mapToInvType(conn->getPlayer()->getInv()->getItem(uid)->getItemID(), 
				conn->getPlayer()->getInv()->getItem(uid)->isEquipped(), decorative);
			int invpos = conn->getPlayer()->getInv()->getItem(uid)->getPosition();

			if (conn->getPlayer()->getInv()->getItem(uid)->getQuantity() == 0) {
				// delete the item
				conn->getPlayer()->getInv()->removeItem(uid);
			}

			conn->sendPacket(InventoryPacket::discardItem(conn->getPlayer(), invtype, invpos).getPacket());

		}

		void openShopReq(PacketReader pr, Connection* conn) {

			int shopid = pr.readInt();
			conn->sendPacket(InventoryPacket::openShop(shopid).getPacket());
		}

		void upgradeEquipEnq(Connection* conn) {
			conn->sendPacket(InventoryPacket::upgradeEquipOK().getPacket()); // lol 
		}

		void upgradeEquipReq(PacketReader pr, Connection* conn) {

			int uid = pr.readLong();
			Item* equip = conn->getPlayer()->getInv()->getItem(uid);
			int upgrades = equip->getUpgrades();
			int itemtype = ItemDataProvider::getItemType(equip->getItemID());
			int level = ItemDataProvider::getItemLevel(equip->getItemID());
			int result = Constants::getUpgradeResult(upgrades);
			std::cout << "RESULT: " << result << std::endl;
			int stone;

			// find upgrade stone required
			if (level <= 20) {
				stone = itemtype == 1 ? 130077 : 130086;
			}
			else if (level <= 30) {
				stone = itemtype == 1 ? 130078 : 130087;
			}
			else if (level <= 40) {
				stone = itemtype == 1 ? 130079 : 130088;
			}
			else if (level <= 50) {
				stone = itemtype == 1 ? 130080 : 130089;
			}
			else if (level <= 60) {
				stone = itemtype == 1 ? 130081 : 130090;
			}
			else if (level <= 70) {
				stone = itemtype == 1 ? 130082 : 130091;
			}
			else { return; }

			std::cout << stone << std::endl;
			
			// remove 1 upgrade stone
			int ugstoneid = conn->getPlayer()->getInv()->findItem(stone);
			Item* ugstone = conn->getPlayer()->getInv()->getItem(ugstoneid);

			int stoneslot;
			
			if (ugstone != nullptr) {
				stoneslot = ugstone->getPosition();
				ugstone->changeQuantity(-1);
				if (ugstone->getQuantity() == 0) {
					conn->getPlayer()->getInv()->removeItem(ugstone->getUniqueID());
					ugstone = nullptr;
				}
			}
			else {
				return;
			}
			
			// modify equip
			switch (result) {
				case 1: // successful
					equip->setUpgrades(equip->getUpgrades() + 1);
					break;
				case 4: // failure
					equip->setUpgrades(equip->getUpgrades() - 1);
					break;
				case 2: // reset
					equip->setUpgrades(0);
					break;
				case 5: // break
					equip->setUpgrades(0);
					// impl break later
					break;
			}
			
			// send response
			conn->sendPacket(InventoryPacket::upgradeEquip(conn->getPlayer(), result, equip, ugstone, stoneslot).getPacket());
			
		}

		void enchantEquipReq(PacketReader pr, Connection* conn) {

			int uid = pr.readLong();
			Item* item = conn->getPlayer()->getInv()->getItem(uid);
			std::cout << "POS: " << item->getPosition() << std::endl;

			int slot = pr.readByte();
			int enc = pr.readByte();
			int shardid;

			std::cout << "SLOT: " << slot << std::endl;

			// get required item
			// 0 is fine - it's for removing enchantments
			if (enc < 0 || enc > 7) {
				std::cout << "RET1" << std::endl;
				return;
			}
			else shardid = Constants::elShardReq[enc];

			std::vector<std::pair<int, Item*> > shardSlots;		//affected slots with shards

			if (enc != 0) {

				if (enc == 7) {
					// wtf random
					if (item->getNumAttr() == 1) {
						// anything will do
						enc = Random::integer(1, 6);
					}
					else {
						// TBD
					}
				}

				// get amount
				int mod = Constants::elShardIGMod[ItemDataProvider::getItemGrade(item->getItemID())];
				double multiplier;

				if (ItemDataProvider::getItemType(item->getItemID()) == 1) {
					std::cout << "POS: " << item->getPosition() << std::endl;
					switch (item->getNumAttr()) {
						case 0: multiplier = 0.5; break;
						case 1: multiplier = 1.5; break;
						case 2: multiplier = 3.0; break;
						default:
							std::cout << "RET2" << std::endl;
							return;
					}
				}
				else if (ItemDataProvider::getItemType(item->getItemID()) == 2) {
					switch (item->getNumAttr()) {
						case 0: multiplier = 0.125; break;
						case 1: multiplier = 0.375; break;
						default:
							std::cout << "RET2" << std::endl;
							return;
					}
				}
				else {
					std::cout << "RET3" << std::endl;
					return;
				}

				int reqShards = (int)floor(((double)ItemDataProvider::getItemLevel(item->getItemID()) - (double)mod) * multiplier);
				std::cout << "POS: " << item->getPosition() << std::endl;
				// remove shards used

				std::cout << "ENC1" << std::endl;

				while (reqShards != 0) {
					std::cout << "POS: " << item->getPosition() << std::endl;
					int sharduid = conn->getPlayer()->getInv()->findItem(shardid);
					Item* shard = conn->getPlayer()->getInv()->getItem(sharduid);
					if (shard != nullptr) {
						int shardslot = shard->getPosition();
						int used = 0;

						if (reqShards >= shard->getQuantity()) {
							shard->setQuantity(0);
							shardSlots.push_back(std::make_pair(shard->getPosition(), nullptr));
							reqShards -= shard->getQuantity();
						}
						else {
							shard->changeQuantity(-reqShards);
							shardSlots.push_back(std::make_pair(shard->getPosition(), shard));
							reqShards = 0;
						}
						std::cout << "ENC2" << std::endl;
						if (shard->getQuantity() == 0) {
							conn->getPlayer()->getInv()->removeItem(shard->getUniqueID());
						}
					}
					else {
						std::cout << "RET4" << std::endl;
						return;
					}
				}
			}

			std::cout << "ENC3" << std::endl;
			// change equipment attribute
			item->setAttribute(enc, slot);
			std::cout << "ATTR: " << item->getAttribute(slot) << std::endl;

			conn->sendPacket(InventoryPacket::enchantItem(conn->getPlayer(), item, slot, enc, shardSlots).getPacket());

		}

		void repairEquipReq(PacketReader pr, Connection* conn) {

			int amount = pr.readInt();
			long long uid;

			std::vector<Item*> repaired;

			for (int i = 0; i < amount; i++) {
				uid = pr.readLong();
				conn->getPlayer()->getInv()->getItem(uid)->setEndurance(10000);
				repaired.push_back(conn->getPlayer()->getInv()->getItem(uid));
			}
			
			conn->getPlayer()->setED(conn->getPlayer()->getED() - (repaired.size() * 1500));

			conn->sendPacket(InventoryPacket::repairEquip(conn->getPlayer(), repaired).getPacket());

		}

		void buyItemReq(PacketReader pr, Connection* conn) {

			pr.skipBytes(1);
			int shopid = pr.readShort();

			// do checks to make sure item is in shop

			int bought = pr.readInt();
			int itemid, amount;
			
			for (int i = 0; i < bought; i++) {
				itemid = pr.readInt();
				amount = pr.readInt();

				// fuck this
			}

		}

	}


}