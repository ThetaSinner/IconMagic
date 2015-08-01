/** \file main.cpp
 * \brief Created by ThetaSinner (Gregory Jensen).
 *        Released as open source.
 *
 * This file launches IconMagic.
 */

#include "IconMagic.hpp"
#include "Testing.hpp"

// Sources for DefaultIcon
// https://msdn.microsoft.com/en-us/library/windows/desktop/hh127427%28v=vs.85%29.aspx
// https://msdn.microsoft.com/en-us/library/windows/desktop/bb762118%28v=vs.85%29.aspx

// Navigate to HKEY_CLASSES_ROOT
// Look for the file type you want to modify, e.g. .aiff, .mp3, .txt
// Then look for a DefaultIcon sub key. If you don't see one, you may have to go
// down the rabbit hole a little, for example with audio, the default value of the .aiff key is
// wmp11... search for this key, and that has a DefaultIcon sub key.

#include <iostream>

#include "RegistryHistory.hpp"

int main(int argc, char **args)
{
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

  if(!inHist.writeHistory())
  {
    std::cout << "Failed to write history 2.\n";
  }

  return 0;
  return runIconMagic();
}
