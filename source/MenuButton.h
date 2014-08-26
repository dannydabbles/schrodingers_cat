/*
 *  MenuButton.h
 *  Kitty
 *
 *  Created by Sam Medalen on 4/29/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#if !defined(_MENU_BUTTON_H)
#define _MENU_BUTTON_H

#include "Unit.h"

class MenuButton : public virtual Unit
{
public:
	MenuButton();
   ~MenuButton();

	void update(uint64 time);
   void draw();
   bool hit(CIwSVec2 touch);
   void setPosition(CIwSVec2 menuPosition);
   void setBoundingBox(CIwSVec2);
   void changeImage(string s);
	
protected:
   CIwSVec2 i2Offset;
   bool bScreenTouched;
   bool bPressed;
};

#endif // _MENU_BUTTON_H