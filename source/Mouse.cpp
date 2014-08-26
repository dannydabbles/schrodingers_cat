//
//
//
//   Project : Schrödinger's cat
//   File Name : Mouse.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Mouse.h"

Mouse::Mouse(CIwSVec2 i2Position): ShinyUnit() 
{
   IW_CALLSTACK("Mouse::Mouse");

   this->iAIHole = 10;
   this->bUpdate = false;
   this->bDead = false;
   this->bScared = false;
   this->f2Velocity = CIwFVec2(0.101f, 0);
   this->tTextureList.push_back(ImageManager::getImage("mouse"));
   this->tTextureList.push_back(ImageManager::getImage("mouseleft"));


   this->sSoundList.push_back(SoundManager::getSound("mouse1"));
   this->sSoundList.push_back(SoundManager::getSound("mouse2"));	
   this->sSoundList.push_back(SoundManager::getSound("mouse3"));
   this->sSoundList.push_back(SoundManager::getSound("mouse4"));

   this->i2Position = i2Position;
   this->f2AbsPosition = CIwFVec2((float)this->i2Position.x, (float)this->i2Position.y);
   this->i2InitialPosition = i2Position;
   this->sName = "mouse";
   this->fShininess = 6;
   this->bIsMoving = true;
   this->brBoundingBox = BoundingRectangle(this->getPosition(), this->getSize(), CIwSVec2((int)(this->i2Size.x * 0.3f), (int)(this->i2Size.y * 0.3f)), true);
   this->csPlayWith = CatState::MOUSEPLAYING;

   ClassTracker::addUnit(this);
}

void Mouse::setTarget(Unit * uTarget)
{
   IW_CALLSTACK("Mouse::setTarget");

   this->uTarget = uTarget;
   this->iAIHole = abs(this->i2Position.x - this->uTarget->i2Position.x)/2;
   if(this->i2Position.x < this->uTarget->i2Position.x)
   {
      this->bMoveLeft = false;
   }
   else
   {
      this->bMoveLeft = true;
   }
}

void Mouse::setBScared(bool bScared)
{
   IW_CALLSTACK("Mouse::setBScared");

   this->bScared = bScared;
   this->fShininess = 50;
}

bool Mouse::getBScared()
{
   IW_CALLSTACK("Mouse::getBScared");

   return this->bScared;
}

void Mouse::setBDead(bool bDead)
{
   IW_CALLSTACK("Mouse::setBDead");

   this->bDead = bDead;
   if(bDead == true)
   {
      this->bUpdate = false;
      this->bDrawn = true;
      this->fShininess = 0;
   }
}

bool Mouse:: getBDead()
{
   IW_CALLSTACK("Mouse::getBDead");

   return this->bDead;
}

bool Mouse::getBMoveLeft()
{
   IW_CALLSTACK("Mouse::getBDead");

   return this->bMoveLeft;
}

void Mouse::setBMoveLeft(bool bMoveLeft)
{
   IW_CALLSTACK("Mouse::setBMoveleft");

   this->bMoveLeft = bMoveLeft;
}

bool Mouse::scaredMove(Box* bCurr, Box* bNext)
{
   IW_CALLSTACK("Mouse::scaredMove");
   CIwFVec2 ftemp = this->f2AbsPosition;
   if(bCurr->i2Position == uTarget->i2Position)
   {
      this->bDead = true;
      this->bUpdate = false;
      this->bDrawn = true;
      this->fShininess = -1;
      return true;
   }
   else if(bCurr->getUnit("bucket") != NULL)
   {
      bCurr->getUnit("bucket")->bUpdate = true;
      bCurr->getUnit("bucket")->bAffectUpdate = true;
      this->bDead = true;
      this->bUpdate = false;
      this->bDrawn = true;
      this->fShininess = -1;
      return true;
   }
   else
   {
      this->iSoundIndex = IwRandMinMax(0, 4);
      SoundManager::playSound(this->sSoundList[this->iSoundIndex]);
      if(this->bMoveLeft == true)
      {
         this->f2AbsPosition.x -= this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
         this->i2Position.x = (int)this->f2AbsPosition.x;
      }
      else
      {
         this->f2AbsPosition.x += this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
         this->i2Position.x = (int)this->f2AbsPosition.x;
      }
   }
   if((bNext == NULL || bCurr->bIsFilled == true || bNext->bIsFilled == true || bCurr->bIsWalkable == false || bNext->bIsWalkable == false))
   {
      if(this->bMoveLeft == true)
      {
         this->f2AbsPosition = ftemp;
         //this->f2AbsPosition.x -= this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
         this->i2Position.x = (int)this->f2AbsPosition.x;
      }
      else
      {
         this->f2AbsPosition = ftemp;
         //this->f2AbsPosition.x += this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
         this->i2Position.x = (int)this->f2AbsPosition.x;
      }
   }
   return false;
}

bool Mouse::regularMove()
{
   IW_CALLSTACK("Mouse::regularMove");
   CIwFVec2 ftemp = this->f2AbsPosition;
   if(this->bScared == true)
   {
   }
   else
   {
      if(this->bMoveLeft == true)
      {
         this->f2AbsPosition.x -= this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
         if(checkPosition())
            this->i2Position.x = (int)this->f2AbsPosition.x;
         else
            this->f2AbsPosition = ftemp;
      }
      else
      {
         this->f2AbsPosition.x += this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
         if(checkPosition())
            this->i2Position.x = (int)this->f2AbsPosition.x;
         else
            this->f2AbsPosition = ftemp;
      }
   }

   return false;
}

bool Mouse::checkPosition()
{
   if(this->bMoveLeft == true)
   {
      if(this->uTarget->i2Position.x < this->i2InitialPosition.x)
      {
         if(this->f2AbsPosition.x < this->uTarget->i2Position.x + this->iAIHole)
         {
            this->bMoveLeft = false;
            return false;
         }
      }
      else
      {
         if(this->f2AbsPosition.x < this->i2InitialPosition.x)
         {
            this->bMoveLeft = false;
            return false;
         }
      }
   }
   else
   {
      if(this->uTarget->i2Position.x < this->i2InitialPosition.x)
      {
         if(this->f2AbsPosition.x > this->i2InitialPosition.x)
         {
            this->bMoveLeft = true;
            return false;
         }
      }
      else 
      {
         if(this->f2AbsPosition.x > this->uTarget->i2Position.x - this->iAIHole)
         {
            this->bMoveLeft = true;
            return false;
         }
      }
   }
   /*
   if(this->i2Position.x == this->i2InitialPosition.x)
   {
   if(this->i2Position.x < this->uTarget->i2Position.x)
   {
   this->bMoveLeft = false;
   }
   else
   {
   this->bMoveLeft = true;
   }
   }
   else if(this->i2Position.x == this->uTarget->i2Position.x - this->iAIHole || this->i2Position.x == this->uTarget->i2Position.x + this->iAIHole)
   {
   if(this->i2Position.x < this->uTarget->i2Position.x)
   {
   this->bMoveLeft = true;
   }
   else
   {
   this->bMoveLeft = false;
   }
   }
   */
   return true;

}

void Mouse::draw()
{
   IW_CALLSTACK("Mouse::draw");

   if(this->bMoveLeft == true)
   {
      this->iTextureIndex = 1;
   }
   else
   {
      this->iTextureIndex = 0;
   }
   Unit::draw();
}

void Mouse::update(uint64 time)
{
   IW_CALLSTACK("Mouse::update");

   if(GameState::getState() != GameState::PLAY)
   {
      return;
   }
   this->iTime = time;
   this->iTimePassed += time;

   this->brBoundingBox.setPosition(this->getPosition(), true);

   if(this->bDead == false)
   {
      if(this->bUpdate == true)
      {
         this->iSoundIndex = IwRandMinMax(0, 4);
         this->bDead = true;
         this->bDrawn = true;
         this->bUpdate = false;
         this->setNotShiny();
         for(int i = 0; i < (int)uAffectList.size(); ++i)
         {
            dynamic_cast<ShinyUnit*>(this->uAffectList[i])->setNotShiny();
            dynamic_cast<Food*>(this->uAffectList[i])->bEmpty = true;
         }
      }
   }
   ShinyUnit::update();
}
