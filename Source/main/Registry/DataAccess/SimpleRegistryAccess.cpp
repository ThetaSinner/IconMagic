#include "./SimpleRegistryAccess.hpp"

#include <Windows.h>

#include "./../Common/KeyService.hpp"
#include "./DirectRegistryAccess.hpp"

std::string SimpleRegistryAccess::getValueAtPath(KeyPath key_path, std::string value_name)
{
  if (!key_path.getPathLength()) return "";

  std::string rootKeyName = key_path.getKeyName(0);
  HKEY keyHandle = KeyService::getkeyByName(rootKeyName);

  for (int i = 1; i < key_path.getPathLength(); i++)
  {
    DirectRegistryAccess::openKeyForEnumeration(keyHandle, key_path.getKeyName(i), keyHandle);
  }

  std::string value = "";
  DirectRegistryAccess::getValueFromKey(keyHandle, value_name, &value);
  return value;
}

std::string SimpleRegistryAccess::getValueAtPath(KeyPath key_path)
{
  return SimpleRegistryAccess::getValueAtPath(key_path, "");
}
