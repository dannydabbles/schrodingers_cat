//
//
//
//   Project : Schrödinger's cat
//   File Name : SplashScreen.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_SPLASHSCREEN_H)
#define _SPLASHSCREEN_H

#include "UserInterface.h"

class SplashScreen : public UserInterface
{
public:
   SplashScreen(CIwSVec2 i2Position);
private:
   void skip();
};

#endif  //_SPLASHSCREEN_H
