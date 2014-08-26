//
//
//
//   Project : Schrödinger's cat
//   File Name : Scythe.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_SCYTHE_LEFT_H)
#define _SCYTHE_LEFT_H

#include "Unit.h"

class ScytheLeft : public Unit
{
public:
   ScytheLeft(CIwSVec2 i2Position);
   void update(uint64 time);
   void draw();
	
};

#endif  //_SCYTHE_LEFT_H
