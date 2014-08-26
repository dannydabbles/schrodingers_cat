//
//
//
//   Project : Schrödinger's cat
//   File Name : MechanicalWall.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "MechanicalWall.h"

MechanicalWall::MechanicalWall(CIwSVec2 i2Position, string sName, bool bIsWall, int iIndexNum): LethalUnit() 
{
   IW_CALLSTACK("MechanicalWall::MechanicalWall");

   this->tTextureList.push_back(ImageManager::getImage("wall"));
   this->tTextureList.push_back(ImageManager::getImage("wallleft"));
   this->tTextureList.push_back(ImageManager::getImage("wallright"));
   this->tTextureList.push_back(ImageManager::getImage("wallboth"));
   this->sSoundList.push_back(SoundManager::getSound("mechanicalwall"));
   this->bPlayedSoundOnce = false;
   this->i2FinalPosition = i2Position;
   this->i2Position = i2Position;
   this->f2Velocity = CIwFVec2(0, 0.06f);
   this->f2AbsPosition = CIwFVec2(this->i2Position.x, this->i2Position.y);
   this->sName = sName;
   this->bDown = false;
   this->count = 0;
   this->iTextureIndex = iIndexNum;
   this->bUpdate = false;
   //this->iCapDeathCount = 1000;
   this->iCapDeathCount = 0;
   //this->bIsWall = bIsWall;
   this->cColor = CIwArray<CIwColour>();
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size, CIwSVec2(this->i2Size.x * 0.25f, this->i2Size.y * 0.25f), true);

   /*if(this->iTextureIndex == 0)
   {
   this->brBoundingBox = BoundingRectangle(this->i2Position + CIwSVec2(12, 1), CIwSVec2(7, 30));
   }
   else if(this->iTextureIndex == 1)
   {
   this->brBoundingBox = BoundingRectangle(this->i2Position + CIwSVec2(1, 1), CIwSVec2(7, 30));
   }
   else if(this->iTextureIndex == 2)
   {
   this->brBoundingBox = BoundingRectangle(this->i2Position + CIwSVec2(24, 1), CIwSVec2(7, 30));
   }
   else if(this->iTextureIndex == 3)
   {
   this->brBoundingBox = BoundingRectangle(this->i2Position + CIwSVec2(1, 1), CIwSVec2(30, 30));
   }*/
   ClassTracker::addUnit(this);
}

MechanicalWall::~MechanicalWall()
{
   IW_CALLSTACK("MechanicalWall::~MechanicalWall");

   this->cColor.clear_optimised();
}

void MechanicalWall::setColor(CIwColour cColor)
{
   IW_CALLSTACK("MechanicalWall::setColor");

   this->cColor.push_back(cColor);
}

void MechanicalWall::setDown(bool bDown)
{
   IW_CALLSTACK("MechanicalWall::setDown");

   this->bDown = bDown;
}

bool MechanicalWall::getDown()
{
   IW_CALLSTACK("MechanicalWall::getDown");

   return this->bDown;
}
// when wall changes its direction will still moving
void MechanicalWall::ToggleMidMove()
{
   this->bDown = !this->bDown;

   if(this->bDown == true)
   {
      this->i2FinalPosition.y = this->i2FinalPosition.y - (this->iMoveDist * Screen::getBOXSIZE().y);
   }
   else
   {
      this->i2FinalPosition.y = this->i2FinalPosition.y + (this->iMoveDist * Screen::getBOXSIZE().y);
   }
}

void MechanicalWall::setMoveDist(int iMoveDist)
{
   IW_CALLSTACK("MechanicalWall::setMoveDist");

   this->iMoveDist = iMoveDist;

   if(bDown == true)
   {
      this->i2FinalPosition.y = this->i2Position.y - (this->iMoveDist * Screen::getBOXSIZE().y);
   }
   else
   {
      this->i2FinalPosition.y = this->i2Position.y + (this->iMoveDist * Screen::getBOXSIZE().y);
   }
}

void MechanicalWall::update(uint64 time)
{
   IW_CALLSTACK("MechanicalWall::update");

   this->iTime = time;
   this->iTimePassed += time;
	this->bBox->bIsFilled = true;
	
   if(this->bTop)
   {
      this->lightCalulation(time);

      if(this->bAffectUpdate == true)
      {
         this->bIsMoving = true;

         if(bPlayedSoundOnce == false)
         {
            SoundManager::playSound(this->sSoundList[5]);
            this->bPlayedSoundOnce = true;
         }

         if(this->bDown == true)
         {
            this->rise();
         }
         else
         {
            this->fall();
         }
         this->brBoundingBox.setPosition(this->i2Position, true);
         //this->brBoundingBox.setPosition(this->i2Position + CIwSVec2(12, 1));

         for(int i = 0; i < (int)this->uAttatchedToList.size(); ++i)
         {
            MechanicalWall* mWall = dynamic_cast<MechanicalWall*>(this->uAttatchedToList[i]);
            mWall->i2Position.y = this->i2Position.y + this->i2Size.y * (i + 1);
            mWall->getBR().setPosition(mWall->i2Position, true);
            //mWall->getBR().setPosition(mWall->i2Position + CIwSVec2(12, 1));
            mWall->bPlayedSoundOnce = this->bPlayedSoundOnce;
            mWall->bIsMoving = true;
            mWall->iCapDeathCount = 1000;
         }
      }
   }

   if(this->bUpdate == true)
   {
      if(this->iDeathCount < this->iCapDeathCount || this->iCapDeathCount == 1000) //1000 means infinite deaths
      {
         CatState::setState(CatState::DEAD);
         this->deathSound();
         ++this->iDeathCount;
      }
      this->bUpdate = false;
   }
}

void MechanicalWall::rise() 
{
   IW_CALLSTACK("MechanicalWall::rise");

   this->iCapDeathCount = 1000;
   this->f2AbsPosition.y -= this->f2Velocity.y * this->iTime * Screen::getMOVEMULTIPLIER().y;
   this->i2Position.y = (int)this->f2AbsPosition.y;

   if(this->i2Position.y <= this->i2FinalPosition.y)
   {
      this->i2Position.y = this->i2FinalPosition.y;
      this->f2AbsPosition.y = (float)this->i2Position.y;
      this->bAffectUpdate = false;
      this->bDown = false;
      this->bPlayedSoundOnce = false;
      this->setMoveDist(this->iMoveDist);
      GameState::setReInitializePathing(true);
      //this->iCapDeathCount = 0;

      return;
   }
}

void MechanicalWall::fall() 
{
   IW_CALLSTACK("MechanicalWall::fall");

   this->iCapDeathCount = 1000;
   this->f2AbsPosition.y += this->f2Velocity.y * this->iTime * Screen::getMOVEMULTIPLIER().y;
   this->i2Position.y = (int)this->f2AbsPosition.y;

   if(this->i2Position.y >= this->i2FinalPosition.y)
   {
      this->i2Position.y = this->i2FinalPosition.y;
      this->f2AbsPosition.y = (float)this->i2Position.y;
      this->bAffectUpdate = false;
      this->bDown = true;
      this->bPlayedSoundOnce = false;
      this->setMoveDist(this->iMoveDist);
      GameState::setReInitializePathing(true);
      //this->iCapDeathCount = 0;

      return;
   }
   //this->i2Position.y += (int)Screen::getMOVEMULTIPLIER().y;
}

void MechanicalWall::setAll()
{   
   IW_CALLSTACK("MechanicalWall::setAll");

   if(this->bDown == true)
   {
      this->i2FinalPosition.y = this->i2Position.y - (this->iMoveDist * Screen::getBOXSIZE().y);
   }
   else
   {
      this->i2FinalPosition.y = this->i2Position.y + (this->iMoveDist * Screen::getBOXSIZE().y);
   }

   for(int b = 0; b < (int)this->uAttatchedToList.size(); ++b)
   {
      MechanicalWall* tempWall = dynamic_cast<MechanicalWall*>(this->uAttatchedToList[b]);
      tempWall->setDown(this->bDown);
      tempWall->setMoveDist(this->iMoveDist);

      if(this->bDown == true)
      {
         tempWall->i2FinalPosition.y = tempWall->i2Position.y - (tempWall->iMoveDist * Screen::getBOXSIZE().y);
      }
      else
      {
         tempWall->i2FinalPosition.y = tempWall->i2Position.y + (tempWall->iMoveDist * Screen::getBOXSIZE().y);
      }
   }
}

void MechanicalWall::draw()
{
   IW_CALLSTACK("MechanicalWall::update");

   if(this->bTop == true)
   {
      int xPos = this->i2Position.x + (int)(Screen::getBOXSIZE().x / 2.5f);
      int yPos = this->i2Position.y + 5;
      int heightMultiplier = 0;
      for(int i = 0; i < (int)this->cColor.size(); ++i)
      {
         if(i % 2 == 0)
         {
            xPos = this->i2Position.x + (int)(Screen::getBOXSIZE().x / 2.5f);
            yPos += heightMultiplier * (Screen::getBOXSIZE().x / 4 + 1);
            ++heightMultiplier;
         }
         else
         {
            xPos = this->i2Position.x + (int)(Screen::getBOXSIZE().x / 2.5f) + Screen::getBOXSIZE().x/4;
         }
         Iw2DSetColour(this->cColor[i]);
         Iw2DSetAlphaMode(IW_2D_ALPHA_HALF);
         Iw2DFillArc(CIwSVec2(xPos, yPos), CIwSVec2(this->lightSize, this->lightSize), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);
         Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
         Iw2DFillArc(CIwSVec2(xPos, yPos), CIwSVec2(Screen::getBOXSIZE().x/16, Screen::getBOXSIZE().y/16), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);
         Iw2DSetColour(0xffffffff);
      }
   }
   Unit::draw();
}


void MechanicalWall::lightCalulation(uint64 time)
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
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 0.2f);
      break;
   case 1:
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 0.4f);
      break;
   case 2:
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 0.6f);
      break;
   case 3:
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 0.8f);
      break;
   case 4:
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 1.0f);
      break;
   case 5:
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 1.2f);
      break;
   }
}
