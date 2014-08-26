/*
*  MenuButton.cpp
*  Kitty
*
*  Created by Sam Medalen on 4/29/11.
*  Copyright 2011 __MyCompanyName__. All rights reserved.
*
*/

#include "MenuButton.h"

MenuButton::MenuButton(): Unit()
{
	IW_CALLSTACK("MenuButton::MenuButton");

   this->i2Offset = CIwSVec2(0, 0);
   this->i2RegionOffset = CIwSVec2(0, 0);
   this->bPressed = false;
   this->bScreenTouched = false;
   this->sName = "button";

   /*if(num <= 26 && num > 0)
   {
   string name = "level_";
   std::stringstream ss;
   ss<<num;
   name += (ss.str());
   tTextureList.push_back(ImageManager::getImage(name.c_str()));
   name+= 'b';
   tTextureList.push_back(ImageManager::getImage(name.c_str()));
   }
   if(num == 0)
   {
   tTextureList.push_back(ImageManager::getImage("level_i"));
   tTextureList.push_back(ImageManager::getImage("level_ib"));
   }
   if(num == -1)
   {
   tTextureList.push_back(ImageManager::getImage("kittyplay"));
   tTextureList.push_back(ImageManager::getImage("kittyplay2"));
   }
   else if(num == -2)
   {
   tTextureList.push_back(ImageManager::getImage("kittybutton_left"));
   tTextureList.push_back(ImageManager::getImage("kittybutton_left2"));
   }

   else if(num == -3)
   {
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_play"));
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_play2"));
   }
   else if(num == -4)
   {
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_restart"));
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_restart2"));
   }
   else if(num == -5)
   {
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_levels"));
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_levels2"));
   }
   else if(num == -6)
   {
   tTextureList.push_back(ImageManager::getImage("kittybutton_pause"));
   tTextureList.push_back(ImageManager::getImage("kittybutton_pause2"));
   }
   else if(num == -7)
   {
   tTextureList.push_back(ImageManager::getImage("kittybutton_right"));
   tTextureList.push_back(ImageManager::getImage("kittybutton_right2"));
   }
   else if(num == -8)
   {
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_volume"));
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_volumex2"));
   }
   else if(num == -9)
   {
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_question"));
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_question2"));
   }
   else if(num == -10)
   {
   tTextureList.push_back(ImageManager::getImage("kittyboard"));
   tTextureList.push_back(ImageManager::getImage("kittyboard"));
   }
   else
   {
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_question"));
   tTextureList.push_back(ImageManager::getImage("kittysidebutton_question2"));
   } */

   ClassTracker::addUnit(this);
}

MenuButton::~MenuButton()
{
   cout << "do nothing" << endl;
}

void MenuButton::setPosition(CIwSVec2 position)
{
	IW_CALLSTACK("MenuButton::setPosition");

   this->i2Position = position + this->i2Offset;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);
}

void MenuButton::update(uint64 time)
{
	IW_CALLSTACK("MenuButton::update");

}

void MenuButton::draw()
{
	IW_CALLSTACK("MenuButton::draw");

   Iw2DDrawImageRegion(this->tTextureList[this->iTextureIndex], this->i2Position, this->i2Size, this->i2RegionOffset, this->i2RegionSize);
}

bool MenuButton::hit(CIwSVec2 point)
{  
	IW_CALLSTACK("MenuButton::hit");

   if(this->bPressed == true && s3ePointerGetState(S3E_POINTER_BUTTON_SELECT) == S3E_POINTER_STATE_UP)
   {
      this->bPressed = false;
      return true;
   }

   if(this->brBoundingBox.pointCollision(point) && s3ePointerGetTouchState(0) && S3E_POINTER_TOUCH_EVENT && bScreenTouched == false)
   {
      this->bPressed = true;
   }
   else
   {
      if(s3ePointerGetTouchState(0) && S3E_POINTER_TOUCH_EVENT)
      {
         this->bScreenTouched = true;
      }
      else
      {
         this->bScreenTouched = false;
      }
      this->bPressed = false;
   }
   return false;
}


void MenuButton::setBoundingBox(CIwSVec2 p)
{
   this->brBoundingBox.setPosition(p,false);
}
