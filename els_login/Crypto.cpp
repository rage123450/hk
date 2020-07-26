#include "Crypto.hpp"
#include "PacketBuilder.hpp"
#include "dll.h"
#include "md5.h"
#include <cstring>
#include <cstdio>
#include <random>
#include <functional>

namespace els {

	Crypto::Crypto() {
		Key[0] = 0xC7; 
		Key[1] = 0xD8;
		Key[2] = 0xC4;
		Key[3] = 0xBF;
		Key[4] = 0xB5;
		Key[5] = 0xE9;
		Key[6] = 0xC0;
		Key[7] = 0xFD;
		HMAC[0] = 0xC0;
		HMAC[1] = 0xD3; 
		HMAC[2] = 0xBD; 
		HMAC[3] = 0xC3;
		HMAC[4] = 0xB7;
		HMAC[5] = 0xCE;
		HMAC[6] = 0xB8;
		HMAC[7] = 0xB8;
	}

	void Crypto::setKey(unsigned long long key) {
		Key[0] = (key >> 56) & 0xFF;
		Key[1] = (key >> 48) & 0xFF;
		Key[2] = (key >> 40) & 0xFF;
		Key[3] = (key >> 32) & 0xFF;
		Key[4] = (key >> 24) & 0xFF;
		Key[5] = (key >> 16) & 0xFF;
		Key[6] = (key >> 8) & 0xFF;
		Key[7] = (key & 0xff);
	}

	void Crypto::setHMAC(unsigned long long hmac) {
		HMAC[0] = (hmac >> 56) & 0xFF;
		HMAC[1] = (hmac >> 48) & 0xFF;
		HMAC[2] = (hmac >> 40) & 0xFF;
		HMAC[3] = (hmac >> 32) & 0xFF;
		HMAC[4] = (hmac >> 24) & 0xFF;
		HMAC[5] = (hmac >> 16) & 0xFF;
		HMAC[6] = (hmac >> 8) & 0xFF;
		HMAC[7] = (hmac & 0xff);
	}

	unsigned char* Crypto::Encrypt(unsigned char* encrypted, unsigned char* data, int size, int sequence) {

		std::uniform_int_distribution<unsigned int> IVDistribution(65, 90);
		std::default_random_engine IVGenerator;
		auto generateIV = std::bind(IVDistribution, IVGenerator);
		unsigned char iv_b = generateIV();
		unsigned char iv[8];
		memset(iv, iv_b, sizeof(iv));
		CryptoPP::CBC_Mode<CryptoPP::DES>::Encryption Encryptor(Key, CryptoPP::DES::DEFAULT_KEYLENGTH, iv);
		Encryptor.ProcessData(encrypted+16, data, size);
		PacketBuilder::writeSize(encrypted, size+26);
		PacketBuilder::writeSeq(encrypted+4, sequence);
		PacketBuilder::writeIV(encrypted+8, iv_b);
		unsigned char* serverAck_hmac = (unsigned char*)malloc((int)10);
		generateChecksum(serverAck_hmac, encrypted + 2, size + 14);
		PacketBuilder::writeChecksum(encrypted + size + 16, serverAck_hmac);
		std::cout << std::endl;

		return encrypted;

	}

	unsigned char* Crypto::Decrypt(unsigned char* decrypted, unsigned char* iv, unsigned char* data, int size) {

		CryptoPP::CBC_Mode<CryptoPP::DES>::Decryption Decryptor(Key, CryptoPP::DES::DEFAULT_KEYLENGTH, iv);
		Decryptor.ProcessData(decrypted, data, size);
		return decrypted;

	}

	unsigned char* Crypto::generateChecksum(unsigned char* checksum, unsigned char* data, int size) {

		CryptoPP::HMAC<CryptoPP::MD5> cHMAC;
		cHMAC.SetKey(HMAC, 8);
		cHMAC.CalculateTruncatedDigest(checksum, 10, data, size);
		return checksum;

	}
}