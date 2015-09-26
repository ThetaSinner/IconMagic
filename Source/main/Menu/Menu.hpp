#ifndef MENU_INCLUDED
#define MENU_INCLUDED

#include <map>
#include <vector>
#include <list>
#include <functional>

class Menu
{
  public:
  Menu();
  ~Menu();

  // Build.
  Menu(std::string title, Menu* sub_menu);
  Menu* add(std::string title, Menu* sub_menu);

  std::vector<std::string> getMenu();
  Menu* getParent();
  virtual Menu* action(std::string input) = 0;

  protected:
  Menu* parent = nullptr;
  std::vector<std::pair<std::string, Menu*>> menu;
};

class MenuBranch : public Menu
{
  public:
  using Menu::Menu;
  Menu* action(std::string input);
};

class MenuLeaf : public Menu
{
  public:
  using Menu::Menu;
  Menu* action(std::string input);

  Menu* addAction(std::function<int(void)> f);

  private:
  std::list<std::function<int(void)>> actions;
};

class MenuExit: public MenuLeaf
{
  public:
  using Menu::Menu;
  Menu* action(std::string _);
};

#endif
