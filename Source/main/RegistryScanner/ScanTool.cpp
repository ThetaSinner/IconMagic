#include "./ScanTool.hpp"

#include <exception>

class registryScanException : public std::exception
{
public:
  std::string err = "Unknown failure.";

  registryScanException(std::string msg) {err = msg;}

  virtual const char* what() const throw()
  {
    return err.c_str();
  }
};

const std::map<std::string, HKEY> ScanTool::predefinedRootKeys = {
  {"classes_root", HKEY_CLASSES_ROOT},
  {"current_config", HKEY_CURRENT_CONFIG},
  {"current_user", HKEY_CURRENT_USER},
  {"local_machine", HKEY_LOCAL_MACHINE},
  {"users", HKEY_USERS}
};

const int ScanTool::UNLIMITED_RECURSION_DEPTH = -7;
const int ScanTool::UNLIMITED_MATCHES = -7;

std::vector<std::pair<KeyPath, std::string>> ScanTool::simpleSearch(
  std::string root_key_name,
  std::string key_name,
  std::string value_name,
  int maximum_recursion_depth,
  int maximum_items_to_search_for
) {
  if (
    (maximum_recursion_depth < 0 && maximum_recursion_depth != ScanTool::UNLIMITED_RECURSION_DEPTH)
    ||
    (maximum_items_to_search_for < 1 && maximum_items_to_search_for != ScanTool::UNLIMITED_MATCHES)
  ) {
    throw new registryScanException("Invalid input(s) for search limitation.");
  }

  std::map<std::string, HKEY>::const_iterator keySearch = predefinedRootKeys.find(root_key_name);
  if (keySearch == predefinedRootKeys.end())
  {
    throw new registryScanException("Requested root key does not exist.");
  }
  HKEY searchRoot = keySearch -> second;

  HKEY hSearchRoot = NULL;
  try {
    openKeyForEnumeration(searchRoot, hSearchRoot);
  } catch (registryScanException e) { // new type needed here.
    // TODO log
    throw e;
  }

  std::vector<std::pair<KeyPath, std::string>> results;
  try {
    KeyPath keyPath = KeyPath(root_key_name);
    depthFirstSearch(
      hSearchRoot,
      key_name,
      value_name,
      keyPath,
      maximum_recursion_depth,
      maximum_items_to_search_for);
  } catch (registryScanException e) {
    // TODO log
    RegCloseKey(hSearchRoot);
    throw e;
  }

  RegCloseKey(hSearchRoot);
  return results;
}

std::vector<std::pair<KeyPath, std::string>> ScanTool::depthFirstSearch(
  HKEY root_key,
  std::string key_name,
  std::string value_name,
  KeyPath key_path,
  int remaining_recursion_depth,
  int remaining_items_to_search_for
) {
  if (remaining_recursion_depth < 0 && remaining_recursion_depth != ScanTool::UNLIMITED_RECURSION_DEPTH)
  {
    return std::vector<std::pair<KeyPath, std::string>> ();
  }

  std::vector<std::pair<KeyPath, std::string>> results;

  int keyIndex = 0;
  std::string nextKeyName = "";
  while (true)
  {
    getSubKeyN(root_key, &nextKeyName, keyIndex);

    if (nextKeyName == "")
    {
      break;
    }
    else if (nextKeyName == key_name)
    {
      KeyPath subKeyPath = KeyPath(key_path);
      subKeyPath.append(nextKeyName);

      results.push_back(std::pair<KeyPath, std::string> (subKeyPath, "value"));

      break;
    }
    else
    {
      HKEY nextKey = NULL;
      openKeyForEnumeration(root_key, nextKey, nextKeyName);

      KeyPath subKeyPath = KeyPath(key_path);
      subKeyPath.append(nextKeyName);

      std::vector<std::pair<KeyPath, std::string>> partResult = depthFirstSearch(
        nextKey,
        key_name,
        value_name,
        subKeyPath,
        remaining_recursion_depth - 1,
        remaining_items_to_search_for
      );

      bool stopNow = false;
      for (auto r : partResult)
      {
        if (remaining_items_to_search_for < 1 && remaining_items_to_search_for != ScanTool::UNLIMITED_MATCHES)
        {
          stopNow = true;
          break;
        }

        results.push_back(r);

        remaining_items_to_search_for--;
      }

      if (stopNow) break;

      nextKeyName = "";
      keyIndex++;
    }
  }
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

   if (status != ERROR_SUCCESS) throw new registryScanException("Failed to open key for enumeration.");
}

void ScanTool::getSubKeyN(const HKEY &root_key, std::string *key_name, int n)
{
  DWORD bufferSize = 500; // you can determine this dynamically - RegQueryInfoKey
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

  if (subKeyState == ERROR_SUCCESS) *key_name = std::string(buffer);
  else if(subKeyState == ERROR_NO_MORE_ITEMS) *key_name = "";
  else throw new registryScanException("Failed to open nth subkey.");
}

/*
bool scanRegistryForDefaultIcons()
{
  HKEY rootKey = NULL;
  DWORD rootKeyState = openKeyForEnumeration(HKEY_CLASSES_ROOT, rootKey);

  if(rootKeyState != ERROR_SUCCESS)
  {
    std::cout << "Failed to open HKEY_CLASSES_ROOT for searching.\n";
    RegCloseKey(rootKey);
    return false;
  }

  std::list<std::string> rootSubKeysList = listSubKeys(rootKey);
  //
  // Look inside the sub keys for default icon keys.
  //
  std::list<std::string> rootSubKeysListFilteredByDefaultIcon;

  for(auto i : rootSubKeysList)
  {
    HKEY subKeyI = NULL;
    DWORD subKeyStateI = openKeyForEnumeration(rootKey, subKeyI, i);

    if(subKeyStateI != ERROR_SUCCESS)
    {
      std::cout << "Failed to open sub key " << i << " for enumeration";
      continue;
    }

    std::list<std::string> temp = listSubKeys(subKeyI);

    for(auto k : temp)
    {
      if(k == "DefaultIcon")
      {
        rootSubKeysListFilteredByDefaultIcon.push_back(i);
        break;
      }
    }
  }

  std::cout << "Found " << rootSubKeysList.size() << " keys.\n";
  std::cout << "Found " << rootSubKeysListFilteredByDefaultIcon.size() << " keys with DefaultIcon sub keys.\n";
  int stopAfter = 10;
  int counter = 0;

  for(auto i : rootSubKeysListFilteredByDefaultIcon)
  {
    std::cout << i << "\n";
    counter++;

    if(counter >= stopAfter)
    {
      break;
    }
  }

  std::ofstream out("out.txt", std::ofstream::out);

  for(auto i : rootSubKeysListFilteredByDefaultIcon)
  {
    out << i << "\n";
  }

  out.close();
  RegCloseKey(rootKey);
  std::cout << "\n\nDone.";
  return true;
}
*/
