#include "ResumeButton.h"


ResumeButton::ResumeButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size)
{
	IW_CALLSTACK("ResumeButton::ResumeButton");

   this->i2Size = size;
	this->i2RegionSize = size;
	this->i2Offset = offset;
   this->i2Position = menuPosition + this->i2Offset;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);
	this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_play"));
	this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_play2"));
	this->sSoundList.push_back(SoundManager::getSound("pause2"));

   this->sName = "resumebutton";

   ClassTracker::addUnit(this);
}

void ResumeButton:: update(uint64 time)
{
	IW_CALLSTACK("ResumeButton::update");

   this->iTime = time;
   this->iTimePassed += time;

   if(this->bPressed == true)
   {
      this->iTextureIndex = 1;
   }
   else
   {
      this->iTextureIndex = 0;
   }

   if(this->bUpdate == true)
   {
      //GameState::setState(GameState::PAUSEBACK);
      GameState::setResume(true);
		SoundManager::playSound(this->sSoundList[0]);
      this->bUpdate = false;
   }
}
