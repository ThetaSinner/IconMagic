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

windowsVersionSupportStatusType testWindowsVersionSupported(bool printing)
{
    static const std::unordered_map<std::string, std::string> versionLookupMap ({
        {"5.0", "[Windows 2000]"},
        {"5.1", "[Windows XP]"},
        {"5.2", "[Windows XP 64-bit Edition]/[Windows Server 2003]/[Windows Server 2003 R2]"},
        {"6.0", "[Windows Vista]/[Windows Server 2008]"},
        {"6.1", "[Windows Server 2008 R2]/[Windows 7]"},
        {"6.2", "[Windows Server 2012]/[Windows 8]"}
    });

    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    if (GetVersionEx(&osvi) == 0) {
        if (printing) std::cout << "Can't detect your operating system version.\n"
                                << "Reason - " << getLastWindowsErrorMessage() << std::endl;

        return windowsVersionSupportStatusType::UNABLE_TO_DETECT;
    }

    std::stringstream versionConvert;
    std::string versionString;
    versionConvert << osvi.dwMajorVersion << "." << osvi.dwMinorVersion;
    versionConvert >> versionString;

    for (auto i : versionLookupMap)
    {
        if (i.first == versionString)
        {
            if (printing) std::cout << "Your Windows version was detected as : " << i.second << "\n" << std::endl;
        }
    }

    /**
     * GetVersionEx depreciated from this version of windows onwards.
     */
    if (osvi.dwMajorVersion < 6)
    {
        if (printing) std::cout << "Your Windows version is outdated, IconMagic CANNOT guarantee compatibility.\n\n";
        return windowsVersionSupportStatusType::DETECTED_OUTDATED;
    }
    if ((osvi.dwMajorVersion == 6 && osvi.dwMinorVersion >= 2) || osvi.dwMajorVersion > 6)
    {
        if (printing) std::cout << "Your version of Windows is quite new. IconMagic CANNOT guarantee that it is \ncompatible with your operating system.\n"
                                << "You may ignore this warning if you are running Windows 8 or Windows 8.1.\n\n";

        return windowsVersionSupportStatusType::DETECTED_FUTURE_DATED;
    }

    return windowsVersionSupportStatusType::SUPPORTED;
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

/*MessageBox(
    NULL,
    _T("Error while creating the file"),
    _T("Registry export"),
    MB_OK
);*/

std::list<std::string> listSubKeys(const HKEY rootKey)
{
    std::list<std::string> subKeyList;

    DWORD subKeyState = ERROR_SUCCESS;
    DWORD subKeyAccessIndex = 0;

    while (subKeyState == ERROR_SUCCESS)
    {
        DWORD bufferSize = 500; // you can determine this dynamically - RegQueryInfoKey
        char buffer[(int) bufferSize];

        subKeyState = RegEnumKeyEx(
            rootKey,
            subKeyAccessIndex,
            buffer,
            &bufferSize,
            0,
            NULL,
            NULL,
            NULL
        );

        subKeyList.push_back(std::string(buffer));

        subKeyAccessIndex++;
    }

    if (subKeyState == ERROR_NO_MORE_ITEMS) {
        //std::cout << "Subkey enumeration enumeration successful.\n";
    }

    return subKeyList;
}

DWORD openKeyForEnumeration(HKEY rootKey, HKEY& hKey, std::string path = "")
{
    return RegOpenKeyEx(
        rootKey,
        LPTSTR (path.c_str()),
        0,
        KEY_READ | KEY_ENUMERATE_SUB_KEYS,
        &hKey
    );
}

bool scanRegistryForDefaultIcons()
{
    HKEY rootKey = NULL;
    DWORD rootKeyState = openKeyForEnumeration(HKEY_CLASSES_ROOT, rootKey);

    if (rootKeyState != ERROR_SUCCESS)
    {
        std::cout << "Failed to open HKEY_CLASSES_ROOT for searching.\n";
        RegCloseKey(rootKey);
        return false;
    }

    std::list<std::string> rootSubKeysList = listSubKeys(rootKey);

    /*
     * Look inside the sub keys for default icon keys.
     */
     std::list<std::string> rootSubKeysListFilteredByDefaultIcon;
    for (auto i : rootSubKeysList)
    {
        HKEY subKeyI = NULL;
        DWORD subKeyStateI = openKeyForEnumeration(rootKey, subKeyI, i);

        if (subKeyStateI != ERROR_SUCCESS)
        {
            std::cout << "Failed to open sub key " << i << " for enumeration";
            continue;
        }

        std::list<std::string> temp = listSubKeys(subKeyI);

        for (auto k : temp)
        {
            if (k == "DefaultIcon")
            {
                rootSubKeysListFilteredByDefaultIcon.push_back(i);
                break;
            }
        }
    }

    std::cout << "Found " << rootSubKeysList.size() << " keys.\n";
    std::cout << "Found " << rootSubKeysListFilteredByDefaultIcon.size() << " keys with DefaultIcon sub keys.\n";

    int stopAfter = 10;
    int counter = 0;
    for (auto i : rootSubKeysListFilteredByDefaultIcon)
    {
        std::cout << i << "\n";
        counter++;
        if (counter >= stopAfter) break;
    }

    std::ofstream out("out.txt", std::ofstream::out);
    for (auto i : rootSubKeysListFilteredByDefaultIcon)
    {
        out << i << "\n";
    }
    out.close();

    RegCloseKey(rootKey);

    std::cout << "\n\nDone.";

    return true;
}
