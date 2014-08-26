#include "MainMenuButton.h"


MainMenuButton::MainMenuButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size) : MenuButton()
{
	IW_CALLSTACK("MainMenuButton::MainMenuButton");

   this->i2Size = size;
	this->i2RegionSize = size;
	this->i2Offset = offset;
   this->i2Position = menuPosition + this->i2Offset;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);

   this->sName = "mainmenubutton";

   this->tTextureList.push_back(ImageManager::getImage("kittybutton_left"));
	this->tTextureList.push_back(ImageManager::getImage("kittybutton_left2"));

	this->sSoundList.push_back(SoundManager::getSound("menu4"));
	
   ClassTracker::addUnit(this);
}


void MainMenuButton::update(uint64 time)
{
	IW_CALLSTACK("MainMenuButton::update");

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

      GameState::setState(GameState::MAINMENU);
      this->bUpdate = false;
   }
}