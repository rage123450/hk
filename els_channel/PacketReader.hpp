#pragma once
#include <string>

namespace els {

	class PacketReader {

		public:
			PacketReader(unsigned char* packet, int length);
			~PacketReader();
			bool readbool();
			unsigned char readByte();
			unsigned short readShort();
			unsigned int readInt();
			unsigned long long readLong();
			float readFloat();
			std::string readElsString();
			std::wstring readElsWString();
			void skipBytes(int length);
			unsigned char* getPacket();
			int getLength();
			void setLength(int length);

		private:
			int m_pos;
			int m_length;
			unsigned char* m_packet;

	};

}