#include "NextLevelButton.h"


NextLevelButton::NextLevelButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size) : MenuButton()
{
	IW_CALLSTACK("NextLevelButton::NextLevelButton");

   this->i2Size = size;
	this->i2RegionSize = size;
	this->i2Offset = offset;
   this->i2Position = menuPosition + this->i2Offset;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);

   this->sName = "nextlevelbutton";

   this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_play"));
	this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_play2"));

	this->sSoundList.push_back(SoundManager::getSound("menu9"));
	
   ClassTracker::addUnit(this);
}

void NextLevelButton::update(uint64 time)
{
	IW_CALLSTACK("NextLevelButton::update");

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
		SoundManager::playSound(this->sSoundList[0]);

      GameState::setState(GameState::PLAY);
      this->bUpdate = false;
   }
}
