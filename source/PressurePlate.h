//
//
//
//   Project : Schrödinger's cat
//   File Name : PressurePlate.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_PRESSUREPLATE_H)
#define _PRESSUREPLATE_H

#include "Buzzsaw.h"
#include "MechanicalWall.h"

class PressurePlate : public Unit
{
public:
   PressurePlate(CIwSVec2 i2Position, string sName);

   void setColor(int iColor);

   CIwColour getColor();

   void update(uint64 time);

   void draw();

private:
	void lightCalculation(uint64);
   CIwColour cColor;
   bool bDown; 
};

#endif  //_PRESSUREPLATE_H
