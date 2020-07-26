#include <locale>
#include <codecvt>
#include <string>

namespace els {

	namespace Converter {

		std::wstring UTF8toUTF16(std::string s) {

	     	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> con;

	        return con.from_bytes(s);
	    }

		std::string UTF16toUTF8(std::wstring s) {

			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> con;

			return con.to_bytes(s);
		}

		int parseIPV4string(char* ipAddress) {
			char ipbytes[4];
			sscanf(ipAddress, "%uhh.%uhh.%uhh.%uhh", &ipbytes[3], &ipbytes[2], &ipbytes[1], &ipbytes[0]);
			return ipbytes[0] | ipbytes[1] << 8 | ipbytes[2] << 16 | ipbytes[3] << 24;
		}
	}
}