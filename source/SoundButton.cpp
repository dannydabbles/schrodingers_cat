#include "SoundButton.h"


SoundButton::SoundButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size) : MenuButton()
{
	IW_CALLSTACK("SoundButton::SoundButton");

   this->i2Size = size;
	this->i2RegionSize = size;
	this->i2Offset = offset;
   this->i2Position = menuPosition + this->i2Offset;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);

   this->sName = "soundbutton";

   this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_volume"));
   this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_volume2"));

   this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_volumex"));
	this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_volumex2"));
	
	this->sSoundList.push_back(SoundManager::getSound("menu3"));

   ClassTracker::addUnit(this);
}

void SoundButton::update(uint64 time)
{
	IW_CALLSTACK("SoundButton::update");

   this->iTime = time;
   this->iTimePassed += time;

   if(SoundManager::getSound() == true)
   {
      if(this->bPressed == true)
      {
         this->iTextureIndex = 1;
      }
      else
      {
         this->iTextureIndex = 0;
      }
   }
   else
   {
      if(this->bPressed == true)
      {
         this->iTextureIndex = 3;
      }
      else
      {
         this->iTextureIndex = 2;
      }
   }

   if(this->bUpdate == true)
   {
		SoundManager::ToggleSound();
		SoundManager::playSound(this->sSoundList[0]);
      this->bUpdate = false;
   }
}
