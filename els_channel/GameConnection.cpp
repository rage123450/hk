#include "GameConnection.hpp"
#include "ChannelServerHandler.hpp"
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "PacketBuilder.hpp"
#include "PacketReader.hpp"
#include "Config.hpp"
#include <cstring>

namespace els {

	boost::asio::ip::tcp::socket& GameConnection::getSocket() {
		return tcpSocket;
	}

	void GameConnection::start() {
//		std::cout << "Connection established with " << tcpSocket.remote_endpoint() << " on port 9301" << std::endl;
		startReadHeader();

	}

	void GameConnection::startReadHeader() {
		m_recvBuffer.reset(new unsigned char[2]);
		boost::asio::async_read(tcpSocket, boost::asio::buffer(m_recvBuffer.get(), 2), boost::bind(&GameConnection::startReadBody, shared_from_this(), boost::asio::placeholders::error));
	}

	void GameConnection::startReadBody(const boost::system::error_code& error) {
//		printf("Length: %x %x\n", m_recvBuffer[0], m_recvBuffer[1]);
		if (!error) {
			unsigned short packetLen = ((m_recvBuffer[1] << 8) | m_recvBuffer[0]) - 2;
//			std::cout << packetLen << std::endl;
			m_recvBuffer.reset(new unsigned char[packetLen]);
			boost::asio::async_read(tcpSocket, boost::asio::buffer(m_recvBuffer.get(), packetLen), boost::bind(&GameConnection::handleRead, shared_from_this(), packetLen, boost::asio::placeholders::error));
		}
		else {
			std::cout << error.message() << std::endl;
			std::cout << "Error Occurred at startReadBody" << std::endl;
		}
	}

	void GameConnection::sendPacket(std::vector<unsigned char> packet) {
		freopen("ChannelOut.txt", "a", stdout);

//		std::printf("TCP port 9301 SEND \n");

		for (int i = 0; i < packet.size() - 33; i++) {
			std::printf("%x ", packet[i + 33]);
		}
		std::printf("\n");

		m_sequence++;
		boost::asio::async_write(tcpSocket, boost::asio::buffer(&packet[0], packet.size()), boost::bind(&GameConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}

	void GameConnection::sendPacket(unsigned char* packet, int size) {
		m_sequence++;
		boost::asio::async_write(tcpSocket, boost::asio::buffer(packet, size), boost::bind(&GameConnection::handleWrite, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
	}

	void GameConnection::handleWrite(const boost::system::error_code&, size_t) {

	}

	void GameConnection::handleRead(int size, const boost::system::error_code& error) {
		if (error) {
			std::cout << error.message() << std::endl;
		}

		PacketReader pr(m_recvBuffer.get(), size - 2);
		ChannelServerHandler::handlePacket(pr, this);

		if (!error) {
			startReadHeader();
		}
	}

	std::string GameConnection::getAccName() {
		return m_accName;
	}

	int GameConnection::getAccID() {
		return m_accID;
	}

	void GameConnection::setAccName(std::string name) {
		m_accName = name;
	}

	void GameConnection::setAccID(int id) {
		m_accID = id;
	}

	void GameConnection::setPlayer(Player* player) {
		m_player = player;
	}

	Player* GameConnection::getPlayer() {
		return m_player;
	}

}