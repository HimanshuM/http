#include <vector>
#include <algorithm>
#include <cctype>
#include <cstring>

#include "string.hpp"

using namespace std;

vector<string> split(string s, string delim /*= " "*/)
{
	vector<string> v;
	size_t current, previous = 0;
    current = s.find(delim);
    while (current != string::npos) {
        v.push_back(s.substr(previous, current - previous));
        previous = current + 1;
        current = s.find(delim, previous);
    }
    v.push_back(s.substr(previous, current - previous));

    return v;
}

string toLowercase(string s)
{
    string newS(s);
    transform(newS.begin(), newS.end(), newS.begin(), ::tolower);

    return newS;
}

string toUppercase(string s)
{
    string newS(s);
    transform(newS.begin(), newS.end(), newS.begin(), ::toupper);

    return newS;
}

string replace_all(string s, string pattern, string replacer)
{
    string newS(s);
    size_t i;
    while ((i = newS.find(pattern)) != string::npos)
    {
        newS.replace(i, pattern.length(), replacer);
    }

    return newS;
}

string replace_all(string s, char* pattern, char* replacer)
{
    string newS(s);
    size_t i;
    while ((i = s.find(pattern)) != string::npos)
    {
        newS.replace(i, strlen(pattern), replacer);
    }

    return newS;
}