//
//
//
//   Project : Schrödinger's cat
//   File Name : Platform.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_PLATFORM_H)
#define _PLATFORM_H

#include "Unit.h"

class Platform : public Unit
{
public:
   Platform();
   Platform(CIwSVec2 i2Position);
   virtual void update(uint64 time);
//protected:
   bool bWalkable;
};

#endif  //_PLATFORM_H
