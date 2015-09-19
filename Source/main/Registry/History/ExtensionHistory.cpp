#include "ExtensionHistory.hpp"

#include "./../../Util.hpp"

// TODO remove temp include.
#include <iostream>

ExtensionHistory::ExtensionHistory()
{
   extensionName = "";
   imageHistory = std::vector<ImageEntry> ();
}

void ExtensionHistory::createFromData(std::string extension_name, ImageEntry image_entry)
{
  // Stop if the object already has data, or the input is invalid.
  if (isValid() || stringIsBlank(extension_name) || !image_entry.isValid()) return;

  extensionName = extension_name;
  imageHistory.push_back(image_entry);
}

void ExtensionHistory::createFromFormatted(std::string entry)
{
  // do not allow overwrite.
  // A minimum valid entry must be .\n[?]
  if (isValid() || entry.size() < 5 || stringDoesNotContains(entry, "\n")) return;

  // Input may be valid, continue.
  int splitIndex = entry.find("\n"); // TODO extract to variable?
  std::string extensionNameLine = entry.substr(0, splitIndex);
  std::string imageEntryLine = entry.substr(splitIndex + 1);

  bool allImageEntriesValid = true;
  while (stringContains(imageEntryLine, ImageEntry::blockOpen) && stringContains(imageEntryLine, ImageEntry::blockShut))
  {
    // Extract an image entry.
    int open = imageEntryLine.find(ImageEntry::blockOpen),
        shut = imageEntryLine.find(ImageEntry::blockShut) + 1;
    if (open > shut)
    {
      allImageEntriesValid = false;
      break;
    }
    std::string imageEntryString = imageEntryLine.substr(open, shut - open);
    imageEntryLine = imageEntryLine.substr(shut);

    // Create an image entry object from the extracted string.
    ImageEntry imageEntry;
    imageEntry.createFromFormatted(imageEntryString);

    // If the image entry object is valid save it, otherwise stop.
    if (imageEntry.isValid())
    {
        imageHistory.push_back(imageEntry);
    }
    else
    {
      allImageEntriesValid = false;
      break;
    }
  }

  // One or more image entries in the file are invalid don't save anything.
  // If this method fails to populate the object then whoever calls the should store the string they passed in.
  if (!allImageEntriesValid)
  {
    extensionName = "";
    imageHistory.clear();
  }
}

int ExtensionHistory::size()
{
  return imageHistory.size();
}

std::string ExtensionHistory::getExtensionName() const
{
  return extensionName;
}

ImageEntry ExtensionHistory::getLastEntry()
{
  return (imageHistory.size() ? imageHistory.back() : ImageEntry());
}

std::string ExtensionHistory::getFormatted() const
{
  std::string formatted = extensionName + "\n";

  for(auto i : imageHistory) formatted += i.getFormatted();

  return formatted;
}

void ExtensionHistory::pushImageEntry(ImageEntry image_entry)
{
  if (!image_entry.isValid()) return;

  imageHistory.push_back(image_entry);
}

void ExtensionHistory::popImageEntry()
{
  // Don't delete the original value of the default icon key.
  if (size() > 1) imageHistory.pop_back();
}

bool ExtensionHistory::isValid()
{
  return (extensionName != "" && imageHistory.size() != 0);
}
