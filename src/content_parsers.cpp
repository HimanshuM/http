#include <string>

#include "content_parsers.hpp"
#include "non_content_parser.hpp"

unordered_map<string, IContentParser*> ContentParsers::_contentParsers;

void ContentParsers::registerContentParser(string contentType, IContentParser *parser)
{
	_contentParsers[contentType] = parser;
}

IContentParser *ContentParsers::getContentParser(string contentType)
{
	auto it = _contentParsers.begin();
	while (it != _contentParsers.end())
	{
		if (contentType.find(it->first) != string::npos)
		{
			return it->second;
		}
		it++;
	}

	return new NonContentParser;
}