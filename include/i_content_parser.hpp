#ifndef HTTP__I_CONTENT_PARSER__
#define HTTP__I_CONTENT_PARSER__

#include <unordered_map>
#include <any>
#include <string>

class IContentParser
{
public:
	virtual ~IContentParser() {}
	virtual void registerSelf() = 0;
	virtual std::unordered_map<std::string, std::any> *parse(std::string) = 0;
};

#endif