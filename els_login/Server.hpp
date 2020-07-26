#pragma once

#include "boost/asio.hpp"
#include "boost/shared_ptr.hpp"
#include "Connection.hpp"

namespace els {
	
	typedef boost::shared_ptr<Connection> sessionPtr;
	
	class Server : boost::noncopyable {
		public:
			boost::asio::io_service iosvc;
			boost::asio::ip::tcp::acceptor acceptor;
			Server(short port) : acceptor(iosvc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {}
			~Server() {};
			void startAccept();
			void handleAccept(sessionPtr session, const boost::system::error_code& error);
			void init();
	};

}