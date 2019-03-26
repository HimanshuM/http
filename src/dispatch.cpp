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
	int bytesRead = 0;
	if ((bytesRead = recv(fileDescriptor, data, maxPostSize, 0)) < 0)
	{
		die();
	}

	prepareObjects(data);
	if (!validateRequest())
	{
		return;
	}

	serve();
}

void Dispatch::prepareObjects(char *data)
{
	RequestParser parser;
	request = parser.parse(data, this);

	verifyRequestBodyIntegrity();
	setClientIP();

	response.setFileDescriptor(fileDescriptor);
}

void Dispatch::verifyRequestBodyIntegrity()
{
	if (request->headers().count("CONTENT_LENGTH") > 0)
	{
		int contentLength = stoi(request->headers()["CONTENT_LENGTH"]);
		std::string rawPost = request->rawPost();
		while (rawPost.length() < contentLength)
		{
			char *data = new char[maxPostSize];
			memset(data, '\0', maxPostSize);
			int bytesRead = 0;
			if ((bytesRead = recv(fileDescriptor, data, maxPostSize, 0)) < 0)
			{
				die();
			}

			rawPost += data;
		}

		if (rawPost.back() == '\n')
		{
			rawPost.erase(rawPost.size() - 1);
			if (rawPost.back() == '\r')
			{
				rawPost.erase(rawPost.size() - 1);
			}
		}

		request->rawPost(rawPost, this, true);
	}
}

void Dispatch::setClientIP()
{
	char s[INET6_ADDRSTRLEN];
	request->ip(
		inet_ntop(clientAddr->ss_family,
			get_in_addr((struct sockaddr *)clientAddr),
			s, sizeof s
		),
		this
	);
}

bool Dispatch::validateRequest()
{
	if (request->method() == "UNDEFINED")
	{
		response.renderFalse();
		return false;
	}

	return true;
}

void Dispatch::serve()
{
	if (debugLevel < WARN)
	{
		printf("INFO: New connection for %s from %s\n",
			request->uri().c_str(),
			request->ip().c_str()
		);
	}

	response.write("<html><head><title>Himanshu's HTTP Server</title></head><body><h2>It Works!</h2></body></html>");

	close();
}

void Dispatch::close()
{
	request->close(this);
	response.end();

	::close(fileDescriptor);
}