
#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "MenuButton.h"

class CreditButton : public MenuButton
{
public:
   CreditButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size, bool back);
   void update(uint64 time);

private:
   bool bBack;
};

#endif

