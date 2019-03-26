#include "non_content_parser.hpp"

unordered_map<string, any> *NonContentParser::parse(string rawPost)
{
	return new unordered_map<string, any>();
}