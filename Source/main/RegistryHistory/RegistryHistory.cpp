/** \file
 * \brief Record changes to 'DefaultIcon' keys in the registry using a custom file format.
 *
 * Designed to manage a custom file format for storing changes made by IconMagic to the registry. Each file extension for which IconMagic has made registry changes will be
 * associated with a list of all the values which have been assigned to the 'DefaultIcon' subkey for that extension. This means that (in the best case) the user can choose to roll
 * back changes, or even revert to the system's default icon.
 *
 * Created by ThetaSinner (Gregory Jensen).
 * Released as open source.
 */

#include "./RegistryHistory.hpp"

// TODO remove temp includes??
#include "./../WindowsToolbox.hpp"
#include "./../Util.hpp"

/** \brief Default constructor.
 */
RegistryHistory::RegistryHistory()
{
  historyFileName = "";
  history = std::vector<ExtensionHistory> ();
}

/** \brief Set the path to the file to be used for storing registry modification history.
 *
 * \param history_file_name std::string
 * \return void
 *
 */
void RegistryHistory::setHistoryFileName(std::string history_file_name)
{
  std::ofstream touch(history_file_name, std::ifstream::app);

  if (touch.is_open())
  {
    historyFileName = history_file_name;
    touch.close();
  }
  else
  {
    historyFileName = "";
  }

  /*
  if(GetFileAttributes(history_file_name.c_str()) == INVALID_FILE_ATTRIBUTES)
  {
    historyFileName = "";
    return;
  }

  historyFileName = history_file_name;
  */
}

/** \brief
 *
 * \return bool
 *
 */
bool RegistryHistory::readHistory()
{
  // TODO If multiple entries are found in the file for the same extension, ask the user to resolve the conflict.

  // This will fail to open if historyFileName is empty.
  std::ifstream reader(historyFileName, std::ifstream::in);
  if(!reader.is_open()) return false;

  while(!reader.eof())
  {
    std::string lineOne, lineTwo;
    reader >> lineOne;
    reader >> lineTwo;

    if(stringIsBlank(lineOne) || stringIsBlank(lineTwo)) break;

    ExtensionHistory extensionHistory;
    extensionHistory.createFromFormatted(lineOne + "\n" + lineTwo);
    if (extensionHistory.isValid())
    {
      history.push_back(extensionHistory);
    }
    else
    {
      // We don't want to delete data that can't currently be used, just store it for now.
      badReads.push_back(lineOne + "\n" + lineTwo);
    }
  }

  reader.close();
  return true;
}

/** \brief
 *
 * \return bool
 *
 */
bool RegistryHistory::writeHistory()
{
  std::ofstream writer(historyFileName, std::ofstream::out);
  if(!writer.is_open()) return false;

  for (auto i : history) writer << i.getFormatted() << "\n";
  for (auto i : badReads) writer << i << "\n";

  writer.close();
  return true;
}

bool RegistryHistory::push(std::string extension_name, std::string image_name, std::string image_index)
{
  ImageEntry imageEntry;
  imageEntry.createFromData(image_name, image_index);
  if (!imageEntry.isValid()) return false;

  bool append = false;
  for(auto &i : history)
  {
    if(i.getExtensionName() == extension_name)
    {
      i.pushImageEntry(imageEntry);
      append = true;
    }
  }

  if (!append)
  {
    ExtensionHistory extensionHistory;
    extensionHistory.createFromData(extension_name, imageEntry);
    if (!extensionHistory.isValid()) return false;

    history.push_back(extensionHistory);
  }

  return true;
}

bool RegistryHistory::pop(std::string extension_name)
{
  for (auto &i : history)
  {
    if (i.getExtensionName() == extension_name)
    {
      int initial = i.size();
      i.popImageEntry();
      int final = i.size();

      return (initial != final);
    }
  }

  return false;
}

void RegistryHistory::deleteExtension(std::string extension_name)
{
  for (std::vector<ExtensionHistory>::iterator i = history.begin(); i != history.end(); i++)
  {
    if (i -> getExtensionName() == extension_name)
    {
      history.erase(i);
      break;
    }
  }
}

std::string RegistryHistory::getPath(std::string extension_name)
{
  return getLast(extension_name).getImagePath();
}

std::string RegistryHistory::getIndex(std::string extension_name)
{
  return getLast(extension_name).getImageIndex();
}

std::string RegistryHistory::getRegString(std::string extension_name)
{
  ImageEntry imageEntry = getLast(extension_name);
  return imageEntry.getImagePath() + "," + imageEntry.getImageIndex();
}

ImageEntry RegistryHistory::getLast(std::string extension_name)
{
  for (auto &i : history)
  {
    if (i.getExtensionName() == extension_name) return i.getLastEntry();
  }

  return ImageEntry();
}
