#include "LuaScript.hpp"

namespace els {
	
	namespace LuaScript {

		lua_State* L;
		std::mutex mtx;

		void init() {
			
			std::cout << "Loading Lua Database..." << std::endl;

			L = luaL_newstate();
			luaL_openlibs(L);
			if (luaL_loadfile(L, "Data/ESDataLoader.lua") || lua_pcall(L, 0, 0, 0)) {
				std::cout << "Lua script loading failed." << std::endl;
				return;
			}

		}

		std::mutex* getLock() {
			return &mtx;
		}

		lua_State* getLuaState() {
			return L;
		}

	}

}