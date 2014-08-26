//
//
//
//   Project : Schrödinger's cat
//   File Name : Block.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_BLOCK_H)
#define _BLOCK_H

#include "LethalUnit.h"

class Block : public LethalUnit
{
public:
   Block(CIwSVec2 i2Position);

	void setMoveDist(int iMoveDist);
   void setColor(CIwColour cColor);
  
	void update(uint64 time);
	void draw();

private:
   bool bRise;
   bool bFall;

   int iMoveDist;

	CIwSVec2 i2FinalPosition;

	CIwArray<CIwColour> cColor;
	
	Box* bFinalBox;
	
	void lightCalculation(uint64 time);
   void rise();
   void fall();
};

#endif  //_BLOCK_H
