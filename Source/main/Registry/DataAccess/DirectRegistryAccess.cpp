#include "./DirectRegistryAccess.hpp"

#include <iostream>

bool DirectRegistryAccess::openKeyForEnumeration(HKEY root_key, std::string path, HKEY &h_key)
{
  DWORD status = RegOpenKeyEx(
    root_key,
    LPTSTR(path.c_str()),
    0,
    KEY_READ | KEY_ENUMERATE_SUB_KEYS,
    &h_key
  );

  return status == ERROR_SUCCESS;
}

bool DirectRegistryAccess::openKeyForEnumeration(HKEY root_key, HKEY &h_key)
{
  openKeyForEnumeration(root_key, "", h_key);
}

bool DirectRegistryAccess::openKeyForSettingValue(HKEY root_key, std::string path, HKEY &h_key)
{
  DWORD status = RegOpenKeyEx(
    root_key,
    LPSTR(path.c_str()),
    0,
    KEY_SET_VALUE,
    &h_key
  );

  return status == ERROR_SUCCESS;
}

bool DirectRegistryAccess::getSubKeyNameAt(const HKEY &root_key, int n, std::string &key_name)
{
  DWORD bufferSize = 5000; // TODO you can determine this dynamically - RegQueryInfoKey
  char buffer[(int) bufferSize];

  DWORD subKeyState = RegEnumKeyEx(
    root_key,
    n,
    buffer,
    &bufferSize,
    0,
    NULL,
    NULL,
    NULL
  );

  // The Windows API will return the last key it finds if you pass in an index greater than the number of keys.
  key_name = subKeyState == ERROR_NO_MORE_ITEMS ? "" : std::string(buffer);

  return subKeyState == ERROR_SUCCESS || subKeyState == ERROR_NO_MORE_ITEMS;
}

bool DirectRegistryAccess::getValueFromKey(HKEY &h_key, std::string search_value_name, std::string *value)
{
  DWORD bufferSize = 5000; // TODO config.
  char buffer[(int) bufferSize];

  DWORD valueState = RegQueryValueEx(
    h_key,
    search_value_name.c_str(),
    NULL,
    NULL,
    (LPBYTE) buffer,
    &bufferSize
  );

  *value = std::string(buffer);

  return valueState == ERROR_SUCCESS;
}

bool DirectRegistryAccess::getValueFromKey(HKEY &h_key, std::string *value)
{
  return getValueFromKey(h_key, "", value);
}

bool DirectRegistryAccess::setValueForKey(HKEY &h_key, std::string value_name, std::string value)
{
  DWORD valueState = RegSetValueEx(
    h_key,
    value_name.c_str(),
    0,
    REG_SZ,
    reinterpret_cast<const unsigned char*> (value.c_str()),
    value.size() + 1
  );

  return valueState == ERROR_SUCCESS;
}

bool DirectRegistryAccess::setValueForKey(HKEY &h_key, std::string value)
{
  return DirectRegistryAccess::setValueForKey(h_key, "", value);
}

void DirectRegistryAccess::closeKey(HKEY &h_key)
{
  RegCloseKey(h_key);
  h_key = NULL;
}
