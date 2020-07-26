#pragma once

#include <map>
#include <vector>

namespace els {

	namespace DungeonDataProvider {

		static std::map<int, std::vector<std::pair<int, int> > > dungeons;

		void loadDungeons(std::string area);
		void init();
		std::vector<std::pair<int, int> >* getRegion(int dungeonGate);

	}


}