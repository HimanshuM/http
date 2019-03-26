#ifndef HTTP__DISPATCH__
#define HTTP__DISPATCH__

#include "i_request_friend.hpp"
#include "request.hpp"
#include "response.hpp"
#include "debug_levels.hpp"

class Dispatch : public IRequestFriend
{
public:
	Dispatch(DebugLevels dl, int fd, struct sockaddr_storage *ca, int mps) : debugLevel{dl}, fileDescriptor{fd}, clientAddr{ca}, maxPostSize{mps} {};
	void operator()();

protected:
	void read();
	void prepareObjects(char*);
	void verifyRequestBodyIntegrity();
	void setClientIP();
	bool validateRequest();
	void serve();
	void close();

	DebugLevels debugLevel;
	int fileDescriptor;
	struct sockaddr_storage *clientAddr;
	int maxPostSize = 512;
	Request *request;
	Response response;

};

#endif