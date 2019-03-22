#ifndef HTTP__REQUEST__
#define HTTP__REQUEST__

#include <string>
#include <unordered_map>

using namespace std;

class Request
{
public:
	Request();
	void close();

	string method = "UNDEFINED";
	string uri;
	unordered_map<string, string> headers;
};

#endif