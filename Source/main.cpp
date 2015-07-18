
//#include <Shlobj.h>
#include <iostream>
#include <string>

#include "WindowsToolbox.hpp"
#include "TextUI.hpp"

#include "Testing.hpp"

// Sources for DefaultIcon
// https://msdn.microsoft.com/en-us/library/windows/desktop/hh127427%28v=vs.85%29.aspx
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb762118%28v=vs.85%29.aspx

// Navigate to HKEY_CLASSES_ROOT
// Look for the file type you want to modify, e.g. .aiff, .mp3, .txt
// Then look for a DefaultIcon sub key. If you don't see one, you may have to go
// down the rabbit hole a little, for example with audio, the default value of the .aiff key is
// wmp11... search for this key, and that has a DefaultIcon sub key.

int main(int argc, char** args)
{
    setPrintFillerCharacter('-');

    printTitleBox("IconMagic");

    bool userMode = true;

    if (userMode)
    {
        bool printMessages = true;

        //printCentered(" Windows version check ", "-");
        //std::cout << rep("-", 80);
        windowsVersionSupportStatusType windowsVersionStatus = testWindowsVersionSupported(printMessages);

        if (windowsVersionStatus == windowsVersionSupportStatusType::UNABLE_TO_DETECT)
        {
            std::cout << "Press any key to finish";
            //std::cin.get();

            return 1;
        }
        else if (windowsVersionStatus == windowsVersionSupportStatusType::DETECTED_FUTURE_DATED ||
                 windowsVersionStatus == windowsVersionSupportStatusType::DETECTED_OUTDATED)
        {
            std::cout << "Would you like to continue anyway? (y/n) : ";
            char* buffer = new char[30];
            std::cin.getline(buffer, 30);

            if (std::string(buffer) != "y") {
                //std::cout << rep("-", 80);
                std::cout << "\nOkay. Press any key to finish";
                std::cin.get();

                return 0;
            }
        }
        //std::cout << rep("-", 80);

        std::cout << "\n";
        //printCentered(" Registry access check ", "-");
        //std::cout << rep("-", 80);

        if (!testProgramHasRegistryAccess(printMessages))
        {
            std::cout << "Press any key to finish";
            std::cin.get();

            return 1;
        }

        //std::cout << rep("-", 80);
    }

    if (!scanRegistryForDefaultIcons()) {
        std::cout << "Failed scanning registry.\n";
    }

    //SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL);

    std::cout << "\n\nDone. Press any key ";
    std::cin.get();

    return 0;
}


