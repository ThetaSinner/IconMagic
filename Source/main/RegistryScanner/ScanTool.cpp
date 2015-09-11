#include "./ScanTool.hpp"

#include <iostream>

// TODO directly access a value with a KeyPath and value name, doesn't belong in this file.

const std::map<std::string, std::string> ScanTool::ALTERNATE_KEY_NAME_MAP = {
  {"classes_root", "HKEY_CLASSES_ROOT"},
  {"current_config", "HKEY_CURRENT_CONFIG"},
  {"current_user", "HKEY_CURRENT_USER"},
  {"local_machine", "HKEY_LOCAL_MACHINE"},
  {"users", "HKEY_USERS"}
};

const std::map<std::string, HKEY> ScanTool::PREDEFINED_ROOT_KEYS = {
  {"HKEY_CLASSES_ROOT", HKEY_CLASSES_ROOT},
  {"HKEY_CURRENT_CONFIG", HKEY_CURRENT_CONFIG},
  {"HKEY_CURRENT_USER", HKEY_CURRENT_USER},
  {"HKEY_LOCAL_MACHINE", HKEY_LOCAL_MACHINE},
  {"HKEY_USERS", HKEY_USERS}
};

const int ScanTool::UNLIMITED_RECURSION_DEPTH = -7;
const int ScanTool::UNLIMITED_MATCHES = -7;

std::vector<std::pair<KeyPath, std::string>> ScanTool::simpleSearch(
  std::string root_key_name,
  std::string search_key_name,
  std::string search_value_name,
  int maximum_recursion_depth,
  int maximum_items_to_search_for)
{
  // Check the recursion limitations are valid.
  if (testRecursionRestrictionsValid(maximum_recursion_depth, maximum_items_to_search_for)) {
    throw RegistryScanException("Invalid input(s) for search restriction.");
  }

  // Check the requested root key has a predefined pair.
  HKEY searchRoot = resolveNameToKey(root_key_name);
  if (searchRoot == NULL) {
    throw RegistryScanException("Requested root key does not exist.");
  }

  // Attempt to open the root key. This should fail because it will have been tested on startup.
  HKEY hSearchRoot = NULL;
  openKeyForEnumeration(searchRoot, hSearchRoot);

  // Kick the recursion off.
  try {
    KeyPath keyPath = KeyPath(root_key_name);

    std::vector<std::pair<KeyPath, std::string>>results = depthFirstSearch(
      hSearchRoot,
      search_key_name,
      search_value_name,
      keyPath,
      maximum_recursion_depth,
      maximum_items_to_search_for);

      RegCloseKey(hSearchRoot);
      return results;
  } catch (const RegistryScanException &e) {
    RegCloseKey(hSearchRoot);
    throw e;
  }
}

bool ScanTool::testRootKeyNameValid(std::string root_key_name)
{
  return resolveNameToKey(root_key_name) != NULL;
}

std::vector<std::pair<KeyPath, std::string>> ScanTool::depthFirstSearch(
  HKEY root_key,
  std::string search_key_name,
  std::string search_value_name,
  KeyPath key_path,
  int remaining_recursion_depth,
  int remaining_items_to_search_for)
{
  // Don't go any deeper on this branch.
  if (remaining_recursion_depth != ScanTool::UNLIMITED_RECURSION_DEPTH && remaining_recursion_depth < 1)
  {
    // TODO depth limit is not working.
    return std::vector<std::pair<KeyPath, std::string>> ();
  }

  // Continue recursion.
  std::vector<std::pair<KeyPath, std::string>> results;

  int keyIndex = -1;
  while (true)
  {
    keyIndex++; // increment at the top to allow 'continue' without increment.

    std::string nextKeyName;
    try {
      getSubKeyN(root_key, &nextKeyName, keyIndex);
    } catch (const RegistryScanException &e) {
      // TODO option to fail here.
      continue;
    }

    if (nextKeyName == "")
    {
      break;
    }
    else
    {
      KeyPath nextKeyPath = KeyPath(key_path).append(nextKeyName);

      HKEY hNextKey = NULL;
      try {
        openKeyForEnumeration(root_key, hNextKey, nextKeyName);
      } catch (const RegistryScanException &e) {
        // TODO option to fail here.
        continue;
      }

      int use_recursion_depth = remaining_recursion_depth;
      if (remaining_recursion_depth != ScanTool::UNLIMITED_RECURSION_DEPTH) use_recursion_depth--;

      std::vector<std::pair<KeyPath, std::string>> partResult = depthFirstSearch(
        hNextKey,
        search_key_name,
        search_value_name,
        nextKeyPath,
        use_recursion_depth,
        remaining_items_to_search_for
      );

      if (nextKeyName == search_key_name)
      {
        std::string value;
        try {
          getValueFromKey(hNextKey, search_value_name, &value);
          partResult.push_back(std::pair<KeyPath, std::string> (nextKeyPath, value));
        } catch (const RegistryScanException& e) {
          // TODO This is a bit of a problem...
        }

        // TODO option to stop the search at this point?
      }

      RegCloseKey(hNextKey);

      if (remaining_items_to_search_for == ScanTool::UNLIMITED_MATCHES) {
        pushPartialToResult(results, partResult, partResult.size() + 1);
      }
      else {
        remaining_items_to_search_for = pushPartialToResult(results, partResult, remaining_items_to_search_for);
        if (remaining_items_to_search_for == 0) break;
      }
    }
  }

  return results;
}

void ScanTool::openKeyForEnumeration(HKEY root_key, HKEY &h_key, std::string path)
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
     throw RegistryScanException("Failed to open key for enumeration.");
   }
}

void ScanTool::getSubKeyN(const HKEY &root_key, std::string *key_name, int n)
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
    *key_name = std::string(buffer);
  }
  else if(subKeyState == ERROR_NO_MORE_ITEMS)
  {
    *key_name = "";
  }
  else
  {
    throw RegistryScanException("Failed to open nth subkey.");
  }
}

int ScanTool::pushPartialToResult(
  std::vector<std::pair<KeyPath, std::string>> &result,
  std::vector<std::pair<KeyPath, std::string>> &partial,
  int limit)
{
  // TODO negative limit is a problem.

  for (auto& i : partial)
  {
    if (limit) {
      result.push_back(partial.back());
      partial.pop_back();
      limit--;
    }
    else break;
  }

  return limit;
}

HKEY ScanTool::resolveNameToKey(std::string &name)
{
  if (ScanTool::ALTERNATE_KEY_NAME_MAP.find(name) != ScanTool::ALTERNATE_KEY_NAME_MAP.end()) {
    name = ScanTool::ALTERNATE_KEY_NAME_MAP.at(name);
  }

  if (ScanTool::PREDEFINED_ROOT_KEYS.find(name) != ScanTool::PREDEFINED_ROOT_KEYS.end()) {
    return ScanTool::PREDEFINED_ROOT_KEYS.at(name);
  }

  return NULL;
}

void ScanTool::getValueFromKey(HKEY &key, std::string search_value_name, std::string *key_value)
{
  DWORD bufferSize = 5000; // TODO config.
  char buffer[(int) bufferSize];

  DWORD valueState = RegQueryValueEx(
    key,
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
    throw RegistryScanException("Failed to get value from key.");
  }
}

bool ScanTool::testRecursionRestrictionsValid(int maximum_recursion_depth, int maximum_items_to_search_for)
{
  return (maximum_recursion_depth < 1 && maximum_recursion_depth != ScanTool::UNLIMITED_RECURSION_DEPTH) ||
         (maximum_items_to_search_for < 1 && maximum_items_to_search_for != ScanTool::UNLIMITED_MATCHES);
}
