//
//
//
//   Project : Schrödinger's cat
//   File Name : MouseHole.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_MouseHole_H)
#define _MouseHole_H

#include "Unit.h"

class MouseHole : public Unit
{
public:
   MouseHole(CIwSVec2 i2Position);
	virtual void update(uint64 time);
};

#endif  
