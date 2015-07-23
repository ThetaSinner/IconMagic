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

void systemClearScreen()
{
    system("cls");
}

/*MessageBox(
    NULL,
    _T("Error while creating the file"),
    _T("Registry export"),
    MB_OK
);*/
