//
//
//
//   Project : Schrˆdinger's cat
//   File Name : CatStates.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_CATSTATE_H)
#define _CATSTATE_H

#include "IwUtil.h"

class CatState
{
public:
	enum State
	{
      __START_IDLE_STATES__,        //0
		IDLING,                       //1
      __END_IDLE_STATES__,          //2
      __START_MOVEMENT_STATES__,    //3
		WALKINGLEFT,                  //4
      WALKINGRIGHT,                 //5
		JUMPINGLEFT,                  //6
      JUMPINGRIGHT,                 //7
      __END_MOVEMENT_STATES__,      //8
      __START_CATEVENT_STATES__,    //9
		LICKINGSELF,                  //10
		ROLLING,                      //11
		SCRATCHINGSELF,               //12
		STRETCHING,                   //13
      __END_CATEVENT_STATES__,      //14
      __START_PLAYWITH_STATES__,    //15
		SCRATCHINGPOST,               //16
		BATTING,                      //17
		MOUSEPLAYING,                 //18
      EATINGFOOD,                   //19
      POOPING,                      //20
      __END_PLAYWITH_STATES__,      //21
      __START_INTERRUPT_STATES__,   //22
      DEAD,                         //23
      TRANSITIONING,                //24
      __END_INTERRUPT_STATES__,     //25
      __START_TRANSITION_STATES__,  //26
      IDLETOLEFT,                   //27
      IDLETORIGHT,                  //28
      IDLETOPLAY,                   //29
      LEFTTOIDLE,                   //30
      LEFTTORIGHT,                  //31
      LEFTTOJUMPLEFT,               //32
      LEFTTOPLAY,                   //33
      RIGHTTOIDLE,                  //34
      RIGHTTOLEFT,                  //35 
      RIGHTTOJUMPRIGHT,             //36
      RIGHTTOPLAY,                  //37
      JUMPLEFTTOIDLE,               //38
      JUMPLEFTTOLEFT,               //39
      JUMPLEFTTOPLAY,               //40
      JUMPRIGHTTOIDLE,              //41
      JUMPRIGHTTORIGHT,             //42
      JUMPRIGHTTOPLAY,              //43
      PLAYTOIDLE,                   //44
      PLAYTOLEFT,                   //45
      PLAYTORIGHT,                  //46
      __END_TRANSITION_STATES__     //47
	};
	
	static void setState(State state);
   static bool isIdle();
   static bool isMoving();
   static bool isPlayingWithEvent();
   static bool isPlayingWith();
   static bool isInterrupting();
   static bool isTransitioning();
	static State getState();
	
private:
	static State csCurrent;
};

#endif