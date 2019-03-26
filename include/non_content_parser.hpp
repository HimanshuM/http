#ifndef HTTP__NON_CONTENT_PARSER__
#define HTTP__NON_CONTENT_PARSER__

#include <unordered_map>
#include <string>
#include <any>

#include "i_content_parser.hpp"

class NonContentParser : public IContentParser
{
public:
	void registerSelf();
	std::unordered_map<std::string, std::any> *parse(std::string);
};

#endif