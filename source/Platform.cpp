//
//
//
//   Project : Schrödinger's cat
//   File Name : Platform.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Platform.h"

Platform::Platform()
{
   IW_CALLSTACK("Platform::Platform");
}

Platform::Platform(CIwSVec2 i2Position): Unit()
{
   IW_CALLSTACK("Platform::Platform");

   //tTextureList.push_back(ImageManager::getImage("platform"));
   tTextureList.push_back(ImageManager::getImage("platform_1"));
   tTextureList.push_back(ImageManager::getImage("platform_2"));
   tTextureList.push_back(ImageManager::getImage("platform_3"));
   tTextureList.push_back(ImageManager::getImage("platform_4"));
   this->i2Position = i2Position;
   this->bWalkable = true;
   sName = "platform";
   this->brBoundingBox = BoundingRectangle(CIwSVec2(0, -2 * Screen::getBOXSIZE().x), this->i2Size, CIwSVec2(1,1));
   //this->brBoundingBox = BoundingRectangle(this->i2Position + CIwSVec2(1, 28), CIwSVec2(30, 4));

   ClassTracker::addUnit(this);
}

void Platform::update(uint64 time)
{
   IW_CALLSTACK("Platform::update");

   this->iTime = time;
   this->iTimePassed += time;
}
