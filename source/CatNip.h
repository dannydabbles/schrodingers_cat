//
//
//
//   Project : Schrödinger's cat
//   File Name : CatNip.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_CATNIP_H)
#define _CATNIP_H

#include "ShinyUnit.h"

class CatNip : public ShinyUnit
{
public:
   CatNip(CIwSVec2 i2Position);
	
   virtual void update(uint64 time);
	
private:
   bool bEmpty;
};

#endif  //_CATNIP_H
