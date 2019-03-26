#ifndef HTTP__CONTENT_PARSERS__
#define HTTP__CONTENT_PARSERS__

#include <string>
#include <unordered_map>

#include "i_content_parser.hpp"

class ContentParsers
{
public:
	static void registerContentParser(std::string contentType, IContentParser *parser);
	static IContentParser *getContentParser(std::string contentType);

protected:
	static std::unordered_map<std::string, IContentParser*> _contentParsers;
};

#endif