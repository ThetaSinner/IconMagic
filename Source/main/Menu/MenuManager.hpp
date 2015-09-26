#ifndef MENU_MANAGER_INCLUDED
#define MENU_MANAGER_INCLUDED

#include "./Menu.hpp"

class MenuManager
{
  public:
  MenuManager(Menu* menu_handle);
  ~MenuManager();

  void start();

  private:
  Menu* menuHandle;
  Menu* menuCurrentViewHandle;

  void cls();
};

#endif
