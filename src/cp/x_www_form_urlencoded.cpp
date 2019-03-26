#include <string>
#include <unordered_map>
#include <vector>

#include "cp/x_www_form_urlencoded.hpp"
#include "content_parsers.hpp"
#include "string.hpp"

void XWwwFormUrlEncoded::registerSelf()
{
	ContentParsers::registerContentParser("application/x-www-form-urlencoded", this);
}

std::unordered_map<std::string, std::any> *XWwwFormUrlEncoded::parse(std::string rawPost)
{
	std::unordered_map<std::string, std::any> *post = new std::unordered_map<std::string, std::any>();

	std::vector<std::string> tokens = split(rawPost, "&");
	for (std::vector<std::string>::iterator it = tokens.begin(); it != tokens.end(); ++it)
	{
		std::vector<std::string> pair = split(*it, "=");
		(*post)[pair[0]] = pair[1];
	}

	return post;
}