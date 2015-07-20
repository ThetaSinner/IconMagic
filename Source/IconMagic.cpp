#include "IconMagic.hpp"

int exitIconMagic(int exitCode = 0);

int runIconMagic()
{
    setPrintFillerCharacter('-');

    printTitleBox("IconMagic");
    printNewLine();

    bool userInteraction = true;

    if (userInteraction)
    {
        if (!verifyWindowsVersionSupportedWithUserInteraction())
        {
            exitIconMagic();
        }
    }
    else
    {
        if (!verifyWindowsVersionSupported())
        {
            exitIconMagic();
        }
    }


    return exitIconMagic();
}

int exitIconMagic(int exitCode)
{
    std::cout
    << "Thank you for using IconMagic!\n\n"
    << "Press any key to finish";

    std::cin.get();

    return exitCode;
}
