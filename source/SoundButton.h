#ifndef SOUND_BUTTON_H
#define SOUND_BUTTON_H

#include "Menubutton.h"

class SoundButton : public MenuButton
{
public:
   SoundButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size);
   
   void update(uint64 time);

private:
};

#endif
