#pragma once
#include "Connection.hpp"
#include "PacketReader.hpp"

namespace els {

	namespace DungeonHandler {

		void tutorialReq(PacketReader pr, Connection* conn);
		void tutorialStartReq(Connection* conn);
		void dungeonLoadReq(PacketReader pr, Connection* conn);
		void dungeonSpawnMonsterReq(Connection* conn);
		void unknown_0xBA(Connection* conn);
		void unknown_0xBE(PacketReader pr, Connection* conn);
		void unknown_0xC1(PacketReader pr, Connection* conn);
		void unknown_0xC4(PacketReader pr, Connection* conn);
		void unknown_0xB1(PacketReader pr, Connection* conn);

		void dungeonListReq(PacketReader pr, Connection* conn);
		void dungeonEntryReq(PacketReader pr, Connection* conn);
		void dungeonStageClear(Connection* conn);

		void Summon(PacketReader pr, Connection* conn);

	}


}