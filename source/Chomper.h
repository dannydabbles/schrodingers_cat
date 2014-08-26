//
//
//
//   Project : Schrödinger's cat
//   File Name : Chomper.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_CHOMPER_H)
#define _CHOMPER_H

#include "LethalUnit.h"

class Chomper : public LethalUnit
{
public:
   Chomper(CIwSVec2 i2Position);
	
	void setCap(int iC);
   void toggleOn();
	
	void update(uint64 time);
	
private:
   int iDefaultCap;
};

#endif  //_CHOMPER_H
