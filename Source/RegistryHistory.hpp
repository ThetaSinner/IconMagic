#ifndef REGISTRYHISTORY_HPP_INCLUDED
#define REGISTRYHISTORY_HPP_INCLUDED

#include <string>
#include <vector>

class ExtensionEntry;
class ImageEntry;

class RegistyHistory
{
private:
    std::string historyFileName;

public:
    bool readHistory(std::string fileName);
    bool writeHistory();

    bool addNewEntry(std::string extName, ImageEntry imageEntry);

    // bool selectEntryByExtensionName(std::string extName);
};

class ExtensionEntry
{
private:
    std::string extensionName;
    std::vector<ImageEntry> imageHistory;
    std::vector<std::string> infoEntries;

public:
    ExtensionEntry();
    ExtensionEntry(std::string entry);

    void createEntryFromRawData(std::string extension_name, std::vector<ImageEntry> image_history, std::vector<std::string> info_entries);
    void loadEntryFromFormatted(std::string entry);

    std::string getFormatted();

    std::string getExtensionName();
    std::vector<ImageEntry> getImageHistory();
    std::vector<std::string> getInfoEntries();
};

class ImageEntry
{
private:
    std::string imagePath;
    std::string imageIndex;

public:
    ImageEntry();
    ImageEntry(std::string entry);

    void createEntryFromRawData(std::string image_path, std::string image_index);
    void loadEntryFromFormatted(std::string entry);

    std::string getFormatted();

    std::string getImagePath();
    std::string getImageIndex();
};

#endif // REGISTRYHISTORY_HPP_INCLUDED
