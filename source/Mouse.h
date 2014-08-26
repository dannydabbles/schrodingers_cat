//
//
//
//   Project : Schrödinger's cat
//   File Name : Mouse.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_MOUSE_H)
#define _MOUSE_H

#include "ShinyUnit.h"
#include "Food.h"

class Mouse : public ShinyUnit
{
public:
	Mouse(CIwSVec2 i2Position);
	
	Unit* uTarget;
	
	void setBDead(bool bDead);
	void setBMoveLeft(bool bMoveLeft);
	void setBScared(bool bScared);
	void setTarget(Unit* uTarget);
	
	bool getBDead();
	bool getBMoveLeft();
	bool getBScared();
	bool scaredMove(Box* bCurr, Box* bNext);
	bool regularMove();
	bool checkPosition();
	
	virtual void draw();
	virtual void update(uint64 time);
private:
	CIwSVec2 i2InitialPosition;
	bool bScared;
	bool bDead;
	bool bMoveLeft;
	int iAIHole;
};

#endif  //_MOUSE_H
