/**
 * \file KeyService.hpp
 * \brief The KeyService class definition.
 * \sa KeyService.cpp
 */

#ifndef KEY_SERVICE_INCLUDED
#define KEY_SERVICE_INCLUDED

#include <Windows.h>
#include <string>
#include <map>

/** \class KeyService
 * \brief Provides a key lookup service.
 *
 * A simple way to get handles to registry root keys. You can lookup any by its
 * friendly name or full name.
 *
 * \sa KeyPath
 */
class KeyService
{
  public:
  /**
   * Maps between simple names and registry key names. For example
   *
   * \code ALTERNATE_KEY_NAME_MAP.at("classes_root") == "HKEY_CLASSES_ROOT" \endcode
   *
   * This is just a shortcut for use within the program.
   */
  static const std::map<std::string, std::string> ALTERNATE_KEY_NAME_MAP;

  /**
   * Maps between registry key names and the handles that are defined in the
   * Windows API.
   * This map is important, you can't access a registry key without its parent key.
   * This map contains all the keys which can be used as parent keys.
   */
  static const std::map<std::string, HKEY> PREDEFINED_ROOT_KEYS;

  /// Convert a valid name into a key for PREDEFINED_ROOT_KEYS
  /**
   * If the input is a key for ALTERNATE_KEY_NAME_MAP or a key for PREDEFINED_ROOT_KEYS
   * then the corresponding key for PREDEFINED_ROOT_KEYS will be returned.
   * If the input is not a valid key into either map then the method returns an
   * empty string.
   *
   * \param name A valid name for a key.
   *
   * \return Corresponding key name or an empty string.
   */
  static std::string resolveName(std::string name);

  /// Get a handle to a registry root key.
  /**
   * If the input is a valid key for PREDEFINED_ROOT_KEYS then a handle to a registry
   * root key will be returned. Otherwise the method will return NULL.
   *
   * \param name A valid key for PREDEFINED_ROOT_KEYS
   *
   * \return A handle to a registry key or NULL
   */
  static HKEY getkeyByName(std::string name);

  /// Get a handle to a registry key using any name for that key.
  /**
   * \sa KeyService::resolveName(std::string) KeyService::getkeyByName(std::string)
   */
  static HKEY getKeyByAnyName(std::string name);
};

#endif
