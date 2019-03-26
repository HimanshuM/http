#ifndef HTTP__X_WWW_FORM_URLENCODED__
#define HTTP__X_WWW_FORM_URLENCODED__

#include "i_content_parser.hpp"

class XWwwFormUrlEncoded : public IContentParser
{
public:
	void registerSelf();
	std::unordered_map<std::string, std::any> *parse(std::string);
};

#endif