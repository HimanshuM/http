#include "request.hpp"
#include "i_content_parser.hpp"
#include "non_content_parser.hpp"

using namespace std;

Request::Request(IRequestFriend *requestFriend)
{
	_requestFriend = requestFriend;
	reset();
}

void Request::registerContentParser(string contentType, IContentParser *parser)
{
	_contentParsers[contentType] = parser;
}

bool Request::isCallerAuthorized(IRequestFriend *caller)
{
	return caller == _requestFriend;
}

string Request::method()
{
	return _method;
}

void Request::method(string method, IRequestFriend *caller)
{
	if (!isCallerAuthorized(caller))
	{
		return;
	}

	_method = method;
}

string Request::uri()
{
	return _uri;
}

void Request::uri(string uri, IRequestFriend *caller)
{
	if (!isCallerAuthorized(caller))
	{
		return;
	}

	_uri = uri;
}

string Request::httpVersion()
{
	return _httpVersion;
}

void Request::httpVersion(string httpVersion, IRequestFriend *caller)
{
	if (!isCallerAuthorized(caller))
	{
		return;
	}

	_httpVersion = httpVersion;
}

string Request::ip()
{
	return _ip;
}

void Request::ip(string ip, IRequestFriend *caller)
{
	if (!isCallerAuthorized(caller))
	{
		return;
	}

	_ip = ip;
}

string Request::rawPost()
{
	return _rawPost;
}

void Request::rawPost(string rawPost, IRequestFriend *caller)
{
	if (!isCallerAuthorized(caller))
	{
		return;
	}

	_rawPost = rawPost;
}

unordered_map<string, string> Request::headers()
{
	return _headers;
}

void Request::addHeader(string key, string value, IRequestFriend *caller)
{
	if (!isCallerAuthorized(caller))
	{
		return;
	}

	_headers[key] = value;
}

void Request::changeFriend(IRequestFriend *newFriend, IRequestFriend *caller)
{
	if (!isCallerAuthorized(caller))
	{
		return;
	}

	_requestFriend = newFriend;
}


void Request::parseRawPost()
{
	if (_rawPost.length() == 0)
	{
		return;
	}

	IContentParser *contentParser = getContentParser();
	post = contentParser->parse(_rawPost);
}

void Request::close(IRequestFriend *caller)
{
	if (isCallerAuthorized(caller))
	{
		reset();
	}
}

void Request::reset()
{
	_method = "UNDEFINED";
	_uri = "/";
	_httpVersion = "0";
	_ip = "0.0.0.0";
	_rawPost = "";
	_headers.clear();
	_contentParsers.clear();
}

IContentParser *Request::getContentParser()
{
	auto it = _contentParsers.begin();
	while (it != _contentParsers.end())
	{
		if (_headers["CONTENT_TYPE"].find(it->first))
		{
			return it->second;
		}
		it++;
	}

	return new NonContentParser;
}