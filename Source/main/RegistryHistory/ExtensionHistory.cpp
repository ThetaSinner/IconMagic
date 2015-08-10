#include "ExtensionHistory.hpp"

ExtensionHistory::ExtensionHistory()
{
   extensionName = "";
   imageHistory = std::vector<ImageEntry> ();
}

// Create

void ExtensionHistory::create(std::string extension_name, ImageEntry image_entry)
{
  // Stop if the object already has data.
  if (instanceHasData()) return;

  // Check the input okay before using it.
  if (extension_name != "" && image_entry.isValid())
  {
    extensionName = extension_name;
    push(image_entry);
  }
}

void ExtensionHistory::createFromFormatted(std::string entry)
{
  // do not allow overwrite.
  if (instanceHasData()) return;

  // A minimum valid entry must be .\n[?]
  if (entry.size() < 5) return;
  if (static_cast<int>(entry.find("\n")) == -1) return;

  // Input may be valid, continue.
  extensionName = extensionName = entry.substr(0, entry.find("\n"));
  std::string imageEntryLine = entry.substr(entry.find("\n") + 1);

  bool allImageEntriesValid = true;
  while (static_cast<int>(imageEntryLine.find(ImageEntry::blockShut)) != -1)
  {
    // Extract an image entry.
    std::string imageEntryString = imageEntryLine.substr(0, imageEntryLine.find("]") + 1);
    imageEntryLine = imageEntryLine.substr(imageEntryString.size());

    // Create an image entry object from the extracted string.
    ImageEntry imageEntry;
    imageEntry.createFromFormatted(imageEntryString);

    // If the image entry object is valid save it, otherwise stop.
    if (imageEntry.isValid())
    {
        push(imageEntry);
    }
    else
    {
      allImageEntriesValid = false;
      break;
    }
  }

  // One or more image entries in the file are invalid don't save anything.
  if (!allImageEntriesValid) // move into private space, so can be written to file again. Must not lose data.
  {
    extensionName = "";
    imageHistory.clear();
  }
}

bool ExtensionHistory::pushImageEntry(ImageEntry image_entry)
{
  if (!image_entry.isValid()) return false;

  push(image_entry);
  return true;
}

// Read

int ExtensionHistory::getImageHistorySize()
{
  return imageHistory.size();
}

std::string ExtensionHistory::getExtensionName() const
{
  return extensionName;
}

ImageEntry ExtensionHistory::getImageEntryAt(int index)
{
  if(0 <= index && index < getImageHistorySize()) return imageHistory[index];

  return ImageEntry();
}

std::string ExtensionHistory::getFormatted() const
{
  std::string formatted = extensionName + "\n";

  for(auto i : imageHistory)
  {
    formatted += i.getFormatted();
  }

  return formatted;
}

// Delete
void ExtensionHistory::popImageEntry()
{
  // Don't delete the original value of the default icon key.
  if (imageHistory.size() > 1)
  {
    imageHistory.pop_back();
  }
}

// Other

bool ExtensionHistory::isValid()
{
  return (extensionName != "" && imageHistory.size());
}

// private

void ExtensionHistory::push(ImageEntry image_entry)
{
  imageHistory.push_back(image_entry);
}

bool ExtensionHistory::instanceHasData()
{
    if (extensionName == "" && imageHistory.size() == 0) return false;
    return true;
}
