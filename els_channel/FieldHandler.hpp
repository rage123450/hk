#pragma once
#include "Connection.hpp"
#include "PacketReader.hpp"

namespace els {

	namespace FieldHandler {

		void moveToField(PacketReader pr, Connection* conn);

	}


}