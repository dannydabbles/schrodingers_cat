#ifndef SKIP_LEVEL_BUTTON_H
#define SKIP_LEVEL_BUTTON_H


#include "MenuButton.h"

class SkipLevelButton : public MenuButton
{
public:
	SkipLevelButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size);
	void update(uint64 time);
	
};

#endif