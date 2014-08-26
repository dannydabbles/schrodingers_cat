//
//
//
//   Project : Schrödinger's cat
//   File Name : UserInterfaceManager.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_USERINTERFACEMANAGER_H)
#define _USERINTERFACEMANAGER_H

#include "UserInterface.h"
#include "PauseMenu.h"
#include "PauseButton.h"
#include "QuitMenu.h"
#include "LevelNavigation.h"
#include "MainMenu.h"
#include "GameMenu.h"
#include "EndOfLevelMenu.h"
#include "FinishedGameMenu.h"
#include "CreditMenu.h"
#include "s3ePointer.h"

class UserInterfaceManager
{
public:
   UserInterfaceManager(CIwArray<string>);
   ~UserInterfaceManager();
   bool update(uint64 time);
   //void update(uint64 time);
   void draw();
   void reset();
	void resetLevel();
	int getLevel();
   void setWin(int e, int d, uint64 t);
private:
	PauseMenu* pmMenu;
	PauseButton* pbButton;
	LevelNavigation* lnMenu;
	MainMenu* mmMenu;
   EndOfLevelMenu* emMenu;
   GameMenu* gmMenu;
   CreditMenu* cmMenu;
   FinishedGameMenu* fmMenu;
};

#endif  //_USERINTERFACEMANAGER_H
