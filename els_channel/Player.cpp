#include "Player.hpp"
#include "Inventory.hpp"
#include "ItemDataProvider.hpp"
#include "World.hpp"
#include <iostream>


namespace els {

	Player::Player(int accid, int playerid, std::wstring name, std::string ip, std::string createDate, std::string lastLogin, int hp, int attack, int mattack, int def, int mdef, int map) :
		m_accountID(accid), m_playerID(playerid), m_name(name), m_ip(ip), m_creationDate(createDate), m_lastLogin(lastLogin),
		m_maxHP(hp), m_baseAttack(attack), m_baseMagicattack(mattack), m_baseDef(def), m_baseMagicDef(mdef), m_map(map) { }

	Player::~Player() {
		/*
		std::cout << "CALLED!" << std::endl;
		if (m_map >= 20000 && m_map <= 20008 || m_map >= 30000 && m_map <= 30007)
			// replace this with something like (isValidMap)
			World::getMap(m_map)->removePlayer(m_playerID);
		*/
	}

	int Player::getAccountID() {
		return m_accountID;
	}

	int Player::getPlayerID() {
		return m_playerID;
	}

	std::wstring Player::getName() {
		return m_name;
	}

	std::string Player::getIP() {
		return m_ip;
	}

	std::string Player::getCreationDate() {
		return m_creationDate;
	}

	std::string Player::getLastLogin() {
		return m_lastLogin;
	}

	unsigned char Player::getLevel() {
		return m_level;
	}

	int Player::getED() {
		return m_ed;
	}

	int Player::getEXP() {
		return m_exp;
	}

	int Player::getAP() {
		return m_ap;
	}

	Constants::unitType Player::getUnitType() {
		return m_unitType;
	}

	Constants::unitClass Player::getUnitClass() {
		return m_unitClass;
	}

	int Player::getMaxHP() {
		return m_maxHP;
	}

	int Player::getBaseAttack() {
		return m_baseAttack;
	}

	int Player::getBaseMagicAttack() {
		return m_baseMagicattack;
	}

	int Player::getBaseDef() {
		return m_baseDef;
	}

	int Player::getBaseMagicDef() {
		return m_baseMagicDef;
	}

	int Player::getMap() {
		return m_map;
	}

	int Player::getCurDungeon() {
		return m_curDungeon;
	}

	int Player::getCurPVPMatch() {
		return m_curPVPmatch;
	}

	int Player::getIndex() {
		return m_index;
	}

	int Player::getState() {
		return m_state;
	}

	int Player::getTeam() {
		return m_Team;
	}

	int Player::getUDPPort() {
		return m_port;
	}

	int Player::getRoomID() {
		return m_roomid;
	}

	bool Player::getLeader() {
		return m_leader;
	}

	bool Player::getReady() {
		return m_ready;
	}

	float Player::getX() {
		return m_X;
	}

	float Player::getY() {
		return m_Y;
	}

	float Player::getZ() {
		return m_Z;
	}

	Inventory* Player::getInv() {
		return &m_inv;
	}

	SkillInventory* Player::getSkillInv() {
		return &m_skillInv;
	}

	Party* Player::getParty() {
		return m_party;
	}

	void Player::setName(std::wstring name) {
		m_name = name;
	}

	void Player::setLevel(unsigned char level) {
		m_level = level;
	}

	void Player::setED(int ed) {
		m_ed = ed;
	}

	void Player::setEXP(int exp) {
		m_exp = exp;
	}

	void Player::setAP(int ap) {
		m_ap = ap;
	}

	void Player::setUnitType(Constants::unitType unitType) {
		m_unitType = unitType;
	}

	void Player::setUnitClass(Constants::unitClass unitClass) {
		m_unitClass = unitClass;
	}
	
	void Player::setMaxHP(int hp) {
		m_maxHP = hp;
	}
	
	void Player::setBaseAttack(int attack) {
		m_baseAttack = attack;
	}

	void Player::setBaseMagicAttack(int mattack) {
		m_baseMagicattack = mattack;
	}

	void Player::setBaseDef(int def) {
		m_baseDef = def;
	}

	void Player::setBaseMagicDef(int mdef) {
		m_baseMagicDef = mdef;
	}

	void Player::setMap(int map) {
		m_map = map;
	}

	void Player::setInventory(Inventory* inv) {
		m_inv = *inv;
	}

	void Player::setCurDungeon(int dungeon) {
		m_curDungeon = dungeon;
	}

	void Player::setCurPVPMatch(int match) {
		m_curPVPmatch = match;
	}

	void Player::setIndex(int value) {
		m_index = value;
	}

	void Player::setState(int value) {
		m_state = value;
	}

	void Player::setTeam(int value) {
		m_Team = value;
	}

	void Player::setUDPPort(int port) {
		m_port = port;
	}

	void Player::setRoomID(int id) {
		m_roomid = id;
	}

	void Player::setLeader(bool b) {
		m_leader = b;
	}

	void Player::setReady(bool bb) {
		m_ready = bb;
	}

	void Player::setX(float value) {
		m_X = value;
	}

	void Player::setY(float value) {
		m_Y = value;
	}

	void Player::setZ(float value) {
		m_Z = value;
	}

	void Player::setParty(Party* party) {
		m_party = party;
	}

	void Player::writeData(PacketBuilder& pb) {
		std::cout << "角色ID:" << getPlayerID() << " IP:" << m_ip << " UDP Port: " << m_port << std::endl;
		pb
			.writeByte(m_index) // 0 1 2 3 4 5 6 7
			.writeByte(m_state) // SLOT_STATE 1 = EMPTY 2 = CLOSE 3 = WAIT 4 = LOADING 5 = PLAY
			.writebool(m_leader)
			.writebool(m_ready)
			.writebool(false) // 正在執行其他動作
			.writebool(false) // 正在執行其他動作
			.writeInt(m_Team) // TEAM_NUM 0 = TN_READ 1 = TN_BLUE) 2 = TN_MONSTER

			.writeLong(getAccountID()) // 2 不是帳號ID 不能跟其他角色一樣
			.writeLong(getAccountID())
			.writeByte(0)
			.writebool(true/*false*/)
			.writeByte(0)
			.writeLong(getPlayerID())
			.writeInt(getPlayerID()) // 17113 不是角色ID
			.writeByte((unsigned char)getUnitClass())
			.writeInt(1500) // PVP score 1500 = E
			.writeElsWString(getName())
			.writeElsString(m_ip)
			.writeShort(m_port/*8133*/) // player udp listen port
			.writeByte(getLevel())

			.writeInt(getMaxHP())
			.writeInt(getBaseAttack())
			.writeInt(getBaseMagicAttack())
			.writeInt(getBaseDef())
			.writeInt(getBaseMagicDef())
			;

		pb.writeInt(getInv()->getQuantity(9)); // equipped equips
		for (int i = 0; i < getInv()->getMaxSlots(9); i++) {
			int uid = (*getInv()->getInventory(9))[i];
			if (uid == -1) continue;
			else {
				auto item = &getInv()->getInventory()->find(uid)->second;
				bool isDecorative = ItemDataProvider::isDecorative(item->getItemID());
				pb
					.writeInt(item->getPosition())
					.writeLong(item->getUniqueID())
					.writeByte(9)
					.writeByte/*Short*/(item->getPosition())

					.writeInt(item->getItemID());
				if (isDecorative) {
					pb.writeByte(0);
				}
				else {
					pb.writeByte(1);
				}

				pb
					.writeInt(0)
					.writeShort(item->getEndurance())
					.writeByte(0)
					.writeByte(0)

					// 屬性
					.writeByte(0)
					.writeByte(0)
					.writeByte(0)

					.writeInt(0); // size -> short 魔法石 socket

				if (isDecorative) {
					pb.writeShort/*Int*/(7);
				}
				else {
					pb.writeShort/*Int*/(0);
				}

				if (item->getExpiry() != "0000-00-00 00:00:00") {
					pb.writeElsString(item->getExpiry());
				}
				else {
					pb.writeElsString("");
				}
			}
		}

		// 技能快捷鍵
		for (int i = 0; i < 8; i++) {
			int skillid = getSkillInv()->getEquippedSkills()[i];
			pb.writeShort(skillid);
			pb.writeByte(getSkillInv()->getSkillLevel(skillid));
		}

		pb
			.writeElsString("2000-01-01 00:00:00")
			.writeByte(2); // B欄

		pb
			.writeInt(0); // size -> short byte

		pb
			.writeInt(0); // size -> short byte 2009版沒有

		pb
			.writeInt(0); // size -> int 2009版沒有

		pb
			.writeInt(4800) // 角色現在疲勞值
			.writeInt(4800) // 疲勞值上限
			.writebool(false) // 網咖
			.writebool(false/*m_leader*//*false*/) // true的話不會讀取== 主線?
			.writeInt(0) // size -> byte float 好像是角色位置 2009版這邊是3個float
			.writebool(true/*false*/)
			.writebool(true/*false*/)
			.writeInt(0) // size -> int int -> int int
			.writeShort(10) // title

			.writeElsWString(L"") // guild
			.writeInt(0)
			.writeByte(0);
	}
}