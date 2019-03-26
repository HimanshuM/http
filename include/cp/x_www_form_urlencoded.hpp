#ifndef HTTP__X_WWW_FORM_URLENCODED__
#define HTTP__X_WWW_FORM_URLENCODED__

#include "i_content_parser.hpp"

class XWwwFormUrlEncoded : public IContentParser
{
public:
	void registerSelf();
	unordered_map<string, any> *parse(string);
};

#endif