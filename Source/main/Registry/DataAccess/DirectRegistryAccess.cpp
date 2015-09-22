#include "./DirectRegistryAccess.hpp"

void DirectRegistryAccess::openKeyForEnumeration(HKEY root_key, std::string path, HKEY &h_key)
{
  DWORD status = RegOpenKeyEx(
    root_key,
    LPTSTR(path.c_str()),
    0,
    KEY_READ | KEY_ENUMERATE_SUB_KEYS,
    &h_key
  );

  if (status != ERROR_SUCCESS)
  {
    throw RegistryAccessException("Failed to open key for enumeration [path=" + path + "]");
  }
}

void DirectRegistryAccess::openKeyForEnumeration(HKEY root_key, HKEY &h_key)
{
  openKeyForEnumeration(root_key, "", h_key);
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

  if (subKeyState == ERROR_SUCCESS)
  {
    key_name = std::string(buffer);
  }
  else if(subKeyState == ERROR_NO_MORE_ITEMS)
  {
    key_name = "";
  }
  else
  {
    return false;
  }

  return true;
}

bool DirectRegistryAccess::getValueFromKey(HKEY &h_key, std::string search_value_name, std::string *key_value)
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

  if (valueState == ERROR_SUCCESS)
  {
    *key_value = std::string(buffer);
  }
  else
  {
    return false;
  }

  return true;
}

bool DirectRegistryAccess::getValueFromKey(HKEY &h_key, std::string *key_value)
{
  return getValueFromKey(h_key, "", key_value);
}

void DirectRegistryAccess::closeKey(HKEY &h_key)
{
  RegCloseKey(h_key);
  h_key = NULL;
}
