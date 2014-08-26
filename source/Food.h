//
//
//
//   Project : Schrödinger's cat
//   File Name : Food.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_FOOD_H)
#define _FOOD_H

#include "ShinyUnit.h"
#include "LitterBox.h"

class Food : public ShinyUnit
{
public:
   Food(CIwSVec2 i2Position);
	
   virtual void update(uint64 time);
	bool bEmpty;
private:
   
};

#endif  //_FOOD_H
