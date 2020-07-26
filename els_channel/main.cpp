#pragma warning(disable : 4251)
#include <iostream>
#include <chrono>
#include "Config.hpp"
#include "Database.hpp"
#include "Server.hpp"
#include "LuaScript.hpp"
#include "DungeonDataProvider.hpp"
#include "ItemDataProvider.hpp"
#include "MapDataProvider.hpp"

int main() {

	std::cout << "[Elsword Emulator Project]" << std::endl;
	std::cout << "<Channel Server>" << std::endl << std::endl;

	std::cout << "<Version: " << els::Config::version << ">" << std::endl << std::endl;

	auto start = std::chrono::high_resolution_clock::now();

	// Database

	std::cout << "Connecting to Database..." << std::endl;
	if (!els::Database::init()) {
		std::system("pause");
		return EXIT_FAILURE;
	}

	// Data

	els::LuaScript::init();
	els::ItemDataProvider::init();
	els::MapDataProvider::loadMaps();	// Maps
	els::DungeonDataProvider::init();	// Dungeons

	// Net
	
	std::cout << "Loading Channel..." << std::endl;
	els::Server channel(els::Config::channelPort, els::Config::gamePort);
	std::cout << "Channel Server listening on port " << els::Config::channelPort << " and " << els::Config::gamePort << std::endl;
	
	auto end = std::chrono::high_resolution_clock::now();

	std::cout << std::endl << "Fully initialized in " <<
		std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() / 1000.0 << " seconds" << std::endl;
	
	try {
		channel.init();
	}
	catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	catch (...) {
		std::cout << "Exception Occurred." << std::endl;
	}
}