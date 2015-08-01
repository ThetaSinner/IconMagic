/** \file
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * // TODO file_desc
 */

#include "RegistryHistory.hpp"

// TODO remove temp includes
#include <iostream>
#include "WindowsToolbox.hpp"

/** \brief Default constructor.
 */
RegistryHistory::RegistryHistory()
{
  this -> historyFileName = "";
  this -> extensionHistory = std::vector<ExtensionEntry> ();
}

/** \brief Constructor to allow history file to be specified on object creation.
 *
 * \param history_file_name std::string
 *
 */
RegistryHistory::RegistryHistory(std::string history_file_name)
{
  this -> historyFileName = "";
  this -> extensionHistory = std::vector<ExtensionEntry> ();
  this -> setHistoryFileName(history_file_name);
}

/** \brief Set the path to the file to be used for storing registry modification history.
 *
 * \param history_file_name std::string
 * \return void
 *
 */
void RegistryHistory::setHistoryFileName(std::string history_file_name)
{
  std::ifstream touch(history_file_name, std::ifstream::app);
  touch.close();

  if(GetFileAttributes(history_file_name.c_str()) == INVALID_FILE_ATTRIBUTES)
  {
    this -> historyFileName = "";
    return;
  }

  this -> historyFileName = history_file_name;
}

/** \brief
 *
 * \return bool
 *
 */
bool RegistryHistory::readHistory()
{
  if(historyFileName == "")
  {
    return false;
  }

  std::ifstream reader(historyFileName, std::ifstream::in);

  if(!reader.is_open())
  {
    return false;
  }

  while(!reader.eof())
  {
    std::string lineOne, lineTwo;
    reader >> lineOne;
    reader >> lineTwo;

    if(lineOne == "" || lineTwo == "")
    {
      break;
    }

    this -> extensionHistory.push_back(ExtensionEntry(lineOne + "\n" + lineTwo));    // this needs some way to fail safely.
  }

  reader.close();
  return true;
}

bool RegistryHistory::writeHistory()
{
  if(historyFileName == "")
  {
    return false;
  }

  std::ofstream writer(historyFileName, std::ofstream::out);

  if(!writer.is_open())
  {
    return false;
  }

  for(auto i : this -> extensionHistory)
  {
    writer << i.getFormatted() << "\n";
  }

  writer.close();
  return true;
}

void RegistryHistory::addNewEntry(std::string extension_name, std::string image_name, std::string image_index)
{
  ImageEntry imageEntry;
  imageEntry.createEntryFromRawData(image_name, image_index);
  ExtensionEntry extensionEntry;
  extensionEntry.createEntryFromRawData(extension_name, imageEntry);
  this -> extensionHistory.push_back(extensionEntry);
}

void RegistryHistory::addImageEntryToExistingExtension(std::string existing_extension_name, std::string image_name, std::string image_index)
{
  for(auto &i : this -> extensionHistory)
  {
    if(i.getExtensionName() == existing_extension_name)
    {
      ImageEntry imageEntry;
      imageEntry.createEntryFromRawData(image_name, image_index);
      i.pushImageEntry(imageEntry);
    }
  }
}

/**
 * class ExtensionEntry
 */

ExtensionEntry::ExtensionEntry()
{
}

ExtensionEntry::ExtensionEntry(std::string entry)
{
  loadEntryFromFormatted(entry);
}

void ExtensionEntry::createEntryFromRawData(std::string extension_name, ImageEntry image_entry)
{
  this -> extensionName = extension_name;
  this -> imageHistory = std::vector<ImageEntry> ();
  this -> imageHistory.push_back(image_entry);
}

void ExtensionEntry::createEntryFromRawData(std::string extension_name, std::vector<ImageEntry> image_history)
{
  this -> extensionName = extension_name;
  this -> imageHistory = image_history;
}

void ExtensionEntry::loadEntryFromFormatted(std::string entry)
{
  this -> extensionName = entry.substr(0, entry.find("\n"));
  std::string imageEntryLine = entry.substr(entry.find("\n") + 1);

  while(imageEntryLine.size())
  {
    if(imageEntryLine[0] == '[')
    {
      std::string imageEntryString = imageEntryLine.substr(0, imageEntryLine.find("]") + 1);
      this -> imageHistory.push_back(ImageEntry(imageEntryString));
      imageEntryLine = imageEntryLine.substr(imageEntryString.size());
    }
    else if(imageEntryLine[0] == ',')
    {
      imageEntryLine = imageEntryLine.substr(1);
    }
    else
    {
      // failure.
      break;
    }
  }
}

std::string ExtensionEntry::getFormatted()
{
  std::string temp = "";
  temp += extensionName;
  temp += "\n";
  int numberOfImageEntries = getNumberOfImageEntries();

  for(int i = 0; i < numberOfImageEntries; i++)
  {
    temp += imageHistory[i].getFormatted();

    if(i + 1 != numberOfImageEntries)
    {
      temp += ",";
    }
  }

  return temp;
}

void ExtensionEntry::pushImageEntry(ImageEntry image_entry)
{
  imageHistory.push_back(image_entry);
}

int ExtensionEntry::getNumberOfImageEntries()
{
  return imageHistory.size();
}

ImageEntry ExtensionEntry::getImageEntryAt(int index)
{
  if(0 <= index && index < getNumberOfImageEntries())
  {
    return imageHistory[index];
  }

  return ImageEntry();
}

std::string ExtensionEntry::getExtensionName()
{
  return this -> extensionName;
}

std::vector<ImageEntry> ExtensionEntry::getImageHistory()
{
  return this -> imageHistory;
}

/**
 * class ImageEntry
 */

ImageEntry::ImageEntry()
{
}

ImageEntry::ImageEntry(std::string entry)
{
  loadEntryFromFormatted(entry);
}

void ImageEntry::createEntryFromRawData(std::string image_path, std::string image_index)
{
  this -> imagePath = image_path;
  this -> imageIndex = image_index;
}

void ImageEntry::loadEntryFromFormatted(std::string entry)
{
  imagePath = entry.substr(1).substr(0, entry.find(",") - 1);
  imageIndex = entry.substr(entry.find(",") + 1, entry.find("]") - entry.find(",") - 1);
}

std::string ImageEntry::getFormatted()
{
  return ("[" + imagePath + "," + imageIndex + "]");
}

std::string ImageEntry::getImagePath()
{
  return imagePath;
}

std::string ImageEntry::getImageIndex()
{
  return imageIndex;
}
