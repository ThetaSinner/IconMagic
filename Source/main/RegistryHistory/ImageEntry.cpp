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

void ImageEntry::create(std::string image_path, std::string image_index)
{
  if (!validPathToFile(image_path))  return;

  if (image_index != "")
  {
    if (!stringIsValidInteger(image_index, 0, 1000)) // expose this value.
    {
      return;
    }
  }

  imagePath = image_path;
  imageIndex = image_index;
}

void ImageEntry::createFromFormatted(std::string entry)
{
  if (entry.size() < 3)  return; // require an open bracket, a seperator and a shut bracket.
  if (std::string(1, entry[0]) != blockOpen) return;
  if (std::string(1, entry.back()) != blockShut) return;
  if (static_cast<int> (entry.find(seperator)) == -1) return;

  create(entry.substr(1).substr(0, entry.find(seperator) - 1),
         entry.substr(entry.find(seperator) + 1, entry.find(blockShut) - entry.find(seperator) - 1));
}

bool ImageEntry::isValid()
{
  return (imagePath != "" && imageIndex != "");
}

std::string ImageEntry::getFormatted() const
{
  return (blockOpen + imagePath + seperator + imageIndex + blockShut);
}

std::string ImageEntry::getImagePath() const
{
  return imagePath;
}

std::string ImageEntry::getImageIndex() const
{
  return imageIndex;
}
