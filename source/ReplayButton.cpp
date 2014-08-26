#include "ReplayButton.h"


ReplayButton::ReplayButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size ) : MenuButton()
{
	IW_CALLSTACK("ReplayButton::ReplayButton");
	
   this->i2Size = size;
	this->i2RegionSize = size;
	this->i2Offset = offset;
   this->i2Position = menuPosition + this->i2Offset;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);
   this->sName = "replaybutton";

   tTextureList.push_back(ImageManager::getImage("kittysidebutton_restart"));
	tTextureList.push_back(ImageManager::getImage("kittysidebutton_restart2"));
	
	this->sSoundList.push_back(SoundManager::getSound("menu10"));

   ClassTracker::addUnit(this);
}

void ReplayButton::update(uint64 time)
{
	IW_CALLSTACK("ReplayButton::update");

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
      //GameState::setState(GameState::RESET);
		SoundManager::playSound(this->sSoundList[0]);
      GameState::setReset(true);
      this->bUpdate = false;
   }
}
