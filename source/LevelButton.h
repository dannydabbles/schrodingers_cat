#ifndef LEVEL_BUTTON_H
#define LEVEL_BUTTON_H


#include "MenuButton.h"

class LevelButton : public MenuButton
{
public:
   LevelButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size, int num, int arrayIndex);
   bool update(uint64 time, bool update);
	int arrayIndex;
};

#endif
