#include "Inventory.hpp"
#include "Item.hpp"
#include "ItemDataProvider.hpp"
#include <utility>
#include <iostream>
#include <algorithm>

namespace els {

	Inventory::Inventory() {
		for (int i = 0; i < 11; i++) {
			m_quantity[i] = 0;
		}
	}

	/*
	std::map<int, Item>* Inventory::getInventory() {
		return &m_items;
	}
	*/

	std::map<int, Item>* Inventory::getInventory() {
		return &m_itemlist;
	}

	std::vector<int>* Inventory::getInventory(int invtype) {
		return &m_items[invtype];
	}

	void Inventory::addItem(Item* item) {
		
		bool decorative = ItemDataProvider::isDecorative(item->getItemID());
		bool equipped = item->isEquipped();
		int type = ItemDataProvider::mapToInvType(item->getItemID(), equipped, decorative);
		m_quantity[type]++;
		m_itemlist.insert(std::make_pair(item->getUniqueID(), *item));
		m_items[type][item->getPosition()] = item->getUniqueID();
	}

	/*
	void Inventory::addNewItem(Item* item) {
		m_items.insert(std::make_pair(item->getItemID(), *item));
		// add db entry
	}
	*/

	void Inventory::removeItem(int uid) {
		auto item = m_itemlist.find(uid);
		if (item != m_itemlist.end()) {
			bool decorative = ItemDataProvider::isDecorative(item->second.getItemID());
			int invtype = ItemDataProvider::mapToInvType(item->second.getItemID(), item->second.isEquipped(), decorative);
			m_itemlist.erase(uid);
			std::replace(m_items[invtype].begin(), m_items[invtype].end(), uid, -1);
		}
	}

	Item* Inventory::getItem(int uid) {
		std::map<int, Item>::iterator item = m_itemlist.find(uid);
		if (item != m_itemlist.end()) {
			return &item->second;
		}
		else return nullptr;
	}

	int Inventory::findItem(int itemid) {
		for (auto item : m_itemlist) {
			if (item.second.getItemID() == itemid) {
				return item.second.getUniqueID();
			}
		}
		return -1;
	}

	short Inventory::getMaxSlots(int invType) {
		if (invType < 11 && invType != 0) {
			return m_maxSlots[invType];
		}
		else return -1;
	}

	void Inventory::setMaxSlots(int invType, int maxSlots) {
		m_maxSlots[invType] = maxSlots;
		m_items[invType].assign(maxSlots, -1);
	}

	int Inventory::getQuantity(int type) {
		return m_quantity[type];
	}

	void Inventory::setQuantity(int type, int amount) {
		m_quantity[type] = amount;
	}

	void Inventory::changeQuantity(int type, int amount) {
		m_quantity[type] += amount;
	}

}