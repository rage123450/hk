#include "PacketReader.hpp"
#include <iostream>

namespace els {

	PacketReader::PacketReader(unsigned char* packet, int length) : 
		m_packet(packet), m_length(length), m_pos(0) { }

	PacketReader::~PacketReader() { }

	bool PacketReader::readbool() {

		m_pos++;
		return (m_packet[m_pos-1] == 1);
	}

	unsigned char PacketReader::readByte() {

		m_pos++;
		return m_packet[m_pos-1];

	}

	unsigned short PacketReader::readShort() {

		m_pos += 2;
		return (m_packet[m_pos-2] << 8) | m_packet[m_pos-1];

	}

	unsigned int PacketReader::readInt() {

		m_pos += 4;
		return (m_packet[m_pos - 4] << 24) | (m_packet[m_pos - 3] << 16) | (m_packet[m_pos - 2] << 8) | m_packet[m_pos - 1];

	}

	unsigned long long PacketReader::readLong() {

		m_pos += 8;
		return (m_packet[m_pos - 8] << 56) | (m_packet[m_pos - 7] << 48) | (m_packet[m_pos - 6] << 40) | (m_packet[m_pos - 5] << 32) | (m_packet[m_pos - 4] << 24) | (m_packet[m_pos - 3] << 16) | (m_packet[m_pos - 2] << 8) | m_packet[m_pos - 1];

	}

	float PacketReader::readFloat() {

		m_pos += 4;
		unsigned int a = (m_packet[m_pos - 4] << 24) | (m_packet[m_pos - 3] << 16) | (m_packet[m_pos - 2] << 8) | m_packet[m_pos - 1];

		float f;
		memcpy(&f, &a, sizeof(f));

		return f;
	}

	std::string PacketReader::readElsString() {

		int length = readInt();
//		std::cout << "LENGTH: " << length << std::endl;
		std::string str;
		int i;
		for (i = m_pos; i < m_pos + length; i += 2) {
			str += static_cast<char>(m_packet[i]);
		}
		m_pos += length;

		return str;
	}

	std::wstring PacketReader::readElsWString() {

		int length = readInt();
//		std::cout << "LENGTH: " << length << std::endl;
		std::wstring str;
		int i;
		for (i = m_pos; i < m_pos + length; i += 2) {
			str += static_cast<wchar_t>((m_packet[i] | m_packet[i + 1] << 8));
		}
		m_pos += length;

		return str;
	}

	void PacketReader::skipBytes(int length) {
		m_pos += length;
	}

	unsigned char* PacketReader::getPacket() {
		return m_packet;
	}

	int PacketReader::getLength() {
		return m_length;
	}

	void PacketReader::setLength(int length) {
		m_length = length;
	}

}