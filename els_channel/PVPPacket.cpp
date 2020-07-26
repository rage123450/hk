#include "PVPPacket.hpp"
#include "Time.hpp"
#include "PVP.hpp"
#include "PVPRoom.hpp"
#include "Config.hpp"
#include "World.hpp"
#include "PacketReader.hpp"

namespace els {

	namespace PVPPacket {

		PacketBuilder pvpLobbyChannelInfo() {

			PacketBuilder pb;
			int 頻道數量 = 2;
			pb
				.writeInt(0)

				.writeInt(/*5*/3) // 預設頻道ID

				.writeInt(頻道數量)

				// for

				.writeInt(0)
				.writeInt(100000000)
				.writeInt(5) // 頻道ID
				.writeByte(11) // PVP_CHANNEL_CLASS.PCC_PLAY 歡樂練習

				.writeInt(0)
				.writeInt(100000000)
				.writeInt(3) // 頻道ID
				.writeByte(9) // PVP_CHANNEL_CLASS.PCC_FREE 自由對戰

				.finishPacket(0x35);
			return pb;

		}

		PacketBuilder pvpLobbyAck() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x37);
			return pb;

		}

		PacketBuilder pvpLobbyRoomInfo() {
//			int 房間size = 1;
			PacketBuilder pb;
			pb
				.writeInt(0)

				.writeInt(1) // 現在頁數
				.writeInt(1) // 最大頁數

				.writeInt(World::getPVPRoomSize());

				for (auto r : *World::getPVPRooms()) {
					r.second.writeRoomInfoData(pb);
				}

//				.writeInt(房間size);
/*			pb
				.writeByte(1)
				.writeLong(4) // RoomID
				.writeInt(0)
				.writeElsWString(L"快告訴老實說熊熊")
				.writeByte(0)
				.writebool(true)
				.writebool(false)
				.writeElsString("")
				.writeByte(8) // 房間最大人數
				.writeByte(1) // 房間人數
				.writeElsString(Config::serverIP)
				.writeShort(9101)
				.writeByte(1)
				.writebool(true)
				.writeInt(-1)
				.writeByte(4)
				.writebool(true)
				.writeFloat(800) // 秒數
				.writeShort(-1)
				.writeShort(-1) // WORLD_ID
				.writeByte(0)
				.writeInt(0)
				.writeByte(0)
				.writeByte(0)
				.writeLong(0)
				;*/
            pb
				.finishPacket(0x3C);
			return pb;

		}

		PacketBuilder pvpLobbyCreateRoomAck(PVPRoom room) {
			PacketBuilder pb;
			pb
				.writeInt(0);

			    room.writeRoomInfoData(pb);
			    room.writeRoomPlayersData(pb);

			pb
				.finishPacket(0x42);

			return pb;
		}

		PacketBuilder pvpLobbyEnterRoomAck(PVPRoom* room) {
			PacketBuilder pb;
			pb
				.writeInt(0);

			    room->writeRoomInfoData(pb);
			    room->writeRoomPlayersData(pb);

			pb
				.finishPacket(0x46);

			return pb;
		}

		PacketBuilder pvpLobbyEnterRoom(Player* player) {
			PacketBuilder pb;

		     	player->writeData(pb);

			pb
				.finishPacket(0x47);

			return pb;
		}

		PacketBuilder pvpRoomExitAck() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x4E);

			return pb;
		}

		PacketBuilder pvpRoomExit(int playerid) {
			PVPRoom* room = World::getPVPRoom(4);

			PacketBuilder pb;
			pb
				.writeByte(1/*0*/) // 不知道
				.writeLong(playerid)
				.writeInt(playerid); // 或許不是

			auto *players = room->getPlayers();
			for (auto p : *players) {
				p.second->writeData(pb);
			}

			for (int i = 0; i < 8; i++) {
				bool empty = true;
				for (auto p : *players) {
					if (p.second->getIndex() == i) {
						empty = false;
						break;
					}
				}
				if (empty) {
					room->writeEmptyPlayerData(pb, i, 1);
					empty = false;
				}
			}

			pb
				.writeInt(0)

				.finishPacket(0x4F);

			return pb;
		}

		PacketBuilder pvpRoomChangeTeamAck() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x5A);

			return pb;
		}

		PacketBuilder pvpRoomChangeTeam(int playerid, int team) {

			PacketBuilder pb;
			pb
				.writeLong(playerid)
				.writeByte(team) // 0 = 紅隊 // 1 = 藍隊
				.writeByte(5) // 位置 index

				.finishPacket(0x5B);

			return pb;
		}

		PacketBuilder pvpRoomReadyAck() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x5D);

			return pb;
		}

		PacketBuilder pvpRoomReady(int playerid, bool ready) {

			PacketBuilder pb;
			pb
				.writeLong(playerid)
				.writebool(ready)

				.finishPacket(0x5E);

			return pb;
		}

		PacketBuilder pvpRoomChangeMapAck() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x63);

			return pb;
		}

		PacketBuilder pvpRoomChangeMap(int WORLD_ID) {

			PacketBuilder pb;
			pb
				.writeShort(WORLD_ID)
				.finishPacket(0x64);

			return pb;
		}

		PacketBuilder pvpRoomChangeSecondAck() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x69);

			return pb;
		}

		PacketBuilder pvpRoomChangeSecond(float second) {

			PacketBuilder pb;
			pb
				.writeFloat(second)
				.finishPacket(0x6A);

			return pb;
		}

		PacketBuilder pvpRoomChangeKillAck() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x6C);

			return pb;
		}

		PacketBuilder pvpRoomChangeKill(int kill) {

			PacketBuilder pb;
			pb
				.writeInt(kill)
				.finishPacket(0x6D);

			return pb;
		}

		PacketBuilder pvpRoomUnkAck() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x72);

			return pb;
		}

		PacketBuilder pvpRoomUnk(int charid, bool unk) {

			PacketBuilder pb;
			pb
				.writeLong(charid)
				.writebool(unk)
				.finishPacket(0x73);

			return pb;
		}

		PacketBuilder pvpDeadAck(float second) {

			PacketBuilder pb;
			pb
				.writeFloat(second)
				.writeInt(0/*10000*/)
				.writeShort(0)
				.writeShort(0)

				.finishPacket(0x92);

			return pb;
		}

		PacketBuilder pvpDead(int playerid1, int playerid2) {

			PacketBuilder pb;
			pb
				.writeInt(10000)
				.writeLong(playerid1)
				.writeLong(playerid2)
				.writeLong(Time::timestamp_now())

				.finishPacket(0x93);

			return pb;
		}

		PacketBuilder pvpRebirthAck() {

			PacketBuilder pb;
			pb.finishPacket(0x95);

			return pb;
		}

		PacketBuilder pvpRebirth(int playerid) {

			PacketBuilder pb;
			pb
				.writeLong(playerid)

				.finishPacket(0x96);

			return pb;
		}

		PacketBuilder pvpTimeAck() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x29F);

			return pb;
		}

		PacketBuilder pvpTime(int time) {

			PacketBuilder pb;
			pb
				.writeInt(0)

				.writeInt(0)
				.writeInt(0)
				.writebool(false)
				.writeInt(0x41200000) // 秒數? float

				.finishPacket(0x2A0);

			return pb;
		}


		PacketBuilder pvpQueueAck() {
			
			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x343);

			return pb;
		}

		PacketBuilder pvpQueue() {

			PacketBuilder pb;
			pb
				.writeInt(90) // estimated waiting time. 1min 30s. 2000s is unk
				.finishPacket(0x344);

			return pb;
		}

		PacketBuilder pvpStartReq() {

			PacketBuilder pb;
			pb
				.writeLong(0x105)
				.finishPacket(0x349);

			return pb;

		}

		PacketBuilder pvpCountdown(int count) {

			PacketBuilder pb;
			pb
				.writeLong(0)
				.writeByte(count)
				.writeByte(0)
				.finishPacket(0x38E);

			return pb;
		}

		PacketBuilder pvpLoadAck() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x96);

			return pb;
		}

		PacketBuilder pvpLoad(Player* player, int load) {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writeInt(player->getPlayerID())
				.writeInt(load)
				.finishPacket(0x97);

			return pb;

		}

		PacketBuilder pvpLoadDone() {
			
			PacketBuilder pb;
			pb.finishPacket(0x98);
			return pb;

		}


	}



}