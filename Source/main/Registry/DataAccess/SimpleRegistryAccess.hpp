#ifndef SIMPLE_REGISTRY_ACCESS_INCLUDED
#define SIMPLE_REGISTRY_ACCESS_INCLUDED

#include <string>

#include "./../Common/KeyPath.hpp"

class SimpleRegistryAccess
{
public:
  static std::string getValueAtPath(KeyPath key_path, std::string value_name);
  static std::string getValueAtPath(KeyPath key_path);
};

#endif
