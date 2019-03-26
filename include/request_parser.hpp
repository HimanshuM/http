#ifndef HTTP__REQUEST_PARSER__
#define HTTP__REQUEST_PARSER__

#include "i_request_friend.hpp"
#include "request.hpp"
#include "string.hpp"
#include "dispatch.hpp"

class RequestParser : public IRequestFriend
{
public:
	Request *parse(std::string, Dispatch *obj);
private:
	// static void constructHeaders(Request *req, )
};

#endif