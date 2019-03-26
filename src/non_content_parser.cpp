#include "non_content_parser.hpp"
#include "content_parsers.hpp"

void NonContentParser::registerSelf()
{
	ContentParsers::registerContentParser("*/*", this);
}

unordered_map<string, any> *NonContentParser::parse(string rawPost)
{
	return new unordered_map<string, any>();
}