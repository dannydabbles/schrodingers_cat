//
//
//
//   Project : Schrödinger's cat
//   File Name : StartBox.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "StartBox.h"

StartBox::StartBox(CIwSVec2 i2Position): Unit()
{
   IW_CALLSTACK("StartBox::StartBox");

   this->tTextureList.push_back(ImageManager::getImage("start"));
   this->i2Position = i2Position;
   this->sName = "startbox";
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size, this->i2Size, true);

   ClassTracker::addUnit(this);
}

void StartBox::update(uint64 time)
{
   IW_CALLSTACK("StartBox::update");

   this->iTime = time;
   this->iTimePassed += time;
}
