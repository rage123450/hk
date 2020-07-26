#include "MessagePacket.hpp"

namespace els {

	namespace MessagePacket {

		PacketBuilder generalChatAck() {

			PacketBuilder pb;
			pb
				.writeInt(0)
				.finishPacket(0x6F);

			return pb;

		}

		PacketBuilder generalChat(int playerid, int channel, long unk, std::wstring message) {

			PacketBuilder pb;
	        pb

				.writeByte(channel)
				.writeLong(playerid)
				.writeInt(0)
				.writeInt(0)
				.writeLong(unk) // FF FF FF FF FF FF FF FF
				.writeByte(0)
				.writeElsWString(message)

				.finishPacket(0x70);

			return pb;

		}

	}


}