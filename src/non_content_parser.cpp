#include "non_content_parser.hpp"
#include "content_parsers.hpp"

void NonContentParser::registerSelf()
{
	ContentParsers::registerContentParser("*/*", this);
}

std::unordered_map<std::string, std::any> *NonContentParser::parse(std::string rawPost)
{
	return new std::unordered_map<std::string, std::any>();
}