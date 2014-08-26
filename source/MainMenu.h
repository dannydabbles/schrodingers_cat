//
//
//
//   Project : Schrödinger's cat
//   File Name : MainMenu.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_MAINMENU_H)
#define _MAINMENU_H

#include "UserInterface.h"
#include "BackgroundManager.h"

class MainMenu : public UserInterface
{

public:
   MainMenu();
   ~MainMenu();
   void draw();


private:
	BackgroundManager * bgManager;
};

#endif  //_MAINMENU_H
