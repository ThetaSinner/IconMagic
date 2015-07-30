#include "RegistryHistory.hpp"



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
