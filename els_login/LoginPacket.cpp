#include "LoginPacket.hpp"
#include "PacketBuilder.hpp"
#include "Config.hpp"

namespace els {

	namespace LoginPacket {

		PacketBuilder serverAck(unsigned long long hmac_key, unsigned long long des_key) {
			std::cout << "SEND: SERVERACK" << std::endl;

			// SERVER_ACK
			// This packet is an exception

			PacketBuilder pb;
			pb

				.writeByte(0x0D)
				.writeByte(0x5B)
				.writeInt(8) // key
				.writeLong(hmac_key)
				.writeInt(8) // key
				.writeLong(des_key)
				//				.writeInt(1)
				//				.writeInt(0)
				//				.writeInt(0)

				//				.writeByte(1)
				//				.writeByte(2)
				//				.writeByte(2)

				.finishPacket(0x01);

/*				.writeHeaderInt(0)
				.writeHeaderInt(0) // size -> long
				.writeHeaderLong(-1)
				.writeHeaderLong(-1)

				.writeHeaderShort(0x01) // opcode
				.writeHeaderInt(38) // 计沮
				.writeHeaderByte(0) // 琌溃罽计沮

				.writeHeaderByte(0x0D)
				.writeHeaderByte(0x5B)
				.writeHeaderInt(8) // key
				.writeHeaderLong(hmac_key)
				.writeHeaderInt(8) // key
				.writeHeaderLong(des_key)
				.writeHeaderInt(1)
				.writeHeaderLong(0)
				.writeHeaderByte(1)
				.writeHeaderByte(2)
				.writeHeaderByte(2)*/
				;
				
			return pb;
		}

		PacketBuilder loginAck() {

			std::cout << "SEND: 0x2C3" << std::endl;

			PacketBuilder pb;
			pb
				.writeShort(0)
				.writeByte(0x61)
				.writeByte(0x99)
				.writeInt(0)
				.finishPacket(0x2C3/*0x2D9*/);
				
			return pb;
		}

		PacketBuilder sendSerial(std::string serial, std::string lastLogin, std::string user, std::string serial2, int accid) {

			std::cout << "SEND: 0x26C A" << std::endl;

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writeElsString(user)
				.writeLong(accid)
				.writeElsString(serial)
//				.writeElsString(serial2)
//				.writeElsString(lastLogin)
				.finishPacket(0x26C);

			return pb;
		}

		PacketBuilder sendSerial(std::string serial, std::string user, int accid) {

			std::cout << "SEND: 0x26C B" << std::endl;

			PacketBuilder pb;
			pb
				.writeInt(0)
				.writeElsString(user)
				.writeLong(accid)
				.writeElsString(serial)
				.finishPacket(0x26C);

			return pb;

		}

		PacketBuilder serverListAck() {

			std::cout << "SEND: 0x4F5" << std::endl;

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x4F5);

			return pb;

		}

		PacketBuilder channelListAck() {

			std::cout << "SEND: 0x2A" << std::endl;

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x2A);

			return pb;

		}

		PacketBuilder serverList() {

			std::cout << "SEND: 0x4F6" << std::endl;

			PacketBuilder pb;
			pb
				.writeInt(1)
				.writeLong(0)
				.writeInt(0)
				.writeElsString(Config::serverName)
				.writeElsString(Config::serverIP)
				.writeInt(0x24B824B9)
				.writeByte(1)
				.finishPacket(0x4F6);

			return pb;

		}

		PacketBuilder channelList() {

			std::cout << "SEND: 0x2B" << std::endl;

			PacketBuilder pb;
			pb
				.writeInt(0)

				.writeInt(Config::channels);

			int i;
			for (i = 1; i <= Config::channels; i++) {
				pb
					.writeInt(i)
					.writeInt(i * 3)
					.writeInt(i)
					.writeElsWString(Config::channelName[i - 1])
					.writeInt(0)
					.writeElsString(Config::channelIP[i - 1])
					.writeShort(9300) // port
					.writeShort(9301) // port
					.writeInt(1500) // 繵笵程计
					.writeInt(0) // 繵笵瞷计
					.writeInt(0)
					.writeInt(0)
					;
			}

			pb.finishPacket(0x2B);

			return pb;

		}

		PacketBuilder terminateConnectionAck() {

			std::cout << "SEND: 0x22F" << std::endl;
			
			PacketBuilder pb;
			pb.finishPacket(0x22F);

			return pb;

		}

	}

}