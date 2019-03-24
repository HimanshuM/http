#include <vector>
#include <iostream>
#include <cstring>

#include "request_parser.hpp"
#include "request.hpp"
#include "string.hpp"

using namespace std;

Request RequestParser::parse(string data)
{
	Request req;
	vector<string> tokens = split(data, "\r\n");
	if (tokens.size() == 0)
	{
		return req;
	}

	vector<string> requestType = split(tokens[0]);
	if (requestType.size() != 3)
	{
		return req;
	}
	req.method = requestType[0];
	req.uri = requestType[1];
	req.httpVersion = requestType[2].substr(requestType[2].find("HTTP/") + strlen("HTTP/"));

	int i = 1;
	while (tokens[i] != "")
	{
		// vector<string> header = split(tokens[i], ":");
		string header = tokens[i];
		string key = header.substr(0, header.find(":"));
		string value = header.substr(key.length() + 1);

		// key = key.substr(0, key.find(":"));
		key = replace_all(key, "-", "_");
		key = toUppercase(key);
		req.headers[key] = trim(value);

		i++;
	}

	return req;
}
