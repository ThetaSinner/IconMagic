/**
 * \file SimpleRegistryAccess.hpp
 * \brief The SimpleRegistryAccess class definition.
 * \sa SimpleRegistryAccess.cpp
 */

#ifndef SIMPLE_REGISTRY_ACCESS_INCLUDED
#define SIMPLE_REGISTRY_ACCESS_INCLUDED

#include <string>

#include "./../Common/KeyPath.hpp"
#include "./DirectRegistryAccess.hpp"

/** \class SimpleRegistryAccess
 * \brief Extends the functionality of DirectRegistryAccess
 *
 * The methods here aren't single Windows API calls, they contain the composition
 * of calls into DirectRegistryAccess.
 *
 * \sa DirectRegistryAccess
 */
class SimpleRegistryAccess : private DirectRegistryAccess
{
public:
  /// Get the value at the end of the given path.
  /**
   * Givem a KeyPath object, this method will open its way to the last key in the
   * path and find the value with the specified name.
   *
   * \param key_path Path to the key to fetch the value from.
   * \param value_name The name of the value to fetch.
   *
   * \todo This method only supports fetching string values.
   */
  static std::string getValueAtPath(KeyPath key_path, std::string value_name);

  /// Get the default value at the end of the given path.
  /**
   * Calls SimpleRegistryAccess::getValueAtPath(KeyPath, std::string) with an emtpy
   * string as the second parameter.
   *
   * \sa SimpleRegistryAccess::getValueAtPath(KeyPath, std::string)
   */
  static std::string getValueAtPath(KeyPath key_path);

  /// Set the specified value at the end of the given path.
  /**
   * Givem a KeyPath object, this method will open its way to the last key in the
   * path and set the specified value.
   *
   * \param key_path The path to the key to open.
   * \param value_name The name of the value to set.
   * \param value The value to set.
   *
   * \return The success of the operation, probably not very helpful.
   *
   * \sa DirectRegistryAccess::setValueForKey(HKEY &, std::string, std::string);
   */
  static bool setValueAtPath(KeyPath key_path, std::string value_name, std::string value);

  /// Set the default value at the end of the given path.
  /**
   * Calls SimpleRegistryAccess::setValueAtPath(KeyPath, std::string, std::string) with an emtpy
   * string as the second parameter.
   *
   * \sa SimpleRegistryAccess::setValueAtPath(KeyPath, std::string)
   */
  static bool setValueAtPath(KeyPath key_path, std::string value);
};

#endif
