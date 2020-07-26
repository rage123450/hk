#include "ChannelPacket.hpp"
#include "Converter.hpp"

namespace els {

	namespace ChannelPacket {

		PacketBuilder unknown_0x2EB() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writeInt(1)
				.writeInt(1)
				.writeInt(0)
				.finishPacket(0x2EB);
			return pb;

		}

		PacketBuilder unknown_0x102(int number) {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writeInt(number)
				.writeLong(0)
				.writeLong(0)
				.writeInt(0)
				.finishPacket(0x102);
			return pb;
		}

		PacketBuilder unknown_0x429() {

			PacketBuilder pb;
			pb
				.writeLong(0)
				.finishPacket(0x429);
			
			return pb;
		}

		PacketBuilder unknown_0x1B9() {

			PacketBuilder pb;
			pb
				.writeLong(0)
				.writeByte(1)
				.writeLong(0)
				.writeLong(0)
				.writeInt(0)
				.finishPacket(0x1B9);

			return pb;

		}

		PacketBuilder unknown_0x233() { // 移至村莊地圖中

			PacketBuilder pb;
			pb
				.writeInt(0)
//				.writeLong(0)
				.finishPacket(0x21D);

			return pb;

		}

		PacketBuilder unknown_0x23F() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x229/*0x23F*/);
			return pb;

		}

		PacketBuilder unknown_0x235() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x21F);

			return pb;

		}

		PacketBuilder useCoBoExpressAck(Player* player) {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writeInt(player->getED())
				.writeInt(player->getMap())
				.finishPacket(0x508);

			return pb;

		}

		PacketBuilder mapPlayerData(Player* player) {

			PacketBuilder pb;

			pb
				.writeInt(1); // 角色數量

			pb
				.writeLong(player->getPlayerID())
				.writeElsWString(player->getName())
				.writeByte((unsigned char)player->getUnitClass())
				.writeByte(player->getLevel())
				.writeByte(-1/*0*/); // 競技排名 0 = F 1 = D

			pb.writeInt(player->getInv()->getQuantity(9));
			for (auto equip : *player->getInv()->getInventory()) {
				if (equip.second.isEquipped()) {
					pb
						.writeLong(equip.second.getUniqueID())
						.writeInt(equip.second.getItemID())
						.writeByte(9)
						.writeByte(equip.second.getPosition())
						.writeByte(0)
						// 屬性
						.writeByte(0)
						.writeByte(0)
						.writeByte(0)
						;
				}
			}

			pb

				.writeShort(0)
				
				.writeFloat(player->getX())
				.writeFloat(player->getY())
				.writeFloat(player->getZ())
/*				.writeInt(0xC4C42516) // float
				.writeInt(0x44065BA5) // float
				.writeInt(0x43930000) // float*/

				.writeLong(0)
				.writeInt(0) // size -> long str int byte byte bool bool byte byte
				.writeElsWString(L"胖呆說得對") // 公會

			.writeInt(0) // size -> long 跟角色數量分開的 角色到公會那邊

				/*				.writeInt(0)
				                .writeInt(0x455B499A)
								.writeInt(0x42883E77)
								.writeLong(0)
								.writeLong(0)
								.writeLong(0)
								.writeLong(0)
								.writeLong(0)
								.writeLong(0)
								.writeLong(0)
								.writeLong(0)
								.writeLong(0)
								.writeLong(0);*/
			   ;

				pb.finishGamePacket(0x221/*0x237*/);

			return pb;
		}

		PacketBuilder mapMovementData(Player* player, PacketReader* pr) {

			PacketBuilder pb;
			pb
				.writeLong(player->getPlayerID());

/*			int i;
			for (i = 0; i < pr->getLength(); i++) {
				pb.writeByte(pr->getPacket()[i]);
			}*/
		    
			pb
				.writeFloat(player->getX())
				.writeFloat(player->getY())
				.writeFloat(player->getZ());

			int size = pr->readInt();
			pb.writeInt(size);
			for (int i = 0; i < size; i++) {
				pb.writeByte(pr->readByte());
				pb.writeByte(pr->readByte());
			}

			pb.writebool(pr->readbool());

			// 下面的的不會傳
			// pr->readByte() // 02
			// pr->readShort() // 3B BE

			pb.finishGamePacket(0x225/*0x23B*/);

			return pb;


		}

	}


}