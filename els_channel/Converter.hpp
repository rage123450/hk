#pragma once
#include <string>

namespace els {

	namespace Converter {

		std::wstring UTF8toUTF16(std::string s);
		std::string UTF16toUTF8(std::wstring s);
		int parseIPV4string(char* ipAddress);

	}


}