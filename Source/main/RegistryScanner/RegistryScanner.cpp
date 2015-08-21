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

std::vector<std::pair<KeyPath, std::string>> RegistryScanner::lookupValue(std::string key_name, std::string value_name)
{
  // Here I'm choosing to assume the input is validated already.
  // use scan tools --- beginScan(key_name, value_name);
  return scanResults;
}
