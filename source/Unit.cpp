//
//
//
//   Project : Schrödinger's cat
//   File Name : Unit.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Unit.h"

Unit::Unit()
{
   IW_CALLSTACK("Unit::Unit");

   this->iTextureIndex = 0;
   this->iAnimateTime = 64;
   this->iSoundIndex = -1;
   this->bDrawn = false;
   this->bUpdate = false;
   this->bAffectUpdate = false;
   this->bTop = false;
   this->iTime = 0;
   this->iTimePassed = 0;
   this->i2Size = Screen::getBOXSIZE();
   this->f2Velocity = CIwFVec2(0, 0);
   this->i2Center = CIwVec2(0, 0);
   this->i2Position = CIwSVec2(0, 0);
   this->i2RegionSize = CIwSVec2(32, 32);
   this->i2RegionOffset = CIwSVec2(this->i2RegionSize.x, 0);
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);
   this->uAttatchedToList = CIwArray<Unit*>();
   this->uAffectList = CIwArray<Unit*>();
   this->tTextureList = CIwArray<CIw2DImage*>();
   this->sSoundList = CIwArray<CIwSoundSpec*>();
   this->bIsShiny = false;
   this->bIsMoving = false;
   this->sName = "NAME_ME_NUB.";
   this->bBox = NULL;
   this->iOldTextureIndex = 9999;
   this->lightSize = 0;
   this->lSize =0;
   this->blinkTime = 0;
   this->up = false;

   ClassTracker::units--;
}


Unit::~Unit()
{
   this->uAffectList.clear();
   this->uAttatchedToList.clear();
   this->tTextureList.clear();
   this->sSoundList.clear();

   ClassTracker::removeUnit(this);
   ClassTracker::units--;
}


void Unit::addUnit(Unit* u)
{
   IW_CALLSTACK("Unit::addUnit");

   this->uAttatchedToList.push_back(u);
}

void Unit::changeTexture(int i)
{
   IW_CALLSTACK("Unit::changeTexture");

   this->iTextureIndex = i;
   //IwAssertMsg(MYAPP, false, ("Error: changeTexture() Called"));
}

void Unit::draw()
{
   IW_CALLSTACK("Unit::draw");

   IwAssertMsg(MYAPP, CatState::getState() != CatState::TRANSITIONING, ("Unit draw exited with interrupt state"));

   if(this->bDrawn == false)
   {
      if(this->i2RegionOffset.x >= this->tTextureList[iTextureIndex]->GetWidth() || this->iTextureIndex != this->iOldTextureIndex)
      {
         this->i2RegionOffset.x = 0;
      }
      Iw2DDrawImageRegion(this->tTextureList[this->iTextureIndex], this->i2Position, this->i2Size, this->i2RegionOffset, this->i2RegionSize);

      if(this->iTimePassed >= this->iAnimateTime)
      {
         this->i2RegionOffset.x += this->i2RegionSize.x;
         this->iTimePassed = 0;
      }
      this->iOldTextureIndex = this->iTextureIndex;
   }
}

CIwSVec2 Unit::getPosition()
{
   IW_CALLSTACK("Unit::getPosition");

   return this->i2Position;
}

CIwSVec2 Unit::getSize()
{
   IW_CALLSTACK("Unit::getSize");

   return this->i2Size;
}

CIwSVec2 Unit::getRO()
{
   IW_CALLSTACK("Unit::getRO");

   return this->i2RegionOffset;
}

CIwSVec2 Unit::getRS()
{
   IW_CALLSTACK("Unit::getRS");

   return this->i2RegionSize;
}

BoundingRectangle& Unit::getBR()
{
   IW_CALLSTACK("Unit::getBR");

   return this->brBoundingBox;
}

void Unit::setSize(int x, int y)
{
   IW_CALLSTACK("Unit::setSize");
   this->i2Size = CIwSVec2(x,y);
}

void Unit::setRO(int x, int y)
{
   IW_CALLSTACK("Unit::setRO");
   this->i2RegionOffset = CIwSVec2(x,y);
}

void Unit::setRS(int x, int y)
{
   IW_CALLSTACK("Unit::setRS");
   this->i2RegionSize = CIwSVec2(x,y);
}
