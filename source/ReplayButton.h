#ifndef REPLAY_BUTTON_H
#define REPLAY_BUTTON_H

#include "MenuButton.h"
class ReplayButton : public MenuButton
{
public:
   ReplayButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size);
   void update(uint64 time);
};

#endif

