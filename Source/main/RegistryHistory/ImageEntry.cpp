#include "ImageEntry.hpp"

#include <sstream>
#include "./../WindowsToolbox.hpp"
#include "./../Util.hpp"

const std::string ImageEntry::seperator = ",";
const std::string ImageEntry::blockOpen = "[";
const std::string ImageEntry::blockShut = "]";

ImageEntry::ImageEntry()
{
  imagePath = "";
  imageIndex = "";
}

void ImageEntry::createFromData(std::string image_path, std::string image_index)
{
  // Don't allow overwrite, check path is valid and index can be converted to an integer.
  if (isValid() || !validPathToFile(image_path) || !stringIsValidInteger(image_index, 0, 1000)) return; // TODO expose this value?

  create(image_path, image_index);
}

void ImageEntry::createFromFormatted(std::string entry)
{
  // require an open bracket, a seperator and a shut bracket.
  if (entry.size() < 3 || entry[0] != blockOpen[0] || entry.back() != blockShut[0] || stringContains(entry, seperator)) return;

  int seperatorPosition = entry.find(seperator);
  createFromData(
    entry.substr(1, seperatorPosition - 1),
    entry.substr(seperatorPosition + 1, entry.size() - seperatorPosition - 2));
}

std::string ImageEntry::getImagePath() const
{
  return imagePath;
}

std::string ImageEntry::getImageIndex() const
{
  return imageIndex;
}

std::string ImageEntry::getFormatted() const
{
  return (blockOpen + imagePath + seperator + imageIndex + blockShut);
}

bool ImageEntry::isValid()
{
  return (imagePath != "" && imageIndex != "");
}

// Private

void ImageEntry::create(std::string image_path, std::string image_index)
{
  imagePath = image_path;
  imageIndex = image_index;
}
