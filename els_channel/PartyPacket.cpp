#include "PartyPacket.hpp"
#include "Party.hpp"
#include "Converter.hpp"
#include "Config.hpp"
#include "ItemDataProvider.hpp"

#pragma once

namespace els {

	namespace PartyPacket {

		PacketBuilder PartyCreateAck(long unk1, std::wstring 隊伍名稱, int dungeonid, int 難度, int unk2, int 最大人數, bool 公開,
			int unk3, bool 不知道, int unk4, int unk5, Player* chr) {

			PacketBuilder pb;
			pb
				.writeInt(0)

				.writeLong(1/*unk1*/)
				.writeElsWString(隊伍名稱)
				.writeInt(dungeonid) // 副本ID
				.writeByte(難度) // 難度
				.writeByte(unk2)
				.writeByte(最大人數)
				.writebool(公開)
				.writeByte(unk3)
				.writebool(不知道)
				.writeByte(unk4)
				.writeByte(unk5)

				// 其他隊員資訊
				.writeLong(0/*1*/) // 伺服器 ?
				.writeInt(1) // 角色頻道
				.writeLong(1/*1*/) // 角色帳號ID ?
				.writeLong(chr->getPlayerID()/*1*/) // 角色ID
				.writeByte((unsigned char)chr->getUnitClass()/*26*/) // 職業 UNITCLASS
				.writeElsWString(chr->getName()) // 角色名字
				.writeByte(chr->getLevel()) // 等級
				.writebool(false)
				.writeByte((unsigned char)chr->getUnitType()/*5*/) // 職業 UNITTYPE
				.writeInt(chr->getMap())
				.writebool(false) // 準備
				.writebool(true) // 隊長

				.finishPacket(0x11F);

			return pb;
		}

		PacketBuilder PartyDungeonEnterAck() {
			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x137);

			return pb;
		}

		PacketBuilder PartyDungeonEnterData(int dungeonid, Player* player) {

			PacketBuilder pb;
			pb
				.writeShort(0/*0x160*/)

				.writeByte(0)

/*				.writeShort(2)
				.writeByte(1)
				.writeByte(0)
				.writeInt(12)*/
				.writeLong(0x100000000B) // roomid

				.writeInt(0)
				.writeElsWString(L""/*"혼자 하는 던전"*/) // 房間名稱 意思是獨自副本
				.writeByte(5)
				.writebool(false/*true*/)
				.writebool(false/*true*/)
				.writeElsString("")
				.writeByte(4)
				.writeByte(1)
				.writeElsString(Config::serverIP) // 主線的IP?
				.writeShort(9101/*9301*/) // UDP port
				.writeByte(0)
				.writebool(false)
				.writeInt(-1)
				.writeByte(0)
				.writebool(false)
				.writeInt(0x469C3E00) // float 秒數 等於19999秒
				.writeShort(0)
				.writeShort(0) // WORLD_ID
				.writeByte(0)
				.writeInt(dungeonid) // 副本ID
				.writeByte(1) // 難度?
				.writeByte(0)
				.writeLong(0)

				.writeInt(1/*4*/) // 副本人數size

				.writeByte(0) // 角色index
				.writeByte(4) // 角色狀態
				.writebool(true)
				.writebool(true)
				.writebool(false)
				.writebool(false)
				.writeInt(0)

				.writeLong(player->getAccountID()) // 2 好像不是帳號ID
				.writeLong(player->getAccountID())
				.writeByte(0)
				.writebool(false)
				.writeByte(0)
				.writeLong(player->getPlayerID())
				.writeInt(player->getPlayerID()) // 17113 不是角色id
				.writeByte((unsigned char)player->getUnitClass())
				.writeInt(0)
				.writeElsWString(player->getName())
				.writeElsString(player->getIP()/*Config::serverIP*/) // 角色IP
				.writeShort(8133) // port
				.writeByte(player->getLevel())

				.writeInt(player->getMaxHP())
				.writeInt(player->getBaseAttack())
				.writeInt(player->getBaseMagicAttack())
				.writeInt(player->getBaseDef())
				.writeInt(player->getBaseMagicDef())

				;

			pb.writeInt(player->getInv()->getQuantity(9)); // equipped equips
			for (int i = 0; i < player->getInv()->getMaxSlots(9); i++) {
				int uid = (*player->getInv()->getInventory(9))[i];
				if (uid == -1) continue;
				else {
					auto item = &player->getInv()->getInventory()->find(uid)->second;
					bool isDecorative = ItemDataProvider::isDecorative(item->getItemID());
					pb
						.writeInt(item->getPosition())
						.writeLong(item->getUniqueID())
						.writeByte(9)
						.writeByte/*Short*/(item->getPosition())
						.writeInt(item->getItemID());
					if (isDecorative) {
						pb.writeByte(0);
					}
					else {
						pb.writeByte(1);
					}

					pb
						.writeInt(0)
						.writeShort(item->getEndurance())
						.writeByte(0)
						.writeByte(0)

						// 屬性
						.writeByte(0)
						.writeByte(0)
						.writeByte(0)

						.writeInt(0); // size -> short 魔法石 socket

					if (isDecorative) {
						pb.writeShort/*Int*/(7);
					}
					else {
						pb.writeShort/*Int*/(0);
					}

					if (item->getExpiry() != "0000-00-00 00:00:00") {
						pb.writeElsString(item->getExpiry());
					}
					else {
						pb.writeElsString("");
					}
				}
			}

			// 技能快捷鍵
			for (int i = 0; i < 8; i++) {
				int skillid = player->getSkillInv()->getEquippedSkills()[i];
				pb.writeShort(skillid);
				pb.writeByte(player->getSkillInv()->getSkillLevel(skillid));
			}

			pb
				.writeElsString("2000-01-01 00:00:00")
				.writeByte(2);

			pb.writeInt(0/*player->getSkillInv()->getSkillInventory()->size()*/); // number of skills

/*			for (auto skill : *player->getSkillInv()->getSkillInventory()) {
				pb.writeShort(skill.first);
				pb.writeByte(skill.second);
			}*/

			pb
				.writeInt(0);

			pb
				.writeInt(0);

			pb
				.writeInt(4800) // 角色現在疲勞值
				.writeInt(4800) // 疲勞值上限
				.writebool(false)
				.writebool(false)
				.writeInt(0)
				.writebool(false)
				.writebool(false)
				.writeInt(0)
				.writeShort(0)
				.writeElsString("")
				.writeInt(0)
				.writeByte(0)
				;

			int size = 0/*3*/; // 第二個人數size
			pb.writeInt(size);

			pb
				.writeElsString("")
				.writeInt(0) /// 裝備

				.finishPacket(0x138);

			return pb;
		}
	}
}