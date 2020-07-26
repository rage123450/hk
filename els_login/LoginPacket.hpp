#pragma once
#include "PacketBuilder.hpp"

namespace els {

	namespace LoginPacket {

		PacketBuilder serverAck(unsigned long long hmac_key, unsigned long long des_key);
		PacketBuilder loginAck();
		PacketBuilder sendSerial(std::string serial, std::string lastLogin, std::string user, std::string serial2, int accid);
		PacketBuilder sendSerial(std::string serial, std::string user, int accid);
		PacketBuilder serverListAck();
		PacketBuilder channelListAck();
		PacketBuilder serverList();
		PacketBuilder channelList();
		PacketBuilder terminateConnectionAck();

	}


}