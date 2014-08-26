#ifndef NEXT_LEVEL_BUTTON_H
#define NEXT_LEVEL_BUTTON_H


#include "MenuButton.h"

class NextLevelButton : public MenuButton
{
public:
   NextLevelButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size);
   void update(uint64 time);
   
};

#endif

