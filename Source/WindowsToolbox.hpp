#ifndef WINDOWSTOOLBOX_HPP_INCLUDED
#define WINDOWSTOOLBOX_HPP_INCLUDED

#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <list>

std::string getLastWindowsErrorMessage();
void systemClearScreen();

bool scanRegistryForDefaultIcons();

#endif // WINDOWSTOOLBOX_HPP_INCLUDED
