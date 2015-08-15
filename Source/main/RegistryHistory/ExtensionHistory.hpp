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
  void createFromData(std::string extension_name, ImageEntry image_entry);
  void createFromFormatted(std::string entry);

  // Read
  int size();
  std::string getExtensionName() const;
  ImageEntry getLastEntry();
  std::string getFormatted() const;

  // Update.
  void pushImageEntry(ImageEntry image_entry);

  // Delete
  void popImageEntry();

  // Other
  bool isValid();

private:
  std::string extensionName;
  std::vector<ImageEntry> imageHistory;
};

#endif
