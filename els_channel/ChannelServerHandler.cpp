#include "ChannelServerHandler.hpp"
#include "AuthHandler.hpp"
#include "CharacterHandler.hpp"
#include "ChannelHandler.hpp"
#include "DungeonHandler.hpp"
#include "FieldHandler.hpp"
#include "InventoryHandler.hpp"
#include "MessageHandler.hpp"
#include "SkillHandler.hpp"
#include "PVPHandler.hpp"
#include "AuthPacket.hpp"
#include "CharacterPacket.hpp"
#include "ChannelPacket.hpp"
#include "DungeonPacket.hpp"
#include "FieldPacket.hpp"
#include "PartyPacket.hpp"
#include "PVPPacket.hpp"
#include "QuestPacket.hpp"
#include "Party.hpp"
#include "World.hpp"
#include <iomanip>

namespace els {

	namespace ChannelServerHandler {

		void handlePacket(PacketReader pr, Connection* c) {

			pr.skipBytes(32);
			unsigned short header = pr.readShort();
			pr.setLength(pr.readInt()); // 數據包長度
			pr.readByte(); // bool 是否壓縮數據包

			std::printf("TCP port 9300 RECV: 0x%x\n", header);
			if (header < 0x900) {
				for (int i = 0; i < pr.getLength(); i++) {
					std::printf("%x ", static_cast<int>(pr.getPacket()[i + 39]));
				}
				std::printf("\n");
			}
			std::cout << std::endl;

			switch (header) {
/*				case 0x27F:
					AuthHandler::userLogin(pr, c);
					break;
				case 0x4C3:
					AuthHandler::serverListReq(c);
					break;
				case 0x490:
					AuthHandler::channelListReq(c);
					break;*/

				case 0x0A:
					AuthHandler::verCheckReq(pr, c);
					break;
				case 0x0E:
					AuthHandler::channelLoginReq(pr, c);
					break;
				case 0x1D:
					AuthHandler::unknown_0x33(c);
					break;
				case 0x1EB:
					AuthHandler::dateReq(c);
					break;
				case 0x21:
					AuthHandler::channelIPReq(c);
					break;
				case 0x12:
					AuthHandler::charlistReq(c);
					break;

/*				case 0x485:
					AuthHandler::channelApproveReq(c);
					break;*/
/*				case 0x48E:
					AuthHandler::unknown_0x48D(c);
					break;
				case 0x48B:
					AuthHandler::checkCharNameReq(pr, c);
					break;*/
				case 0x14/*0x489*/:
					AuthHandler::createCharReq(pr, c);
					break;

/*				case 0x22A:
					AuthHandler::terminateConnection(c);
					break;*/

				case 0x18:
					CharacterHandler::playerDataReq(pr, c);
					break;
				case 0x1A7:
					c->sendPacket(CharacterPacket::unknown_0x1DB().getPacket());
					break;
				case 0x1A:
					InventoryHandler::invDataReq(c);
					break;

				case 0x21C:
//					std::cout << "MAP ID: " << pr.readInt() << std::endl;
					ChannelHandler::unknown_0x232(pr, c);
					break;
				// 0xE7
			    // 0x2EE
				case 0x21E:
					ChannelHandler::unknown_0x234(c); // 發了這個後才看得到自己角色
					break;
				case 0x228:
					c->sendPacket(ChannelPacket::unknown_0x23F().getPacket());
					break;

				// PVP 排隊
/*				case 0x342:
					PVPHandler::pvpQueueReq(pr, c);
					break;
				case 0x345:
					PVPHandler::pvpQueueCancel(c);
					break;
				case 0x34A:
					PVPHandler::pvpApproveReq(pr, c);
					break;*/

/*				case 0x95:
					PVPHandler::pvpLoadReq(pr, c);
					break;*/

				case 0x34: // 進入競技場(自由對戰)
					c->sendPacket(PVPPacket::pvpLobbyChannelInfo().getPacket());
					break;
				case 0x36: {
					int channel = pr.readInt();
					c->sendPacket(PVPPacket::pvpLobbyAck().getPacket());
					break;
				}
				case 0x3B: {
					// 00 00 00 01 FF
					int unk = pr.readInt(); // 系統發是0 自己選分類是1
					int type = pr.readByte(); // -1 = 觀看全部 0 = 團隊戰 1 = 團隊死鬥 2 = 生存戰
					c->sendPacket(PVPPacket::pvpLobbyRoomInfo().getPacket());
					break;
				}
				case 0x3D: { // 商店街頻道清單請求
					c->sendPacket(FieldPacket::SquareInfo().getPacket());
					break;
				}
				case 0x41:{ // 開設房間
					PVPRoom room(4); // id
					bool 不知道 = pr.readbool(); // false
					pr.readByte();
					pr.readLong();
					pr.readInt();
					room.setRoomName(pr.readElsWString());
					pr.readByte();
					room.setOpen(pr.readbool()); // false = 不公開房間 true = 公開房間
					pr.readbool(); // true
					room.setPassword(pr.readElsWString()); // 密碼
					room.setMaxPlayer(pr.readByte()); // 8 房間最大人數
					pr.readByte(); // 0 房間現在人數
					pr.readElsWString();
					pr.readShort(); // ushort
					room.setType(pr.readByte()); // 團隊戰 = 1 生存戰 = 2
					room.setProp(pr.readbool()); // 道具戰
					pr.readInt(); // FF FF FF FF
					room.setKill(pr.readByte()); // 擊殺數
					pr.readbool(); // true
					room.setSecond(pr.readFloat()); // float 44 48 00 00 = 800 秒
					pr.readShort(); // FF FF
					room.setMapId(pr.readShort()); // FF FF WORLD_ID
					pr.readByte();
					pr.readInt();
					pr.readByte();
					pr.readByte();
					pr.readLong();

					room.addPlayer(c->getPlayer());

					c->getPlayer()->setIndex(0);
					c->getPlayer()->setTeam(0);
					c->getPlayer()->setLeader(true);
					c->getPlayer()->setReady(true);

					room.setLeader(*c->getPlayer());

					World::addPVPRoom(room);

					c->sendPacket(PVPPacket::pvpLobbyCreateRoomAck(room).getPacket());
					break;
				}
				case 0x45:{ // 進入PVP房間
					// 00 00 00 00 00 00 00 00 00 00 00 00 00

					int roomid = pr.readLong();
					std::wstring password = pr.readElsWString();
					pr.readbool();

					PVPRoom* room = World::getPVPRoom(roomid);

					c->getPlayer()->setIndex(room->getPlayerSize()/*1*//*7*/); // 要找空的index
					int team = room->getPlayerSize() == 1 || room->getPlayerSize() == 3 || room->getPlayerSize() == 5 || room->getPlayerSize() == 7 ? 1 : 0;
					c->getPlayer()->setTeam(team/*1*/); // 要找缺人的隊伍
					c->getPlayer()->setLeader(false);
					c->getPlayer()->setReady(false);

					room->addPlayer(c->getPlayer());

					c->sendPacket(PVPPacket::pvpLobbyEnterRoomAck(room).getPacket());

//					c->sendPacket(PVPPacket::pvpLobbyEnterRoom(c->getPlayer()).getPacket());

					// for other players
					for (auto p : *room->getPlayers()) {
						if (p.second != c->getPlayer()) {
						    World::getClient(p.second->getIP())->first->sendPacket(PVPPacket::pvpLobbyEnterRoom(c->getPlayer()).getPacket());
						}
					}

					break;
				}
				case 0x48:{ // 進入商店街
					int 頻道 = pr.readLong();
					c->sendPacket(FieldPacket::SquareEnter(c->getPlayer()).getPacket());
					break;
				}
				case 0x1A9: { // 開設商店
					c->sendPacket(FieldPacket::OpenPersonalShopAck(c->getPlayer()->getPlayerID()).getPacket());
					break;
				}
				case 0x1AB:{ // 開始販售
					std::wstring 商店名稱 = pr.readElsWString();
					int itemsize = pr.readInt();
/*					for itemsize
					long invpos = pr.readLong(); // 7
					int quanity = pr.readInt(); // 1
					int ed = pr.readInt(); // 最大值為 500000000
					*/
//					c->sendPacket(FieldPacket::OpenPersonalShop(c->getPlayer()->getPlayerID()).getPacket());
					break;
				}
				case 0x4D: { // 退出 PVP 房間
					// 00 00 00 72
					c->sendPacket(PVPPacket::pvpRoomExitAck().getPacket());
					PVPRoom* room = World::getPVPRoom(4);
					room->removePlayer(c->getPlayer()->getPlayerID());
					if (c->getPlayer()->getLeader()) {
						World::removePVPRoom(*room);
					}
					else {
						for (auto p : *room->getPlayers()) {
//							if (p.second != c->getPlayer()) {
							World::getClient(p.second->getIP())->first->sendPacket(PVPPacket::pvpRoomExit(c->getPlayer()->getPlayerID()).getPacket());
//							}
						}
					}
					c->getPlayer()->setLeader(false);
					c->getPlayer()->setReady(false);
					break;
				}
				case 0x50: { // 退出商店街
					// 00 00 00 72
					break;
				}
				case 0x53: { // 退出 PVP 遊戲
					break;
				}
				case 0x59: { // 換隊
					int team = pr.readByte(); // 0 = 換紅隊 1 = 換藍隊
					c->sendPacket(PVPPacket::pvpRoomChangeTeamAck().getPacket());
					// 要找空的index
/*					PVPRoom* room = World::getPVPRoom(4);
					for (auto p : *room->getPlayers()) {
						World::getClient(p.second->getIP())->first->sendPacket(PVPPacket::pvpRoomChangeTeam(c->getPlayer()->getPlayerID(), team).getPacket());
					}*/
					break;
				}
				case 0x5C: { // 準備
					bool ready = pr.readbool();
					c->getPlayer()->setReady(ready);
					c->sendPacket(PVPPacket::pvpRoomReadyAck().getPacket());
					PVPRoom* room = World::getPVPRoom(4);
					for (auto p : *room->getPlayers()) {
						World::getClient(p.second->getIP())->first->sendPacket(PVPPacket::pvpRoomReady(c->getPlayer()->getPlayerID(), ready).getPacket());
					}
					break;
				}
				case 0x62:{ // 房長修改地圖
					int WORLD_ID = pr.readShort();
					PVPRoom* room = World::getPVPRoom(4);
					room->setMapId(WORLD_ID);
					c->sendPacket(PVPPacket::pvpRoomChangeMapAck().getPacket());
					for (auto p : *room->getPlayers()) {
						World::getClient(p.second->getIP())->first->sendPacket(PVPPacket::pvpRoomChangeMap(WORLD_ID).getPacket());
					}
					break;
				}
				case 0x65: { // 房長關閉開放格子
					// 01 02 
					// 位置長這樣 00 01 02 03
					//            07 06 05 04
					int 位置 = pr.readByte(); // index
					int state = pr.readByte(); // 01 = 開放 02 = 關閉
					break;
				}
				case 0x68: { // 房長修改時間
					// 44 89 80 00 float
					PVPRoom* room = World::getPVPRoom(4);
					float second = pr.readFloat();
					c->sendPacket(PVPPacket::pvpRoomChangeSecondAck().getPacket());
					for (auto p : *room->getPlayers()) {
						World::getClient(p.second->getIP())->first->sendPacket(PVPPacket::pvpRoomChangeSecond(second).getPacket());
					}
					break;
				}
				case 0x6B: { // 修改擊殺數
					PVPRoom* room = World::getPVPRoom(4);
					int kill = pr.readInt();
					c->sendPacket(PVPPacket::pvpRoomChangeKillAck().getPacket());
					for (auto p : *room->getPlayers()) {
						World::getClient(p.second->getIP())->first->sendPacket(PVPPacket::pvpRoomChangeKill(kill).getPacket());
					}
					break;
				}
				case 0x71: { // 在PVP房間裡面會一直發
					PVPRoom* room = World::getPVPRoom(4);
					bool unk = pr.readbool(); // 00 或 01
					c->sendPacket(PVPPacket::pvpRoomUnkAck().getPacket());
//					c->sendPacket(PVPPacket::pvpRoomUnk(c->getPlayer()->getPlayerID(), true).getPacket());
					for (auto p : *room->getPlayers()) {
//						if (p.second != c->getPlayer()) {
							World::getClient(p.second->getIP())->first->sendPacket(PVPPacket::pvpRoomUnk(c->getPlayer()->getPlayerID(), unk).getPacket());
//						}
					}
					break;
				}
				case 0x29E: { // PVP 遊戲裡面會發的
					// 00 00 00 0D
//					int time = pr.readInt();
					break;
				}
				case 0x43: // 新手教學
					DungeonHandler::tutorialReq(pr, c);
					break;
				case 0x74: { // PVP 也是用這個
//					int WORLD_ID = pr.readShort(); // 00 49
					// 00 04 00 00
//					DungeonHandler::tutorialStartReq(c);

					c->sendPacket(DungeonPacket::tutorialStartAck().getPacket());

//					c->sendPacket(DungeonPacket::tutorialStartAck2(c->getPlayer()).getPacket());
					PVPRoom* room = World::getPVPRoom(4);
					for (auto p : *room->getPlayers()) {
						World::getClient(p.second->getIP())->first->sendPacket(DungeonPacket::tutorialStartAck2(c->getPlayer()).getPacket());
					}
					break;
				}
				case 0x77: { // PVP 亂入
					break;
				}
				case 0x7A/*0x95*/: {// PVP的讀取也是用這個 
//				    DungeonHandler::dungeonLoadReq(pr, c);
					int load = pr.readInt();
					c->sendPacket(DungeonPacket::dungeonLoadAck().getPacket());

//					c->sendPacket(DungeonPacket::dungeonLoad(c->getPlayer(), load).getPacket());
					PVPRoom* room = World::getPVPRoom(4);
					for (auto p : *room->getPlayers()) {
						World::getClient(p.second->getIP())->first->sendPacket(DungeonPacket::dungeonLoad(c->getPlayer(), load).getPacket());
					}

					if (load == 100) { // 這個要房間裡全玩家同步

/*						for (auto p : *room->getPlayers()) {
							World::getClient(p.second->getIP())->first->sendPacket(DungeonPacket::dungeonLoadDone().getPacket());
							World::getClient(p.second->getIP())->first->sendPacket(DungeonPacket::dungeonEnter(c->getPlayer()).getPacket());
						}*/
						c->sendPacket(DungeonPacket::dungeonLoadDone().getPacket());
						c->sendPacket(DungeonPacket::dungeonEnter(c->getPlayer()).getPacket());

						float 時間 = room->getSecond()/*1000*/;
/*						for (auto p : *room->getPlayers()) {
							for (float i = 時間; i > 0; i -= 5) {
								World::getClient(p.second->getIP())->first->sendPacket(DungeonPacket::TimeUpdate(時間).getPacket());
							}
						}*/
						// 不發這個角色會不能動
						for (float i = 時間; i > 0; i -= 5) {
							c->sendPacket(DungeonPacket::TimeUpdate(時間).getPacket());
						}
					}
					break;
				}

				case 0x8A: {
					// 00 00 00 00 00 00 00 00 00 00 03 20 00 00 00 00 00 00
					break;
				}
				case 0x9A: {// 擊倒怪物
					// 00 00 02 00 (怪物OID)
					// 00 
					// 00 00 00 00 00 00 00 01 
					// 00 00 00 00 00 00 00 01 
					// 45 07 95 88 00 00 00 00 43 d3 92 e8 
					// 00
					int moboid = pr.readInt();
					int unk1 = pr.readByte();
					int playerid1 = pr.readLong();
					int playerid2 = pr.readLong();
					float X = pr.readFloat();
					float Y = pr.readFloat();
					float Z = pr.readFloat();
					int unk2 = pr.readByte();
					break;
				}

				case 0x9D/*0xB7*/: // 召喚怪物
					DungeonHandler::dungeonSpawnMonsterReq(c);
					break;
				case 0xA0/*0xBA*/:
					DungeonHandler::unknown_0xBA(c);
					break;
				case 0xA4/*0xBE*/:
					DungeonHandler::unknown_0xBE(pr, c);
					break;
				case 0xA7/*0xC1*/: // 進入玻璃門的範圍請求敲碎
					DungeonHandler::unknown_0xC1(pr, c);
					break;
				case 0xAA/*0xC4*/:
					DungeonHandler::unknown_0xC4(pr, c);
					break;
/*				case 0xB1:
					DungeonHandler::unknown_0xB1(pr, c);
					break;*/

				case 0xD7: { // 遊戲指南開關
					// 00
					bool open = pr.readbool();
					break; 
				}

				// Storyline Dungeons
/*				case 0x389:
					DungeonHandler::dungeonListReq(pr, c);
					break;
				case 0x37C:
					DungeonHandler::dungeonEntryReq(pr, c);
					break;
				case 0x470:
					DungeonHandler::dungeonStageClear(c);
					break;
				case 0xB4:
					//DungeonHandler::dungeonDestroyObject(pr, c);
					break;*/

				case 0xE9:{ // 打開NPC
					int npcid = pr.readInt();
					c->sendPacket(QuestPacket::OpenNPCAck(npcid).getPacket());
					// 要發送 0xEA int(ack) int(npcid?)
					break;
				}

				case 0xDD: { // 接任務
					// 00 00 C3 A0 00 00 27 14
					int questid = pr.readInt();
					int npcid = pr.readInt();
					c->sendPacket(QuestPacket::QuestAcceptAck().getPacket());
					c->sendPacket(QuestPacket::QuestAccept(npcid, questid).getPacket());
					break;
				}

				case 0x104: // 角色資訊
//					std::wstring playername = pr.readElsWString();
					break;
				case 0x106: // 玩家資訊
//					int playerid = pr.readLong();
					break;
				case 0x16A: // 個人交易
//					int playerid = pr.readLong();
					break;

                // 組隊
				case 0x3F: { // 隊伍清單
					bool firstopen = pr.readByte() == 1;
					pr.skipBytes(6);
					if (firstopen) {
						int mapid = pr.readInt();
					} else {
						int dungeonid = pr.readInt();
					}
					break;
				}
				case 0x11E: { // 創建組隊
					long unk1 = pr.readLong(); // FF FF FF FF FF FF FF FF
					std::wstring partyname = pr.readElsWString(); // 00 00 00 00
					int dungeonid = pr.readInt();
					int difficulty = pr.readByte(); // 00
					int unk2 = pr.readByte(); // 00
					int maxplayer = pr.readByte(); // 04
					bool notprivate = pr.readByte() == 1; // 01
					int unk3 = pr.readByte(); // 01
					bool idk = pr.readByte() == 1; // 00
					int unk4 = pr.readByte(); // 01
					int unk5 = pr.readByte(); // 00
					Party party;
					party.setLeader(c->getPlayer());
					long long pid = World::addParty(&party);
					c->getPlayer()->setParty(World::getParty(pid));
					World::getMap(c->getPlayer()->getMap())->addParty(c->getPlayer()->getParty());
					c->sendPacket(PartyPacket::PartyCreateAck(unk1, partyname, dungeonid, difficulty, unk2, maxplayer, notprivate,
						unk3, idk, unk4, unk5, c->getPlayer()).getPacket());
					break;
				}

				case 0x126: { // 退出組隊
					// 00 00 00 72
					break;
				}
				case 0x129: { // 隊伍邀請
					int inviteplayerid = pr.readLong();
					break;
				}
				case 0x130: { // 準備
					break;
				}
				case 0x136: { // 開始副本
					// 86 1C
					c->sendPacket(PartyPacket::PartyDungeonEnterAck().getPacket());
					
					c->sendPacket(PartyPacket::PartyDungeonEnterData(30000, c->getPlayer()).getPacket());

					break;
				}
				case 0x13F: {// 更改組隊公開不公開
					bool public = pr.readByte() == 1;
					break;
				}
				case 0x14B: {// 更改組隊最大人數
					int maxplayer = pr.readByte();
					break;
				}
				case 0x148: { // 更改組隊獲得道具方式
					pr.readByte(); // 1 = 隨機 2 = 各自
					break;
				}
				case 0x151: {// 快速隊伍
					// 00 00 75 30 00 01
					int dungeonid = pr.readInt();
					int unk1 = pr.readByte();
					int unk2 = pr.readByte();
					break;
				}
			    
				case 0x15D: { // 隱私 0=拒絕 1=接受
					bool friendinvite = pr.readbool();
					bool guildinvite = pr.readbool();
					bool partyinvite = pr.readbool();
					bool trade = pr.readbool();
					// Send 0x15E
					break;
				}

				// field
/*				case 0x371: // 舊版好像沒這個
					FieldHandler::moveToField(pr, c);
					break;*/

				case 0x240: { // 添加好友
					std::wstring inviteplayername = pr.readElsWString();
					std::wstring message = pr.readElsWString();
					break;
				}
				case 0x26D: // 進入商城
					// 00 00 00 01
					c->sendPacket(FieldPacket::CashShopInfo().getPacket());
					break;
				case 0x26F: // 進入商城後會發的
					//00 00 00 10 00 00 00 01
					c->sendPacket(FieldPacket::CashShopUnk().getPacket());
					break;

				// inventory
				case 0xEB/*0x10A*/:
					InventoryHandler::moveItemReq(pr, c);
					break;
/*				case 0x110:
					InventoryHandler::discardItemReq(pr, c);
					break;
				case 0x562:
					InventoryHandler::openShopReq(pr, c);
					break;
				case 0x3D0:
					InventoryHandler::upgradeEquipEnq(c);
					break;
				case 0x1CF:
					InventoryHandler::upgradeEquipReq(pr, c);
					break;
				case 0x211:
					InventoryHandler::enchantEquipReq(pr, c);
					break;
				case 0x193:
					InventoryHandler::repairEquipReq(pr, c);
					break;*/
				case 0xD9/*0xF0*/:
					InventoryHandler::buyItemReq(pr, c);
					break;
				
				case 0xFD:{ // 使用快捷鍵道具
					int invpos = pr.readByte(); // 00 第一格
					break;
				}

				// 技能
				case 0x10A/*0x127*/:
					SkillHandler::distributeSP(pr, c);
					break;
				case 0x10C/*0x129*/:
					SkillHandler::modifySkillSlots(pr, c);
					break;

				case 0x91: { // 角色死亡
					pr.readInt(); // 00 18 FC 44
					int playerid1 = pr.readLong();
					int playerid2 = pr.readLong();
					float second = 3;
//					PVPRoom* room = World::getPVPRoom(4);
					c->sendPacket(PVPPacket::pvpDeadAck(second).getPacket());
/*					for (auto p : *room->getPlayers()) {
						World::getClient(p.second->getIP())->first->sendPacket(PVPPacket::pvpDead(playerid1, playerid2).getPacket());
					}*/
					break;
				}
				case 0x94: { // 角色復活?
//					PVPRoom* room = World::getPVPRoom(4);
					c->sendPacket(PVPPacket::pvpRebirthAck().getPacket());
/*					for (auto p : *room->getPlayers()) {
						World::getClient(p.second->getIP())->first->sendPacket(PVPPacket::pvpRebirth(c->getPlayer()->getPlayerID()).getPacket());
					}*/
					break;
				}
				case 0x153: { // 復活
					// 00 
					// 00 46 1c 3c 00 0e d3 dd 座標?
					// 00 00 00 00 00 00 00 02 角色ID
					pr.readbool();
					pr.readLong();
					int playerid = pr.readLong();
					c->sendPacket(DungeonPacket::RebirthAck().getPacket());
					break;
				}
				case 0x97: { // 放召喚獸
					DungeonHandler::Summon(pr, c);
					// SEND 0x98 int 0x99 (跟上面一樣)
					break;
				}
				case 0x194: {// 放BUFF
					// 法力光環
					// 00 00 00 00 00 00 00 01 (playerid)
					// 01 (bool)
					// 02 (byte) 光環種類
					// 3E 4C CC D0 (float) 等於0.2 施法時間?
					// 42 34 00 00 (float) 等於45 持續時間
					int playerid = pr.readLong();
					bool unk = pr.readbool();
				    int type = pr.readByte();
					float time = pr.readFloat();
					float duration = pr.readFloat();

					c->sendPacket(DungeonPacket::BuffAck().getPacket());

//					c->sendPacket(DungeonPacket::Buff(playerid, unk, type, time, duration).getPacket());
					// 下面也要發給其他玩家
					PVPRoom* room = World::getPVPRoom(4);
					for (auto p : *room->getPlayers()) {
						World::getClient(p.second->getIP())->first->sendPacket(DungeonPacket::Buff(playerid, unk, type, time, duration).getPacket());
					}
					// SEND 0x195 int 0x196 long(playerid) bool byte float float (跟上面一樣)
					break;
				}

				// world 科保地圖移動
/*				case 0x507:
					ChannelHandler::useCoBoExpress(pr, c);
					break;*/

				// 說話
				case 0x6E/*0x88*/:
					MessageHandler::generalChatReq(pr, c);
					break;
				
				// 其他
				case 0xD3: // shit went wrong
					ChannelHandler::packetError(pr, c);
					break;

				// 在商店街 角色移動
				case 0x108:
					// byte byte float float float byte bool
					break;

				// 在村莊 角色移動
				case 0x222/*0x238*/: // send 0x23B
//					ChannelHandler::mapMovement(pr, c);
					break;

				default:
					std::printf("unhandled: 0x%x\n", header);
			}

		}

		void handlePacket(PacketReader pr, GameConnection* c) {
			pr.skipBytes(24);
			unsigned short header = pr.readShort();
			pr.setLength(pr.readInt()); // 數據包長度
			pr.readByte(); // bool 是否壓縮數據包

			std::printf("TCP port 9301 RECV: 0x%x\n", header);
			if (header < 0x900 && header != 0x400) {
				for (int i = 0; i < pr.getLength(); i++) {
					std::printf("%x ", static_cast<int>(pr.getPacket()[i + 31]));
				}
				std::printf("\n");
			}
			std::cout << std::endl;

			switch (header) {
				case 0x223:
					ChannelHandler::gameConnStartReq(pr, c);
					break;

//				default:
//					std::printf("unhandled: 0x%x\n", header);
			}

		}

	}

}