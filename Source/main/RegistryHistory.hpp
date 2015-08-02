/** \file
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * // TODO file_desc
 */

#ifndef REGISTRYHISTORY_HPP_INCLUDED
#define REGISTRYHISTORY_HPP_INCLUDED

#include <string>
#include <vector>
#include <windows.h>
#include <fstream>

class ExtensionEntry;
class ImageEntry;

class RegistryHistory
{
private:
  std::string historyFileName;
  std::vector<ExtensionEntry> extensionHistory;

public:
  RegistryHistory();
  RegistryHistory(std::string history_file_name);

  void setHistoryFileName(std::string history_file_name);

  bool readHistory();
  bool writeHistory();

  void addNewEntry(std::string extension_name, std::string image_name, std::string image_index);
  void addImageEntryToExistingExtension(std::string existing_extension_name, std::string image_name, std::string image_index);

  // bool selectEntryByExtensionName(std::string extName);
};

class ExtensionEntry
{
private:
  std::string extensionName;
  std::vector<ImageEntry> imageHistory;

public:
  ExtensionEntry();
  ExtensionEntry(std::string entry);

  void createEntryFromRawData(std::string extension_name, ImageEntry image_entry);
  void createEntryFromRawData(std::string extension_name, std::vector<ImageEntry> image_history);
  void loadEntryFromFormatted(std::string entry);
  std::string getFormatted();

  void pushImageEntry(ImageEntry image_entry);
  int getNumberOfImageEntries();
  ImageEntry getImageEntryAt(int index);

  std::string getExtensionName();
  std::vector<ImageEntry> getImageHistory();
};

class ImageEntry
{
private:
  std::string imagePath;
  std::string imageIndex;

public:
  ImageEntry();

  void createEntryFromRawData(std::string image_path, std::string image_index);
  void loadEntryFromFormatted(std::string entry);

  std::string getFormatted();

  std::string getImagePath();
  std::string getImageIndex();
};

#endif // REGISTRYHISTORY_HPP_INCLUDED
