#ifndef HTTP__STRING__
#define HTTP__STRING__

#include <string>
#include <vector>

using namespace std;

vector<string> split(string s, string delim = " ");

string toLowercase(string s);
string toUppercase(string s);
string replace_all(string s, string pattern, string replacer);
string ltrim(string s);
string rtrim(string s);
string trim(string s);

#endif
