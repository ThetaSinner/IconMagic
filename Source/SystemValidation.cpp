#include "SystemValidation.hpp"

std::string windowsVersion();
std::string windowsVersionToName(std::string);
bool registryAccess();


bool verifyWindowsVersionSupported()
{
    std::string windowsVersionAsString = windowsVersion();

    if (windowsVersionAsString == "6.1" || windowsVersionAsString == "6.2")
        return true;

    return false;
}

bool verifyWindowsVersionSupportedWithUserInteraction()
{
    std::string windowsVersionAsString = windowsVersion();

    std::cout
        << "Windows version detected as: "
        << windowsVersionToName(windowsVersionAsString) << std::endl;

    if (windowsVersionAsString == "")
    {
        std::cout
            << "Can't detect your operating system version.\n"
            << "Reason - " << getLastWindowsErrorMessage() << std::endl;

        return false;
    }
    else if (windowsVersionAsString == "6.1")
    {
        std::cout
            << "Your version of Windows is supported."
            << std::endl;

        return true;
    }
    else if (windowsVersionAsString == "6.2")
    {
        std::cout
            << "Your version of Windows is supported if the above line is correct."
            << std::endl;

        std::string yn = getInputYesNo("Would you like to continue?", true);
        if (yn == "y")
            return true;
        else
            return false;
    }
    else
    {
        std::cout
            << "It appears your version of Windows is not supported."
            << std::endl;

        return false;
    }
}


/**
 * GetVersionEx depreciated from this version of windows onwards.
 */
std::string windowsVersion()
{
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (GetVersionEx(&osvi) == 0)
    {
        return "";
    }

    std::stringstream versionConvert;
    versionConvert << osvi.dwMajorVersion << "." << osvi.dwMinorVersion;

    return versionConvert.str();
}

std::string windowsVersionToName(std::string versionString)
{
    const std::unordered_map<std::string, std::string> versionLookupMap ({
        {"5.0", "[Windows 2000]"},
        {"5.1", "[Windows XP]"},
        {"5.2", "[Windows XP 64-bit Edition]/[Windows Server 2003]/[Windows Server 2003 R2]"},
        {"6.0", "[Windows Vista]/[Windows Server 2008]"},
        {"6.1", "[Windows Server 2008 R2]/[Windows 7]"},
        {"6.2", "[Windows Server 2012]/[Windows 8]"}
    });

    for (auto i : versionLookupMap)
    {
        if (i.first == versionString)
        {
            return i.second;
        }
    }

    return "";
}





bool verifyProgramHasRegistryAccess()
{
    if (registryAccess())
        return true;
    else
        return false;
}

bool verifyProgramHasRegistryAccessWithUserInteraction()
{
    if (registryAccess())
    {
        std::cout
            << "Success. IconMagic has access to the registry."
            << std::endl;

        return true;
    }
    else
    {
        std::cout
            << "Failure. IconMagic does NOT have access to the registry.\n"
            << "Reason - " << getLastWindowsErrorMessage()
            << std::endl;

        return false;
    }
}

bool registryAccess()
{
    HKEY dummyKey = NULL;
    LONG dummyKeyState = RegOpenKeyEx(HKEY_CLASSES_ROOT, "", 0, KEY_READ, &dummyKey);
    RegCloseKey(dummyKey);

    if (dummyKeyState == WINDOWS_OPERATION_SUCCESS)
        return true;
    else
        return false;
}
