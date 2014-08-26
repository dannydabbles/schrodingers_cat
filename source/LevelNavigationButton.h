#ifndef LEVEL__NAVIGATION_BUTTON_H
#define LEVEL_NAVIGATION_BUTTON_H


#include "MenuButton.h"

class LevelNavigationButton : public MenuButton
{
public:
   LevelNavigationButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size, bool mainMenu );
   LevelNavigationButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size, string sSpriteName);

   void update(uint64 time);
};

#endif

