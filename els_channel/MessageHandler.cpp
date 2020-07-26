#include "MessageHandler.hpp"
#include "MessagePacket.hpp"
#include "World.hpp"
#include <iostream>   
#include <string>
//#include <iomanip>

namespace els {

	namespace MessageHandler {

		void generalChatReq(PacketReader pr, Connection* conn) {
			int channel = pr.readByte(); // 0 = ¥þÅé 1 = ¶¤¥î
			pr.readByte(); // 00
			long unk = pr.readLong(); // FF FF FF FF FF FF FF FF
			pr.readInt(); // 00 00 00 00
			std::wstring message = pr.readElsWString();

			conn->sendPacket(MessagePacket::generalChatAck().getPacket());

//			conn->sendPacket(MessagePacket::generalChat(conn->getPlayer()->getPlayerID(), unk, message).getPacket());
			auto players = World::getMap(conn->getPlayer()->getMap())->getPlayers();
			for (auto p : *players) {
				World::getClient(p.second->getIP())->first->sendPacket(MessagePacket::generalChat(conn->getPlayer()->getPlayerID(), channel, unk, message).getPacket());
			}

		}


	}



}