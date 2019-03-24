#ifndef HTTP__DISPATCH__
#define HTTP__DISPATCH__

#include <string>

#include "request.hpp"
#include "response.hpp"
#include "debug_levels.hpp"

class Dispatch {
public:
	Dispatch(DebugLevels dl, int fd, struct sockaddr_storage *ca, int mps) : debugLevel{dl}, fileDescriptor{fd}, clientAddr{ca}, maxPostSize{mps} {};
	void operator()();

protected:
	void read();
	void prepareObjects(char*);
	void setClientIP();
	bool validateRequest();
	void serve();

	DebugLevels debugLevel;
	int fileDescriptor;
	struct sockaddr_storage *clientAddr;
	int maxPostSize = 512;
	Request request;
	Response response;

};

#endif