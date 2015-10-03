#include "./MenuFactory.hpp"

#include <iostream>

int func()
{
  std::cout << "pop it\n";
  std::cin.get();
  std::cin.get();
}

int rebuildTheWindowsIconCache()
{
  std::cout << "Rebuilding the icon cache.\n";
  std::cin.get();
  std::cin.get();
  return 0;
}

Menu* MenuFactory::getMainMenuInstance()
{
  Menu* modifyAnIcon =
  (new MenuBranch("Add a new icon",    (new MenuLeaf()) -> addAction(rebuildTheWindowsIconCache)))
           -> add("Roll back an icon", (new MenuLeaf()) -> addAction(rebuildTheWindowsIconCache))
           -> add("Back",               new MenuExit());

  Menu* changeIcons =
  (new MenuBranch("Build IconMagic cache",                      (new MenuLeaf()) -> addAction(rebuildTheWindowsIconCache)))
           -> add("Sync the registry with the IconMagic cache", (new MenuLeaf()) -> addAction(rebuildTheWindowsIconCache))
           -> add("Modify an icon",                             modifyAnIcon)
           -> add("Back",                                       new MenuExit());

  Menu* lookupIcons =
  (new MenuBranch("Lookup by file extension",    (new MenuLeaf()) -> addAction(rebuildTheWindowsIconCache)))
           -> add("Lookup by registry key name", (new MenuLeaf()) -> addAction(rebuildTheWindowsIconCache))
           -> add("Back",                         new MenuExit());

  Menu* mainMenu =
  (new MenuBranch("Change icons", changeIcons))
           -> add("Lookup icons", lookupIcons)
           -> add("Rebuild the windows icon cache", (new MenuLeaf()) -> addAction(rebuildTheWindowsIconCache))
           -> add("Exit", new MenuExit());

  return mainMenu;
}
