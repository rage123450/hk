#pragma once
#include "Connection.hpp"
#include "PacketReader.hpp"

namespace els {

	namespace CharacterHandler {

		void playerDataReq(PacketReader pr, Connection* conn);


	}


}