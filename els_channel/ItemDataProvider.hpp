#pragma once
#include "Constants.hpp"

namespace els {

	namespace ItemDataProvider {

		void init();
		Constants::itemType getItemType(int itemid);
		bool isDecorative(int itemid);
		int getItemLevel(int itemid);
		int getItemGrade(int itemid);
		int mapToInvType(int itemid, bool equipped, bool decorative);

	}

}