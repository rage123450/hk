#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <mutex>
#include "lua.hpp"

namespace els {
	
	namespace LuaScript {
		
		void init();
		std::mutex* getLock();
		lua_State* getLuaState();

	}

}