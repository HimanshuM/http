#ifndef HTTP__RESPONSE__
#define HTTP__RESPONSE__

#include <string>
#include <unordered_map>

using namespace std;

class Response
{
public:
	void setFileDescriptor(int);
	void setHeader(string, string);
	void setStatus(int);
	void write(string);
	void end();
	void renderFalse();

protected:
	void respond();
	void writeHeaders();
	string sanitizeHeaderKey(string);

	int fileDescriptor = -1;
	bool responded = false;

	string status = "200";
	unordered_map<string, string> headers;
	string response;
	string data = "";
};

#endif