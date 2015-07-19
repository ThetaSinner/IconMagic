#ifndef WINDOWSTOOLBOX_HPP_INCLUDED
#define WINDOWSTOOLBOX_HPP_INCLUDED

#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <list>

std::string getLastWindowsErrorMessage();

enum class windowsVersionSupportStatusType {
    UNABLE_TO_DETECT,
    DETECTED_OUTDATED,
    DETECTED_FUTURE_DATED,
    SUPPORTED
};

windowsVersionSupportStatusType testWindowsVersionSupported(bool printing = false);
bool testProgramHasRegistryAccess(bool printing = false);

bool scanRegistryForDefaultIcons();

void systemClearScreen();

#endif // WINDOWSTOOLBOX_HPP_INCLUDED
