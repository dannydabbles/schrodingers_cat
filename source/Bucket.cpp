//
//
//
//   Project : Schrödinger's cat
//   File Name : Bucket.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Bucket.h"

Bucket::Bucket(CIwSVec2 i2Position): Unit() 
{
   IW_CALLSTACK("Bucket::Bucket");

   this->bFilled = false;
   this->tTextureList.push_back(ImageManager::getImage("bucket"));
   this->i2Position = i2Position;
   this->i2CurrentPosition = i2Position;
   this->i2FinalPosition = i2Position;
   this->f2AbsPosition = CIwFVec2((float)i2Position.x, (float)i2Position.y);
   this->f2Velocity = CIwFVec2(0, 0.06f);
   this->sName = "bucket";
   this->iCapDeathCount = 1;
   this->iCurrentDeathCount = 0;
   this->iMoveDist = 0;
   this->bFall = false;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size, CIwSVec2(1,1));

   ClassTracker::addUnit(this);
}

void Bucket::setCap(int iC)
{
   IW_CALLSTACK("Bucket::setCap");

   this->iCapDeathCount = iC;
}

void Bucket::setMoveDist(int iMoveDist)
{
   IW_CALLSTACK("Bucket::setMoveDist");

   this->iMoveDist = iMoveDist;
   this->i2FinalPosition.y = i2Position.y + (iMoveDist * Screen::getBOXSIZE().y);
}

void Bucket::update(uint64 time)
{
   IW_CALLSTACK("Bucket::update");

   if (GameState::getState() != GameState::PLAY)
   {
      return;
   }
   this->iTime = time;
   this->iTimePassed += time;
   this->brBoundingBox.setPosition(this->i2Position, true);

   if(this->bAffectUpdate == true)
   {
      if(this->bFilled == false) 
      {
         ++this->iCurrentDeathCount;
         if(this->iCurrentDeathCount >= this->iCapDeathCount)
         {
            this->bFilled = true;
            this->bFall = true;
            for(int i = 0; i < (int)this->uAffectList.size(); ++i) 
            {
               this->uAffectList[i]->bAffectUpdate = true;
            }
         }
         //this->bAffectUpdate = false;
      }
      if(this->bFall == true) 
      {
         this->bIsMoving = true;
         this->f2AbsPosition.y += this->f2Velocity.y * this->iTime * Screen::getMOVEMULTIPLIER().y;
         this->i2Position.y = (int)this->f2AbsPosition.y;
         
         if(this->i2Position.y >= this->i2FinalPosition.y)
         {
            this->i2Position.y = this->i2FinalPosition.y;
            this->f2AbsPosition.y = (float)this->i2Position.y;
            this->bFall = false;
            this->bAffectUpdate = false;
            this->bIsMoving = false;
         }
      }
   } 
}
