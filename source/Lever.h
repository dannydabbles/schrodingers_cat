//
//
//
//   Project : Schrödinger's cat
//   File Name : Lever.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_LEVER_H)
#define _LEVER_H

#include "Buzzsaw.h"
#include "MechanicalWall.h"
#include "GameState.h"

using namespace std;

class Lever : public Unit
{
public:
   Lever(CIwSVec2 i2Position);
	
   bool bCooldown;

	void setColor(int cColorCode);
   
   CIwColour getColor();

	void update(uint64 time);
   void draw();
   
private:
   bool bOn;
   CIwColour cColor;


   void lightCalulation(uint64);
   
   
  
};

#endif  //_LEVER_H
