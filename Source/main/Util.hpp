#ifndef UTIL
#define UTIL

#include <string>

bool stringIsValidInteger(std::string str, int min = 0, int max = 0);
bool stringIsNotValidInteger(std::string str, int min = 0, int max = 0);

bool stringIsBlank(std::string str);
bool StringIsNotBlank(std::string str);

bool stringContains(std::string str, std::string c);
bool stringDoesNotContains(std::string str, std::string c);

#endif
