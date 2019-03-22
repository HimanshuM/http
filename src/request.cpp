#include "request.hpp"

Request::Request()
{

}

void Request::close()
{
	method = "UNDEFINED";
	uri.clear();
	headers.clear();
}