//
//
//
//   Project : Schrödinger's cat
//   File Name : Block.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Block.h"

Block::Block(CIwSVec2 i2Position): LethalUnit()
{
   IW_CALLSTACK("Block::Block");
   this->tTextureList.clear_optimised();
   this->tTextureList.push_back(ImageManager::getImage("block"));
	this->sSoundList.push_back(SoundManager::getSound("block"));
   this->i2Position = i2Position;
   this->f2AbsPosition = CIwFVec2(i2Position.x, i2Position.y);
   this->i2FinalPosition = CIwSVec2(0, 0);
   this->sName = "block";
   this->bFall = true;
   this->bRise = false;
   this->iTimePassed = 0;
   this->f2Velocity = CIwFVec2(0, 0.15f);
   this->brBoundingBox = BoundingRectangle(this->getPosition(), this->getSize(), this->getSize(), true);
   this->iCapDeathCount = 0;
   this->iDeathCount = 0;
   this->iMoveDist = 0;
   this->bUpdate = false;

   ClassTracker::addUnit(this);
}

void Block::lightCalculation(uint64 time)
{
   this->blinkTime += time;
	
   if(this->blinkTime > 125)
   {
      if(this->up)
         ++this->lSize;
      else 
         --this->lSize;
		
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

void Block::setColor(CIwColour cColor)
{
   IW_CALLSTACK("MechanicalWall::setColor");
	
   this->cColor.push_back(cColor);
}


void Block::rise() 
{
   IW_CALLSTACK("Block::rise");

   this->f2AbsPosition.y -= this->f2Velocity.y * this->iTime * Screen::getMOVEMULTIPLIER().y;
   this->i2Position.y = (int)this->f2AbsPosition.x;

   if(this->bBox == this->bFinalBox || this->i2Position.y <= this->i2FinalPosition.y + Screen::getBOXSIZE().y)
   {
      this->i2Position.y = this->i2FinalPosition.y;
      this->bAffectUpdate = false;
      this->bRise = false;
		SoundManager::playSound(this->sSoundList[5]);
   }
}

void Block::fall() 
{
   IW_CALLSTACK("Block::fall");
   
   this->iCapDeathCount = 1000;
   this->f2AbsPosition.y += this->f2Velocity.y * this->iTime * Screen::getMOVEMULTIPLIER().y;
   this->i2Position.y = (int)this->f2AbsPosition.y;
   
   // check to see if block is at final position
   if(this->bBox == this->bFinalBox || this->i2Position.y > this->i2FinalPosition.y + Screen::getBOXSIZE().y) //Can't be equal because bBox needs to update
   {
      this->i2Position.y = this->i2FinalPosition.y;
	   this->bBox = this->bFinalBox;
      this->bAffectUpdate = false;
      this->bFall = false;
      this->bIsMoving = false;
      this->iCapDeathCount = 0;
      this->bBox->bConnectList[1]->bIsWalkable = true;
      //this->bBox->bIsWalkable = false;
      this->bBox->bIsFilled = true;
      GameState::setReInitializePathing(true);
		SoundManager::playSound(this->sSoundList[5]);
   }
}

void Block::setMoveDist(int iMoveDist)
{
   IW_CALLSTACK("Block::setMoveDist");
   this->iMoveDist = iMoveDist;
   this->i2FinalPosition.y = (iMoveDist * Screen::getBOXSIZE().y) + this->i2Position.y;

   this->bFinalBox = this->bBox;
   for(int i = 0; i < this->iMoveDist; ++i)
   {
	   this->bFinalBox = this->bFinalBox->bConnectList[5];
   }
}

void Block::update(uint64 time)
{
   IW_CALLSTACK("Block::update");
	
   this->iTime = time;
   this->iTimePassed += time;
	this->lightCalculation(time);
	
   if(bAffectUpdate == true)
   {
      this->bIsMoving = true;
		
      if(this->bRise)
      {
         this->rise();
      }
      if(this->bFall)
      {
         this->fall();
      }
      this->brBoundingBox.setPosition(this->getPosition(), true);
   }
	
   if(this->bUpdate == true)
   {
      LethalUnit::update();
   }
}

void Block::draw()
{
	if(this->bDrawn == false)
	{
		for(int i = 0; i < (int)this->cColor.size(); ++i)
		{
			Iw2DSetColour(this->cColor[i]);
			
			Iw2DSetAlphaMode(IW_2D_ALPHA_HALF);
			Iw2DFillArc(CIwSVec2(this->i2Position.x + Screen::getBOXSIZE().x/2, this->i2Position.y + Screen::getBOXSIZE().y), CIwSVec2(this->lightSize, this->lightSize), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);
			Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
			Iw2DFillArc(CIwSVec2(this->i2Position.x + Screen::getBOXSIZE().x/2, this->i2Position.y + Screen::getBOXSIZE().y), CIwSVec2(Screen::getBOXSIZE().x/6, Screen::getBOXSIZE().y/6), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);
			
			Iw2DSetColour(0xffffffff);
		}
	}
	Unit::draw();
}
