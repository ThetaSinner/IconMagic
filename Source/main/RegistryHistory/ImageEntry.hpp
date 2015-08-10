#ifndef IMAGE_ENTRY
#define IMAGE_ENTRY

#include <string>

class ImageEntry
{
public:
  const static std::string seperator;
  const static std::string blockOpen;
  const static std::string blockShut;

  ImageEntry();

  void create(std::string image_path, std::string image_index);
  void createFromFormatted(std::string entry);

  bool isValid();

  std::string getImagePath() const;
  std::string getImageIndex() const;
  std::string getFormatted() const;

private:
  std::string imagePath;
  std::string imageIndex;
};

#endif
