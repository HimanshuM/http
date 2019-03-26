#ifndef HTTP__SERVER__
#define HTTP__SERVER__

#include <sys/types.h>
#include <sys/socket.h>
/*#include <netinet/in.h>*/
#include "debug_levels.hpp"

class Server
{
public:
	Server(char *port) : port{port} {};
	~Server();
	void configure(DebugLevels);
	void initialize();
	void listener();

	DebugLevels debugLevel = INFO;
	int maxPostSize = 1024;

protected:
	void dispatch(int, struct sockaddr_storage*);
	void setupContentParsers();

	struct addrinfo *serverInfo;
	char *port;
	int socketFD;
	socklen_t clientLen;
	struct addrinfo *serverAddress;

};

#endif