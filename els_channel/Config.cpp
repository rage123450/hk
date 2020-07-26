#include "Config.hpp"
#include <string>

namespace els {

	namespace Config {

		std::string version = "N_20100405_A";

		// General

		unsigned int expRate = 1;
		unsigned int edRate = 1;
		int startMap = 20001; // ruben

		// Database

		std::string sqlhost = "127.0.0.1";
		std::string sqluser = "root";
		std::string sqlpass = "";
		std::string sqldb = "els";

		//Net

		short channelPort = 9300;
		short gamePort = 9301;
		std::string serverName = "Server 1";
		std::string serverIP = "127.0.0.1";

		//Channels

		int channels = 1;
		std::wstring channelName[1] = { L"¤À¬y1" };
		std::string channelIP[1] = { "127.0.0.1" };

	}
}