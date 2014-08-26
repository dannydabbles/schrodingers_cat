//
//
//
//   Project : Schrödinger's cat
//   File Name : Scythe.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_SCYTHE__RIGHT_H)
#define _SCYTHE__RIGHT_H

#include "Unit.h"

class ScytheRight : public Unit
{
	public:
		ScytheRight(CIwSVec2 i2Position);
		void update(uint64 time);
		void draw();
	
};

#endif  //_SCYTHE_RIGHT
