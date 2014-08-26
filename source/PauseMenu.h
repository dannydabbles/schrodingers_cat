//
//
//
//   Project : Schrödinger's cat
//   File Name : PauseMenu.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_PAUSEMENU_H)
#define _PAUSEMENU_H

#include "GameState.h"
#include "UserInterface.h"
#include <iomanip>



class PauseMenu : public UserInterface
{
public:
   PauseMenu();
   ~PauseMenu();

	void update(uint64 time);
   void draw();

private:
   CIwSVec2 opaquePos;
   CIwSVec2 opaqueSize;
   CIwColour opaqueColor;

   Message * mHighScore;
   Message * mHighScoreDeath;
   Message * mDeadCat;
   Message * mX;
   Message * mClock;
   Message * mHighScoreTime;
   
 
 };

#endif  //_PAUSEMENU_H
