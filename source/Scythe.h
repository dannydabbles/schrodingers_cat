//
//
//
//   Project : Schrödinger's cat
//   File Name : Scythe.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_SCYTHE_H)
#define _SCYTHE_H

#include "LethalUnit.h"

class Scythe : public LethalUnit
{
public:

   Scythe(CIwSVec2 i2Position);
   void update(uint64 time);
   void draw();

   CIwSVec2 getPosition();
   CIwSVec2  getRotatedCoords(CIwSVec2 pos);
   void calculateMaxRotation();

private:

   float fMaxLeft; //maximum angle it swings to the left
   float fMaxRight; 
   
   int iLength;
   double fAngularVel;
   double fAngularAcceleration;
   double fAngle;
   double fGDividedByLength;
   //float fperoid;
   
   CIwSVec2 postRotatedCoords;
   CIwVec2 rotAxis;
   CIwMat2D mRot;

   CIwColour DarkGreen;
   CIwColour LightGreen;
   int green; 
   bool up;

   
  
};

#endif  //_SCYTHE_H
