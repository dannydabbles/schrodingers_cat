/*
 *  FinishedGameMenu.h
 *  Kitty
 *
 *  Created by Sam Medalen on 5/16/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#if !defined(_FINISHEDGAMEMENU_H)
#define _FINISHEDGAMEMENU_H

#include "GameState.h"
#include "UserInterface.h"
#include "Message.h"

class FinishedGameMenu : public UserInterface
{
public:
	FinishedGameMenu();

	void update(uint64 time);
   void draw();
   void setWin();


private:
	
  Message * credits;
  
   Message * DeatchCount;

   bool bRolling;
	bool bFadeOut;
	int imIndex;

   CIwSVec2 opaquePos;
   CIwSVec2 opaqueSize;
   CIwColour opaqueColor;
   CIwColour goldColor;
   CIwColour blackColor;

   float fAlpha;
   float fAlphaInit;

   
};

#endif // _FINISHEDGAMEMENU_H