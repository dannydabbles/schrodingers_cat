//
//
//
//   Project : Schrödinger's cat
//   File Name : SplashScreen.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "SplashScreen.h"

SplashScreen::SplashScreen(CIwSVec2 i2Position): UserInterface()
{
   IW_CALLSTACK("SplashScreen::SplashScreen");

   this->i2Position = i2Position;
}

void SplashScreen::skip() 
{
   IW_CALLSTACK("SplashScreen::skip");
}
