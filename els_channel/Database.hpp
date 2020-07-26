#pragma once

#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"

namespace els {
	namespace Database {
		extern sql::Driver* driver;
		extern sql::Connection* con;

		bool init();
		sql::ResultSet* query(std::string query);
		int getClientStatus(std::string user);

	}
}