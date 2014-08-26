/*
*  EndOfLevelMenu.cpp
*  Kitty
*
*  Created by Sam Medalen on 5/16/11.
*  Copyright 2011 __MyCompanyName__. All rights reserved.
*
*/

#include "FinishedGameMenu.h"

FinishedGameMenu::FinishedGameMenu()
{
   IW_CALLSTACK("FinishedGameMenu::FinishedGameMenu");

	this->bFadeOut = true;
	this->bRolling = false;
   this->goldColor.Set(236, 216, 114, 255);
   this->blackColor.Set(0,0,0,255);

   this->i2Position = CIwSVec2(0, 0);
   this->i2Size = CIwSVec2(Screen::getSCREENSIZE().x, Screen::getSCREENSIZE().y);
   this->i2RegionSize = this->i2Size;
   this->i2RegionOffset = CIwSVec2(0, 0);
   this->tTextureList.push_back(ImageManager::getImage("kittybglvls_field"));

   this->mbHitList.push_back(new MainMenuButton(this->i2Position, CIwSVec2(Screen::getSCREENSIZE().x * 0.5f - 25,Screen::getSCREENSIZE().y * 0.8f - 25),CIwSVec2(480,320)));
   this->mbHitList[0]->setBoundingBox(CIwSVec2(0,0));
   this->mMessageList = CIwArray<Message*>();
   this->mMessageList.push_back(new Message(CIwSVec2(0,0)));
   this->mMessageList[0]->setFont("font_large");
   this->mMessageList[0]->setUseTexture(false);
	this->mMessageList.push_back(new Message(CIwSVec2(0,0)));
	this->mMessageList[1]->setFont("font_large");
	this->mMessageList[1]->setUseTexture(false);

	this->imIndex = 0;

   // for dimming
   this->fAlphaInit = 200;
   this->fAlpha = this->fAlphaInit;
   this->opaqueColor.Set(0,0,0, (int)this->fAlpha);
   this->opaquePos = CIwSVec2(0,0);
   this->opaqueSize = CIwSVec2(Screen::getSCREENSIZE().x, Screen::getSCREENSIZE().y);
	
   ClassTracker::addUnit(this);
}

void FinishedGameMenu::setWin()
{
	

   this->opaqueColor.Set(0,0,0, this->fAlphaInit);
	this->iTimePassed = 0;
	this->imIndex = 0;
	this->bRolling = false;
	this->bFadeOut = true;
   stringstream ss;
   ss<<PlayerProfile::getTotalDeath()<<" cats were harmed in the making of this game"<<"\n";
   this->mMessageList[0]->setString(ss.str());
   ss.str("");
	ss<<"Sam Medalen    Level Design\n";
	ss<<"Danny Key       AI\n";
	ss<<"Dante Ratto     Code Design\n";
	ss<<"Tommy           Music\n";
	ss<<"Travis Brown    Art Liaison/Sound\n";
	ss<<"Melissa             Playtest Coordinator\n";
	ss<<"Aurie               Ooooh Yeah\n";
	ss<<"Justin              UI Design";
	this->mMessageList[1]->setString(ss.str());
	ss.str("");
}

void FinishedGameMenu::update(uint64 time)
{
   IW_CALLSTACK("FinishedGameMenu::update");

	s3ePointerUpdate();
	s3ePointerGetState(S3E_POINTER_BUTTON_SELECT);
	CIwSVec2 touch = CIwSVec2(s3ePointerGetX(), s3ePointerGetY()); 

	this->iTimePassed += time;
	//if(this->bRolling == false && this->iTimePassed > 5000)
	{
		this->bRolling = true;
		this->iTimePassed = 0;
	}
	if(this->opaqueColor.a <= 0)
	{
		++this->imIndex;
		this->bFadeOut = false;
      this->opaqueColor.Set(0,0,0,1);
      this->fAlpha = 1;
		if(this->imIndex >= (int)this->mMessageList.size())
		{
			this->imIndex = 0;
			GameState::setState(GameState::MAINMENU);
		}
      return;
	}
	else if(this->opaqueColor.a >= 200)
	{
		this->bFadeOut = true;
	}
	if(this->bRolling == true)
	{
      float fFadeMod = .04;
		if(this->bFadeOut)
      {
		   this->fAlpha -= fFadeMod * time;
      }
		else
      {
		   this->fAlpha += fFadeMod * time;
      }
      //this->opaqueColor.a = (int)this->fAlpha;
      this->opaqueColor.Set(0,0,0,(int)this->fAlpha);
	}
	this->mbHitList[0]->bUpdate = this->mbHitList[0]->hit(touch);
	this->mbHitList[0]->update(time);
   //UserInterface::update(time);
}

void FinishedGameMenu::draw()
{
   SoundManager::setMusic("Catzophrenia");

 Iw2DSetColour(0xffffffff);  
   Iw2DDrawImageRegion(this->tTextureList[this->iTextureIndex], this->i2Position, this->i2Size, this->i2RegionOffset, this->i2RegionSize);
   if(this->imIndex == 0)
   {
	   this->mMessageList[this->imIndex]->drawCenter(this->opaqueColor);
   }
	else
   {
		this->mMessageList[this->imIndex]->drawLeft(this->opaqueColor);
   }
   Iw2DSetColour(0xffffffff);  
   // UserInterface::draw();
}
