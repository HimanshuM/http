#include <string>
#include <unordered_map>
#include <vector>

#include "cp/x_www_form_urlencoded.hpp"
#include "content_parsers.hpp"
#include "string.hpp"

using namespace std;

void XWwwFormUrlEncoded::registerSelf()
{
	ContentParsers::registerContentParser("application/x-www-form-urlencoded", this);
}

unordered_map<string, any> *XWwwFormUrlEncoded::parse(string rawPost)
{
	unordered_map<string, any> *post = new unordered_map<string, any>();

	vector<string> tokens = split(rawPost, "&");
	for (std::vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		vector<string> pair = split(*it, "=");
		(*post)[pair[0]] = pair[1];
	}

	return post;
}