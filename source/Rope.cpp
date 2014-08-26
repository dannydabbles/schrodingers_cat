//
//
//
//   Project : Schrödinger's cat
//   File Name : Rope.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Rope.h"

Rope::Rope(CIwSVec2 i2Position): Unit()
{
   IW_CALLSTACK("Rope::Rope");

   this->tTextureList.push_back(ImageManager::getImage("rope"));
   this->sSoundList.push_back(SoundManager::getSound("ropecut"));
   this->sSoundList.push_back(SoundManager::getSound("ropeslide"));

   this->i2Position = i2Position;
   this->f2AbsPosition = CIwFVec2(i2Position.x, i2Position.y);
   this->f2Velocity = CIwFVec2(0, 0.06f);
   this->sName="rope";
   this->iTextureIndex = 0;
   this->i2FinalPosition = i2Position;
   this->bCuttable = true;
   this->bCut = false;
   this->bRise = false;
   this->bFall = false;
   this->bFallable = false;
   this->bRiseable = false;
   this->bPlayedSoundOnce = false;
   this->brBoundingBox = BoundingRectangle(this->getPosition(), this->getSize(), this->i2Size, true);

   ClassTracker::addUnit(this);
}

void Rope::setCuttable(bool bCuttable)
{
   IW_CALLSTACK("Rope::setCuttable");

   this->bCuttable = bCuttable;
}

void Rope::setMoveDist(int iMoveDist)
{
   IW_CALLSTACK("Rope::setMoveDist");

   this->iMoveDist = iMoveDist;
}

void Rope::setRiseable(bool bRiseable)
{
   IW_CALLSTACK("Rope::setRiseable");

   this->bRiseable = bRiseable;
	this->bCuttable = bRiseable;
}

void Rope::setFallable(bool bFallable)
{
   IW_CALLSTACK("Rope::setFallable");

   this->bFallable = bFallable;
   this->bCuttable = !bFallable;
}

void Rope::update(uint64 time)
{ 
   IW_CALLSTACK("Rope::update");

   if(GameState::getState() != GameState::PLAY)
   {
      return;
   }
   this->iTime = time;
   this->iTimePassed += time;

   // set bounding boxes if rope is going to move
   if(this->bAffectUpdate == true || (this->bCuttable == true && this->bUpdate == true && CatState::getState() == CatState::BATTING))
   {
      if(this->bPlayedSoundOnce == false)
      {
         if(this->bUpdate == true && CatState::getState() == CatState::BATTING)
         {
            SoundManager::playSound(this->sSoundList[0]);
         }				
         SoundManager::playSound(this->sSoundList[1]);
         bPlayedSoundOnce = true;
      }

      this->bIsMoving = true;

      if(bTop == true && bRise != true && bFall!= true)
      {
         /*
         for(int i = 0; i < (int)uAttatchedToList.size(); ++i)
         {
         Rope* temp = (Rope*)uAttatchedToList[i];
         if(this->bRiseable == true)
         {
         temp->bRise = true;
         }
         else if(this->bFallable == true)
         {
         temp->bFall = true;
         }
         temp->bUpdate = true;
         }
         */
         if(this->bRiseable == true)
         {
            this->bRise = true;
         }
         else if(this->bFallable == true)
         {
            this->bFall = true;
         }
         for(int i = 0; i < (int)uAffectList.size(); ++i)
         {
            //uAffectList[i]->bUpdate = true;
            this->uAffectList[i]->bAffectUpdate = true;
            if(this->uAffectList[i]->sName.compare("rope") == 0)
            {
               dynamic_cast<Rope*>(this->uAffectList[i])->bPlayedSoundOnce = this->bPlayedSoundOnce;
            }
         }
      }
      //else if(bTop != true)
      //{
      //   uAttatchedToList[0]->bUpdate = true;
      //}
      if(this->bRiseable == true || this->bFallable == true)
      {
         if(bRise == true)
            rise();
         else if(bFall == true)
            fall();
      }
      else if(this->bRiseable ==false && this->bFallable == false)
      {
         this->bUpdate = false;
      }
   }
}

void Rope::draw()
{
   IW_CALLSTACK("Rope::draw");

   CIwSVec2 tempPosition = this->i2Position;
   Unit::draw();
   for(int i = 0; i <= (tempPosition.y / 32); ++i)
   {
      this->i2Position.y -= Screen::getBOXSIZE().y;
      Unit::draw();
   }
   this->i2Position = tempPosition;
}

void Rope::rise() 
{
   IW_CALLSTACK("Rope::rise");

   if(i2Position.y <= i2FinalPosition.y)
   {
      i2Position.y = i2FinalPosition.y;
      bUpdate = false;
      bCuttable = false;
      this->bRiseable = false;
      return;
   }
   this->f2AbsPosition.y -= this->f2Velocity.y * this->iTime * Screen::getMOVEMULTIPLIER().y;
   this->i2Position.y = (int)this->f2AbsPosition.y;
}

void Rope::fall() 
{
   IW_CALLSTACK("Rope::fall");

   if(i2Position.y >= i2FinalPosition.y)
   {
      i2Position.y = i2FinalPosition.y;
      bUpdate = false;
      bCuttable = false;
      this->bFallable = false;
      return;
   }
   this->f2AbsPosition.y += this->f2Velocity.y * this->iTime * Screen::getMOVEMULTIPLIER().y;
   this->i2Position.y = (int)this->f2AbsPosition.y;
}

void Rope::setAll()
{
   IW_CALLSTACK("Rope::setAll");

   if(bRiseable == true)
      this->i2FinalPosition.y = this->i2Position.y - (this->iMoveDist * 32);
   else if(bFallable == true)
      this->i2FinalPosition.y = this->i2Position.y + (this->iMoveDist * 32);
   for(int b = 0; b < (int)uAttatchedToList.size(); ++b)
   {
      Rope* tempWall = (Rope*)uAttatchedToList[b];
      tempWall->setRiseable(this->bRiseable);
      tempWall->setFallable(this->bFallable);
      tempWall->setMoveDist(this->iMoveDist);
      if(bRiseable == true)
         tempWall->i2FinalPosition.y = tempWall->i2Position.y - (tempWall->iMoveDist * 32);
      else if(bFallable == true)
         tempWall->i2FinalPosition.y = tempWall->i2Position.y + (tempWall->iMoveDist * 32);
   }
}
