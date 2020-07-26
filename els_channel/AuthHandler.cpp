#pragma warning(disable: 4251)
#include "AuthHandler.hpp"
#include "AuthPacket.hpp"
#include "Connection.hpp"
#include "Config.hpp"
#include "Constants.hpp"
#include "Database.hpp"
#include "Converter.hpp"
#include "Random.hpp"
#include "Time.hpp"
#include "dll.h"
#include "md5.h"
#include <string>
#include <iostream>

namespace els {

	namespace AuthHandler {

		void userLogin(PacketReader pr, Connection* conn) {

			pr.skipBytes(1);
			std::string username = pr.readElsString();
			std::string password = pr.readElsString();
			pr.skipBytes(8);
			int status = pr.readByte();

			if (status == 1) {
				std::cout << "2nd/3rd CONNECTION" << std::endl;
				checkSerial(pr, conn, username, password);
				return;
			}

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
						conn->setLastLogin(res->getString("last_login"));

						std::string endpoint = conn->getSocket().remote_endpoint().address().to_string();
						std::cout << "NOT BANNED" << std::endl;
						Database::query("UPDATE accounts SET migration_serial = ' " + serial + "', ip = '" + endpoint + "' WHERE name = '" + username + "';");
						std::cout << "Sending packet to..." << conn->getSocket().remote_endpoint() << std::endl;
//						conn->sendPacket(AuthPacket::loginAck().getPacket());
						conn->sendPacket(AuthPacket::sendSerial(serial, Time::now(), username, "006cafbba014868be7686e72fd5879ee", conn->getAccID()).getPacket());
						std::cout << "Sent" << std::endl;

					}
					else {

						std::cout << "BANNED" << std::endl;
						conn->getSocket().close();

					}

				}
				else {

					std::cout << "INVALID INFO" << std::endl;
					// handle invalid info entered

				}

			}

		}

		void checkSerial(PacketReader pr, Connection* conn, std::string user, std::string serial) {

			sql::ResultSet* res;
			// adding ip check would be good here
			res = Database::query("SELECT * FROM accounts WHERE name = '" + user + "' && migration_serial = '" + serial + "'; ");

			if (res->rowsCount() != 1 && false) {
				// hacking
				std::cout << "FAIL CHECK" << std::endl;
				conn->getSocket().close();
			}
			else {

				std::string newSerial = Random::numeric(9);

//				conn->sendPacket(AuthPacket::loginAck().getPacket());
				conn->sendPacket(AuthPacket::sendSerial(newSerial, user, conn->getAccID()).getPacket());

				std::cout << "ACCID: " << conn->getAccID() << std::endl;

				Database::query("UPDATE accounts SET migration_serial = '" + newSerial + "' WHERE name = '" + user + "';");

			}

		}

		void serverListReq(Connection* conn) {

			conn->sendPacket(AuthPacket::serverListAck().getPacket());
			conn->sendPacket(AuthPacket::serverList().getPacket());

		}

		void channelListReq(Connection* conn) {

			//conn->sendPacket(AuthPacket::channelListAck().getPacket());
			conn->sendPacket(AuthPacket::channelList().getPacket());

		}

		void verCheckReq(PacketReader pr, Connection* conn) {

			std::string version = pr.readElsString();

			if (version != Config::version) {
				// wrong version. No entry!
				conn->getSocket().close();

			} else {
//				conn->sendPacket(AuthPacket::levelLimit().getPacket());
//				conn->sendPacket(AuthPacket::unknown1_0x509().getPacket());
//				conn->sendPacket(AuthPacket::unknown2_0x50A().getPacket());
//				conn->sendPacket(AuthPacket::unknown_0x53A().getPacket());
				conn->sendPacket(AuthPacket::versionAck().getPacket());
			}


		}

		void channelLoginReq(PacketReader pr, Connection* conn) {

/*			for (int i = 0; i < pr.getLength() + 39; i++) {
				std::cout << static_cast<int>(pr.getPacket()[i]) << " ";
			}*/

			pr.skipBytes(1);
			std::string user = pr.readElsString();
			std::string serial = pr.readElsString();

			std::cout << "USER: " << user << ", SERIAL: " << serial << std::endl;

			sql::ResultSet* res;
			// adding ip check would be good here
			res = Database::query("SELECT * FROM accounts WHERE name = '" + user + "' && migration_serial = '" + serial + "'; ");

			if (res->rowsCount() != 1 && false) {
				// hacking again
				std::cout << "FAIL CHECK" << std::endl;
				conn->getSocket().close();
			}
			else {

				res->next();

				conn->setAccName(user);
				conn->setAccID(res->getInt("id"));
				conn->setLastLogin(res->getString("last_login"));

				std::string newSerial = Random::numeric(9);

				Database::query("UPDATE accounts SET migration_serial = '" + newSerial + "' WHERE name = '" + user + "';");
				conn->sendPacket(AuthPacket::channelLoginAck(user, Time::now(), newSerial, res->getString("creation_date"), res->getString("last_login"), "", conn->getSocket().remote_endpoint().address().to_string(), conn->getAccID()).getPacket());
				conn->sendPacket(AuthPacket::unknown3_0x1A4().getPacket());

//				conn->sendPacket(AuthPacket::unknown5_0x39A().getPacket());
			}

		}

		void unknown_0x33(Connection* conn) {

			conn->sendPacket(AuthPacket::unknown7_0x34().getPacket());

		}

		void dateReq(Connection* conn) {

			conn->sendPacket(AuthPacket::dateAck(Time::now()).getPacket());

		}

		void channelIPReq(Connection* conn) {

			conn->sendPacket(AuthPacket::channelIPAck().getPacket());

		}

		void charlistReq(Connection* conn) {

			conn->sendPacket(AuthPacket::charList(conn->getAccName(), conn->getSocket().remote_endpoint().address().to_string()).getPacket());

		}

		void channelApproveReq(Connection* conn) {

			conn->sendPacket(AuthPacket::channelApproveAck(conn->getAccName(), conn->getSocket().remote_endpoint().address().to_string()).getPacket());
			conn->sendPacket(AuthPacket::unknown8_0x327().getPacket());
			conn->sendPacket(AuthPacket::itemData().getPacket());
			conn->sendPacket(AuthPacket::charList(conn->getAccName(), conn->getSocket().remote_endpoint().address().to_string()).getPacket());

		}

		void unknown_0x48D(Connection* conn) {

			conn->sendPacket(AuthPacket::unknown10_0x48F(conn->getAccID()).getPacket());

		}

		void checkCharNameReq(PacketReader pr, Connection* conn) {

			pr.skipBytes(4);
			std::string name = pr.readElsString();

			// ~.~ character name checks go here
			// check if - name is ok and - name is available

			conn->sendPacket(AuthPacket::checkCharNameAck(name, true).getPacket());
		}

		void createCharReq(PacketReader pr, Connection* conn) {

			std::wstring name = pr.readElsWString();
			int charUT = pr.readInt();

			// stats

			int level = 1;
			int exp = 0;
			int hp = 1;
			int attack = 0;
			int mattack = 0;
			int def = 0;
			int mdef = 0;
			int ed = 100;
			int unittype = charUT;
			int unitclass = charUT;
			
			// equipment

			// order: shirt, pants, gloves, shoes, weapon
			int normal[5];
			int decorative[5];

			// skills

			int skill1 = 0;
			int skill2 = 0;


			switch ((Constants::unitType) charUT) {

				case Constants::unitType::UN_ELSWORD:
					hp = 11250;
					attack = 360;
					mattack = 296;
					def = 80;
					mdef = 66;

					normal[0] = 111094;
					normal[1] = 111095;
					normal[2] = 111096;
					normal[3] = 111097;
					normal[4] = 131641;
					decorative[0] = 130098;
					decorative[1] = 130099;
					decorative[2] = 130100;
					decorative[3] = 130101;
					decorative[4] = 130112;
					
					skill1 = 1001;
					skill2 = 1205;
					break;
				case Constants::unitType::UN_AISHA:
					hp = 9500;
					attack = 288;
					mattack = 392;
					def = 68;
					mdef = 86;

					normal[0] = 111098;
					normal[1] = 111099;
					normal[2] = 111100;
					normal[3] = 111101;
					normal[4] = 131642;
					decorative[0] = 130019;
					decorative[1] = 130020;
					decorative[2] = 130021;
					decorative[3] = 130022;
					decorative[4] = 130018;

					skill1 = 2001;
					skill2 = 2200;
					break;
				case Constants::unitType::UN_RENA:
					hp = 10000;
					attack = 312;
					mattack = 336;
					def = 74;
					mdef = 84;

					normal[0] = 111102;
					normal[1] = 111103;
					normal[2] = 111104;
					normal[3] = 111105;
					normal[4] = 131643;
					decorative[0] = 130103;
					decorative[1] = 130104;
					decorative[2] = 130105;
					decorative[3] = 130106;
					decorative[4] = 130102;

					skill1 = 3001;
					skill2 = 3202;
					break;
				case Constants::unitType::UN_RAVEN:
					hp = 11250;
					attack = 344;
					mattack = 304;
					def = 82;
					mdef = 66;

					normal[0] = 111106;
					normal[1] = 111107;
					normal[2] = 111108;
					normal[3] = 111109;
					normal[4] = 131644;
					decorative[0] = 130113;
					decorative[1] = 130114;
					decorative[2] = 130115;
					decorative[3] = 130116;
					decorative[4] = 130675;

					skill1 = 4000;
					skill2 = 4205;
					break;
				case Constants::unitType::UN_EVE:
					hp = 10500;
					attack = 304;
					mattack = 376;
					def = 86;
					mdef = 60;

					normal[0] = 111110;
					normal[1] = 111111;
					normal[2] = 111112;
					normal[3] = 111113;
					normal[4] = 131645;
					decorative[0] = 130135;
					decorative[1] = 130136;
					decorative[2] = 130137;
					decorative[3] = 130138;
					decorative[4] = 130134;

					skill1 = 5001;
					skill2 = 5205;
					break;
				case Constants::unitType::UN_CHUNG:
					hp = 10000;
					attack = 352;
					mattack = 304;
					def = 86;
					mdef = 70;

					normal[0] = 111115;
					normal[1] = 111116;
					normal[2] = 111117;
					normal[3] = 111118;
					normal[4] = 111114;
					decorative[0] = 133126;
					decorative[1] = 133127;
					decorative[2] = 133128;
					decorative[3] = 133129;
					decorative[4] = 133125;

					skill1 = 6000;
					skill2 = 6203;
					break;
				case Constants::unitType::UN_ARA:
					hp = 10500;
					attack = 352;
					mattack = 296;
					def = 82;
					mdef = 72;

					normal[0] = 112701;
					normal[1] = 112702;
					normal[2] = 112703;
					normal[3] = 112704;
					normal[4] = 112700;
					decorative[0] = 41470;
					decorative[1] = 41480;
					decorative[2] = 41490;
					decorative[3] = 41500;
					decorative[4] = 41460;

					skill1 = 7001;
					skill2 = 7204;
					break;
				case Constants::unitType::UN_ELESIS:
					hp = 11250;
					attack = 360;
					mattack = 296;
					def = 80;
					mdef = 66;

					normal[0] = 112986;
					normal[1] = 112987;
					normal[2] = 112988;
					normal[3] = 112989;
					normal[4] = 112985;
					decorative[0] = 41721;
					decorative[1] = 41722;
					decorative[2] = 41723;
					decorative[3] = 41724;
					decorative[4] = 41720;

					skill1 = 0;
					skill2 = 0;
					break;

			}

			sql::PreparedStatement *pst;
			pst = Database::con->prepareStatement("INSERT INTO characters (accid, name, level, exp, hp, attack, mattack, def, mdef, ed, unittype, unitclass, createdate, map) VALUES (?,?,?,?,?,?,?,?,?,?,?,?,?,?);");
			pst->setInt(1, conn->getAccID());
			pst->setString(2, Converter::UTF16toUTF8(name));
			pst->setInt(3, level);
			pst->setInt(4, exp);
			pst->setInt(5, hp);
			pst->setInt(6, attack);
			pst->setInt(7, mattack);
			pst->setInt(8, def);
			pst->setInt(9, mdef);
			pst->setInt(10, ed);
			pst->setInt(11, unittype);
			pst->setInt(12, unitclass);
			pst->setDateTime(13, Time::now());
			pst->setInt(14, Config::startMap);
			pst->execute();
			pst->close();
			delete pst;

			sql::ResultSet* sti = Database::query("SELECT id FROM characters WHERE name = '" + Converter::UTF16toUTF8(name) + "'; ");
			sti->next();
			int chrid = sti->getInt("id");
			delete sti;

			
			sql::PreparedStatement *pste;
			pste = Database::con->prepareStatement("INSERT INTO item (charid, itemid, quantity, expiredate, isequip, invpos) VALUES (?,?,?,?,?,?);");
			pste->setInt(1, chrid);
			pste->setInt(3, 1);
			pste->setBoolean(5, true);

			sql::PreparedStatement *pstc;
			pstc = Database::con->prepareStatement("INSERT INTO equip(itemid, endurance, equipped) VALUES (LAST_INSERT_ID(),?,?);");

			sql::PreparedStatement *psts;
			psts = Database::con->prepareStatement("INSERT INTO skills(charid, skillid, level) VALUES (?,?,?);");
			psts->setInt(1, chrid);
			psts->setInt(3, 1);

			int pos = 1;
			
			for (int i = 0; i < 5; i++) {

				pste->setInt(2, normal[i]);
				pste->setDateTime(4, "0000-00-00 00:00:00");
				pste->setInt(6, pos);
				pste->execute();
				pos += 2;

				pstc->setInt(2/*1*/, 10000);
//				pstc->setBoolean(2, false);
				pstc->setBoolean(3, true);
				pstc->execute();

			}

			pos = 2;

			for (int i = 0; i < 5; i++) {

				pste->setInt(2, decorative[i]);
				pste->setDateTime(4, "0000-00-00 00:00:00");
				pste->setInt(6, pos);
				pste->execute();
				pos += 2;

				pstc->setInt(1, -1);
				pstc->setBoolean(2, true);
				pstc->setBoolean(3, true);
				pstc->execute();

			}

			psts->setInt(2, skill1);
			psts->execute();
			psts->setInt(2, skill2);
			psts->execute();

			conn->sendPacket(AuthPacket::createCharAck(chrid, name, charUT, hp, attack, mattack, def, mdef).getPacket());
			

		}

		void terminateConnection(Connection* conn) {

			conn->sendPacket(AuthPacket::terminateConnectionAck().getPacket());

		}

	}

}