/*
 *  EndOfLevelMenu.h
 *  Kitty
 *
 *  Created by Sam Medalen on 5/16/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#if !defined(_ENDOFLEVELMENU_H)
#define _ENDOFLEVELMENU_H

#include "GameState.h"
#include "UserInterface.h"
#include "Message.h"

class EndOfLevelMenu : public UserInterface
{
public:
	EndOfLevelMenu();

	void update(uint64 time);
   void setWin(int e, int d, uint64 t);
   void draw();


private:
	
   Message* mRating;
   Message * mBestRating;

   Message * CurrentString;
   Message * mBestString;
   
   Message * mBestClock;
   Message * mCurrentClock;

   Message * mBestTime;
   Message * mCurrentTime;

   Message * mCurrentCheck;
   Message * mBestCheck;

   CIwSVec2 opaquePos;
   CIwSVec2 opaqueSize;
   CIwColour opaqueColor;
   CIwColour goldColor;
   CIwColour blackColor;
   CIwColour greenColor;

   bool dispalyBestCheck;
   bool disaplyCurrentCheck;
   bool bestDeathSoundPlayed;
   

  

   
};

#endif // _ENDOFLEVELMENU_