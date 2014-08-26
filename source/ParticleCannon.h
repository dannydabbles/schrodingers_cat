//
//
//
//   Project : Schrˆdinger's cat
//   File Name : Anvil.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_ParticleCannon_H)
#define _ParticleCannon_H

#include "Iw2D.h"
#include "ImageManager.h"
#include "GameState.h"
#include "Particle.h"

enum particle_mode
{
	PARTICLE_BASIC = 0,
	PARTICLE_DIRECTIONAL = 1,
	PARTICLE_GRAVITY = 2,
	PARTICLE_DIRECTIONAL_GRAVITY = 3
};

class ParticleCannon
{
public:
	ParticleCannon(uint64 time, int life,CIwSVec2 i2Position, bool full, particle_mode mode, double angle);
	ParticleCannon(uint64 time, int life, CIwSVec2 i2Position, bool full, particle_mode mode,CIwSVec2 direction);
	
   void reset(CIwSVec2 newPos);
   
   void update(uint64 time);
	void draw();
	Particle* makeParti();
	bool bDone;
private:
	double dProductionRate, dMinVelocity, dMaxVelocity, dMinLife, dMaxLife,dAngle;
	uint64 uLife;
   uint64 iTime;
   uint64 iTimePassed;
	int  iProductionCap, iTotalCap, iTotal;
	int move, moveRate;
	int iLife, iCLife, iCTime, iMinLife, iMaxLife;
	CIwSVec2 i2Position,iGoal;
	CIwArray<Particle*> apCannon,deadParticles;
	particle_mode mode;
	
	CIwArray<CIw2DImage*> tTextureList;
};
#endif