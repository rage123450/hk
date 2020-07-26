#pragma once
#include <string>
#include <vector>
#include "Constants.hpp"
#include <array>

namespace els {

	class Item {
		
		private:
			int m_uniqueID;
			int m_itemID;
			int m_quantity;
			bool m_isEquip;
			int m_endurance;
			bool m_equipped;
			short m_pos;
			unsigned char m_status;
			unsigned char m_upgrades;
			bool m_sealed;
			std::vector<int> m_sockets;
			std::vector<int> m_addeffects;
			int m_attribute[3];
			int m_numattr; // number of attributes

			std::string m_expiry;

		public:
			Item(int uid, int itemid, int quantity, int endurance, bool equipped, bool isEquip, short pos, std::string expiry);
			Item() {}
			~Item() { }
			int getUniqueID();
			int getItemID();
			int getQuantity();
			bool isEquip();
			int getEndurance();
			void setEndurance(int endurance);
			bool isEquipped();
			short getPosition();
			std::string getExpiry();
			void setQuantity(int quantity);
			void setEquipped(bool equipped);
			void setPosition(short pos);
			void changeQuantity(int amount);
			int getAttribute(int slot);
			void setAttribute(int attribute, int slot);
			int getNumAttr();
			unsigned char getStatus();
			void setStatus(unsigned char status);
			unsigned char getUpgrades();
			void setUpgrades(unsigned char upgrades);
			bool isSealed();
			void setSealed(bool seal);
			std::vector<int>* getSockets();
			void addSocket(int socket);
			std::vector<int>* getAddEffects();
			void addAddEffect(int addeffect);


	};

}