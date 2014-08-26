//
//
//
//   Project : Schrödinger's cat
//   File Name : GameMenu.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_GAMEMENU_H)
#define _GAMEMENU_H

#include "UserInterface.h"

class GameMenu : public UserInterface
{
public:
   GameMenu();
   void draw();

private:
   //Message* mTime;
   //Message* mDeaths;
   stringstream ssHUD;
   string seconds;
   string minutes;
};

#endif  //_GAMEMENU_H