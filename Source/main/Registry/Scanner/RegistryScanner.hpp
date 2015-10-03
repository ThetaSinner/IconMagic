#ifndef REGISTRY_SCANNER
#define REGISTRY_SCANNER

#include <vector>
#include <map>
#include <utility>

#include "./../Common/KeyPath.hpp"

class RegistryScanner
{
public:
  RegistryScanner();

  std::vector<std::pair<KeyPath, std::string>> getValues(std::string key_name, std::string value_name);

  void setRootKey(std::string root_key_name);
  std::string getRootKey();

  void setMaxDepth(int max_depth);
  int getMaxDepth();

  void setMaxMatches(int max_matches);
  int getMaxMatches();

  static int unlimitedMatches();
  static int unlimitedRecursionDepth();

private:
  std::vector<std::pair<KeyPath, std::string>> scanResults;

  std::string useRootKey;
  int maximumRecursionDepth;
  int maximumNumberOfMatches;
};

#endif
