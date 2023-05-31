#include "Client.hpp"

Network::Client::Client(std::string _address, int _port) : m_address(_address), m_port(_port) {};

void Network::Client::connectToServer() {
	try
	{
		boost::asio::connect(m_socket, m_resolver.resolve(tcp::endpoint(boost::asio::ip::address::from_string(m_address), 8050))).address().to_string();
	}
	catch (const std::exception& _error)
	{
		spdlog::error("Error connect to server: {0}", _error.what());
	}
}
std::string Network::Client::requestToServer(std::string _msg)
{
	strcpy(m_request, _msg.c_str());
	boost::asio::write(m_socket, boost::asio::buffer(m_request, m_request_length = _msg.length()));
	spdlog::info("Request (Success): {0}", m_request);

	replyToServer();
	return std::string(m_reply, m_reply_length);
}

void Network::Client::replyToServer()
{
	m_reply_length = boost::asio::read(m_socket, boost::asio::buffer(m_reply, m_request_length));
	spdlog::info("Reply (Success): {0} ", std::string(m_reply, m_reply_length));
}