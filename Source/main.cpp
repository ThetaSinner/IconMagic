/** \file main.cpp
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * This file launches IconMagic.
 */

#include "main/IconMagic.hpp"
//#include "Testing.hpp"

// Sources for DefaultIcon
// https://msdn.microsoft.com/en-us/library/windows/desktop/hh127427%28v=vs.85%29.aspx
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb762118%28v=vs.85%29.aspx

// Navigate to HKEY_CLASSES_ROOT
// Look for the file type you want to modify, e.g. .aiff, .mp3, .txt
// Then look for a DefaultIcon sub key. If you don't see one, you may have to go
// down the rabbit hole a little, for example with audio, the default value of the .aiff key is
// wmp11... search for this key, and that has a DefaultIcon sub key.

#include <iostream>
#include "./main/RegistryHistory/RegistryHistory.hpp"

//#include "test/RegistryHistoryTest.hpp"

#include <sstream>
#include <fstream>

int main(int argc, char **args)
{
  ImageEntry image;
  image.createFromData("musicIcon.ico", "12");
  if (image.isValid()) std::cout << "Image is valid.\n";
  else std::cout << "Image invalid.\n";
  std::cout << image.getImagePath() << "\n";
  std::cout << image.getImageIndex() << "\n";

  ExtensionHistory extensionHistory;
  extensionHistory.createFromData(".bat", image);
  if (extensionHistory.isValid()) std::cout << "valid.\n";
  else std::cout << "Invalid\n";
  std::cout << extensionHistory.getExtensionName() << "\n";

  RegistryHistory r;
  r.setHistoryFileName("sol.txt");
  r.push(".bat", "musicIcon.ico", "4");
  r.push(".bat", "musicIcon.ico", "12");
  r.push(".mp3", "musicIcon.ico", "3");
  std::cout << r.getRegString(".bat") << "\n";
  r.writeHistory();

  RegistryHistory s;
  s.setHistoryFileName("sol.txt");
  s.readHistory();
  s.setHistoryFileName("sol2.txt");
  s.writeHistory();

  std::cin.get();
  return 0;

  /*
  int totalTestsRun_RegistryHistory = 0;
  int totalTestsRunSuccessfully_RegistryHistory = 0;

  if(testRegistryHistory(totalTestsRun_RegistryHistory, totalTestsRunSuccessfully_RegistryHistory))
  {
    std::cout << "Tests for registry history succeeded.\n";
  }
  else
  {
    std::cout << "Tests for registry history failed.\n";
  }

  std::cout << totalTestsRunSuccessfully_RegistryHistory << " of " << totalTestsRun_RegistryHistory << " tests ran successfully.\n";
  return 0;
  */
  /*
  ImageEntry i;
  i.createEntryFromRawData("sloppy.png", "");
  std::cout << i.getFormatted() << "\n";
  ImageEntry k;
  k.loadEntryFromFormatted(i.getFormatted());
  std::cout << k.getFormatted() << "\n";
  */
  /*
  ExtensionEntry e;
  e.createEntryFromRawData(".mp3", std::vector<ImageEntry> ());
  e.pushImageEntry(ImageEntry("[blue.png,5]"));
  e.pushImageEntry(ImageEntry("[yellow.png,1]"));
  e.pushImageEntry(ImageEntry("[red.jpg,3]"));

  ExtensionEntry f(e.getFormatted());

  std::cout << e.getFormatted() << "\n\n";

  std::cout << f.getFormatted() << "\n\n";

  return 0;
  */
  /*
  RegistryHistory regHist(".\\test\\testhistory.txt");
  regHist.addNewEntry(".png", "funnyfaces.png", "1");
  regHist.addNewEntry(".aiff", "yummy.jpg", "5");
  regHist.addImageEntryToExistingExtension(".png", "yellowmonkey.bmp", "10");

  if(!regHist.writeHistory())
  {
    std::cout << "Failed to write history.\n";
  }

  RegistryHistory inHist(".\\test\\testhistory.txt");

  if(!inHist.readHistory())
  {
    std::cout << "Failed to read history 2.\n";
  }

  inHist.setHistoryFileName(".\\test\\testhistory2.txt");
  inHist.addImageEntryToExistingExtension(".aiff", "bumcheese.pdf", "12");

  if(!inHist.writeHistory())
  {
    std::cout << "Failed to write history 2.\n";
  }
  */
  //return 0;
  return runIconMagic();
}
