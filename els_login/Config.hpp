#pragma once
#include <string>

namespace els {

	namespace Config {

		extern std::string version;

		// Database
		extern std::string sqlhost;
		extern std::string sqluser;
		extern std::string sqlpass;
		extern std::string sqldb;

		//Net
		extern short loginport;
		extern std::string serverIP;
		extern std::string serverName;

		//Channels
		extern int channels;
		extern std::wstring channelName[1];
		extern std::string channelIP[1];
	}
}