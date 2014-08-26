//
//
//
//   Project : Schrödinger's cat
//   File Name : Chomper.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Chomper.h"

Chomper::Chomper(CIwSVec2 i2Position): LethalUnit()
{
   IW_CALLSTACK("Chomper::Chomper");

   tTextureList.push_back(ImageManager::getImage("chomp"));
   this->i2Position = i2Position;
   sName = "chomper";
   this->iCapDeathCount = 10;
   this->iDefaultCap = 10;

   ClassTracker::addUnit(this);
}

void Chomper::toggleOn()
{
   IW_CALLSTACK("Chomper::toggleOn");

   if(this->iDeathCount < this->iCapDeathCount)
   {
      this->iCapDeathCount = 0;
   }
   else
   {
      this->iCapDeathCount = this->iDefaultCap;
   }
}

void Chomper::setCap(int iC)
{
   IW_CALLSTACK("Chomper::setCap");

   this->iCapDeathCount = iC;
   this->iDefaultCap = iC;
}

void Chomper::update(uint64 time)
{
   IW_CALLSTACK("Chomper::update");

   if (GameState::getState() != GameState::PLAY)
   {
      return;
   }
   this->iTime = time;
   this->iTimePassed += time;
   //this->boundingBoxPos = this->i2Position;

   if(this->bAffectUpdate == true)
   {
      this->toggleOn();
      this->bAffectUpdate = false;
   }

   if(this->bUpdate == true)
   {
      LethalUnit::update();
   }
}
