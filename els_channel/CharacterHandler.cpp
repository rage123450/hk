#include "CharacterHandler.hpp"
#include "CharacterPacket.hpp"
#include "Converter.hpp"
#include "Database.hpp"
#include "Party.hpp"
#include "World.hpp"

namespace els {

	namespace CharacterHandler {

		void playerDataReq(PacketReader pr, Connection* conn) {

			int playerID = pr.readLong();

			sql::ResultSet* chr;
			sql::PreparedStatement* pst;
			pst = Database::con->prepareStatement("SELECT * FROM characters WHERE id = ?;");
			pst->setInt(1, playerID);
			chr = pst->executeQuery();
			pst->close();
			delete pst;

			sql::ResultSet* equip;
			sql::PreparedStatement* pste;
			pste = Database::con->prepareStatement("SELECT item.id, item.itemid, item.invpos, equip.endurance, equipped, expiredate, status, upgrades, sealed, attribute1, attribute2, attribute3 FROM item, equip WHERE item.id = equip.itemid AND item.charid = ?;");
			pste->setInt(1, playerID);
			equip = pste->executeQuery();
			pste->close();
			delete pste;

			sql::ResultSet* item;
			sql::PreparedStatement* pstc;
			pstc = Database::con->prepareStatement("SELECT * FROM item WHERE isequip=false AND item.charid = ?;");
			pstc->setInt(1, playerID);
			item = pstc->executeQuery();
			pstc->close();
			delete pstc;

			sql::ResultSet* skills;
			sql::PreparedStatement* psts;
			psts = Database::con->prepareStatement("SELECT * FROM skills WHERE charid = ?");
			psts->setInt(1, playerID);
			skills = psts->executeQuery();
			psts->close();
			delete psts;

			sql::ResultSet* invSlots;
			sql::PreparedStatement* psti;
			psti = Database::con->prepareStatement("SELECT * FROM invslots WHERE charid = ?");
			psti->setInt(1, playerID);
			invSlots = psti->executeQuery();
			psti->close();
			delete psti;


			// load player
			chr->next();
			Player player(chr->getInt("accid"), chr->getInt("id"), Converter::UTF8toUTF16(chr->getString("name")), conn->getSocket().remote_endpoint().address().to_string(), chr->getString("createdate"), conn->getLastLogin(), chr->getInt("hp"), chr->getInt("attack"), chr->getInt("mattack"), chr->getInt("def"), chr->getInt("mdef"), chr->getInt("map"));
			player.setUnitClass((els::Constants::unitClass)chr->getInt("unitclass"));
			player.setUnitType((els::Constants::unitType)chr->getInt("unittype"));
			player.setED(chr->getInt("ed"));
			player.setAP(chr->getInt("ap"));
			player.setEXP(chr->getInt("exp"));
			player.setLevel(chr->getInt("level"));
			player.getSkillInv()->setSP(chr->getInt("sp"));

			// load inventory slots
			while (invSlots->next()) {
				player.getInv()->setMaxSlots(invSlots->getInt("invtype"), invSlots->getInt("maxslots"));
			}

			short quantity[11];
			memset(quantity, 0, sizeof(quantity));

			// init inventory

			// load equips

			while (equip->next()) {
				Item eqp(equip->getInt("id"), equip->getInt("itemid"), 1, equip->getInt("endurance"), equip->getBoolean("equipped"), true, equip->getInt("invpos"), equip->getString("expiredate"));
				eqp.setAttribute(equip->getInt("attribute1"), 1);
				eqp.setAttribute(equip->getInt("attribute2"), 2);
				eqp.setAttribute(equip->getInt("attribute3"), 3);
				eqp.setSealed(equip->getBoolean("sealed"));
				eqp.setStatus(equip->getInt("status"));
				eqp.setUpgrades(equip->getInt("upgrades"));
				player.getInv()->addItem(&eqp);
			}

			// load items

			while (item->next()) {
				Item it(item->getInt("id"), item->getInt("itemid"), item->getInt("quantity"), 0, false, false, item->getInt("invpos"), item->getString("expiredate"));
				it.setAttribute(0, 1);
				it.setAttribute(0, 2);
				it.setAttribute(0, 3);
				it.setSealed(false);
				it.setStatus(1);
				it.setUpgrades(0);
				player.getInv()->addItem(&it);
			}

			//load skills
			while (skills->next()) {
				player.getSkillInv()->addSkill(skills->getInt("skillid"), skills->getInt("level"));
				if (skills->getBoolean("isequipped")) {
					player.getSkillInv()->getEquippedSkills()[skills->getInt("slotid")] = skills->getInt("skillid");
				}
			}

			conn->setPlayer(&player);

			//add player to a party
/*			Party party;
			party.setLeader(conn->getPlayer());
			long long pid = World::addParty(&party);
			conn->getPlayer()->setParty(World::getParty(pid));
			World::getMap(player.getMap())->addParty(conn->getPlayer()->getParty());*/

			std::cout << "ADDR: " << World::getMap(player.getMap())->getPlayers() << std::endl;

			// update world (add player to map)
			World::getMap(conn->getPlayer()->getMap())->addPlayer(conn->getPlayer());
			std::cout << "MAPSIZE: " << World::getMap(conn->getPlayer()->getMap())->getPlayers()->size() << std::endl;

			// send response
			conn->sendPacket(CharacterPacket::playerDataAck(conn->getPlayer()).getPacket()); // 2A
/*			conn->sendPacket(CharacterPacket::unknown_0x2B(conn->getPlayer()).getPacket());
			conn->sendPacket(CharacterPacket::unknown_0x2C().getPacket());
			conn->sendPacket(CharacterPacket::unknown_0x2D(conn->getPlayer()).getPacket());
			conn->sendPacket(CharacterPacket::unknown_0x29().getPacket());

			conn->sendPacket(CharacterPacket::unknown_0x136().getPacket());
			conn->sendPacket(CharacterPacket::unknown_0x2D8().getPacket());
			//conn->sendPacket(CharacterPacket::unknown_0x222().getPacket());
			conn->sendPacket(CharacterPacket::unknown_0xF5(0).getPacket());
			conn->sendPacket(CharacterPacket::unknown_0xF6(conn->getPlayer(), 0x30E58).getPacket());
			conn->sendPacket(CharacterPacket::unknown_0xF5(0).getPacket());
			conn->sendPacket(CharacterPacket::unknown_0xF6(conn->getPlayer(), 0x123AE).getPacket());
			conn->sendPacket(CharacterPacket::unknown_0xF5(0xA2).getPacket());
			conn->sendPacket(CharacterPacket::unknown_0x26F().getPacket());
			conn->sendPacket(CharacterPacket::unknown_0x1DB().getPacket());
			conn->sendPacket(CharacterPacket::unknown_0x3A0().getPacket());*/

		}


	}


}