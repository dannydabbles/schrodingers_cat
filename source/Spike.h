//
//
//
//   Project : Schrödinger's cat
//   File Name : Spike.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_SPIKE_H)
#define _SPIKE_H

#include "LethalUnit.h"

class Spike : public LethalUnit
{
public:
   Spike(CIwSVec2 i2Position);
	void update(uint64 time);


};

#endif  //_SPIKE_H
