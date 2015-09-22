#ifndef DIRECT_REGISTRY_ACCESS_INCLUDED
#define DIRECT_REGISTRY_ACCESS_INCLUDED

#include <Windows.h>
#include "./RegistryAccessException.hpp"

class DirectRegistryAccess
{
  public:

  static void openKeyForEnumeration(HKEY root_key, std::string path, HKEY &h_key);
  static void openKeyForEnumeration(HKEY root_key, HKEY &h_key);

  static bool getSubKeyNameAt(const HKEY &root_key, int n, std::string &key_name);

  static bool getValueFromKey(HKEY &h_key, std::string search_value_name, std::string *key_value);
  static bool getValueFromKey(HKEY &h_key, std::string *key_value);

  static void closeKey(HKEY &h_key);
};

#endif
