#include "WindowsToolbox.hpp"

#include <Windows.h>

std::string getLastWindowsErrorMessage()
{
    char* message = NULL;

    FormatMessage(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER,
        NULL,
        GetLastError(),
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPTSTR) &message,
        0,
        NULL
    );

    std::string rMessage(message);
    LocalFree(message);

    return rMessage;
}

bool testProgramHasRegistryAccess(bool printing)
{
    HKEY dummyKey = NULL;

    LONG dummyKeyState = RegOpenKeyEx(HKEY_CLASSES_ROOT, "", 0, KEY_READ, &dummyKey);
    RegCloseKey(dummyKey);

    if (dummyKeyState == ERROR_SUCCESS)
    {
        if (printing) { std::cout << "Success. IconMagic has access to the registry." << std::endl; }
        return true;
    }
    else
    {
        if (printing) { std::cout << "Failure. IconMagic does NOT have access to the registry.\n" << "Reason - " << getLastWindowsErrorMessage() << std::endl; }
        return false;
    }
}
