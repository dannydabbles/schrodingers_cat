//
//
//
//   Project : Schrödinger's cat
//   File Name : BearTrap.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_BEARTRAP_H)
#define _BEARTRAP_H

#include "LethalUnit.h"

class BearTrap : public LethalUnit
{
public:
   BearTrap(CIwSVec2 i2Position);
	
	void update(uint64 time);
};

#endif  //_BEARTRAP_H
