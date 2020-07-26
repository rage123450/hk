#include "Server.hpp"
#include "Connection.hpp"
#include "boost/asio.hpp"
#include "boost/bind.hpp"

namespace els {

	void Server::startAccept() {
		sessionPtr session(new Connection(iosvc));
		acceptor.async_accept(session->getSocket(), boost::bind(&Server::handleAccept, this, session, boost::asio::placeholders::error));
	}

	void Server::handleAccept(sessionPtr session, const boost::system::error_code& error) {
		if (!error) {
			session->start(); // pass session into here
			startAccept();
		}
	}

	void Server::init() {
		startAccept(); 
		iosvc.run();
	}

}