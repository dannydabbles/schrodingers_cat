//
//
//
//   Project : Schrödinger's cat
//   File Name : LaserPointer.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_LASERPOINTER_H)
#define _LASERPOINTER_H


#include "ShinyUnit.h"
#include "s3ePointer.h"

class LaserPointer : public ShinyUnit
{
public:
   LaserPointer();

   float getMovement();
   void update(uint64 time);
   void draw();
   float getShininess();
   virtual void reset();
   void pause();
   void toggle();
private:
	
   bool bOn;
   
   int alpha;
	int timer;
   int trailThickness;
  
	uint64 iMoveCalcTimePassed;
	
   float velocity;
   float iStillTime;
	
	CIwColour color;
	
   CIwArray<CIwSVec2> i2PositionList; // stores an arbiraray number of previous positions

   //CIwArray<LaserPointerParticle*> pParticleList;
   //CIwArray<LaserPointerParticle*> pDeadParticleList

   CIwArray<CIwSVec2> positionList;
   CIwArray<float> fDistanceList;
   CIwArray<int64> lifeTimeList;

   void updatePositionList();
   void calculateMovement(); 
};

#endif  //_LASERPOINTER_H
