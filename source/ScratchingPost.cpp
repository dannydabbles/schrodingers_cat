//
//
//
//   Project : Schrödinger's cat
//   File Name : ScratchingPost.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "ScratchingPost.h"

ScratchingPost::ScratchingPost(CIwSVec2 i2Position): ShinyUnit()
{
   IW_CALLSTACK("ScratchingPost::ScratchingPost");

   tTextureList.push_back(ImageManager::getImage("scratching_post"));

   this->sSoundList.push_back(SoundManager::getSound("scratching1"));
   this->sSoundList.push_back(SoundManager::getSound("scratching1"));
   this->sSoundList.push_back(SoundManager::getSound("scratching2"));
   this->sSoundList.push_back(SoundManager::getSound("scratching2"));
   this->sSoundList.push_back(SoundManager::getSound("scratching2"));
   this->sSoundList.push_back(SoundManager::getSound("scratching3"));
   this->sSoundList.push_back(SoundManager::getSound("scratching3"));
   this->sSoundList.push_back(SoundManager::getSound("scratching4"));
   this->sSoundList.push_back(SoundManager::getSound("scratching4"));

   this->i2Position = i2Position;
   this->sName = "scratchingpost";
   this->fShininess = 64;
   this->i2Size = CIwSVec2(Screen::getBOXSIZE().x, Screen::getBOXSIZE().y * 2);
   this->i2RegionSize = CIwSVec2(Screen::getBOXSIZE().x, Screen::getBOXSIZE().y * 2);
   this->brBoundingBox = BoundingRectangle(this->getPosition(), CIwSVec2(this->i2Size.x, (int)(this->i2Size.y * 0.5f)), CIwSVec2(this->i2Size.x, (int)(this->i2Size.y * 0.5f)), true);
   this->csPlayWith = CatState::SCRATCHINGPOST;
	this->i2Position.y -= Screen::getBOXSIZE().y;

   ClassTracker::addUnit(this);
}

void ScratchingPost::update(uint64 time)
{
   IW_CALLSTACK("ScratchingPost::update");
   this->iTime = time;
   this->iTimePassed += time;

   if(this->bUpdate == true)
   {
      this->iSoundIndex = IwRandMinMax(0, 8);
   }
   ShinyUnit::update();
}
