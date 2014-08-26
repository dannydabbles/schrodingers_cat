//
//
//
//   Project : Schrödinger's cat
//   File Name : BearTrap.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "BearTrap.h"

BearTrap::BearTrap(CIwSVec2 i2Position): LethalUnit()
{
   IW_CALLSTACK("BearTrap::BearTrap");

   this->iCapDeathCount = 1;
   this->tTextureList.push_back(ImageManager::getImage("bear_trap"));
   this->tTextureList.push_back(ImageManager::getImage("bear_trap_close"));
   this->sSoundList.push_back(SoundManager::getSound("beartrap"));
   this->i2Position = i2Position;
   this->iSoundIndex = 5;
   this->sName = "beartrap";
   this->brBoundingBox = BoundingRectangle(this->getPosition(), this->getSize(), CIwSVec2((int)(this->getSize().x * 0.5f), this->getSize().y), true);

   ClassTracker::addUnit(this);
}

void BearTrap::update(uint64 time)
{
   IW_CALLSTACK("BearTrap::update");

   this->iTime = time;
   this->iTimePassed += time;

   if(bUpdate == true)
   {
      LethalUnit::update();
   }
}
