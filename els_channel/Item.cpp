#include "Item.hpp"
#include "Constants.hpp"

namespace els {

	Item::Item(int uid, int itemid, int quantity, int endurance, bool equipped, bool isEquip, short pos, std::string expiry) :
		m_uniqueID(uid), m_itemID(itemid), m_quantity(quantity), m_endurance(endurance),
		m_equipped(equipped), m_isEquip(isEquip), m_pos(pos), m_expiry(expiry), m_numattr(0)
	{
		m_attribute[0] = 0;
		m_attribute[1] = 0;
		m_attribute[2] = 0;
	}

	int Item::getUniqueID() {
		return m_uniqueID;
	}

	int Item::getItemID() {
		return m_itemID;
	}

	int Item::getQuantity() {
		return m_quantity;
	}

	bool Item::isEquip() {
		return m_isEquip;
	}

	int Item::getEndurance() {
		return m_endurance;
	}

	void Item::setEndurance(int endurance) {
		m_endurance = endurance;
	}

	bool Item::isEquipped() {
		return m_equipped;
	}

	short Item::getPosition() {
		return m_pos;
	}
	
	std::string Item::getExpiry() {
		return m_expiry;
	}

	void Item::setQuantity(int quantity) {
		m_quantity = quantity;
	}

	void Item::changeQuantity(int amount) {
		m_quantity += amount;
	}

	void Item::setEquipped(bool equipped) {
		m_equipped = equipped;
	}

	void Item::setPosition(short pos) {
		m_pos = pos;
	}

	int Item::getAttribute(int slot) {
		return m_attribute[slot];
	}

	void Item::setAttribute(int attribute, int slot) {
		if (attribute != 0) {
			m_numattr += 1;
		}
		else m_numattr -= 1;
		m_attribute[slot] = attribute;
	}

	int Item::getNumAttr() {
		return m_numattr;
	}

	unsigned char Item::getStatus() {
		return m_status;
	}

	void Item::setStatus(unsigned char status) {
		m_status = status;
	}

	unsigned char Item::getUpgrades() {
		return m_upgrades;
	}

	void Item::setUpgrades(unsigned char upgrades) {
		m_upgrades = upgrades;
	}

	bool Item::isSealed() {
		return m_sealed;
	}

	void Item::setSealed(bool seal) {
		m_sealed = seal;
	}

	std::vector<int>* Item::getSockets() {
		return &m_sockets;
	}

	void Item::addSocket(int socket) {
		m_sockets.push_back(socket);
	}

	std::vector<int>* Item::getAddEffects() {
		return &m_addeffects;
	}

	void Item::addAddEffect(int addeffect) {
		m_addeffects.push_back(addeffect);
	}

}