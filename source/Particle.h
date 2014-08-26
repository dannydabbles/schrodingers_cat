//
//
//
//   Project : Schrˆdinger's cat
//   File Name : Anvil.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_Particle_H)
#define _Particle_H

#include "Screen.h"
#include "Unit.h"
#include "Memory.h"

class Particle: public Unit
{
public:
   friend class Blood;
	
   Particle();

	void update(uint64 time);
	void draw();
   void setPosition(CIwSVec2 i2Position);

private:
	uint64 iLife;
	bool bDead;
   static CIw2DImage* tTexture;
};

#endif