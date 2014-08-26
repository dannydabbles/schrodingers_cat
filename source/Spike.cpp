//
//
//
//   Project : Schrödinger's cat
//   File Name : Spike.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Spike.h"

Spike::Spike(CIwSVec2 i2Position): LethalUnit()
{
   IW_CALLSTACK("Spike::Spike");

   this->iCapDeathCount = 1;
   this->iDeathCount = 0;
   this->tTextureList.push_back(ImageManager::getImage("spike"));
   this->tTextureList.push_back(ImageManager::getImage("spike_cat"));
   this->sSoundList.push_back(SoundManager::getSound("spike3"));
   this->i2Position = i2Position;
   this->sName="spike";
   this->brBoundingBox = BoundingRectangle(CIwSVec2(this->i2Position.x + this->i2Size.x / 2, this->i2Position.y + (int)(this->i2Size.y * 0.66f)), this->i2Size, CIwSVec2(1, 1));

   ClassTracker::addUnit(this);
}

void Spike::update(uint64 time)
{
   IW_CALLSTACK("Spike::update");

   this->iTime = time;
   this->iTimePassed += time;

   if(this->bUpdate == true)
   {
      this->bBox->bConnectList[1]->bIsWalkable = true;
      //this->bBox->bIsWalkable = false;
      this->bBox->bIsFilled = true;
      GameState::setReInitializePathing(true);
      SoundManager::playSound(this->sSoundList[5]);
      LethalUnit::update();
   }
}
