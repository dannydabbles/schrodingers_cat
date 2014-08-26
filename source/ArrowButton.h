#ifndef ARROW_BUTTON_H
#define ARROW_BUTTON_H


#include "MenuButton.h"

class ArrowButton : public MenuButton
{
public:
   ArrowButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size, bool foward);
   void update(uint64 time);
private:
   bool foward;
};

#endif

