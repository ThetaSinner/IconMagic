#ifndef SCAN_TOOL
#define SCAN_TOOL

#include <vector>
#include <map>
#include <utility>
#include <string>

#include <Windows.h>

#include "./KeyPath.hpp"

#include <exception>

class RegistryScanException : public std::exception
{
public:
  std::string err = "Unknown failure.";

  RegistryScanException(std::string msg) {err = msg;}

  virtual const char* what() const throw()
  {
    return err.c_str();
  }
};

class ScanTool
{
public:
  static const std::map<std::string, HKEY> PREDEFINED_ROOT_KEYS;
  static const int UNLIMITED_RECURSION_DEPTH;
  static const int UNLIMITED_MATCHES;

  std::vector<std::pair<KeyPath, std::string>> simpleSearch(
    std::string root_key_name,
    std::string search_key_name,
    std::string value_name,
    int maximum_recursion_depth,
    int maximum_items_to_search_for
  );

  bool testRootKeyNameValid(std::string root_key_name);

private:

  std::vector<std::pair<KeyPath, std::string>> depthFirstSearch(
    HKEY root_key,
    std::string search_key_name,
    std::string value_name,
    KeyPath key_path,
    int remaining_recursion_depth = -1,
    int remaining_items_to_search_for = -1
  );

  void openKeyForEnumeration(HKEY root_key, HKEY &h_key, std::string path = "");
  void getSubKeyN(const HKEY &root_key, std::string *key_name, int n);
};

#endif
