//
//
//
//   Project : Schrödinger's cat
//   File Name : LevelNavigation.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_LEVELNAVIGATION_H)
#define _LEVELNAVIGATION_H

#include "UserInterface.h"
#include "PlayerProfile.h"
#include "BackgroundManager.h"

class LevelNavigation : public UserInterface
{
public:
   LevelNavigation(CIwArray<string>);
   ~LevelNavigation();
   bool update(uint64 time, bool update);
   void draw();

   int getLevel();
private:
   int page;
	int worldPage;
   int levelsPerPage;
   int totalLevels;
   int iLevel;
	int iWorld;
	int iWorldLevel;
   float numberOfPages;
   CIwArray<string> mapNames;
   CIwArray<CIwArray<CIwArray<LevelButton*> > > levelButtonList;
   BackgroundManager * bgManager;
	bool firstTut;


   ArrowButton * back;
   ArrowButton * foward;
   MainMenuButton * mainMenu;
};

#endif  //_LEVELNAVIGATION_H
