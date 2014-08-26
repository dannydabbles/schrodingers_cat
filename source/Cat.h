//
//
//
//   Project : Schrödinger's cat
//   File Name : Cat.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_CAT_H)
#define _CAT_H

#include "CatEvent.h"
#include "CatState.h"
#include "Unit.h"

class CatEvent;

class Cat : public Unit
{
public:
   friend class CatAI;
	
   Cat(CIwSVec2 i2Position);
   ~Cat();

	
	int iDeathCount;
	uint64 iMeowTimePassed;
	
	CIwArray<CIwFVec2>* curves;
	CIwSVec2 i2Finish;
   CIwSVec2 i2PreJumpBoxPosition;
   CIwSVec2 i2StartPosition;
   CIwFVec2 f2DefaultVelocity;   
   CatEvent* ceEvent;
	
	void reset();
   void setCurves(CIwArray<CIwFVec2>* curves);
   void setFinish(CIwSVec2 i2Finish);
	
	void update(uint64 time);
   void draw();
	
private:
	bool bHasMouse;
   float fGravC;
   int* piPathIndex;
   float fJumpSpeedMod;

	void deathMeow();
	void playEventMeow();
	void playMeow();
	void regularMeow();
	
   void moveLeft();
   void moveRight();
   void moveJumpRight();
   void moveJumpLeft();
   void performActions();
};

#endif  //_CAT_H
