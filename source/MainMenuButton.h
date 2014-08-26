#ifndef MAIN_MENU_BUTTON_H
#define MAIN_MENU_BUTTON_H

#include "MenuButton.h"

class MainMenuButton : public MenuButton
{
public:
   MainMenuButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size);
   void update(uint64 time);
};

#endif

