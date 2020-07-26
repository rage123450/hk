#include "PacketBuilder.hpp"

namespace els {

	PacketBuilder::PacketBuilder() {
		
	}

	void PacketBuilder::writeSize(unsigned char* buffer, int size) {
		buffer[0] = size & 0xff;
		buffer[1] = (size >> 8) & 0xFF;
		buffer[2] = 0x0;
		buffer[3] = 0x0;
	}

	void PacketBuilder::writeSeq(unsigned char* buffer, int seq) {
		buffer[0] = seq & 0xff;
		buffer[1] = (seq >> 8) & 0xFF;
		buffer[2] = (seq >> 16) & 0xFF;
		buffer[3] = (seq >> 24) & 0xFF;
	}

	void PacketBuilder::writeIV(unsigned char* buffer, unsigned char iv) {
		int i;
		for (i = 0; i < 8; i++) {
			buffer[i] = iv;
		}
	}

	void PacketBuilder::writeChecksum(unsigned char* buffer, unsigned char* checksum) {
		int i;
		for (i = 0; i < 10; i++) {
			buffer[i] = checksum[i];
		}
	}

	PacketBuilder& PacketBuilder::writeByte(unsigned char value) {
		m_body.push_back(value);
		return *this;
	}

	PacketBuilder& PacketBuilder::writeByte(int value) {
		m_body.push_back((char)value);
		return *this;
	}

	PacketBuilder& PacketBuilder::writebool(bool b) {
		m_body.push_back(b ? 1 : 0);
		return *this;
	}

	PacketBuilder& PacketBuilder::writeZeroBytes(int amount) {
		for (int i = 0; i < amount; i++) {
			m_body.push_back(0);
		}
		return *this;
	}

	PacketBuilder& PacketBuilder::writeShort(unsigned short value) {
		m_body.push_back((value >> 8) & 0xFF);
		m_body.push_back(value & 0xff);
		return *this;
	}

	PacketBuilder& PacketBuilder::writeUShort(unsigned short value) {
		m_body.push_back(value & 0xff);
		m_body.push_back((value >> 8) & 0xFF);
		return *this;
	}

	PacketBuilder& PacketBuilder::writeInt(unsigned int value) {
		m_body.push_back((value >> 24) & 0xFF);
		m_body.push_back((value >> 16) & 0xFF);
		m_body.push_back((value >> 8) & 0xFF);
		m_body.push_back(value & 0xff);
		return *this;
	}

	PacketBuilder& PacketBuilder::writeLong(unsigned long long value) {
		m_body.push_back((value >> 56) & 0xFF);
		m_body.push_back((value >> 48) & 0xFF);
		m_body.push_back((value >> 40) & 0xFF);
		m_body.push_back((value >> 32) & 0xFF);
		m_body.push_back((value >> 24) & 0xFF);
		m_body.push_back((value >> 16) & 0xFF);
		m_body.push_back((value >> 8) & 0xFF);
		m_body.push_back(value & 0xff);
		return *this;
	}

	PacketBuilder& PacketBuilder::writeFloat(float value) {
		unsigned int f = *(reinterpret_cast<int*>(&value));
		m_body.push_back((f >> 24) & 0xFF);
		m_body.push_back((f >> 16) & 0xFF);
		m_body.push_back((f >> 8) & 0xFF);
		m_body.push_back(f & 0xff);
		return *this;
	}

	PacketBuilder& PacketBuilder::writeBytes(unsigned char* value, int length) {

		int i;
		for (i = 0; i < length; i++) {
			m_body.push_back(value[i]);
		}

		return *this;
	}

	PacketBuilder& PacketBuilder::writeElsString(std::string value) {
		int i;
		writeInt(value.length() * 2);
		for (i = 0; i < (int) value.length(); i++) {
			m_body.push_back(static_cast<int>(value[i]));
			m_body.push_back(0);
		}

		return *this;
	}

	PacketBuilder& PacketBuilder::writeElsWString(std::wstring value) {
		int i;
		writeInt(value.length() * 2);
		for (i = 0; i < (int) value.length(); i++) {
			m_body.push_back(value[i]);
			m_body.push_back(value[i] >> 8);
		}

		return *this;
	}

	PacketBuilder& PacketBuilder::writePadding() {

		int length = 8 - ((m_packet.size() + m_body.size() + 1) % 8);
		int i;
		for (i = 1; i <= length; i++) {
			m_body.push_back(i);
		}
		m_body.push_back(length);

		return *this;
	}

	PacketBuilder& PacketBuilder::writeHeaderByte(unsigned char value) {
		m_packet.push_back(value);
		return *this;
	}

	PacketBuilder& PacketBuilder::writeHeaderShort(unsigned short value) {
		m_packet.push_back((value >> 8) & 0xFF);
		m_packet.push_back(value & 0xff);
		return *this;
	}

	PacketBuilder& PacketBuilder::writeHeaderInt(unsigned int value) {
		m_packet.push_back((value >> 24) & 0xFF);
		m_packet.push_back((value >> 16) & 0xFF);
		m_packet.push_back((value >> 8) & 0xFF);
		m_packet.push_back(value & 0xff);
		return *this;
	}

	PacketBuilder& PacketBuilder::writeHeaderLong(unsigned long long value) {
		m_packet.push_back((value >> 56) & 0xFF);
		m_packet.push_back((value >> 48) & 0xFF);
		m_packet.push_back((value >> 40) & 0xFF);
		m_packet.push_back((value >> 32) & 0xFF);
		m_packet.push_back((value >> 24) & 0xFF);
		m_packet.push_back((value >> 16) & 0xFF);
		m_packet.push_back((value >> 8) & 0xFF);
		m_packet.push_back(value & 0xff);
		return *this;
	}

	PacketBuilder& PacketBuilder::writeHeader(unsigned short opcode, unsigned int length) {

		std::printf("TCP port 9300 SEND: 0x%x\n", opcode);

		writeHeaderByte(0);
		writeHeaderShort(1);
		writeHeaderByte(1);

		writeHeaderInt(1); // size -> long

		writeHeaderByte(0x40);
		writeHeaderShort(0);
		writeHeaderByte(0x8B);
		writeHeaderByte(0xDF);
		writeHeaderByte(0x4F);
		writeHeaderByte(0xBD);
		writeHeaderByte(0xF6);

		writeHeaderLong(-1);
		writeHeaderLong(-1);

		writeHeaderShort(opcode); // opcode
		writeHeaderInt(length);	// 長度
		if (length > 0) {
			writeHeaderByte(0); // 是否壓縮數據包
		}

		return *this;
	}

	PacketBuilder& PacketBuilder::writeGameHeader(unsigned short opcode, unsigned int length) {

		std::printf("TCP port 9301 SEND: 0x%x\n", opcode);

		// //Hours wasted not seeing the incorrect header length: 22 (fixed now) - Jonathan
		unsigned int l = length + 33;
		writeHeaderByte((unsigned char)(l & 0xFF));
		writeHeaderByte((unsigned char)((l >> 8) & 0xFF));
		writeHeaderLong(0);
		writeHeaderLong(-1);
		writeHeaderLong(-1);
		writeHeaderShort(opcode); // opcode
		writeHeaderInt(length);	// 長度
		if (length > 0) {
			writeHeaderByte(0); // 是否壓縮數據包
		}

		return *this;
	}

	PacketBuilder& PacketBuilder::finishPacket(unsigned short opcode) {

		writeHeader(opcode, m_body.size());
		writePadding();
		m_packet.insert(m_packet.end(), m_body.begin(), m_body.end());

		return *this;
	}

	PacketBuilder& PacketBuilder::finishGamePacket(unsigned short opcode) {

		writeGameHeader(opcode, m_body.size());
		m_packet.insert(m_packet.end(), m_body.begin(), m_body.end());

		return *this;
	}
	/*
	PacketBuilder& PacketBuilder::writeHexString(std::string value) {
		

	}
	*/

	std::vector<unsigned char> PacketBuilder::getPacket() {
		return m_packet;
	}
}