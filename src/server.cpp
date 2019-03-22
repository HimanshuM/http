#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <thread>

#include "server.hpp"
#include "error.hpp"
#include "dispatch.hpp"
#include "ip_helper.hpp"

Server::~Server()
{
	close(this->socketFD);
}

// void configure(DebugLevels debugLevel)
// {
// 	this->debugLevel = debugLevel;
// }

void Server::initialize()
{
	struct addrinfo hints;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;     // don't care IPv4 or IPv6
	hints.ai_socktype = SOCK_STREAM; // TCP stream sockets
	hints.ai_flags = AI_PASSIVE;

	int status;
	if ((status = getaddrinfo(NULL, this->port, &hints, &this->serverInfo)) != 0) {
		fprintf(stderr, "ERROR: Could not get address information: %s", gai_strerror(status));
		exit(1);
	}

	this->socketFD = socket(this->serverInfo->ai_family, this->serverInfo->ai_socktype, this->serverInfo->ai_protocol);
	if (this->socketFD < 0)
	{
		die("ERROR: Could not open socket");
	}

	int yes = 1;
	if (setsockopt(socketFD,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes) == -1) {
		perror("setsockopt");
		exit(1);
	}

	if (bind(this->socketFD, this->serverInfo->ai_addr, this->serverInfo->ai_addrlen) < 0)
	{
		die("ERROR on binding");
	}

	listener();
}

void Server::listener()
{
	listen(this->socketFD, 5);

	while (1)
	{
		struct sockaddr_storage client_addr;
		socklen_t addr_size = sizeof client_addr;

		int request_fd = accept(this->socketFD, (struct sockaddr *) &client_addr, &addr_size);
		if (request_fd < 0)
		{
			die("ERROR on accept");
		}

		dispatch(request_fd, &client_addr);
	}

}

void Server::dispatch(int request_fd, struct sockaddr_storage *client_addr)
{
	Dispatch req(debugLevel, request_fd, client_addr, this->maxPostSize);
	std::thread tRequest(req);
	tRequest.join();
	// req();
}