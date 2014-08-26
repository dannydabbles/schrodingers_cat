//
//
//
//   Project : Schrödinger's cat
//   File Name : MechanicalWall.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_MECHANICALWALL_H)
#define _MECHANICALWALL_H

#include "LethalUnit.h"

class MechanicalWall : public LethalUnit
{
public:
   MechanicalWall(CIwSVec2 i2Position, string sName, bool bIsWall, int iIndexNum);
	~MechanicalWall();
	void setAll();
   void setColor(CIwColour cColor);
   void setDown(bool bDown);
   bool getDown();
   void ToggleMidMove();
   void setMoveDist(int iMoveDist);
	
   void update(uint64 time);
   void draw();

  

private:
	bool bDown;
	bool bPlayedSoundOnce;

	int count;
   int iMoveDist;

   CIwArray<CIwColour> cColor;

   CIwSVec2 i2FinalPosition;
   Box* bFinalBox;
	
   void rise();
   void fall();

   void lightCalulation(uint64);

 
};

#endif  //_MECHANICALWALL_H
