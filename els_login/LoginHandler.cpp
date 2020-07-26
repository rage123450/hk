#pragma warning(disable: 4251)
#include "LoginHandler.hpp"
#include "LoginPacket.hpp"
#include "Connection.hpp"
#include "Database.hpp"
#include "Random.hpp"
#include "Time.hpp"
#include "dll.h"
#include "md5.h"
#include <string>
#include <iostream>

namespace els {

	namespace LoginHandler {

		void userLogin(PacketReader pr, Connection* conn) {
			
			pr.skipBytes(1); // 01
			std::string username = pr.readElsString();
			std::string password = pr.readElsString();
//			pr.skipBytes(8);
			int status = 0/*pr.readByte()*/;

/*			if (status == 1) {
				std::cout << "2nd/3rd CONNECTION" << std::endl;
				std::cout << username << std::endl;
				checkSerial(pr, conn, username, password);
				return;
			}*/

			sql::ResultSet* res;

			res = Database::query("SELECT salt FROM accounts WHERE name = '" + username + "'; ");
			res->next();

			if (res->rowsCount() == 1) {

				std::cout << "ACCOUNT FOUND" << std::endl;
				std::string salt = res->getString("salt");
				std::string enc_password;
				//password = password + salt;

				/*
				CryptoPP::MD5 md5;
				std::string digest;
				CryptoPP::StringSource(password, true, new CryptoPP::HashFilter(md5, new CryptoPP::HexEncoder(new CryptoPP::StringSink(digest))));
				std::cout << digest << std::endl;
				*/

				res = Database::query("SELECT * FROM accounts WHERE name = '" + username + "' && password = '" + /*digest*/ password + "'; ");

				if (res->rowsCount() == 1) {

					res->next();

					std::cout << "PASSWORD OK" << std::endl;
					if (!res->getBoolean("banned")) {

						std::string serial = Random::numeric(9);
						
						conn->setAccName(username);
						conn->setAccID(res->getInt("id"));
						std::string endpoint = conn->getSocket().remote_endpoint().address().to_string();
						std::cout << "NOT BANNED" << std::endl;
						Database::query("UPDATE accounts SET migration_serial = '" + serial + "', ip = '" + endpoint  + "' WHERE name = '" + username + "';");
						std::cout << "Sending packet to..." << conn->getSocket().remote_endpoint() << std::endl;
//						conn->sendPacket(LoginPacket::loginAck().getPacket());
						conn->sendPacket(LoginPacket::sendSerial(serial, Time::now(), username, "006cafbba014868be7686e72fd5879ee", conn->getAccID()).getPacket());
//						std::cout << "Sent" << std::endl;
					
					} else {
						
						std::cout << "BANNED" << std::endl;
						conn->getSocket().close();

					}

				} else {
					
					std::cout << "INVALID INFO" << std::endl;
					// handle invalid info entered

				}

			}

		}

		void checkSerial(PacketReader pr, Connection* conn, std::string user, std::string serial) {
			
			sql::ResultSet* res;
			std::cout << user << " " << serial << std::endl;
			// adding ip check would be good here
			res = Database::query("SELECT * FROM accounts WHERE name = '" + user + "' && migration_serial = '" + serial  + "'; ");
			res->next();

			if (res->rowsCount() != 1) {
				// hacking
				std::cout << "FAIL CHECK" << std::endl;
				conn->getSocket().close();
			} else {
				std::cout << "2nd/3rd FOUND" << std::endl;
				
				conn->setAccID(res->getInt("id"));

				std::string newSerial = Random::numeric(9);

//				conn->sendPacket(LoginPacket::loginAck().getPacket());
				conn->sendPacket(LoginPacket::sendSerial(newSerial, user, conn->getAccID()).getPacket());
				
				Database::query("UPDATE accounts SET migration_serial = '" + newSerial + "' WHERE name = '" + user + "';");
			
			}

		}

		void serverListReq(Connection* conn) {

			conn->sendPacket(LoginPacket::serverListAck().getPacket());
			conn->sendPacket(LoginPacket::serverList().getPacket());

		}

		void channelListReq(Connection* conn) {

			conn->sendPacket(LoginPacket::channelListAck().getPacket());
			conn->sendPacket(LoginPacket::channelList().getPacket());

		}

		void terminateConnection(Connection* conn) {

			conn->sendPacket(LoginPacket::terminateConnectionAck().getPacket());

		}
		
	}

}