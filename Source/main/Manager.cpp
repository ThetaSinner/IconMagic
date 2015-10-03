/** \file
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * // TODO file_desc
 */

#include "./Manager.hpp"

#include <stdio.h>

#include "./Util.hpp"
#include "./WindowsToolbox.hpp"
#include "./Registry/Scanner/RegistryScanner.hpp"
#include "./Registry/History/registryHistory.hpp"

const std::string Manager::ICON_MAGIC_CACHE_NAME = "IconMagicCache";
const std::string Manager::ICON_MAGIC_CACHE_FILE_EXTENSION = ".txt";

void Manager::cacheBuild()
{
  // If the cache already exists, then move it so we can reuse the cache name.
  if (fileExists(ICON_MAGIC_CACHE_NAME + ICON_MAGIC_CACHE_FILE_EXTENSION))
  {
    int shift = 1;
    while (fileExists(ICON_MAGIC_CACHE_NAME + integerToString(shift) + ICON_MAGIC_CACHE_FILE_EXTENSION))
    {
      shift++;
    }

    int renameStatus = rename((ICON_MAGIC_CACHE_NAME + ICON_MAGIC_CACHE_FILE_EXTENSION).c_str(),
                              (ICON_MAGIC_CACHE_NAME + integerToString(shift) + ICON_MAGIC_CACHE_FILE_EXTENSION).c_str());

    if (renameStatus != 0)
    {
      std::cout << "Cache build failed. Can't move existing cache file.\n";
      return;
    }
  }

  std::cout << "Decided on a name.\n";

  RegistryScanner scanner = RegistryScanner();
  scanner.setRootKey("classes_root");
  scanner.setMaxMatches(5); // RegistryScanner::unlimitedMatches()
  scanner.setMaxDepth(3); // TODO config

  std::cout << "Set up the scanner.\n";

  std::vector<std::pair<KeyPath, std::string>> results = scanner.getValues("DefaultIcon", "");

  std::cout << "Scanned the registry.\n";

  RegistryHistory history;
  history.setHistoryFileName(ICON_MAGIC_CACHE_NAME + ICON_MAGIC_CACHE_FILE_EXTENSION);

  std::cout << "Created the history object.\n";

  //history.push(".txt", "test.png", "1");

  std::cout << "Got " << results.size() << " results.\n";

  for (auto r : results)
  {
    std::string value = r.second;

    std::string namePart, indexPart;
    if (stringContains(value, ","))
    {
      namePart = value.substr(0, value.find(","));
      indexPart = value.substr(value.find(",") + 1);
    }
    else
    {
      namePart = value;
      indexPart = "";
    }

    while (stringContains(namePart, "\""))
    {
      namePart.erase(namePart.find("\""), 1);
    }

    /*std::cout << "pushing\n"
      << "\tname part " << namePart << "\n"
      << "\tindex part " << indexPart << "\n";*/

    if (!history.push(r.first.toString(), namePart, indexPart))
    {
      std::cout << "Failed to add " << namePart << "\n";
    }
  }

  std::cout << "Populated the history object\n";

  history.writeHistory();

  std::cout << "Wrote the history to file.\n";
}
