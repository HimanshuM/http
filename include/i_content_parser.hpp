#ifndef HTTP__I_CONTENT_PARSER__
#define HTTP__I_CONTENT_PARSER__

#include <unordered_map>
#include <any>
#include <string>

using namespace std;

class IContentParser
{
public:
	virtual ~IContentParser() {}
	virtual unordered_map<string, any> *parse(string) = 0;
};

#endif