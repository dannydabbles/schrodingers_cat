//
//
//
//   Project : Schrˆdinger's cat
//   File Name : LaserParticlePointer.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_LETHAL_UNIT_H)
#define _LETHAL_UNIT_H

#include "Unit.h"

class LethalUnit : public virtual Unit
{
public:
   LethalUnit();

	int getDeathCount();
	
   void update();

protected:
   int iDeathCount;
   int iCapDeathCount;
	
	virtual void deathSound();
};

#endif