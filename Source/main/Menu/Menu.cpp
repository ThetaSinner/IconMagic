#include "./Menu.hpp"

Menu::Menu()
{

}

Menu::Menu(std::string title, Menu* sub_menu)
{
  sub_menu -> parent = this;
  add(title, sub_menu);
}

Menu* Menu::add(std::string title, Menu* sub_menu)
{
  menu.insert({title, sub_menu});
  return this;
}

std::list<std::string> Menu::getMenu()
{
  std::list<std::string> list_menu = std::list<std::string>();

  std::cout << "fuckballs";
  for (auto &i : menu)
  {
    list_menu.push_back(i.first);
  }

  return list_menu;
}

Menu* Menu::trigger(std::string name)
{
  return menu.at(name) -> action(name);
}
