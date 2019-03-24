#include <vector>
#include <algorithm>
#include <cctype>
#include <cstring>

#include "string.hpp"

using namespace std;

vector<string> split(string s, string delim /*= " "*/)
{
	vector<string> v;
	size_t current = 0, previous = 0;
	current = s.find(delim);
	while (current != string::npos) {
		v.push_back(s.substr(previous, current - previous));
		previous = current + delim.length();
		current = s.find(delim, previous);
	}
	v.push_back(s.substr(previous, current - previous));

	return v;
}

string toLowercase(string s)
{
	transform(s.begin(), s.end(), s.begin(), ::tolower);
	return s;
}

string toUppercase(string s)
{
	transform(s.begin(), s.end(), s.begin(), ::toupper);
	return s;
}

string replace_all(string s, string pattern, string replacer)
{
	size_t i;
	while ((i = s.find(pattern)) != string::npos)
	{
		s.replace(i, pattern.length(), replacer);
	}

	return s;
}

string ltrim(string s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);}));
	return s;
}

string rtrim(string s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
    return s;
}

string trim(string s)
{
	s = ltrim(s);
	return rtrim(s);
}