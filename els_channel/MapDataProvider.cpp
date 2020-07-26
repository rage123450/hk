#include "MapDataProvider.hpp"
#include <fstream>
#include <utility>
#include <iostream>

namespace els {

	namespace MapDataProvider {

		void loadMaps() {

			std::cout << "Loading Maps..." << std::endl;
			/*
			std::ifstream fin("Data/World/Map.txt");
			int id;

			while (fin >> id) {
				Map map(id);
				World::addMap(map);
			}
			*/

			// ¾Ô°«³õ
			for (int i = 10000; i <= 10006; i++) {
				Map map(i);
				World::addMap(map);
			}
			// §ø²ø
			for (int i = 20000; i <= 20006; i++) {
				Map map(i);
				World::addMap(map);
			}
			// ¥ð®§°Ï
			for (int i = 30000; i <= 30006; i++) {
				Map map(i);
				World::addMap(map);
			}

			//fin.close();

		}

	}

}