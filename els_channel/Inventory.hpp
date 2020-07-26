#pragma once
#include "Item.hpp"
#include <map>
#include <vector>

namespace els {

	class Inventory {
		
		private:
			std::map<int, Item> m_itemlist;		// for easy searching of items (uid, item*)
			std::vector<int> m_items[16];			// keeping track of pos of items (uid, item)
			short m_maxSlots[16];
			short m_quantity[16];

		public:
			Inventory();
			~Inventory() { }
			std::map<int, Item>* getInventory();
			std::vector<int>* getInventory(int invtype);
			void addItem(Item* item);
			void addNewItem(Item* item);
			void removeItem(int uid);
			Item* getItem(int uid);
			int findItem(int itemid);
			short getMaxSlots(int invType);
			void setMaxSlots(int invType, int maxSlots);
			int getQuantity(int type);
			void setQuantity(int type, int amount);
			void changeQuantity(int type, int amount);
		/*
		private:
			std::map<int, Item> m_items;
			int m_equipped;
			short m_maxSlots[8];


		public:
			std::map<int, Item>* getInventory();
			void addItem(Item* item);
			void addNewItem(Item* item);
			Item* getItem(int uItemID);
			int getEquipped();
			void setEquipped(int equipped);
			short getMaxSlots(int invType);
			void setMaxSlots(int invType, int maxSlots);
		*/
	};


}