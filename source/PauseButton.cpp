/*
 *  PauseButton.cpp
 *  Kitty
 *
 *  Created by DrLight on 4/8/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "PauseButton.h"

PauseButton::PauseButton(): MenuButton()
{

	IW_CALLSTACK("PauseButton::PauseButton");
	
	this->tTextureList.push_back(ImageManager::getImage("kittybutton_pause"));
   this->tTextureList.push_back(ImageManager::getImage("kittybutton_pause2"));
	this->sSoundList.push_back(SoundManager::getSound("pause1"));
	
	//this->i2Position = CIwSVec2(Screen::getBOXSIZE().x / 4, Screen::getSCREENSIZE().y - (Screen::getBOXSIZE().y + Screen::getBOXSIZE().y / 4));
   //this->i2Offset = CIwSVec2(Screen::getBOXSIZE().x / 4, Screen::getSCREENSIZE().y - (Screen::getBOXSIZE().y + Screen::getBOXSIZE().y / 4));
   this->i2Position = CIwSVec2(0, 0);
   this->i2Offset = CIwSVec2(0, 0);
	this->sName = "pausebutton";
	this->i2Size = CIwSVec2(Screen::getBOXSIZE().x, Screen::getBOXSIZE().y);
	this->i2RegionSize = CIwSVec2(32, 32);
	BoundingRectangle r = BoundingRectangle(i2Position, i2Size);

   ClassTracker::addUnit(this);
}

void PauseButton::update(uint64 time)
{	
	IW_CALLSTACK("PauseButton::update");
	
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
      GameState::setState(GameState::PAUSE);
		SoundManager::playSound(this->sSoundList[0]);
      this->bUpdate = false;
   }
}
