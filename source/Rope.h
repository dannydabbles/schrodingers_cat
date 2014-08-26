//
//
//
//   Project : Schrödinger's cat
//   File Name : Rope.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_ROPE_H)
#define _ROPE_H

#include "Unit.h"

class Rope : public Unit
{
public:
   Rope(CIwSVec2 i2Position);
	virtual void update(uint64 time);
	virtual void draw();
   void setCuttable(bool bCuttable);
   void setMoveDist(int iMoveDist);
   void setRiseable(bool bRiseable);
   void setFallable(bool bFallable);
   void setAll();
	
   bool bCuttable;
private:
	
	bool bCut;
	bool bRise;
	bool bFall;
	bool bRiseable;
	bool bFallable;
	bool bPlayedSoundOnce;
	
	int iMoveDist;
	
	CIwSVec2 i2FinalPosition;

	void rise();
	void fall();
};

#endif  //_ROPE_H
