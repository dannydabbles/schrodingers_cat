//
//
//
//   Project : Schrödinger's cat
//   File Name : ShinyUnit.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_SHINYUNIT_H)
#define _SHINYUNIT_H

#include "Unit.h"

class ShinyUnit : public virtual Unit
{
public:
   ShinyUnit();
  

   void decrementTimeSpentWithCat();
   void incrementTimeSpentWithCat();

   float getDistanceFromCat(CIwSVec2 i2Position);
   virtual float getShininess();
	float getTimeSpentWithCat();

   CatState::State getPlayWith();

   void update();

   static void setShiniestUnit(ShinyUnit * shiniestUnit);
	static ShinyUnit* getShiniestUnit();
	static void setShinyDropDownBox(Box* bShinyDropDownBox);
	static Box* getShinyDropDownBox();
	void setNotShiny();
	void setShiny();

protected:
   static ShinyUnit* shiniestUnit;
	static Box* bShinyDropDownBox;

   bool bToggleIncrement;
   int iShinyIndex;
	uint64 iShinyTimePassed;
   float fShininess;

	CIwArray<float> fTimeSpentWithCat;

   CatState::State csPlayWith;
};

#endif  //_SHINYUNIT_H
