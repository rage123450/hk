#include "Connection.hpp"
#include "ChannelServerHandler.hpp"
#include "AuthPacket.hpp"
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "PacketBuilder.hpp"
#include "PacketReader.hpp"
#include "Config.hpp"
#include "World.hpp"
#include <random>
#include <climits>
#include <cstring>

namespace els {

	boost::asio::ip::tcp::socket& Connection::getSocket() {
		return tcpSocket;
	}

	void Connection::start() {

		/*std::default_random_engine ULLGenerator;
		std::uniform_int_distribution<unsigned int> keyDistribution(1, UINT_MAX);
		auto generateKey = std::bind(keyDistribution, ULLGenerator);
		unsigned long long hmac_key = generateKey();
		unsigned long long key = generateKey() + generateKey();
		*/
		unsigned long long hmac_key = 3890346735;
		unsigned long long key = 4081080916;
		std::cout << hmac_key << std::endl;
		std::cout << key << std::endl;
		sendPacket(AuthPacket::serverAck(hmac_key, key).getPacket());
		m_crypto.setHMAC(hmac_key); // set new hmac
		m_crypto.setKey(key); // set new key
		m_sequence++;
		std::cout << "Connection established with " << tcpSocket.remote_endpoint() << " on port 9300" << std::endl;

		startReadHeader();
		
	}

	void Connection::startReadHeader() {
		m_recvBuffer.reset(new unsigned char[2]);
		boost::asio::async_read(tcpSocket, boost::asio::buffer(m_recvBuffer.get(), 2), boost::bind(&Connection::startReadBody, shared_from_this(), boost::asio::placeholders::error));
	}

	void Connection::startReadBody(const boost::system::error_code& error) {
		//printf("Length: %x %x\n", m_recvBuffer[0], m_recvBuffer[1]);
		if (!error) {
			unsigned short packetLen = ((m_recvBuffer[1] << 8) | m_recvBuffer[0]) - 2;
//			std::cout << packetLen << std::endl;
			m_recvBuffer.reset(new unsigned char[packetLen]);
			boost::asio::async_read(tcpSocket, boost::asio::buffer(m_recvBuffer.get(), packetLen), boost::bind(&Connection::handleRead, shared_from_this(), packetLen, boost::asio::placeholders::error));
		}
		else {
			std::cout << error.message() << std::endl;
			std::cout << "Error Occurred at startReadBody" << std::endl;

			if (getPlayer() != nullptr) {
				World::getMap(getPlayer()->getMap())->removePlayer(getPlayer()->getPlayerID());
			}
		}
	}

	void Connection::sendPacket(std::vector<unsigned char> packet) {
		freopen("ChannelOut.txt", "a", stdout);

//		std::printf("TCP port 9300 SEND \n");

		for (int i = 0; i < packet.size() - 39; i++) {
			std::printf("%x ", packet[i + 39]);
		}
		std::printf("\n");

		unsigned char* encrypted = (unsigned char*)malloc((int)packet.size() + 26);
		m_crypto.Encrypt(encrypted, &packet[0], packet.size(), m_sequence);
		m_sequence++;
		boost::asio::async_write(tcpSocket, boost::asio::buffer(encrypted, packet.size() + 26), boost::bind(&Connection::handleWrite, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}

/*	void Connection::sendPacket(unsigned char* packet, int size) {
		unsigned char* encrypted = (unsigned char*)malloc(size + 26);
		m_crypto.Encrypt(encrypted, packet, size, m_sequence);
		m_sequence++;
		boost::asio::async_write(tcpSocket, boost::asio::buffer(encrypted, size + 26), boost::bind(&Connection::handleWrite, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}*/

	void Connection::handleWrite(const boost::system::error_code&, size_t) {

	}

	void Connection::handleRead(int size, const boost::system::error_code& error) {
		if (error) {
			std::cout << error.message() << std::endl;
		}
		unsigned char iv[8];
		memset(iv, m_recvBuffer[6], sizeof(iv));
		unsigned char* decrypted = (unsigned char*)malloc(size - 24);
		m_crypto.Decrypt(decrypted, iv, m_recvBuffer.get() + 14, size - 24);

		PacketReader pr(decrypted, size - 24);
		ChannelServerHandler::handlePacket(pr, this);

		if (!error) {
			startReadHeader();
		}
	}

	std::string Connection::getAccName() {
		return m_accName;
	}

	int Connection::getAccID() {
		return m_accID;
	}

	void Connection::setAccName(std::string name) {
		m_accName = name;
	}

	void Connection::setAccID(int id) {
		m_accID = id;
	}

	void Connection::setPlayer(Player* player) {
		m_player = *player;
	}

	Player* Connection::getPlayer() {
		return &m_player;
	}

	std::string Connection::getLastLogin() {
		return m_lastLogin;
	}

	void Connection::setLastLogin(std::string lastlogin) {
		m_lastLogin = lastlogin;
	}

}