#ifndef HTTP__RESPONSE__
#define HTTP__RESPONSE__

#include <string>
#include <unordered_map>

class Response
{
public:
	void setFileDescriptor(int);
	void setHeader(std::string, std::string);
	void setStatus(int);
	void write(std::string);
	void end();
	void renderFalse();

protected:
	void respond();
	void writeHeaders();
	std::string sanitizeHeaderKey(std::string);

	int fileDescriptor = -1;
	bool responded = false;

	std::string status = "200";
	std::unordered_map<std::string, std::string> headers;
	std::string response;
	std::string data = "";
};

#endif