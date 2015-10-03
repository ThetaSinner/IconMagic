#include "./RegistryScanner.hpp"

#include <list> // TODO temp
#include <iostream>
#include <fstream>

#include "./ScanTool.hpp"

RegistryScanner::RegistryScanner()
{
  useRootKey = "current_user"; // If user doesn't set a key to use, then pick the 'safest' one.
  maximumRecursionDepth = 0; // Zero means search top level only.
  maximumNumberOfMatches = 0; // Zero means return as many matches as you can.
}

std::vector<std::pair<KeyPath, std::string>> RegistryScanner::getValues(std::string key_name, std::string value_name)
{
  /*std::cout << "using" << "\n"
   << "root key " << useRootKey << "\n"
   << "key name " << key_name << "\n"
   << "value name " << value_name << "\n"
   << "max depth " << maximumRecursionDepth << "\n"
   << "max matches " << maximumNumberOfMatches << "\n";

  std::cin.get();
  std::cin.get();
  exit(1);*/

  ScanTool scan;
  return scan.simpleSearch(
    useRootKey,
    key_name,
    value_name,
    maximumRecursionDepth,
    maximumNumberOfMatches
  );
}

void RegistryScanner::setRootKey(std::string root_key_name)
{
  useRootKey = root_key_name;
}

std::string RegistryScanner::getRootKey()
{
  return useRootKey;
}

void RegistryScanner::setMaxDepth(int max_depth)
{
  maximumRecursionDepth = max_depth;
}

int RegistryScanner::getMaxDepth()
{
  return maximumRecursionDepth;
}

void RegistryScanner::setMaxMatches(int max_matches)
{
  maximumNumberOfMatches = max_matches;
}

int RegistryScanner::getMaxMatches()
{
  return maximumNumberOfMatches;
}

int RegistryScanner::unlimitedMatches()
{
  return ScanTool::unlimitedMatches();
}

int RegistryScanner::unlimitedRecursionDepth()
{
  return ScanTool::unlimitedRecursionDepth();
}
