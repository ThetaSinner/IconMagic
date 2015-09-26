#include "./MenuManager.hpp"

#include <Windows.h>
#include <iostream>
#include <string>
#include <list>

MenuManager::MenuManager(Menu* menu_handle)
{
  menuHandle = menuCurrentViewHandle = menu_handle;
}

MenuManager::~MenuManager()
{
  menuCurrentViewHandle = nullptr;
  menuHandle = nullptr;
}

void MenuManager::start()
{
  while (menuCurrentViewHandle != nullptr)
  {
    system("cls");

    std::vector<std::string> currentMenuItems = menuCurrentViewHandle -> getMenu();

    if (currentMenuItems.size() == 0)
    {
      // No more submenus to draw, trigger leaf actions.
      menuCurrentViewHandle = menuCurrentViewHandle -> action("");
    }
    else
    {
      int hint = 1;
      for (auto i : currentMenuItems)
      {
        std::cout << hint << " : " << i << "\n";
        hint++;
      }
      std::cout << "\n";

      int selection = -1;
      while (selection < 1 || selection > currentMenuItems.size())
      {
        std::cout << ">>> ";
        std::cin >> selection;
      }

      menuCurrentViewHandle = menuCurrentViewHandle -> action(currentMenuItems.at(selection - 1));
    }
  }

  std::cout << "done\n";
  std::cin.get();
}

void MenuManager::cls()
{
  for (int i = 0; i < 32; i++) std::cout << "\n";
}
