//
//
//
//   Project : Schrödinger's cat
//   File Name : UserInterface.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_USERINTERFACE_H)
#define _USERINTERFACE_H


#include "ArrowButton.h"
#include	"CreditButton.h"
#include	"LevelButton.h"
#include	"LevelNavigationButton.h"
#include	"MainMenuButton.h"
#include	"NextLevelButton.h"
#include	"PauseButton.h"
#include	"ReplayButton.h"
#include	"ResumeButton.h"
#include	"SkipLevelButton.h"
#include	"SoundButton.h"
#include	"Message.h"
#include	"FontManager.h"


class UserInterface : public Unit
{
public:
   UserInterface();
   ~UserInterface();
   virtual void update(uint64 time);
   virtual void draw();

protected:
	CIwArray<MenuButton*> mbHitList;
    CIwArray<Message*> mMessageList;

};

#endif  //_USERINTERFACE_H
