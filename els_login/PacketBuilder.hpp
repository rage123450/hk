#pragma once

#include "boost/shared_array.hpp"
#include <string>
#include <vector>

namespace els {

	class PacketBuilder {

		public:
			PacketBuilder();
			static void writeSize(unsigned char* buffer, int size);
			static void writeSeq(unsigned char* buffer, int seq);
			static void writeIV(unsigned char* buffer, unsigned char iv);
			static void writeChecksum(unsigned char* buffer, unsigned char* checksum);
			PacketBuilder& writeByte(unsigned char value);
			PacketBuilder& writeByte(int value);
			PacketBuilder& writeShort(unsigned short value);
			PacketBuilder& writeInt(unsigned int value);
			PacketBuilder& writeLong(unsigned long long value);
			PacketBuilder& writeBytes(unsigned char* value, int length);
			PacketBuilder& writeString(std::string value);
			PacketBuilder& writeElsString(std::string value);
			PacketBuilder& writeElsWString(std::wstring value);
			PacketBuilder& writeHexString(std::string value);
			PacketBuilder& writePadding();
			PacketBuilder& writeHeaderByte(unsigned char value);
			PacketBuilder& writeHeaderShort(unsigned short value);
			PacketBuilder& writeHeaderInt(unsigned int value);
			PacketBuilder& writeHeaderLong(unsigned long long value);
			PacketBuilder& writeHeader(unsigned short opcode, unsigned int length);
			PacketBuilder& finishPacket(unsigned short opcode);
			std::string toString();
			int getLength();
			std::vector<unsigned char> getPacket();
			
		private:
			std::vector<unsigned char> m_packet;
			std::vector<unsigned char> m_body;

	};

}