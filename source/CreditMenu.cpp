//
//
//
//   Project : Schrödinger's cat
//   File Name : CreditMenu.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "CreditMenu.h"

CreditMenu::CreditMenu(): UserInterface()
{
   IW_CALLSTACK("CreditMenu::CreditMenu");

   this->i2Size = CIwSVec2(412, 268);
   this->i2Position = CIwSVec2(Screen::getSCREENSIZE().x, Screen::getSCREENSIZE().y - (this->i2Size.y - 1));
   this->f2AbsPosition = CIwFVec2(this->i2Position.x, this->i2Position.y);
   this->i2RegionSize = CIwSVec2(412, 268);
   this->tTextureList.push_back(ImageManager::getImage("kittyboard"));
   this->f2Velocity = CIwFVec2(0.6f, 0);
   this->i2FinalPosition = CIwSVec2(Screen::getSCREENSIZE().x - (this->i2Size.x - 14), Screen::getSCREENSIZE().y - (Screen::getSCREENSIZE().y/2 ));
   this->mbHitList.push_back(new CreditButton(this->i2Position, CIwSVec2(this->i2Size.x - 84, this->i2Size.y - 64), CIwSVec2(50, 50), true));

   ClassTracker::addUnit(this);
}

void CreditMenu::update(uint64 time)
{
   IW_CALLSTACK("CreditMenu::update");

   UserInterface::update(time);

   if(GameState::getState() == GameState::CREDITMENUBACK)
   {
      this->f2AbsPosition.x += this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
      this->i2Position.x = (int)this->f2AbsPosition.x;

      if(this->i2Position.x >= Screen::getSCREENSIZE().x)
      {
         GameState::setState(GameState::MAINMENU);
         this->i2Position.x = Screen::getSCREENSIZE().x;
         this->f2AbsPosition.x = (float)this->i2Position.x;
      }
   }
   else
   {
      this->f2AbsPosition.x -= this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
      this->i2Position.x = (int)this->f2AbsPosition.x;

      if(this->i2Position.x <= this->i2FinalPosition.x)
      {
         this->i2Position.x = this->i2FinalPosition.x;
         this->f2AbsPosition.x = (float)this->i2Position.x;
      }
   }

   for(int i = 0; i < (int)this->mbHitList.size(); ++i)
   {
      this->mbHitList[i]->setPosition(this->i2Position);
   }
}

void CreditMenu::draw()
{
	CIwColour tmp;
	tmp.Set(0, 0, 0, 100);
	Iw2DSetColour(tmp);
	Iw2DFillRect(CIwSVec2(0, 0), Screen::getSCREENSIZE());
	tmp.Set(255, 255, 255, 255);
	Iw2DSetColour(tmp);
	UserInterface::draw();
}