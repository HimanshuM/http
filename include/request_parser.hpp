#ifndef HTTP__REQUEST_PARSER__
#define HTTP__REQUEST_PARSER__

#include "request.hpp"
#include "string.hpp"

class RequestParser
{
public:
	static Request parse(std::string);
private:
	// static void constructHeaders(Request *req, )
};

#endif