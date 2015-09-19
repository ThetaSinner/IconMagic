#ifndef REGISTRY_HISTORY_API
#define REGISTRY_HISTORY_API

#include <string>
#include <vector>
#include <windows.h>
#include <fstream>

#include "./ImageEntry.hpp"
#include "./ExtensionHistory.hpp"

class RegistryHistory
{
public:
  RegistryHistory();

  void setHistoryFileName(std::string history_file_name);

  bool readHistory();
  bool writeHistory();

  bool push(std::string extension_name, std::string image_name, std::string image_index);
  bool pop(std::string extension_name);

  void deleteExtension(std::string extension_name);

  std::string getPath(std::string extension_name);
  std::string getIndex(std::string extension_name);
  std::string getRegString(std::string extension_name);
private:
  std::string historyFileName;
  std::vector<ExtensionHistory> history;
  std::vector<std::string> badReads;

  ImageEntry getLast(std::string extension_name);
};

#endif
