#include "PacketBuilder.hpp"
#include "Connection.hpp"
#include "PVPRoom.hpp"

#pragma once

namespace els {

	namespace PVPPacket {

		PacketBuilder pvpLobbyChannelInfo();
		PacketBuilder pvpLobbyAck();
		PacketBuilder pvpLobbyRoomInfo();

		PacketBuilder pvpLobbyCreateRoomAck(PVPRoom room);
		PacketBuilder pvpLobbyEnterRoomAck(PVPRoom* room);
		PacketBuilder pvpLobbyEnterRoom(Player* player);

		PacketBuilder pvpRoomExitAck();
		PacketBuilder pvpRoomExit(int playerid);
		PacketBuilder pvpRoomUnkAck();
		PacketBuilder pvpRoomUnk(int playerid, bool unk);
		PacketBuilder pvpRoomChangeTeamAck();
		PacketBuilder pvpRoomChangeTeam(int playerid, int team);
		PacketBuilder pvpRoomReadyAck();
		PacketBuilder pvpRoomReady(int playerid, bool ready);
		PacketBuilder pvpRoomChangeMapAck();
		PacketBuilder pvpRoomChangeMap(int WORLD_ID);
		PacketBuilder pvpRoomCloseSlotAck();
		PacketBuilder pvpRoomCloseSlot(int slot);
		PacketBuilder pvpRoomChangeSecondAck();
		PacketBuilder pvpRoomChangeSecond(float second);
		PacketBuilder pvpRoomChangeKillAck();
		PacketBuilder pvpRoomChangeKill(int kill);

		PacketBuilder pvpDeadAck(float second);
		PacketBuilder pvpDead(int playerid1, int playerid2);
		PacketBuilder pvpRebirthAck();
		PacketBuilder pvpRebirth(int playerid);
		PacketBuilder pvpTimeAck();
		PacketBuilder pvpTime(int time);

		PacketBuilder pvpQueueAck();
		PacketBuilder pvpQueue();
		PacketBuilder pvpStartReq();
		PacketBuilder pvpCountdown(int count);
		PacketBuilder pvpLoadAck();
		PacketBuilder pvpLoad(Player* player, int load);
		PacketBuilder pvpLoadDone();
		//PacketBuilder pvpEnter(Player* player);
		//PacketBuilder unknown_0x38D();

	}


}