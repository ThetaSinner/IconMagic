#ifndef EXTENSION_HISTORY
#define EXTENSION_HISTORY

#include <string>
#include <vector>

#include "./ImageEntry.hpp"

class ExtensionHistory
{
public:
  ExtensionHistory();

  // Create
  void create(std::string extension_name, ImageEntry image_entry);
  void createFromFormatted(std::string entry);

  bool pushImageEntry(ImageEntry image_entry);

  // Read
  int getImageHistorySize();
  std::string getExtensionName() const;
  ImageEntry getImageEntryAt(int index);

  std::string getFormatted() const;

  // Delete
  void popImageEntry();

  // Other
  bool isValid();

private:
  std::string extensionName;
  std::vector<ImageEntry> imageHistory;

  void push(ImageEntry image_entry);

  bool instanceHasData();
};

#endif
