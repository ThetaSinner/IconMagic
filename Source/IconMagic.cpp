#include "IconMagic.hpp"

int exitIconMagic(int exitCode = 0);

int runIconMagic()
{
    setPrintFillerCharacter('-');

    printTitleBox("IconMagic");
    printNewLine(2);
    printLine("IconMagic needs permission to:\n\n  1. Check compatibility with your version of Windows.\n  2. Read from and write to the registry.");
    printNewLine(2);
    printLine("If you continue you agree that you are solely responsible any problems that may arise.");
    printNewLine(2);
    bool userPermission = getInputYesNo("Would you like to continue?", true) == "y" ? true : false;

    if (!userPermission)
    {
        return exitIconMagic();
    }

    bool userInteraction = true;

    if (userInteraction)
    {
        if (!verifyWindowsVersionSupportedWithUserInteraction())
        {
            return exitIconMagic();
        }
    }
    else
    {
        if (!verifyWindowsVersionSupported())
        {
            return exitIconMagic();
        }
    }

    if (userInteraction)
    {
        if (!verifyProgramHasRegistryAccessWithUserInteraction())
        {
            return exitIconMagic();
        }
        else
        {
            return exitIconMagic();
        }
    }


    return exitIconMagic();
}

int exitIconMagic(int exitCode)
{
    systemClearScreen();

    std::cout
        << "Thank you for using IconMagic!\n\n"
        << "Press any key to finish"
        << std::endl;

    std::cin.ignore();

    return exitCode;
}
