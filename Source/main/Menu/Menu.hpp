#ifndef MENU_INCLUDED
#define MENU_INCLUDED

#include <map>
#include <list>

#include <iostream>

class Menu
{
  public:
  Menu();
  Menu(std::string title, Menu* sub_menu);
  Menu* add(std::string title, Menu* sub_menu);

  virtual Menu* action(std::string input) = 0;

  std::list<std::string> getMenu();
  Menu* trigger(std::string name);

  protected:
  Menu* parent = nullptr;
  std::map<std::string, Menu*> menu;
};

class MenuBranch : public Menu
{
  using Menu::Menu;

  Menu* action(std::string input)
  {
    std::cout << "branch update\n" << input << "\n";

    return menu.at(input);
  }
};

class MenuLeaf : public Menu
{
  using Menu::Menu;

  Menu* action(std::string input)
  {
    // do all registered actions.

    std::cout << "leaf update\n" << input << "\n";

    return (input == "back" ? parent : this);
  }
};

#endif
