#pragma warning(disable : 4251)
#include "Database.hpp"
#include "Config.hpp"

#include "mysql_connection.h"
#include "cppconn/driver.h"
#include "cppconn/exception.h"
#include "cppconn/resultset.h"
#include "cppconn/statement.h"
#include "cppconn/prepared_statement.h"

namespace els {
	namespace Database {
		sql::Driver* driver;
		sql::Connection* con;

		bool init() {
			try {
				driver = get_driver_instance();
				con = driver->connect(els::Config::sqlhost, els::Config::sqluser, els::Config::sqlpass);
				//con->setAutoCommit(0);
				con->setSchema(els::Config::sqldb);
			}
			catch (sql::SQLException &e) {
				std::cerr << "MySQL Error " << e.getErrorCode() << ": " << e.what() << std::endl;
				return false;
			}
			
			return true;
		}

		sql::ResultSet* query(std::string query) {

			sql::Statement* stmt = con->createStatement();
			try {
				sql::ResultSet* res = stmt->executeQuery(query);
				return res;
			}
			catch (sql::SQLException &e) {
				std::cerr << "MySQL Error " << e.getErrorCode() << ": " << e.what() << std::endl;
			}
		}

		int getClientStatus(std::string user) {

			sql::ResultSet* res;
			
			res = query("SELECT status FROM accounts WHERE name = '" + user + "' ");
			if (res->rowsCount() != 1) {
				return -1;
			}
			else {
				res->next();
				return res->getInt("status");
			}

		}
		

	}
}