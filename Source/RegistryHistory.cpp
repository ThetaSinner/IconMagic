#include "RegistryHistory.hpp"

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

void ExtensionEntry::createEntryFromRawData(std::string extension_name, std::vector<ImageEntry> image_history)
{
    this -> extensionName = extension_name;
    this -> imageHistory = image_history;
}

void ExtensionEntry::loadEntryFromFormatted(std::string entry)
{
    this -> extensionName = entry.substr(0, entry.find("\n"));

    std::string imageEntryLine = entry.substr(entry.find("\n") + 1);
    do {
        if (imageEntryLine[0] == '[')
        {
            std::string imageEntryString = imageEntryLine.substr(0, imageEntryLine.find("]") + 1);
            this -> imageHistory.push_back(ImageEntry(imageEntryString));
            imageEntryLine = imageEntryLine.substr(imageEntryString.size());
        }
        else if (imageEntryLine[0] == ',')
        {
            imageEntryLine = imageEntryLine.substr(1);
        }
        else
        {
            // failure.
            break;
        }
    } while (imageEntryLine.size());
}

std::string ExtensionEntry::getFormatted()
{
    std::string temp = "";
    temp += extensionName;
    temp += "\n";
    int numberOfImageEntries = getNumberOfImageEntries();
    for (int i = 0; i < numberOfImageEntries; i++)
    {
        temp += imageHistory[i].getFormatted();
        if (i + 1 != numberOfImageEntries) temp += ",";
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
    if (0 <= index && index < getNumberOfImageEntries())
    {
        return imageHistory[index];
    }

    return ImageEntry();
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

#ifdef DEBUG_BUILD
std::string ImageEntry::getImagePath()
{
    return imagePath;
}

std::string ImageEntry::getImageIndex()
{
    return imageIndex;
}
#endif // DEBUG_BUILD
