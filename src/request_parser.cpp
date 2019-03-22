#include <vector>
#include <iostream>

#include "request_parser.hpp"
#include "request.hpp"
#include "string.hpp"

using namespace std;

Request RequestParser::parse(string data)
{
	Request req;
	vector<string> tokens = split(data, "\n");
	if (tokens.size() == 0)
	{
		return req;
	}

	vector<string> requestType = split(tokens[0]);
	req.method = requestType[0];
	req.uri = requestType[1];

	int i = 1;
	while (tokens[i] != "\r" && tokens[i] != "")
	{
		vector<string> header = split(tokens[i]);
		string key = header[0];
		string value = header[1];

		key = key.substr(0, key.find(":"));
		key = replace_all(key, "-", "_");
		req.headers[toUppercase(key)] = value.substr(0, value.find("\r"));

		i++;
	}

	return req;
}