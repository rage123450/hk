#include "ItemDataProvider.hpp"
#include "LuaScript.hpp"

namespace els {

	namespace ItemDataProvider {

		void init() {

			std::cout << "Loading Items..." << std::endl;

			lua_getglobal(LuaScript::getLuaState(), "loadItems");
			
			if (lua_pcall(LuaScript::getLuaState(), 0, 0, 0) != 0) {
				std::cout << "Failed to load items" << std::endl;
			}
			
		}

		Constants::itemType getItemType(int itemid) {
			LuaScript::getLock()->lock();

			lua_getglobal(LuaScript::getLuaState(), "getItemType");
			lua_pushnumber(LuaScript::getLuaState(), itemid);
			lua_call(LuaScript::getLuaState(), 1, 1);
			
			int type = lua_tonumber(LuaScript::getLuaState(), -1);
			lua_pop(LuaScript::getLuaState(), 1);
			LuaScript::getLock()->unlock();
			
			return (Constants::itemType)type;
		}

		bool isDecorative(int itemid) {
			LuaScript::getLock()->lock();

			lua_getglobal(LuaScript::getLuaState(), "isDecorative");
			lua_pushnumber(LuaScript::getLuaState(), itemid);
			lua_call(LuaScript::getLuaState(), 1, 1);

			bool isdecor = lua_toboolean(LuaScript::getLuaState(), -1);
			lua_pop(LuaScript::getLuaState(), 1);
			LuaScript::getLock()->unlock();
			
			return isdecor;
		}

		int getItemLevel(int itemid) {

			LuaScript::getLock()->lock();

			lua_getglobal(LuaScript::getLuaState(), "getItemLevel");
			lua_pushnumber(LuaScript::getLuaState(), itemid);
			lua_call(LuaScript::getLuaState(), 1, 1);

			int level = lua_tointeger(LuaScript::getLuaState(), -1);
			lua_pop(LuaScript::getLuaState(), 1);
			LuaScript::getLock()->unlock();

			return level;

		}

		int getItemGrade(int itemid) {

			LuaScript::getLock()->lock();

			lua_getglobal(LuaScript::getLuaState(), "getItemGrade");
			lua_pushnumber(LuaScript::getLuaState(), itemid);
			lua_call(LuaScript::getLuaState(), 1, 1);

			int grade = lua_tointeger(LuaScript::getLuaState(), -1);
			lua_pop(LuaScript::getLuaState(), 1);
			LuaScript::getLock()->unlock();

			return grade;

		}

		int mapToInvType(int itemid, bool equipped, bool decorative) {
			
			int type = getItemType(itemid);
			switch (type) {
				case 1: // attack
				case 2: // defence
					if (equipped) return 9;
					else if (decorative) return 7; // decoratives
					else return 1;
				case 3:
					if (equipped) return 9;
					return 2; // accessory
				case 5:
					return 6; // consume
				case 6:
					return 3; // material
				case 7:
					return 4; // special
				case 8:
					return 5; // quest
				default:
					return 0;
				
			}
		}

	}

}