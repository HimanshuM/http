#ifndef HTTP__REQUEST__
#define HTTP__REQUEST__

#include <string>
#include <unordered_map>
#include <any>

#include "i_content_parser.hpp"
#include "i_request_friend.hpp"
#include "property.hpp"

using namespace std;

class Request
{
public:
	Request(IRequestFriend *requestFriend);
	void close(IRequestFriend *caller);

	string method();
	void method(string method, IRequestFriend *caller);

	string uri();
	void uri(string uri, IRequestFriend *caller);

	string httpVersion();
	void httpVersion(string httpVersion, IRequestFriend *caller);

	string ip();
	void ip(string ip, IRequestFriend *caller);

	string rawPost();
	void rawPost(string rawPost, IRequestFriend *caller, bool parseNow = false);

	unordered_map<string, string> headers();
	void addHeader(string key, string value, IRequestFriend *caller);

	void changeFriend(IRequestFriend *newFriend, IRequestFriend *caller);

	unordered_map<string, any> *post;

protected:
	void parseRawPost();

	bool isCallerAuthorized(IRequestFriend *caller);

	string _method;
	string _uri;
	string _httpVersion;
	string _ip;
	string _rawPost;
	unordered_map<string, string> _headers;

	IRequestFriend *_requestFriend;

private:
	void reset();
};

#endif
