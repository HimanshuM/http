#ifndef HTTP__REQUEST__
#define HTTP__REQUEST__

#include <string>
#include <unordered_map>
#include <any>

#include "i_content_parser.hpp"
#include "i_request_friend.hpp"
#include "property.hpp"

class Request
{
public:
	Request(IRequestFriend *requestFriend);
	void close(IRequestFriend *caller);

	std::string method();
	void method(std::string method, IRequestFriend *caller);

	std::string uri();
	void uri(std::string uri, IRequestFriend *caller);

	std::string httpVersion();
	void httpVersion(std::string httpVersion, IRequestFriend *caller);

	std::string ip();
	void ip(std::string ip, IRequestFriend *caller);

	std::string rawPost();
	void rawPost(std::string rawPost, IRequestFriend *caller, bool parseNow = false);

	std::unordered_map<std::string, std::string> headers();
	void addHeader(std::string key, std::string value, IRequestFriend *caller);

	void changeFriend(IRequestFriend *newFriend, IRequestFriend *caller);

	std::unordered_map<std::string, std::any> *post;

protected:
	void parseRawPost();

	bool isCallerAuthorized(IRequestFriend *caller);

	std::string _method;
	std::string _uri;
	std::string _httpVersion;
	std::string _ip;
	std::string _rawPost;
	std::unordered_map<std::string, std::string> _headers;

	IRequestFriend *_requestFriend;

private:
	void reset();
};

#endif
