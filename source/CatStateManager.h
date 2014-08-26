//
//
//
//   Project : Schrödinger's cat
//   File Name : CatStateManager.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_CATSTATEMANAGER_H)
#define _CATSTATEMANAGER_H

#include "CatState.h"
#include "Iw2D.h"

class CatStateManager
{
public:
   CatStateManager();
	
	CatState::State getPrevious();
   CatState::State getNext();
   void pushState(CatState::State newState);
	void reset();
   void update();
	
private:
	CatState::State csNext;
   CatState::State csPrevious;
	
   void idling();
   void walkingLeft();
   void walkingRight();
   void jumpingLeft();
   void jumpingRight();
   void playing();
   
   void idleToLeft();
   void idleToRight();
   void idleToPlay();
   void leftToIdle();
   void leftToRight();
   void leftToJumpLeft();
   void leftToPlay();
   void rightToIdle();
   void rightToLeft();
   void rightToJumpRight();
   void rightToPlay();
   void jumpLeftToIdle();
   void jumpLeftToLeft();
   void jumpLeftToPlay();
   void jumpRightToIdle();
   void jumpRightToRight();
   void jumpRightToPlay();
   void playToIdle();
   void playToLeft();
   void playToRight();
   
   void resolveStates();
};

#endif