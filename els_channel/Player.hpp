#pragma once

#include "Inventory.hpp"
#include "SkillInventory.hpp"
#include "Constants.hpp"
#include "PacketBuilder.hpp"
#include <string>

namespace els {

	class Party;

	class Player {

		private:
			int m_accountID;
			int m_playerID;
			std::wstring m_name;
			std::string m_ip;
			int m_port = 0;
			std::string m_creationDate;
			std::string m_lastLogin;

			unsigned char m_level;
			int m_ed;
			int m_exp;
			int m_ap;
			Constants::unitType m_unitType;
			Constants::unitClass m_unitClass;

			int m_maxHP;
			int m_baseAttack;
			int m_baseMagicattack;
			int m_baseDef;
			int m_baseMagicDef;

			int m_map;
			int m_curDungeon;
			int m_curPVPmatch;

			int m_index = -1;
			int m_state = 3;
			int m_Team;

			bool m_leader;
			bool m_ready;

			float m_X = 0;
			float m_Y = 0;
			float m_Z = 0;

			int m_roomid = -1;

			Inventory m_inv;
			SkillInventory m_skillInv;
			
			Party* m_party;

		public:
			Player(int accid, int playerid, std::wstring name, std::string ip, std::string createDate, std::string lastLogin, int hp, int attack, int mattack, int def, int mdef, int map);
			Player() { }
			~Player();
			int getAccountID();
			int getPlayerID();
			std::wstring getName();
			std::string getIP();
			std::string getCreationDate();
			std::string getLastLogin();
			unsigned char getLevel();
			int getED();
			int getEXP();
			int getAP();
			Constants::unitType getUnitType();
			Constants::unitClass getUnitClass();
			int getMaxHP();
			int getBaseAttack();
			int getBaseMagicAttack();
			int getBaseDef();
			int getBaseMagicDef();
			int getMap();
			int getCurDungeon();
			int getCurPVPMatch();

			int getIndex();
			int getState();
			int getTeam();
			int getUDPPort();
			int getRoomID();

			bool getLeader();
			bool getReady();

			float getX();
			float getY();
			float getZ();
			Inventory* getInv();
			SkillInventory* getSkillInv();
			Party* getParty();
			void setName(std::wstring name);
			void setLevel(unsigned char level);
			void setED(int ed);
			void setEXP(int exp);
			void setAP(int ap);
			void setUnitType(Constants::unitType unitType);
			void setUnitClass(Constants::unitClass unitClass);
			void setMaxHP(int hp);
			void setBaseAttack(int attack);
			void setBaseMagicAttack(int mattack);
			void setBaseDef(int def);
			void setBaseMagicDef(int mdef);
			void setMap(int map);
			void setCurDungeon(int dungeon);
			void setCurPVPMatch(int match);

			void setIndex(int value);
			void setState(int value);
			void setTeam(int value);
			void setUDPPort(int port);
			void setRoomID(int id);

			void setLeader(bool b);
			void setReady(bool bb);

			void setX(float value);
			void setY(float value);
			void setZ(float value);
			void setInventory(Inventory* inv);
			void setParty(Party* party);

			void writeData(PacketBuilder& pb);
		
	};

}