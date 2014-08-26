//
//
//
//   Project : Schrödinger's cat
//   File Name : Anvil.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Anvil.h"

Anvil::Anvil(CIwSVec2 i2Position): LethalUnit()
{
   IW_CALLSTACK("Anvil::Anvil");

   this->tTextureList.push_back(ImageManager::getImage("anvil"));
	this->sSoundList.push_back(SoundManager::getSound("boxingglove"));
   this->i2Position = i2Position;
   this->f2AbsPosition = CIwFVec2(i2Position.x, i2Position.y);
   this->sName = "anvil";
   this->i2FinalPosition = CIwSVec2(0, 0);
   this->f2Velocity = CIwFVec2(0, 0.2f);
   this->bFall = true;
	this->cColor = CIwArray<CIwColour>();
   this->brBoundingBox = BoundingRectangle(this->getPosition(), this->getSize(), this->getSize(), true);
   this->iCapDeathCount = 2;
   this->i2FinalPosition.y = Screen::getSCREENSIZE().y;

   ClassTracker::addUnit(this);
}

void Anvil::lightCalulation(uint64 time)
{
   this->blinkTime += time;
	
   if(this->blinkTime > 200)
   {
      if(this->up)
         this->lSize += (int)Screen::getMOVEMULTIPLIER().x;
      else 
         this->lSize -= (int)Screen::getMOVEMULTIPLIER().x;
		
      if(this->lSize >= 5 || this->lSize < 0)
      {
         this->blinkTime = 0;
         this->up = !this->up;
      }
   }
	
   switch(this->lSize)
   {
		case 0:
			this->lightSize = (int)(Screen::getBOXSIZE().x * 0.25f * 0.2f);
			break;
		case 1:
			this->lightSize = (int)(Screen::getBOXSIZE().x * 0.25f * 0.4f);
			break;
		case 2:
			this->lightSize = (int)(Screen::getBOXSIZE().x * 0.25f * 0.6f);
			break;
		case 3:
			this->lightSize = (int)(Screen::getBOXSIZE().x * 0.25f * 0.8f);
			break;
		case 4:
			this->lightSize = (int)(Screen::getBOXSIZE().x * 0.25f * 1.0f);
			break;
		case 5:
			this->lightSize = (int)(Screen::getBOXSIZE().x * 0.25f * 1.2f);
			break;
   }
}

void Anvil::setColor(CIwColour cColor)
{
   IW_CALLSTACK("MechanicalWall::setColor");
	
   this->cColor.push_back(cColor);
}

void Anvil::setMoveDist(int iMoveDist)
{
   IW_CALLSTACK("Anvil::setMoveDist");
   //this->i2FinalPosition.y = (iMoveDist * Screen::getBOXSIZE().y) + this->i2Position.y;
   this->i2FinalPosition.y = Screen::getSCREENSIZE().y;
}

void Anvil::update(uint64 time)
{
   IW_CALLSTACK("Anvil::update");

   this->iTime = time;
   this->iTimePassed += time;
	this->lightCalulation(time);
	
   if(bAffectUpdate == true)
   {
      this->bIsMoving = true;
      this->f2AbsPosition.y += this->f2Velocity.y * this->iTime * Screen::getMOVEMULTIPLIER().y;
      this->i2Position.y = (int)this->f2AbsPosition.y;

      if(this->i2Position.y >= this->i2FinalPosition.y)
      {
         this->i2Position.y = this->i2FinalPosition.y;
         this->bAffectUpdate = false;
         this->bFall = false;
         this->bDrawn = true;
         this->iCapDeathCount = 0;
      }
      this->brBoundingBox.setPosition(this->getPosition(), true);
   }

   if(bUpdate == true)
   {
		SoundManager::playSound(this->sSoundList[5]);
      LethalUnit::update();
   }
}

void Anvil::draw()
{
	if(this->bDrawn == false)
	{
		for(int i = 0; i < (int)this->cColor.size(); ++i)
		{
			Iw2DSetColour(this->cColor[i]);
			
			Iw2DSetAlphaMode(IW_2D_ALPHA_HALF);
			Iw2DFillArc(CIwSVec2(this->i2Position.x + Screen::getBOXSIZE().x/2, i2Position.y + Screen::getBOXSIZE().y), CIwSVec2(this->lightSize, this->lightSize), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);
			Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
			Iw2DFillArc(CIwSVec2(this->i2Position.x + Screen::getBOXSIZE().x/2, i2Position.y + Screen::getBOXSIZE().y), CIwSVec2(Screen::getBOXSIZE().x/6 ,Screen::getBOXSIZE().x/6), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);

			Iw2DSetColour(0xffffffff);
		}
	}
	Unit::draw();
}
