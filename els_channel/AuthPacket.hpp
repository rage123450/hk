#pragma once
#include "PacketBuilder.hpp"

namespace els {

	namespace AuthPacket {

		PacketBuilder serverAck(unsigned long long hmac_key, unsigned long long des_key);
		PacketBuilder loginAck();
		PacketBuilder sendSerial(std::string serial, std::string lastLogin, std::string user, std::string serial2, int accid);
		PacketBuilder sendSerial(std::string serial, std::string user, int accid);
		PacketBuilder serverListAck();
		PacketBuilder channelListAck();
		PacketBuilder serverList();
		PacketBuilder channelList();
		PacketBuilder versionAck();
		PacketBuilder levelLimit();
		PacketBuilder unknown_0x53A();
		PacketBuilder unknown1_0x509();
		PacketBuilder unknown2_0x50A();
		PacketBuilder channelLoginAck(std::string user, std::string logindate, std::string serial, std::string creationdate, std::string lastlogin, std::string url, std::string remoteip, int accid);
		PacketBuilder unknown3_0x1A4();
		PacketBuilder unknown5_0x39A();
		PacketBuilder unknown7_0x34();
		PacketBuilder dateAck(std::string date);
		PacketBuilder channelIPAck();
		PacketBuilder channelApproveAck(std::string user, std::string remoteip);
		PacketBuilder unknown8_0x327();
		PacketBuilder itemData();
		PacketBuilder charList(std::string user, std::string remoteip);
		PacketBuilder unknown10_0x48F(int accid);
		PacketBuilder checkCharNameAck(std::string name, bool isOK);
		PacketBuilder unknown11_0x535();
		PacketBuilder createCharAck(int id, std::wstring name, int unitType, int hp, int atk, int matk, int def, int mdef);
		PacketBuilder terminateConnectionAck();


	}

}