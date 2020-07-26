#pragma once
#include <string>

namespace els {

	class PacketReader {

		public:
			PacketReader(unsigned char* packet, int length);
			~PacketReader();
			unsigned char readByte();
			unsigned short readShort();
			unsigned int readInt();
			unsigned long long readLong();
			std::string readElsString();
			void skipBytes(int length);
			unsigned char* getPacket();
			int getLength();

		private:
			int m_pos;
			int m_length;
			unsigned char* m_packet;

	};

}