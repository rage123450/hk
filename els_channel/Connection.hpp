#pragma once

#include "boost/asio.hpp"
#include "boost/enable_shared_from_this.hpp"
#include "boost/shared_array.hpp"
#include "Crypto.hpp"
#include "Player.hpp"

namespace els {

	class Connection : public boost::enable_shared_from_this<Connection> {
		
		private:
			Player m_player;
			int m_sequence;
			std::string m_accName;
			int m_accID;
			int m_port;
			std::string m_lastLogin;
			Crypto m_crypto;
			boost::shared_array<unsigned char> m_recvBuffer;
			boost::asio::ip::tcp::socket tcpSocket;
		public:
			Connection(boost::asio::io_service& iosvc) : tcpSocket(iosvc) { m_sequence = 1; }
			boost::asio::ip::tcp::socket& getSocket();
			void start();
			void startReadHeader();
			void startReadBody(const boost::system::error_code& error);
			void handleRead(int size, const boost::system::error_code& error);
			void sendPacket(unsigned char* packet, int size);
			void sendPacket(std::vector<unsigned char> packet);
			void handleWrite(const boost::system::error_code& error, size_t bytes_transferred);
			std::string getAccName();
			int getAccID();
			void setAccName(std::string name);
			void setAccID(int id);
			void setPlayer(Player* player);
			Player* getPlayer();
			std::string getLastLogin();
			void Connection::setLastLogin(std::string lastlogin);
	};
	
}