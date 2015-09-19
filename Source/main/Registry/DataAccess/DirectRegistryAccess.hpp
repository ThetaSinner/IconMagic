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

  static void closeKey(HKEY &h_key);
};

#endif
