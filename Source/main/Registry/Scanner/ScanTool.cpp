#include "./ScanTool.hpp"

#include <iostream>

// TODO directly access a value with a KeyPath and value name, doesn't belong in this file.

#include "./../Common/KeyService.hpp"
#include "./../DataAccess/DirectRegistryAccess.hpp"

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
    // don't use exception here.
    throw RegistryScanException("Invalid input(s) for search restriction.");
  }

  // Check the requested root key has a predefined pair.
  HKEY searchRoot = KeyService::getKeyByAnyName(root_key_name);
  if (searchRoot == NULL) {
    // don't use exception here.
    throw RegistryScanException("Requested root key does not exist.");
  }

  // Attempt to open the root key. This should fail because it will have been tested on startup.
  HKEY hSearchRoot = NULL;
  DirectRegistryAccess::openKeyForEnumeration(searchRoot, hSearchRoot);

  // Kick the recursion off.
  try {
    KeyPath keyPath = KeyPath(KeyService::resolveName(root_key_name));

    std::vector<std::pair<KeyPath, std::string>> results = depthFirstSearch(
      hSearchRoot,
      search_key_name,
      search_value_name,
      keyPath,
      maximum_recursion_depth,
      maximum_items_to_search_for);

      DirectRegistryAccess::closeKey(hSearchRoot);
      return results;
  } catch (const RegistryScanException &e) {
    DirectRegistryAccess::closeKey(hSearchRoot);
    throw e;
  }

  return std::vector<std::pair<KeyPath, std::string>> ();
}

bool ScanTool::testRootKeyNameValid(std::string root_key_name)
{
  return KeyService::getKeyByAnyName(root_key_name) != NULL;
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
    // TODO depth limit is not working. Might be now.
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
      DirectRegistryAccess::getSubKeyNameAt(root_key, keyIndex, nextKeyName);
      //getSubKeyN(root_key, &nextKeyName, keyIndex);
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
        DirectRegistryAccess::openKeyForEnumeration(root_key, nextKeyName, hNextKey);
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
          DirectRegistryAccess::getValueFromKey(hNextKey, search_value_name, &value);
          partResult.push_back(std::pair<KeyPath, std::string> (nextKeyPath, value));
        } catch (const RegistryScanException& e) {
          // TODO This is a bit of a problem...
        }

        // TODO option to stop the search at this point?
      }

      DirectRegistryAccess::closeKey(hNextKey);

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

/*
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
*/

bool ScanTool::testRecursionRestrictionsValid(int maximum_recursion_depth, int maximum_items_to_search_for)
{
  return (maximum_recursion_depth < 1 && maximum_recursion_depth != ScanTool::UNLIMITED_RECURSION_DEPTH) ||
         (maximum_items_to_search_for < 1 && maximum_items_to_search_for != ScanTool::UNLIMITED_MATCHES);
}
