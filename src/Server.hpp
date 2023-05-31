#pragma once

#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/make_shared.hpp>

#include <spdlog/spdlog.h>


#define DEFAULT_LENGTH 1024
#define DEFAULT_PORT 8050

namespace Network {
	using namespace boost::asio;
	using boost::asio::ip::tcp;
	using socket_ptr = boost::shared_ptr<tcp::socket>;
	
	class Session final : public boost::enable_shared_from_this<Network::Session> {
	private:
		tcp::socket m_socket;
		char m_data[DEFAULT_LENGTH];
	public:
		Session(tcp::socket&&);
		~Session();

		void start();
		void doread();
		void dowrite(std::size_t);
		
		inline std::string getaddress() { return m_socket.remote_endpoint().address().to_string(); };
		inline int getport() { return m_socket.remote_endpoint().port(); };
	};

	class Server final {
	private:
		int m_port = DEFAULT_PORT;

		io_service m_server;
		tcp::endpoint m_epserver;
		tcp::acceptor m_acserver;
	public:
		Server();
		Server(int);
		Server(std::string, int);
		~Server() = default;

		void start();
		void accepting();
	};
}