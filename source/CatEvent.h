//
//
//
//   Project : Schrˆdinger's cat
//   File Name : CatEvent.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_CATEVENT_H)
#define _CATEVENT_H

#include "Cat.h"
#include "CatState.h"
#include "ShinyUnit.h"

class Cat;

class CatEvent : public ShinyUnit
{
public:
	friend class Cat;
	
	CatEvent(CIwSVec2 i2Position);
	
	void update(uint64 time);
	void draw();

private:
   void setEvent();
};

#endif  //_CATEVENT_H


