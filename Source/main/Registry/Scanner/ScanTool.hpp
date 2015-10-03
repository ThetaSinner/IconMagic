#ifndef SCAN_TOOL
#define SCAN_TOOL

#include <vector>

#include <utility>
#include <string>

#include <Windows.h>

#include "./../Common/KeyPath.hpp"

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
  static const int UNLIMITED_RECURSION_DEPTH;
  static const int UNLIMITED_MATCHES;

  std::vector<std::pair<KeyPath, std::string>> simpleSearch(
    std::string root_key_name,
    std::string search_key_name,
    std::string search_value_name,
    int maximum_recursion_depth,
    int maximum_items_to_search_for
  );

  bool testRootKeyNameValid(std::string root_key_name); // TODO Debug only.

  static int unlimitedMatches();
  static int unlimitedRecursionDepth();

private:

  std::vector<std::pair<KeyPath, std::string>> depthFirstSearch(
    HKEY root_key,
    std::string search_key_name,
    std::string value_name,
    KeyPath key_path,
    int remaining_recursion_depth = -1,
    int remaining_items_to_search_for = -1
  );

  int pushPartialToResult(
    std::vector<std::pair<KeyPath, std::string>> &result,
    std::vector<std::pair<KeyPath, std::string>> &partial,
    int limit
  );

  void openKeyForEnumeration(HKEY root_key, HKEY &h_key, std::string path = "");
  void getSubKeyN(const HKEY &root_key, std::string *key_name, int n);
  void getValueFromKey(HKEY &key, std::string value_name, std::string *key_value);

  bool testRecursionRestrictionsValid(int maximum_recursion_depth, int maximum_items_to_search_for);
};

#endif
