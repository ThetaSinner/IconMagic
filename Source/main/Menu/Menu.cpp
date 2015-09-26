#include "./Menu.hpp"

#include <iostream>

Menu::Menu()
{

}

Menu::~Menu()
{
  parent = nullptr;
  for (auto &i : menu)
  {
    delete i.second;
    i.second = nullptr;
  }
}

Menu::Menu(std::string title, Menu* sub_menu)
{
  add(title, sub_menu);
}

Menu* Menu::add(std::string title, Menu* sub_menu)
{
  sub_menu -> parent = this;
  menu.push_back({title, sub_menu});
  return this;
}

std::vector<std::string> Menu::getMenu()
{
  std::vector<std::string> displayMenu = std::vector<std::string> ();
  for (auto &i : menu) displayMenu.push_back(i.first);
  return displayMenu;
}

Menu* Menu::getParent()
{
  return parent;
}

Menu* MenuBranch::action(std::string input)
{
  for (auto &i : menu) if (i.first == input) return i.second;
  return nullptr;
}

Menu* MenuLeaf::action(std::string input)
{
  for (auto &i : actions)
  {
    i();
  }
  //std::cout << "leaf update\n" << input << "\n";
  return parent;
}

Menu* MenuLeaf::addAction(std::function<int(void)> f)
{
  actions.push_back(f);
  return this;
}

Menu* MenuExit::action(std::string _)
{
  //std::cout << "menu exit\n";
  return (parent == nullptr ? parent : getParent() -> getParent());
}
