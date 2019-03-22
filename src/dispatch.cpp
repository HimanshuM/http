#include <stdlib.h>
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include "error.hpp"
#include "dispatch.hpp"
#include "ip_helper.hpp"
#include "request_parser.hpp"
#include "string.hpp"

void Dispatch::operator()()
{
	read();
}

void Dispatch::read()
{
	char *data = new char[maxPostSize];
	memset(data, '\0', maxPostSize);
	if (recv(this->fileDescriptor, data, this->maxPostSize, 0) < 0)
	{
		die();
	}

	std::cout<<data<<std::endl;

	prepareObjects(data);
	if (!validateRequest())
	{
		return;
	}

	serve();
}

void Dispatch::prepareObjects(char *data)
{
	request = RequestParser::parse(data);
	response.setFileDescriptor(fileDescriptor);
}

bool Dispatch::validateRequest()
{
	if (request.method == "UNDEFINED")
	{
		response.renderFalse();
		return false;
	}

	return true;
}

void Dispatch::serve()
{
	char s[INET6_ADDRSTRLEN];
	if (debugLevel < WARN)
	{
		printf("INFO: New connection for %s from %s\n",
			request.uri.c_str(),
			inet_ntop(clientAddr->ss_family,
			get_in_addr((struct sockaddr *)clientAddr),
			s, sizeof s));
	}

	response.write("<html><head><title>Himanshu's HTTP Server</title></head><body><h2>It Works!</h2></body></html>");
	response.end();

	close(fileDescriptor);
}