//
//
//
//   Project : Schrˆdinger's cat
//   File Name : CatEvent.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "CatEvent.h"

CatEvent::CatEvent(CIwSVec2 i2Position): ShinyUnit()
{
   IW_CALLSTACK("CatEvent::CatEvent");

   this->i2Position = i2Position;
   this->sName = "catevent";
   this->fShininess = -1;
   this->bIsMoving = true;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size,this->i2Size, true);
   this->csPlayWith = CatState::IDLING;

   ClassTracker::addUnit(this);
}

void CatEvent::setEvent()
{
   IW_CALLSTACK("CatEventt::setEvent");

   int iRandomNum = IwRandMinMax(7, 10);
   switch(iRandomNum) 
   {
   case 7:
      // cout << "LICK" << endl;
      this->csPlayWith = CatState::LICKINGSELF;
      break;
   case 8:
      //cout << "SCRATCH" << endl;
      this->csPlayWith = CatState::SCRATCHINGSELF;
      break;
   case 9:
      //cout << "STRETCH" << endl;
      this->csPlayWith = CatState::STRETCHING;
      break;
   default:
      IwAssertMsg(MYAPP, false, ("Invalid CatState"));
      this->csPlayWith = CatState::IDLING;
   }
}

void CatEvent::update(uint64 time)
{
   IW_CALLSTACK("CatEventt::update");

   this->iTime = time;
   this->iTimePassed += time;
   ShinyUnit::update();
   this->brBoundingBox.setPosition(this->i2Position, true);

   if(CatState::getState() == CatState::TRANSITIONING)
   {
      //cout << "cat event: TRANNY " << endl;

      this->fShininess = (float)IwRandMinMax(0, 1000);

      if(this->fShininess != 999)
      {
         this->fShininess = (float)IwRandMinMax(-4, 4);
      }
      this->setEvent();
      //cout << "Cat event base shininess " << this->fShininess << endl; 
   }
}

void CatEvent::draw()
{
   IW_CALLSTACK("CatEventt::draw");

   return;
}
