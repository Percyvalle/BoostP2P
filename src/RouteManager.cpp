#include "RouteManager.hpp"

Network::RouteManager::RouteManager(std::string _address, int _port, std::string _password, std::string _namedb, std::string _accaunt) 
	: m_addressdb(_address), m_port(_port), m_passwordb(_password), m_namedb(_namedb), m_accauntdb(_accaunt), 
	  m_connectdb(pqxx::connection{ "postgresql://" + _accaunt + "@" + _address + ":" + std::to_string(_port) + "/" + _namedb })
{
}

void Network::RouteManager::registrationRoute(std::string _address_client, int _port_client)
{
	pqxx::work worker{m_connectdb};

	worker.exec("INSERT INTO blockchain_route(ip, port) "
				"VAlUES ( '" + _address_client + "', " + std::to_string(_port_client) + ")");
	
	worker.commit();
}

void Network::RouteManager::writeoffRoute(std::string _address_client, int _port_clinet)
{
	pqxx::work worker{m_connectdb};

	worker.exec("DELETE FROM blockchain_route WHERE ip='" + _address_client + "' AND port=" + std::to_string(_port_clinet));

	worker.commit();
}
