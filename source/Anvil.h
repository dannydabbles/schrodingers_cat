//
//
//
//   Project : Schrödinger's cat
//   File Name : Anvil.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_ANVIL_H)
#define _ANVIL_H

#include "LethalUnit.h"

class Anvil : public LethalUnit
{
public:
   Anvil(CIwSVec2 i2Position);
	
	void setMoveDist(int iMoveDist);
	void setColor(CIwColour cColor);

	void update(uint64 time);
	void draw();
	
private:
   bool bFall;
	CIwFVec2 f2Velocity;
	CIwSVec2 i2FinalPosition;
	
	CIwArray<CIwColour> cColor;
	
	void lightCalulation(uint64 time);
};

#endif  
