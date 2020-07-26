#include "PVPHandler.hpp"
#include "PVPPacket.hpp"
#include "PVP.hpp"
#include "World.hpp"
#include <thread>

namespace els {

	namespace PVPHandler {
		
		void pvpQueueReq(PacketReader pr, Connection* conn) {
			
			int mode = pr.readByte(); // 1 = 1v1, 2 = 2v2, 3 = 3v3

			conn->sendPacket(PVPPacket::pvpQueueAck().getPacket()); // 0x343
			conn->sendPacket(PVPPacket::pvpQueue().getPacket()); // 0x344

			if (World::getPVPQueue(mode-1).size() != 0) {
				Player* opponent = World::getPVPQueue(mode-1).begin()->second;
				World::getPVPQueue(mode-1).erase(opponent->getPlayerID());
				// assume 1v1
				PVP match;
				match.addPlayer(1, conn->getPlayer());
				match.addPlayer(2, opponent);
				int id = World::addPVPMatch(mode-1, match);

				conn->getPlayer()->setCurPVPMatch(id);
				opponent->setCurPVPMatch(id);

				conn->sendPacket(PVPPacket::pvpStartReq().getPacket()); // 0x349
				World::getClient(opponent->getIP())->first->sendPacket(PVPPacket::pvpStartReq().getPacket()); // 0x349
			}
			else World::pvpQueue(mode-1, conn->getPlayer());
			
		}

		void pvpQueueCancel(Connection* conn) {
			
			World::pvpUnqueue(1, conn->getPlayer()->getPlayerID());
			World::pvpUnqueue(2, conn->getPlayer()->getPlayerID());
			World::pvpUnqueue(3, conn->getPlayer()->getPlayerID());

		}

		void pvpApproveReq(PacketReader pr, Connection* conn) {

			if (pr.readByte() == 1) {
				PVP* match = World::getPVPMatch(conn->getPlayer()->getCurPVPMatch());
				match->approvePVP();
				if (match->getApprovals() == 2) {
					for (int i = 3; i > 0; i--) {
						for (int j = 0; j < 1; j++) { // assume 1v1
							World::getClient(match->getTeam(1)[j]->getIP())->first->sendPacket(PVPPacket::pvpCountdown(i).getPacket());
							World::getClient(match->getTeam(2)[j]->getIP())->first->sendPacket(PVPPacket::pvpCountdown(i).getPacket());
							std::this_thread::sleep_for(std::chrono::seconds(1));
						}
					}
				}
			}

		}

		void pvpLoadReq(PacketReader pr, Connection* conn) {
			
				int load = pr.readInt();
				PVP* match = World::getPVPMatch(conn->getPlayer()->getCurPVPMatch());

				for (int j = 0; j < 1; j++) { // assume 1v1
					World::getClient(match->getTeam(1)[j]->getIP())->first->sendPacket(PVPPacket::pvpLoad(conn->getPlayer(), load).getPacket());
					World::getClient(match->getTeam(2)[j]->getIP())->first->sendPacket(PVPPacket::pvpLoad(conn->getPlayer(), load).getPacket());
				}
				conn->sendPacket(PVPPacket::pvpLoadAck().getPacket());

				if (load == 100) {
					match->doneLoad();
				}
				if (match->getLoaded() == 2) { // again assume 1v1
					conn->sendPacket(PVPPacket::pvpLoadDone().getPacket());
				}

		}


	}



}