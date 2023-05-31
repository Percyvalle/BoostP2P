#pragma once

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <spdlog/spdlog.h>

#define DEFAULT_LENGTH 1024

namespace Network {
	using namespace boost::asio;
	using boost::asio::ip::tcp;
	using socket_ptr = boost::shared_ptr<tcp::socket>;
	
	class Client final {
	private:
		io_service m_client;
		tcp::socket m_socket{m_client};
		tcp::resolver m_resolver{m_client};

		std::string m_address;
		int m_port;

		char m_request[DEFAULT_LENGTH];
		size_t m_request_length = 0;

		char m_reply[DEFAULT_LENGTH];
		size_t m_reply_length = 0;
	public:
		Client(std::string, int);
		~Client() = default;

		void connectToServer();
		std::string requestToServer(std::string);

	private:
		void replyToServer();
	};
}