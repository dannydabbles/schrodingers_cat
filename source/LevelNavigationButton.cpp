#include "LevelNavigationButton.h"

LevelNavigationButton::LevelNavigationButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size, bool mainMenu) : MenuButton()
{
	IW_CALLSTACK("LevelNavigationButton::LevelNavigationButton");

   this->i2Size = size;
	this->i2RegionSize = size;
	this->i2Offset = offset;
   this->i2Position = menuPosition + this->i2Offset;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);

   this->sName = "levelnavigationbutton";

   if(mainMenu == true)
   {
      this->tTextureList.push_back(ImageManager::getImage("kittyplay"));
	   this->tTextureList.push_back(ImageManager::getImage("kittyplay2"));
   }
   else
   {
      this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_levels"));
		this->tTextureList.push_back(ImageManager::getImage("kittysidebutton_levels2"));
   }

	this->sSoundList.push_back(SoundManager::getSound("menu2"));
	this->sSoundList.push_back(SoundManager::getSound("menu8"));

   ClassTracker::addUnit(this);
}

LevelNavigationButton::LevelNavigationButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size, string sSpriteName)
{
	IW_CALLSTACK("LevelNavigationButton::LevelNavigationButton");
}

void LevelNavigationButton::update(uint64 time)
{
	IW_CALLSTACK("LevelNavigationButton::update");

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
		
		if(GameState::getState() == GameState::MAINMENU)
		{
			SoundManager::playSound(this->sSoundList[1]);
		}
		else 
		{
			SoundManager::playSound(this->sSoundList[0]);
		}
		
      GameState::setState(GameState::LEVELNAVIGATION);
      this->bUpdate = false;
   }
}