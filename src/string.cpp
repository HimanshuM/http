#include <vector>
#include <algorithm>
#include <cctype>
#include <cstring>

#include "string.hpp"

std::vector<std::string> split(std::string s, std::string delim)
{
	std::vector<std::string> v;
	size_t current = 0, previous = 0;
	current = s.find(delim);
	while (current != std::string::npos) {
		v.push_back(s.substr(previous, current - previous));
		previous = current + delim.length();
		current = s.find(delim, previous);
	}
	v.push_back(s.substr(previous, current - previous));

	return v;
}

std::string toLowercase(std::string s)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

std::string toUppercase(std::string s)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}

std::string replace_all(std::string s, std::string pattern, std::string replacer)
{
	size_t i;
	while ((i = s.find(pattern)) != std::string::npos)
	{
		s.replace(i, pattern.length(), replacer);
	}

	return s;
}

std::string ltrim(std::string s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
	return s;
}

std::string rtrim(std::string s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

std::string trim(std::string s)
{
	s = ltrim(s);
	return rtrim(s);
}