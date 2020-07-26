#include "FieldHandler.hpp"
#include "FieldPacket.hpp"
#include "MapDataProvider.hpp"

namespace els {

	namespace FieldHandler {

		void moveToField(PacketReader pr, Connection* conn) {
			
			int fieldID = pr.readInt();

			World::getMap(conn->getPlayer()->getMap())->removePlayer(conn->getPlayer()->getPlayerID());
			World::getMap(fieldID)->addPlayer(conn->getPlayer());
			conn->getPlayer()->setMap(fieldID);

			conn->sendPacket(FieldPacket::playerList(conn->getPlayer()).getPacket());

		}

	}



}