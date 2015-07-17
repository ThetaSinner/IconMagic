#include <Windows.h>
#include <Shlobj.h>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <Tchar.h>

// Sources for DefaultIcon
// https://msdn.microsoft.com/en-us/library/windows/desktop/hh127427%28v=vs.85%29.aspx
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb762118%28v=vs.85%29.aspx

// Navigate to HKEY_CLASSES_ROOT
// Look for the file type you want to modify, e.g. .aiff, .mp3, .txt
// Then look for a DefaultIcon sub key. If you don't see one, you may have to go
// down the rabbit hole a little, for example with audio, the default value of the .aiff key is
// wmp11... search for this key, and that has a DefaultIcon sub key.

const std::unordered_map<std::string, std::string> versionLookup ({
        {"5.0", "[Windows 2000]"},
        {"5.1", "[Windows XP]"},
        {"5.2", "[Windows XP 64-bit Edition]/[Windows Server 2003]/[Windows Server 2003 R2]"},
        {"6.0", "[Windows Vista]/[Windows Server 2008]"},
        {"6.1", "[Windows Server 2008 R2]/[Windows 7]"},
        {"6.2", "[Windows Server 2012]/[Windows 8]"}
        // Need to put a warning with windows 8, for can't detect higher versions.
        // My program won't find these. GetVersion depreciated, use new functionality (VCPP required).
    });

bool checkOS();

std::string rep(std::string str, int times)
{
    std::string temp = "";
    while (times > 0) {
        temp += str;
        times--;
    }

    return temp;
}

void printCenter(std::string str)
{
    const int CON_WIDTH = 80;

    int starCountL = (CON_WIDTH - str.length()) / 2 - 1;
    int starCountR = CON_WIDTH - str.length() - starCountL - 2;

    //if ((starCountL + 1 + str.length() + 1 + starCountR) != CON_WIDTH) {std::cout << "Your adding sux!\n";}

    if (starCountL < 1 || starCountR < 1) {
        std::cout << str;
    } else {
        std::cout << rep("*", starCountL) << " " << str << " " << rep("*", starCountR) << std::endl;
    }
}

void testReadRegistry()
{
    HKEY testKey = NULL;

    if (ERROR_SUCCESS == RegOpenKeyEx(
        HKEY_CLASSES_ROOT,
        ".aiff",
        0,
        KEY_READ,
        &testKey
    ) && false)
    {
        std::cout << "Opened key.";
    }
    else
    {
        std::cout << "Failed to open key.";

        char* msg = NULL;

        FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &msg,
            0,
            NULL
        );

        std::cout << "Reason - " << msg << std::endl;
    }

    RegCloseKey(testKey);
}

int main(int argc, char** args)
{
    std::cout << "Welcome to IconMagic.\n";

    checkOS();
    testReadRegistry();

    //SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);

    std::cout << "Done. Press any key ";
    std::cin.get();

    return 0;
}

bool checkOS()
{
    OSVERSIONINFO osvi;
    ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);

    GetVersionEx(&osvi);

    //std::cout << "Major version " << osvi.dwMajorVersion << std::endl;
    //std::cout << "Minor version " << osvi.dwMinorVersion << std::endl;

    std::stringstream versionConvert;
    versionConvert << osvi.dwMajorVersion;
    versionConvert << ".";
    versionConvert << osvi.dwMinorVersion;

    std::string versionString;
    versionConvert >> versionString;

    /*MessageBox(
        NULL,
        _T("Error while creating the file"),
        _T("Registry export"),
        MB_OK
    );*/

    /**
     * GetVersionEx depreciated from this version of windows onwards.
     */
    if (true || (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion >= 2) ||
        (osvi.dwMajorVersion > 6))
    {
        printCenter("WARNING");
        std::cout << "You're version of Windows is quite new. I CANNOT guarantee that I am able to correctly select compatible settings.";

    }
    for (auto i : versionLookup)
    {
        if (i.first == versionString)
        {
            std::cout << i.second << std::endl;
        }
    }

    return true;
}
