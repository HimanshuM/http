#ifndef HTTP__CONTENT_PARSERS__
#define HTTP__CONTENT_PARSERS__

#include <string>
#include <unordered_map>

#include "i_content_parser.hpp"

using namespace std;

class ContentParsers
{
public:
	static void registerContentParser(string contentType, IContentParser *parser);
	static IContentParser *getContentParser(string contentType);

protected:
	static unordered_map<string, IContentParser*> _contentParsers;
};

#endif