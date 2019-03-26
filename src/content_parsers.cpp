#include <string>

#include "content_parsers.hpp"
#include "non_content_parser.hpp"

std::unordered_map<std::string, IContentParser*> ContentParsers::_contentParsers;

void ContentParsers::registerContentParser(std::string contentType, IContentParser *parser)
{
	_contentParsers[contentType] = parser;
}

IContentParser *ContentParsers::getContentParser(std::string contentType)
{
	auto it = _contentParsers.begin();
	while (it != _contentParsers.end())
	{
		if (contentType.find(it->first) != std::string::npos)
		{
			return it->second;
		}
		it++;
	}

	return new NonContentParser;
}