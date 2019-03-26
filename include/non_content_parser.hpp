#ifndef HTTP__NON_CONTENT_PARSER__
#define HTTP__NON_CONTENT_PARSER__

#include <unordered_map>

#include "i_content_parser.hpp"

using namespace std;

class NonContentParser : public IContentParser
{
public:
	unordered_map<string, any> *parse(string rawPost);
};

#endif