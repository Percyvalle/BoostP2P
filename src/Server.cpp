#include "Server.hpp"

Network::Server::Server() : m_acserver(m_server, m_epserver = tcp::endpoint(tcp::v4(), m_port)) {}

Network::Server::Server(int _port) : m_acserver(m_server, m_epserver = tcp::endpoint(tcp::v4(), m_port = _port)) {}

Network::Server::Server(std::string _address, int _port) 
	: m_acserver(m_server, m_epserver = tcp::endpoint(boost::asio::ip::address::from_string(_address), m_port = _port)) {}

void Network::Server::start()
{
	spdlog::info("Accepting to server {0}:{1}", m_epserver.address().to_string(), m_port);
	accepting();

	spdlog::info("Server started");
	m_server.run();
}

void Network::Server::accepting()
{
	m_acserver.async_accept([this](boost::system::error_code _error, tcp::socket _socket) {
			
			if (!_error) {
				spdlog::info("Connect to {0}:{1}", _socket.remote_endpoint().address().to_string(), _socket.remote_endpoint().port());
				boost::make_shared<Session>(std::move(_socket))->start(); 
			}
			else { spdlog::error(_error.to_string()); }

			accepting();
		});
}

Network::Session::Session(tcp::socket&& _socket) : m_socket(std::forward<tcp::socket>(_socket)) {}

Network::Session::~Session() {}

void Network::Session::start() { doread(); }

void Network::Session::doread()
{
	boost::shared_ptr<Network::Session> self(shared_from_this());
	m_socket.async_read_some(boost::asio::buffer(m_data, DEFAULT_LENGTH), 
		[this, self](boost::system::error_code _error,	std::size_t _length) {
			if (!_error) {
				spdlog::info("receive {0} bytes to {1}:{2}(Success)", _length, m_socket.remote_endpoint().address().to_string(), m_socket.remote_endpoint().port());

				std::cout << std::string(m_data, _length) << std::endl;

				dowrite(_length);
			}
			else { spdlog::warn("Error receiving message: {0}", _error.to_string()); }
		});
}

void Network::Session::dowrite(std::size_t _length)
{
	boost::shared_ptr<Network::Session> self(shared_from_this());
	boost::asio::async_write(m_socket, boost::asio::buffer(m_data, _length),
		[this, self](boost::system::error_code _error, std::size_t _length) {
			if (!_error) {
				doread();
			}
			else { spdlog::warn("Error writing message: {0}\n", _error.to_string()); }
		});
}
