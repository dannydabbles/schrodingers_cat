#include "CreditButton.h"


CreditButton::CreditButton( CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size, bool back) : MenuButton()
{
	IW_CALLSTACK("CreditButton::CreditButton");

   this->i2Size = size;
   this->i2RegionSize = size;
   this->i2Offset = offset;
   this->i2Position = menuPosition + this->i2Offset;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);
   this->bBack = back;
   this->sName = "creditbutton";

   if(this->bBack == true)
   {
      this->tTextureList.push_back(ImageManager::getImage("kittybutton_right"));
      this->tTextureList.push_back(ImageManager::getImage("kittybutton_right2"));
   }
   else
   {
      this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_question"));
      this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_question2"));
   }

	this->sSoundList.push_back(SoundManager::getSound("menu3"));

   ClassTracker::addUnit(this);
}

void CreditButton::update(uint64 time)
{
	IW_CALLSTACK("CreditButton::update");

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

      if(this->bBack == true)
      {
         GameState::setState(GameState::CREDITMENUBACK);
      }
      else 
      {
         GameState::setState(GameState::CREDITMENU);
      }
      this->bUpdate = false;
   }
}

