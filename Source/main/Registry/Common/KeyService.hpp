#ifndef KEY_SERVICE_INCLUDED
#define KEY_SERVICE_INCLUDED

#include <Windows.h>

#include <string>
#include <map>

class KeyService
{
  public:

  static const std::map<std::string, std::string> ALTERNATE_KEY_NAME_MAP;
  static const std::map<std::string, HKEY> PREDEFINED_ROOT_KEYS;

  static std::string resolveName(std::string name);
  static HKEY getkeyByName(std::string name);

  static HKEY getKeyByAnyName(std::string name);
};

#endif
