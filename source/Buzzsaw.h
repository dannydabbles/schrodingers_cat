//
//
//
//   Project : Schrödinger's cat
//   File Name : Buzzsaw.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_BUZZSAW_H)
#define _BUZZSAW_H

#include "LethalUnit.h"

class Buzzsaw : public LethalUnit
{
public:
   Buzzsaw(CIwSVec2 i2Position);
   ~Buzzsaw();
	
   void setCap(int iC);
   void toggleOn();

   void setColor(CIwColour cColor);
	
  void update(uint64 time);
  void draw();
	
private:
   int iDefaultCap;
	int iRot;
   CIwArray<CIwColour> cColor;
  
 
   
};

#endif  //_BUZZSAW_H
