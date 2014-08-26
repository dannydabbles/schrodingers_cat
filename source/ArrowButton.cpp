#include "ArrowButton.h"

ArrowButton::ArrowButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size, bool foward) : MenuButton()
{
	IW_CALLSTACK("ArrowButton::ArrowButton");

   this->i2Size = size;
	this->i2RegionSize = size;
	this->i2Offset = offset;
   this->i2Position = menuPosition + this->i2Offset;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);
   this->foward = foward;
   this->sName = "arrowbutton";

   if(foward == true)
   {
      this->tTextureList.push_back(ImageManager::getImage("kittybutton_right"));
		this->tTextureList.push_back(ImageManager::getImage("kittybutton_right2"));
   }
   else
   {
      this->tTextureList.push_back(ImageManager::getImage("kittybutton_left"));
		this->tTextureList.push_back(ImageManager::getImage("kittybutton_left2"));
   }

	this->sSoundList.push_back(SoundManager::getSound("menu3"));

   ClassTracker::addUnit(this);
}

void ArrowButton::update(uint64 time)
{
	IW_CALLSTACK("ArrowButton::update");

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

      if(this->foward)
      {
         GameState::setState(GameState::PAGERIGHT);
      }
      else 
      {
         GameState::setState(GameState::PAGELEFT);
      }
      this->bUpdate = false;
   }
}

