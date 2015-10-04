/**
 * \file KeyPath.hpp
 * \brief The KeyPath class definition.
 * \sa KeyPath.cpp
 */

#ifndef KEY_PATH_INCLUDED
#define KEY_PATH_INCLUDED

#include <vector>
#include <string>

/** \class KeyPath
 * \brief Object representation of a registry path.
 *
 * The registry doesn't really support paths via the windows API, so the paths represented
 * by this class are really just a sequence of keys where the sequence relationship is parent-child.
 *
 * \sa KeyService
 */
class KeyPath
{
public:
  /// Default constructor.
  /**
   * The existence of this constructor forces every KeyPath to have a root key.
   * Since relative paths don't have a defined meaning this key should be one of
   * the registry root keys, i.e. of the form HKEY_xxx
   * \param key_name The name of the root key to use.
   *
   * * \sa KeyService::PREDEFINED_ROOT_KEYS, KeyService::ALTERNATE_KEY_NAME_MAP
   *
   * \todo This constructory should allow you to pass in a path, not just a single key.
   * i.e. it accepts the result of the toString method provided by this class.
   */
  KeyPath(std::string key_name);

  /// Copy constructor.
  /**
   * \sa ScanTool
   */
  KeyPath(const KeyPath& kp);

  /// Append a key name to the path.
  /**
   * This method can be chained to construct a complete path in a single statement.
   *
   * \param key_name The name of the key to be added to the path.
   *
   * \return A reference to the current object.
   */
  KeyPath& append(std::string key_name);

  /// Get the length of the path.
  /**
   * Returns the number of keys present in the path. This value should always be
   * at least 1.
   *
   * \return The length of the path.
   *
   * \sa KeyPath::KeyPath(std::string)
   */
  int getPathLength();

  /// Get the name of a key in the path.
  /**
   * Returns the key name at the specified index along the path. The first item
   * in the path is at index 0.
   *
   * \param index Index of the key to return.
   *
   * \return The key name if the index is valid, empty string otherwise.
   */
  std::string getKeyName(int index);

  /// Get a string representation of the path.
  /**
   * The key names are combined into a single string separated by the forward
   * slash character.
   *
   * \return String representation of the path.
   */
  std::string toString();

private:
  /// Internal representation of the path.
  /**
   * Collection of strings, each of which is a key name on the path. The collection
   * maintains the order of the key names.
   */
  std::vector<std::string> keyNames;
};

#endif
