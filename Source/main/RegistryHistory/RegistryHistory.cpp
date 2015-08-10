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
  std::ifstream touch(history_file_name, std::ifstream::app);
  touch.close();

  if(GetFileAttributes(history_file_name.c_str()) == INVALID_FILE_ATTRIBUTES)
  {
    historyFileName = "";
    return;
  }

  historyFileName = history_file_name;
}

/** \brief
 *
 * \return bool
 *
 */
bool RegistryHistory::readHistory()
{
  // This will fail to open if historyFileName is empty.
  std::ifstream reader(historyFileName, std::ifstream::in);
  if(!reader.is_open()) return false;

  while(!reader.eof())
  {
    std::string lineOne, lineTwo;
    reader >> lineOne;
    reader >> lineTwo;

    if(isStringBlank(lineOne) || isStringBlank(lineTwo))
    {
      break;
    }

    ExtensionHistory extensionHistory;
    extensionHistory.createFromFormatted(lineOne + "\n" + lineTwo);
    this -> history.push_back(extensionHistory);    // this needs some way to fail safely.
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
  if(historyFileName == "")
  {
    return false;
  }

  std::ofstream writer(historyFileName, std::ofstream::out);

  if(!writer.is_open())
  {
    return false;
  }

  for(auto i : history)
  {
    writer << i.getFormatted() << "\n";
  }

  writer.close();
  return true;
}

void RegistryHistory::add(std::string extension_name, std::string image_name, std::string image_index)
{
  ImageEntry imageEntry;
  imageEntry.create(image_name, image_index);
  ExtensionHistory extensionHistory;
  extensionHistory.create(extension_name, imageEntry);
  this -> history.push_back(extensionHistory);
}

void RegistryHistory::update(std::string existing_extension_name, std::string image_name, std::string image_index)
{
  for(auto &i : this -> history)
  {
    if(i.getExtensionName() == existing_extension_name)
    {
      ImageEntry imageEntry;
      imageEntry.create(image_name, image_index);
      i.pushImageEntry(imageEntry);
    }
  }
}
