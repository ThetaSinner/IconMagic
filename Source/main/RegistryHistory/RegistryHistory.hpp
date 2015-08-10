#ifndef REGISTRY_HISTORY_API
#define REGISTRY_HISTORY_API

#include <string>
#include <vector>
#include <windows.h>
#include <fstream>

#include "./ImageEntry.hpp"
#include "./extensionHistory.hpp"

class RegistryHistory
{
public:
  RegistryHistory();

  void setHistoryFileName(std::string history_file_name);

  bool readHistory();
  bool writeHistory();

  void add(std::string extension_name, std::string image_name, std::string image_index);
  void update(std::string existing_extension_name, std::string image_name, std::string image_index);

  //ImageEntry getItem(std::string extensionName, int index);

  // bool selectEntryByExtensionName(std::string extName);
private:
  std::string historyFileName;
  std::vector<ExtensionHistory> history;
};

#endif
