#include "./ScanTool.hpp"

#include <exception>

class subKeyAccessException : public std::exception
{
  virtual const char* what() const throw()
  {
    return "Failed to access subkey.";
  }
};

const std::map<std::string, HKEY> ScanTool::predefinedRootKeys = {
  {"classes_root", HKEY_CLASSES_ROOT},
  {"current_config", HKEY_CURRENT_CONFIG},
  {"current_user", HKEY_CURRENT_USER},
  {"local_machine", HKEY_LOCAL_MACHINE},
  {"users", HKEY_USERS}
};

std::vector<std::pair<KeyPath, std::string>> ScanTool::simpleSearch(
  std::string root_key_name,
  std::string key_name,
  std::string value_name,
  int maximum_recursion_depth,
  int maximum_items_to_search_for
) {
  std::map<std::string, HKEY>::const_iterator keySearch = predefinedRootKeys.find(root_key_name);
  if (keySearch == predefinedRootKeys.end())
    return std::vector<std::pair<KeyPath, std::string> > ();
  HKEY searchRoot = keySearch -> second;

  HKEY hSearchRoot = NULL;
  try {
    openKeyForEnumeration(searchRoot, hSearchRoot);
  } catch (subKeyAccessException) { // new type needed here.
    // oh no.
  }

  try {
    KeyPath keyPath(root_key_name);
    std::vector<std::pair<KeyPath, std::string>> results = depthFirstSearch(hSearchRoot, key_name, value_name, maximum_recursion_depth, maximum_items_to_search_for, keyPath);
    return results;
  } catch (subKeyAccessException e) {
    // oh dear.
  }

  RegCloseKey(hSearchRoot);

  return std::vector<std::pair<KeyPath, std::string>> ();
}

std::vector<std::pair<KeyPath, std::string>> ScanTool::depthFirstSearch(
  HKEY root_key,
  std::string key_name,
  std::string value_name,
  int remaining_recursion_depth,
  int remaining_items_to_search_for,
  KeyPath key_path
) {
  if (remaining_recursion_depth < 0) return std::vector<std::pair<KeyPath, std::string>> ();

  int keyIndex = 0;
  std::string nextKeyName = " ";
  while (nextKeyName != "")
  {
    nextKeyName = "";
    getSubKeyN(root_key, &nextKeyName, keyIndex);

    HKEY nextKey = NULL;
    openKeyForEnumeration(root_key, nextKey, nextKeyName);

    KeyPath subKeyPath(key_path);
    subKeyPath.append(nextKeyName);
    depthFirstSearch(
      nextKey,
      key_name,
      value_name,
      remaining_recursion_depth - 1,
      remaining_items_to_search_for,
      subKeyPath
    );

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

   if (status != ERROR_SUCCESS) throw new subKeyAccessException;
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
  else throw new subKeyAccessException;
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
