//
//
//
//   Project : Schrödinger's cat
//   File Name : ShinyUnit.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "ShinyUnit.h"

#define SHININESS 10
#define MINCALCTIME 64
#define TIME_SPENT_PERIOD 100

ShinyUnit* ShinyUnit::shiniestUnit = NULL;
Box* ShinyUnit::bShinyDropDownBox = NULL;

ShinyUnit::ShinyUnit(): Unit()
{
   IW_CALLSTACK("ShinyUnit::ShinyUnit");
   this->iShinyIndex = 0;
   this->bIsShiny = true;
   this->bToggleIncrement;
   this->fTimeSpentWithCat = CIwArray<float>();
   this->csPlayWith = CatState::IDLING;
   for(int i = 0; i < TIME_SPENT_PERIOD + 1; ++i)
   {
      this->fTimeSpentWithCat.push_back(0);
   }
}

ShinyUnit* ShinyUnit::getShiniestUnit()
{
   IW_CALLSTACK("ShinyUnit::getShiniestUnit");

   return ShinyUnit::shiniestUnit;
}

Box* ShinyUnit::getShinyDropDownBox()
{
   IW_CALLSTACK("ShinyUnit::getShinyDropDownBox");

   return ShinyUnit::bShinyDropDownBox;
}

void ShinyUnit::decrementTimeSpentWithCat()
{
   IW_CALLSTACK("ShinyUnit::decrementTimeSpentWithCat");

   if(this->iShinyTimePassed >= MINCALCTIME)
   {
      if(this->iShinyIndex >= TIME_SPENT_PERIOD)
      {
         this->iShinyIndex = 0;
      }
      ++this->iShinyIndex;
      this->fTimeSpentWithCat[iShinyIndex] = 0;
      this->iShinyTimePassed = 0;
   }
}

void ShinyUnit::incrementTimeSpentWithCat()
{
   IW_CALLSTACK("ShinyUnit::incrementTimeSpentWithCat");

   if(this->iShinyTimePassed >= MINCALCTIME)
   {
      if(this->iShinyIndex >= TIME_SPENT_PERIOD)
      {
         this->iShinyIndex = 0;
      }
      ++this->iShinyIndex;
      this->fTimeSpentWithCat[iShinyIndex] = (float)this->iShinyTimePassed / (float)MINCALCTIME;
      this->iShinyTimePassed = 0;
   }
}

CatState::State ShinyUnit::getPlayWith()
{
   IW_CALLSTACK("ShinyUnit::getPlayWith");

   return this->csPlayWith;
}

float ShinyUnit::getDistanceFromCat(CIwSVec2 i2Position)
{
   IW_CALLSTACK("ShinyUnit::getDistanceFromCat");

	CIwFVec2 f2CatPosition = CIwFVec2((float)i2Position.x, (float)i2Position.y);
	CIwFVec2 f2MyPosition = CIwFVec2((float)this->i2Position.x, (float)this->i2Position.y); 
	
   float fDist = (f2CatPosition - f2MyPosition).GetLength();
   if(fDist < 0)
   {
      fDist *= -1;
   }
   return fDist;
}

float ShinyUnit::getShininess()
{
   IW_CALLSTACK("ShinyUnit::getShininess");

   return this->fShininess;
}

float ShinyUnit::getTimeSpentWithCat()
{
   IW_CALLSTACK("ShinyUnit::getTimeSpentWithCat");

   float fTimeSpentSum = 0;
   for(int i = 0; i < TIME_SPENT_PERIOD; ++i)
   {
      fTimeSpentSum += this->fTimeSpentWithCat[i];
   }
   return fTimeSpentSum;
}

void ShinyUnit::update()
{
   IW_CALLSTACK("ShinyUnit::update");

   this->iShinyTimePassed += this->iTime;

   if(this == ShinyUnit::shiniestUnit && CatState::getState() == this->csPlayWith)
   {
      if(this->bUpdate == true)
      {
         if(this->iSoundIndex >= 0)
         {
            SoundManager::playSound(this->sSoundList[this->iSoundIndex]);
         }
         this->incrementTimeSpentWithCat();
      } 
   }
   else
   {
      this->decrementTimeSpentWithCat();
   }
   this->bUpdate = false;
}

void ShinyUnit::setShiniestUnit(ShinyUnit* shiniestUnit)
{
   IW_CALLSTACK("ShinyUnit::setShiniestUnit");

   ShinyUnit::shiniestUnit = shiniestUnit;
}

void ShinyUnit::setShinyDropDownBox(Box* bShinyDropDownBox)
{
   IW_CALLSTACK("ShinyUnit::setShiniestUnit");

   ShinyUnit::bShinyDropDownBox = bShinyDropDownBox;
}

void ShinyUnit::setNotShiny()
{
   IW_CALLSTACK("ShinyUnit::setNoShiny");

   this->fShininess = -1;
}

void ShinyUnit::setShiny()
{
   IW_CALLSTACK("ShinyUnit::setShiny");

   this->bIsShiny = true;
   this->fShininess = SHININESS;
}
