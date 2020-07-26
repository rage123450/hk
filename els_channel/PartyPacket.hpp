#include "PacketBuilder.hpp"
#include "Connection.hpp"

#pragma once

namespace els {

	namespace PartyPacket {

		PacketBuilder PartyCreateAck(long unk1, std::wstring 隊伍名稱, int dungeonid, int 難度, int unk2, int 最大人數, bool 公開,
			int unk3, bool 不知道, int unk4, int unk5, Player* chr);

		PacketBuilder PartyDungeonEnterAck();
		PacketBuilder PartyDungeonEnterData(int dungeonid, Player* player);

	}


}