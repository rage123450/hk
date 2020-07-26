#include "DungeonDataProvider.hpp"
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>

namespace els {

	namespace DungeonDataProvider {

		void loadDungeons(std::string area) {

			std::ifstream fin("Data/Dungeon/Dungeon" + area + ".txt");
			
			int dungeonGate, dungeonID;
			fin >> dungeonGate;

			std::vector<std::pair<int, int> > dg;

			while (fin >> dungeonID) {
				dg.push_back(std::make_pair(dungeonID, 0));
			}

			dungeons.insert(std::make_pair(dungeonGate, dg));

			fin.close();

		}

		void init() {

			std::cout << "Loading Dungeons..." << std::endl;

			loadDungeons("Ruben");
			loadDungeons("Elder");
			// finish other regions

		}

		std::vector<std::pair<int, int> >* getRegion(int dungeonGate) {

			if (dungeons.find(dungeonGate) != dungeons.end()) {
				return &dungeons[dungeonGate];
			}
			else {
				
				for (auto area : dungeons) {
					for (auto i = area.second.begin(); i != area.second.end(); i++) {
						if (i->first == dungeonGate) {
							return &area.second;
						}
					}
				}
			}
			return nullptr;
		}

	}


}