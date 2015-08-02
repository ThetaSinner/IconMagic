/** \file
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * // TODO file_desc
 */


#ifndef WINDOWSTOOLBOX_HPP_INCLUDED
#define WINDOWSTOOLBOX_HPP_INCLUDED

#include <iostream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <fstream>
#include <list>

#define WINDOWS_OPERATION_SUCCESS ERROR_SUCCESS

std::string getLastWindowsErrorMessage();
void systemClearScreen();

bool scanRegistryForDefaultIcons();

#endif // WINDOWSTOOLBOX_HPP_INCLUDED
