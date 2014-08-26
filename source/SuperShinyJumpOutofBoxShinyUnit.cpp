//
//
//   Project : Schrödinger's cat
//   File Name : SuperShinyJumpOutofBoxShinyUnit.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//

#include "SuperShinyJumpOutofBoxShinyUnit.h"

SuperShinyJumpOutofBoxShinyUnit::SuperShinyJumpOutofBoxShinyUnit(CIwSVec2 i2Position) : ShinyUnit()
{
   this->sName = "supershiny";
   this->fShininess = 0;
   this->bDrawn = true;
   this->i2Position = i2Position;
   this->brBoundingBox = BoundingRectangle(this->getPosition(), this->getSize(), this->getSize(), true);
   this->bIsMoving = true;
}

void SuperShinyJumpOutofBoxShinyUnit::update(uint64 time)
{
   if(this->bUpdate == true)
   {
      this->fShininess = 0;
   }
   ShinyUnit::update();
}