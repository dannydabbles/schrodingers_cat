//
//
//
//   Project : Schrödinger's cat
//   File Name : SuperShinyJumpOutofBoxShinyUnit.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_SUPER_H)
#define _SUPER_H

#include "ShinyUnit.h"

class SuperShinyJumpOutofBoxShinyUnit : public ShinyUnit
{

public:

   SuperShinyJumpOutofBoxShinyUnit(CIwSVec2 i2Position);

   void update(uint64 time);

};

#endif