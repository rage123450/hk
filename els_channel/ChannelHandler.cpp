#include "ChannelHandler.hpp"
#include "ChannelPacket.hpp"
#include "CharacterPacket.hpp"
#include "FieldPacket.hpp"
#include "World.hpp"
#include <iomanip>

namespace els {

	namespace ChannelHandler {

		void unknown_0x232(PacketReader pr, Connection* conn) {

			int mapid = pr.readInt();
			std::cout << "MAP ID: " << mapid << std::endl;
			if (conn->getPlayer() != nullptr && conn->getPlayer()->getMap() != mapid) {
				World::getMap(conn->getPlayer()->getMap())->removePlayer(conn->getPlayer()->getPlayerID());
				World::getMap(mapid)->addPlayer(conn->getPlayer());
				conn->getPlayer()->setMap(mapid);

//				conn->sendPacket(FieldPacket::playerList(conn->getPlayer()).getPacket());
			}

//			conn->sendPacket(ChannelPacket::unknown_0x2EB().getPacket());
//			conn->sendPacket(ChannelPacket::unknown_0x102(0x30E58).getPacket());
//			conn->sendPacket(ChannelPacket::unknown_0x102(0x123AE).getPacket());
//			conn->sendPacket(ChannelPacket::unknown_0x429().getPacket());
//			conn->sendPacket(ChannelPacket::unknown_0x1B9().getPacket());
			conn->sendPacket(ChannelPacket::unknown_0x233().getPacket());
//			conn->sendPacket(CharacterPacket::unknown_0x3A0().getPacket());

		}

		void unknown_0x234(Connection* conn) {

//			conn->sendPacket(ChannelPacket::unknown_0x23F().getPacket());
			conn->sendPacket(ChannelPacket::unknown_0x235().getPacket());

			//conn->sendPacket(CharacterPacket::unknown_0x39F().getPacket());

		}

		void packetError(PacketReader pr, Connection* conn) {

			for (int i = 0; i < pr.getLength(); i++) {
				std::cout << std::setbase(16) << std::setw(2) << std::setfill('0') << static_cast<int>(pr.getPacket()[i]) << " ";
			}

		}

		void useCoBoExpress(PacketReader pr, Connection* conn) {

			int map = pr.readInt();
			// deduct ed if using this is not free.
			conn->getPlayer()->setMap(map);
			conn->sendPacket(ChannelPacket::useCoBoExpressAck(conn->getPlayer()).getPacket());

		}

		void gameConnStartReq(PacketReader pr, GameConnection* conn) {
			
			// don't really need to read the packet
			Player* player = World::getClient(conn->getSocket().remote_endpoint().address().to_string())->first->getPlayer();
			conn->setPlayer(player);

			// do checks
			auto players = World::getMap(player->getMap())->getPlayers();

			// send everyone's data to me
			// and send my stuff to everyone
			std::cout << "MAP: " << player->getMap() << std::endl;
			std::cout << "SEARCH: " << std::endl;
			std::cout << "SIZE: " << players->size() << std::endl;
			std::cout << "ADDR2: " << players << std::endl;
			for (auto p : *players) {
				std::cout << "角色ID: " << p.first /*<< " 角色名字: " << p.second->getName()*/ << std::endl;
				if (p.first != player->getPlayerID()) {
					std::cout << "其他角色 ID: " << p.second->getPlayerID() /*<< " 其他角色名字: " << p.second->getName()*/ << std::endl;
					conn->sendPacket(ChannelPacket::mapPlayerData(p.second).getPacket());
					World::getClient(p.second->getIP())->second->sendPacket(ChannelPacket::mapPlayerData(player).getPacket());
				}
			}
			
		}

		void mapMovement(PacketReader pr, Connection* conn) {
			
			Player* player = conn->getPlayer();

/*			std::cout << "LEN: " << pr.getLength() << std::endl;
			for (int i = 0; i < pr.getLength(); i++) {
				std::cout << std::hex << static_cast<int>(pr.getPacket()[i + 39]) << " " << std::flush;
			}
			std::cout << std::endl;*/

//			float x = pr.readFloat()/* *reinterpret_cast<float*>(pr->readInt())*/;
//			float y = pr.readFloat()/* *reinterpret_cast<float*>(pr->readInt())*/;
//			float z = pr.readFloat()/* *reinterpret_cast<float*>(pr->readInt())*/;

			player->setX(pr.readFloat());
			player->setY(pr.readFloat());
			player->setZ(pr.readFloat());

//			std::cout << "X: " << x << " Y: " << y << " Z: " << z << std::endl;

			// broadcast the movement
			for (auto others : *World::getMap(player->getMap())->getPlayers()) {
				if (others.second->getPlayerID() != player->getPlayerID()) {
					World::getClient(others.second->getIP())->second->sendPacket(ChannelPacket::mapMovementData(player, &pr).getPacket());
				}
			}

		}

	}

}