#include "src/Server.hpp"

int main()
{

	Network::Server server{"127.0.0.1", 8050};
	server.start();

	return EXIT_SUCCESS;
}
