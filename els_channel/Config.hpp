#pragma once
#include <string>
#include <cstdint>

namespace els {
	namespace Config {

		extern std::string version;

		// General

		extern unsigned int expRate;
		extern unsigned int edRate;
		extern int startMap;

		// Database
		extern std::string sqlhost;
		extern std::string sqluser;
		extern std::string sqlpass;
		extern std::string sqldb;

		//Net
		extern short channelPort;
		extern short gamePort;
		extern std::string serverIP;
		extern std::string serverName;

		//Channels
		extern int channels;
		extern std::wstring channelName[1];
		extern std::string channelIP[1];
	}
}