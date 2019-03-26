#ifndef HTTP__STRING__
#define HTTP__STRING__

#include <string>
#include <vector>

std::vector<std::string> split(std::string s, std::string delim = " ");

std::string toLowercase(std::string s);
std::string toUppercase(std::string s);
std::string replace_all(std::string s, std::string pattern, std::string replacer);
std::string ltrim(std::string s);
std::string rtrim(std::string s);
std::string trim(std::string s);

#endif
