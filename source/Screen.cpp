//
//
//
//   Project : Schrödinger's cat
//   File Name : Screen.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Screen.h"

CIwSVec2 Screen::BOXSIZE = CIwSVec2(0, 0);
CIwSVec2 Screen::GRIDSIZE = CIwSVec2(15, 12);
CIwSVec2 Screen::SCREENSIZE = CIwSVec2(0, 0);
CIwSVec2 Screen::PHONESIZE = CIwSVec2(0, 0);
CIwFVec2 Screen::MOVEMULTIPLIER = CIwFVec2(0, 0);
float Screen::fRatio = 0.0f;

void Screen::init()
{
   IW_CALLSTACK("Screen::init");

   PHONESIZE = CIwSVec2(s3eSurfaceGetInt(S3E_SURFACE_WIDTH), s3eSurfaceGetInt(S3E_SURFACE_HEIGHT));
   //IwAssertMsg(MYAPP, false, ("Phone width: %d Phone height: %d", PHONESIZE.x, PHONESIZE.y));
   fRatio = (float)PHONESIZE.x / (float)PHONESIZE.y;

   if( fRatio < 1.0f )
   {
      PHONESIZE = CIwSVec2(s3eSurfaceGetInt(S3E_SURFACE_HEIGHT), s3eSurfaceGetInt(S3E_SURFACE_WIDTH));
      fRatio = (float)PHONESIZE.x / (float)PHONESIZE.y;
   }
   //IwAssertMsg(MYAPP, false, ("Ratio: %f", fRatio));

   // ideal screen size
   if(fRatio == 1.5f)
   {
      BOXSIZE = CIwSVec2(PHONESIZE.x / GRIDSIZE.x, PHONESIZE.y / (GRIDSIZE.y - 2));
   }
   // too wide
   else if(fRatio > 1.5f)
   {
      BOXSIZE = CIwSVec2(PHONESIZE.y / (GRIDSIZE.y - 2), PHONESIZE.y / (GRIDSIZE.y - 2));
   }
   // too tall
   else 
   {
      BOXSIZE = CIwSVec2(PHONESIZE.x / GRIDSIZE.x, PHONESIZE.x / GRIDSIZE.x);
   }
   SCREENSIZE = CIwSVec2(BOXSIZE.x * GRIDSIZE.x, BOXSIZE.y * (GRIDSIZE.y - 2));
   MOVEMULTIPLIER = CIwFVec2((float)BOXSIZE.x / 32, (float)BOXSIZE.y / 32);
   //IwAssertMsg(MYAPP, false, ("Box width: %d Box height: %d", BOXSIZE.x, BOXSIZE.y));
   //IwAssertMsg(MYAPP, false, ("Screen width: %d Screen height: %d", SCREENSIZE.x, SCREENSIZE.y));
}

CIwSVec2 Screen::getBOXSIZE()
{
   IW_CALLSTACK("Screen::getBOXSIZE");

   return BOXSIZE;
}

CIwSVec2 Screen::getSCREENSIZE()
{
   IW_CALLSTACK("Screen::getSCREENSIZE");

   return SCREENSIZE;
}

CIwSVec2 Screen::getGRIDSIZE()
{
   IW_CALLSTACK("Screen::getGRIDSIZE");

   return GRIDSIZE;
}

CIwFVec2 Screen::getMOVEMULTIPLIER()
{
   IW_CALLSTACK("Screen::getMOVEMULTIPLIER");

   return MOVEMULTIPLIER;
}
