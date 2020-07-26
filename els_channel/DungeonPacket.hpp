#pragma once
#include "PacketReader.hpp"
#include "PacketBuilder.hpp"
#include "Player.hpp"

namespace els {

	namespace DungeonPacket {

		PacketBuilder tutorialAck(std::string serial, int dID, Player* player);
		PacketBuilder tutorialStartAck();
		PacketBuilder tutorialStartAck2(Player* player);
		PacketBuilder dungeonLoadAck();
		PacketBuilder dungeonLoad(Player* player, int load);
		PacketBuilder unknown_0x3A0(Player* player);
		PacketBuilder dungeonLoadDone();
		PacketBuilder unknown_0x35A();
		PacketBuilder dungeonEnter(Player* player);
		PacketBuilder SpawnMonsterAck();
		PacketBuilder SpawnMonster();
		PacketBuilder unknown_0xBB();
		PacketBuilder unknown_0xBC(Player* player);
		PacketBuilder unknown_0xBD();
		PacketBuilder unknown_0xBF();
		PacketBuilder unknown_0xC0(int a1);
		PacketBuilder unknown_0xC2();
		PacketBuilder unknown_0xC3(int a1);
		PacketBuilder unknown_0xC5();
		PacketBuilder unknown_0xC6(int a1);
		PacketBuilder TimeUpdate(float second);
		PacketBuilder unknown_0xB2();
		PacketBuilder unknown_0xB3(int n1, int n2, int n3, int n4);

		PacketBuilder dungeonList(int reg, int dungeonID);
		PacketBuilder dungeonEntryAck();
		PacketBuilder dungeonStartCountdown(int toStart);
		PacketBuilder dungeonPartyData(Player* player, int dungeonID);
		PacketBuilder dungeonStageClearAck();
		PacketBuilder dungeonDropItem();
		PacketBuilder BuffAck();
		PacketBuilder Buff(int playerid, bool unk, int type, float time, float duration);
		PacketBuilder SummonAck();
		PacketBuilder Summon(PacketReader* pr);
		PacketBuilder SummonAck();
		PacketBuilder RebirthAck();

	}

}