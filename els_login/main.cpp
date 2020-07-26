#pragma warning(disable : 4251)
#include <iostream>
#include "Config.hpp"
#include "Database.hpp"
#include "Server.hpp"

int main() {

	std::cout << "[Elsword Emulator Project]" << std::endl;
	std::cout << "<Login Server>" << std::endl << std::endl;

	std::cout << "<Version: " << els::Config::version << ">" << std::endl << std::endl;

	// Database

	std::cout << "Connecting to Database..." << std::endl;
	if (!els::Database::init()) {
		std::system("pause");
		return 1;
	}

	// Data



	// Net
	std::cout << "Loading Login..." << std::endl;
	els::Server login(els::Config::loginport);
	std::cout << "Login Server listening on port " << els::Config::loginport << std::endl;
	login.init();

}