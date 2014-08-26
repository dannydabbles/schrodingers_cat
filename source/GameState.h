//
//
//
//   Project : Schrˆdinger's cat
//   File Name : GameStates.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#ifndef _GAMESTATE_H
#define _GAMESTATE_H

#include "IwUtil.h"

class GameState
{
public:
	enum State
	{
		MAINMENU,
      CREDITMENU,
      CREDITMENUBACK,
      GAMEOVER,
		LEVELNAVIGATION,
      PAGELEFT,
      PAGERIGHT,
		PAUSE,
      RESET,
		SCORESCREEN,
		PLAY,
		LEVELBEATEN,
		SKIPLEVEL,
		__START_CUTSCENES__,
		CUTSCENE,
		__END_CUTSCENESE__
	};
	
	static void setReInitializePathing(bool bReInit);
	static void setState(State state);
	static void setDebugging(bool bDebug);
   static void setReset(bool bSetReset);
	static void setResume(bool bSetResume);
	
	static bool getReInitializePathing();
	static bool getDebugging();
	static bool getResume();
   static bool getReset();
	static State getState();
	
private:
	static State gsCurrent;
	static bool bReInitializePathing;
	static bool bDebugging;
   static bool bResume;
   static bool bReset;
};

#endif
