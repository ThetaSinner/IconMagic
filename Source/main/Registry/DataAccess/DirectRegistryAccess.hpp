/**
 * \file DirectRegistryAccess.hpp
 * \brief The DirectRegistryAccess class definition.
 * \sa DirectRegistryAccess.cpp
 */

#ifndef DIRECT_REGISTRY_ACCESS_INCLUDED
#define DIRECT_REGISTRY_ACCESS_INCLUDED

#include <Windows.h>
#include "./RegistryAccessException.hpp"

/** \class DirectRegistryAccess
 * \brief Wrapper for Windows API registry access.
 *
 * All the Windows API functions which are related to registry access are wrapped
 * here. There isn't much need to expose the Windows API calls, most of the parameters
 * to real calls can take their default values.
 *
 * \sa SimpleRegistryAccess
 */
class DirectRegistryAccess
{
  public:
  /// Open a key for reading.
  /**
   * The key handle you get back allows for reading and for accessing child keys.
   *
   * \param root_key An open handle to a key.
   * \param path The name of the child key to open.
   * \param h_key Handle to the child key to be opened.
   *
   * \return Depending on the success or failure of the Windows API call.
   */
  static bool openKeyForEnumeration(HKEY root_key, std::string path, HKEY &h_key);

  /// Shortcut.
  /**
   * Calls DirectRegistryAccess::openKeyForEnumeration(HKEY, std::string, HKEY&) with
   * an empty string as the second parameter.
   *
   * \sa DirectRegistryAccess::openKeyForEnumeration(HKEY, std::string, HKEY&)
   */
  static bool openKeyForEnumeration(HKEY root_key, HKEY &h_key);

  /// Open a registry key for writing.
  /**
   * Open a key with the write flag. This method always returns true for valid inputs,
   * however you only get access to the real registry if the program is running
   * with administrator privileges.
   *
   * See [registry virtualisation](https://msdn.microsoft.com/en-us/library/windows/desktop/aa965884%28v=vs.85%29.aspx)
   *
   * \param root_key An open handle to a key.
   * \param path The name of the child key to open.
   * \param h_key Handle to the child key to be opened.
   *
   * \return Depending on the success or failure of the Windows API call.
   */
  static bool openKeyForSettingValue(HKEY root_key, std::string path, HKEY &h_key);

  /// Iterate over subkeys.
  /**
   * Given a key handle opened with the enumerate flag, we can fetch the name of
   * each child key name.
   *
   * If you use an index greater than the number of children a key has then the
   * Windows API returns the the last key name it finds. My method will give back
   * en empty string in this case. This is not a failure case, the method will
   * continue to return true.
   *
   * \param root_key A handle to a key opened with the enumerate flag.
   * \param n The index of the child key to access.
   * \param key_name The name of the child key at index n will be set on this value.
   *
   * \return Depending on the success or failure of the Windows API call.
   *
   * \todo You can determine the buffer size required at runtime, see RegQueryInfoKey.
   */
  static bool getSubKeyNameAt(const HKEY &root_key, int n, std::string &key_name);

  /// Get the value with the specified name from a key.
  /**
   * Fetch the value with the specified name from the the key handle which must be
   * opened with a read flag.
   *
   * \param h_key Handle to an open key.
   * \param search_value_name The name of the value to retrieve.
   * \param value The retrieved value will be set on this parameter.
   *
   * \return Depending on the success or failure of the Windows API call.
   *
   * \todo This method only supports string output, you can determine the type
   * by querying the registry.
   *
   * \todo The output parameter should be pass by reference rather than a pointer.
   *
   * \todo You can determine the buffer size required at runtime, see RegQueryInfoKey.
   */
  static bool getValueFromKey(HKEY &h_key, std::string search_value_name, std::string *value);

  /// Shortcut
  /**
   * This shortcut calls DirectRegistryAccess::getValueFromKey(HKEY&, std::string, std::string*)
   * with an empty string as the second parameter. This tells the Windows API to fetch
   * the 'default' value from the input key.
   *
   * \sa DirectRegistryAccess::getValueFromKey(HKEY&, std::string, std::string*)
   */
  static bool getValueFromKey(HKEY &h_key, std::string *value);

  /// Set the value with the specified name on the input key.
  /**
   * Given a key handle opened with some write flag, this method sets 'value' at
   * the location 'value_name'.
   *
   * This method requires administrator privileges to work. It will return true if
   * it succeeds, but will be accessing the virtualised registry when it has standard
   * permissions.
   *
   * \param h_key A key handle opened with some write flag.
   * \param value_name The name of the value to modify.
   * \param value The value to set.
   *
   * \return Depending on the success or failure of the Windows API call.
   */
  static bool setValueForKey(HKEY &h_key, std::string value_name, std::string value);

  /// Shortcut
  /**
   * Set the default value for on the input key.
   *
   * \sa DirectRegistryAccess::etValueForKey(HKEY&, std::string, std::string)
   */
  static bool setValueForKey(HKEY &h_key, std::string value);

  /// Close the key handle.
  /**
   * This should always the used to release open key handles, regardless of the
   * flag used to open them.
   *
   * The Windows API doesn't reliably report the success or otherwise of this method
   * so this method returns void.
   *
   * \param h_key Handle to the key to be closed.
   */
  static void closeKey(HKEY &h_key);
};

#endif
