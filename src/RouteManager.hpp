#pragma once

#include <pqxx/pqxx>
#include <string>

namespace Network {
	class RouteManager {
	private:
		unsigned int m_port;
		std::string m_addressdb;
		std::string m_passwordb;
		std::string m_namedb;
		std::string m_usernamedb;

		pqxx::connection m_connectdb;
	public:
		RouteManager() = default;
		RouteManager(std::string, int, std::string, std::string, std::string);
		~RouteManager() = default;

		void registrationRoute(std::string, int);
		void writeoffRoute(std::string, int);

	};
}