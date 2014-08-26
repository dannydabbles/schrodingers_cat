//
//
//
//   Project : Schrödinger's cat
//   File Name : Screen.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Iw2D.h"

#if !defined(_SCREEN_H)
#define _SCREEN_H

class Screen 
{
public:
   static void init();
   static CIwSVec2 getSCREENSIZE();
   static CIwSVec2 getBOXSIZE(); 
   static CIwSVec2 getGRIDSIZE();
   static CIwSVec2 getPHONESIZE();
   static CIwFVec2 getMOVEMULTIPLIER();
private:
   static float fRatio;
   static CIwSVec2 BOXSIZE;
   static CIwSVec2 SCREENSIZE;
   static CIwSVec2 PHONESIZE;
   static CIwSVec2 GRIDSIZE;
   static CIwFVec2 MOVEMULTIPLIER;
} ;

#endif  
