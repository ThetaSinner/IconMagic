/** \file
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * // TODO file_desc
 */

#include "WindowsToolbox.hpp"

#include <Windows.h>

/** \fn
 * \brief A description of the last error that occurred in the Windows API.
 *
 * The Windows API only gives you a value when an error occurs.
 * This functions uses the FormatMessage function, also from the Windows API, to get the message associated with the error code.
 *
 * \return std::string
 *
 */
std::string getLastWindowsErrorMessage()
{
  char *message = NULL;
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

bool validPathToFile(std::string file_path)
{
  if (GetFileAttributes(file_path.c_str()) == INVALID_FILE_ATTRIBUTES)
  {
    return false;
  }

  return true;
}

bool canOpenFile(std::string file_path)
{
  std::ifstream test(file_path, std::ios::app);
  if (!test.is_open()) return false;

  return true;
}

/*MessageBox(
    NULL,
    _T("Error while creating the file"),
    _T("Registry export"),
    MB_OK
);*/
