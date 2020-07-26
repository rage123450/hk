#pragma once

namespace els {

	class Crypto {

		public:
			Crypto();
			void setKey(unsigned long long key);
			void setHMAC(unsigned long long hmac);
			unsigned char* Encrypt(unsigned char* encrypted, unsigned char* data, int size, int sequence);
			unsigned char* Decrypt(unsigned char* decrypted, unsigned char* iv, unsigned char* data, int size);
			unsigned char* generateChecksum(unsigned char* checksum, unsigned char* data, int size);

		private:
			unsigned char Key[8];
			unsigned char HMAC[8];

	};

}