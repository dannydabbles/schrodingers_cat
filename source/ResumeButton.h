#ifndef RESUME_BUTTON_H
#define RESUME_BUTTON_H

#include "MenuButton.h"

class ResumeButton : public MenuButton
{
public:
   ResumeButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size);
   void update(uint64 time);
};


#endif

