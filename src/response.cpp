#include <unistd.h>
#include <cstdio>
#include <sys/socket.h>
#include <string>
#include <queue>
#include <cctype>

#include "response.hpp"
#include "string.hpp"

void Response::setFileDescriptor(int fd)
{
	if (fileDescriptor == -1)
	{
		fileDescriptor = fd;
	}
}

void Response::setHeader(std::string name, std::string value)
{
	name = sanitizeHeaderKey(name);
	headers[name] = value;
}

void Response::setStatus(int status)
{
	this->status = std::to_string(status);
}

void Response::write(std::string response)
{
	data = response;
}

void Response::respond()
{
	response.append("HTTP/1.1 ").append(status).append("\r\n");
	writeHeaders();

	response.append("\r\n").append(data);

	send(fileDescriptor, response.c_str(), response.length() + 1, 0);

}

void Response::end()
{
	if (!responded)
	{
		respond();
	}

	response.clear();
	headers.clear();
	data.clear();

	if (close(fileDescriptor) < 0)
	{
		perror("CLOSE ERROR");
	}
}

void Response::renderFalse()
{
	setStatus(400);
	end();
}

void Response::writeHeaders()
{
	for ( auto it = headers.begin(); it != headers.end(); ++it )
    {
		std::string header = std::string(it->first);
		header.append(": ").append(it->second);
		response.append(header).append("\r\n");
	}

	if (headers.count("Content-Length") == 0)
	{
		std::string header("Content-Length: ");
		std::string size = std::to_string(data.size());
		header.append(size);
	}
}

std::string Response::sanitizeHeaderKey(std::string name)
{
	std::string newName("");
	std::vector<std::string> tokens = split(name, "-");
	for (int i = 0; i < tokens.size(); i++)
	{
		tokens[i] = toLowercase(tokens[i]);
		tokens[i][0] = toupper(tokens[i][0]);

		newName.append(tokens[i]);
		if (i < tokens.size() - 1)
		{
			newName.append("-");
		}
	}

	return newName;
}