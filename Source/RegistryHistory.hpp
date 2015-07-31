#ifndef REGISTRYHISTORY_HPP_INCLUDED
#define REGISTRYHISTORY_HPP_INCLUDED

#include <string>
#include <vector>

class ExtensionEntry;
class ImageEntry;

class RegistryHistory
{
private:
    std::string historyFileName;
    std::vector<ExtensionEntry> extensionHistory;

public:
    RegistryHistory();
    RegistryHistory(std::string history_file_name);

    void setHistoryFileName(std::string history_file_name);

    bool readHistory();
    bool writeHistory();

    void addNewEntry(std::string extension_name, std::string image_name, std::string image_index);
    void addImageEntryToExistingExtension(std::string image_name, std::string image_index);

    // bool selectEntryByExtensionName(std::string extName);
};

class ExtensionEntry
{
private:
    std::string extensionName;
    std::vector<ImageEntry> imageHistory;

public:
    ExtensionEntry();
    ExtensionEntry(std::string entry);

    void createEntryFromRawData(std::string extension_name, std::vector<ImageEntry> image_history);
    void loadEntryFromFormatted(std::string entry);
    std::string getFormatted();

    void pushImageEntry(ImageEntry image_entry);
    int getNumberOfImageEntries();
    ImageEntry getImageEntryAt(int index);

    #ifdef DEBUG_BUILD
    std::string getExtensionName();
    std::vector<ImageEntry> getImageHistory();
    #endif // DEBUG_BUILD
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

    #ifdef DEBUG_BUILD
    std::string getImagePath();
    std::string getImageIndex();
    #endif // DEBUG_BUILD
};

#endif // REGISTRYHISTORY_HPP_INCLUDED
