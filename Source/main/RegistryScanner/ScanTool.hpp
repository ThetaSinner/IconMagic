#ifndef SCAN_TOOL
#define SCAN_TOOL

#include <vector>
#include <map>
#include <utility>
#include <string>

#include <Windows.h>

#include "./KeyPath.hpp"

class ScanTool
{
public:
  static const std::map<std::string, HKEY> predefinedRootKeys;

  std::vector<std::pair<KeyPath, std::string>> simpleSearch(
    std::string root_key_name,
    std::string key_name,
    std::string value_name,
    int maximum_recursion_depth,
    int maximum_items_to_search_for
  );

private:

  std::vector<std::pair<KeyPath, std::string>> depthFirstSearch(
    HKEY root_key,
    std::string key_name,
    std::string value_name,
    int remaining_recursion_depth,
    int remaining_items_to_search_for,
    KeyPath key_path
  );

  void openKeyForEnumeration(HKEY root_key, HKEY &h_key, std::string path = "");
  void getSubKeyN(const HKEY &root_key, std::string *key_name, int n);
};

#endif