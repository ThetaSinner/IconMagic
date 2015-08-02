/** \file
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * // TODO file_desc
 */

#ifndef SYSTEMVALIDATION_HPP_INCLUDED
#define SYSTEMVALIDATION_HPP_INCLUDED

#include <Windows.h>
#include <string>

#include "WindowsToolbox.hpp"
#include "TextUI.hpp"

bool verifyWindowsVersionSupported();
bool verifyWindowsVersionSupportedWithUserInteraction();

bool verifyProgramHasRegistryAccess();
bool verifyProgramHasRegistryAccessWithUserInteraction();

#endif // SYSTEMVALIDATION_HPP_INCLUDED

// TODO add comments to source.
