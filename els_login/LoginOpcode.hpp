#pragma once

namespace els {

	namespace LoginOpcode {

		enum Send {
			
			SERVER_ACK,
			LOGIN_ACK,
			LOGIN_SERIAL
			
		};

		enum Recv {

			LOGIN_PASSWORD

		};

	}

}