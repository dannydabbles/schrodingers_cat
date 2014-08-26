//
//
//
//   Project : Schrödinger's cat
//   File Name : ScytheRight.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "ScytheRight.h"

ScytheRight::ScytheRight(CIwSVec2 i2Position): Unit()
{
   IW_CALLSTACK("ScytheRight::ScytheRight");

   this->i2Position = i2Position;
   this->sName="scytheright";

   ClassTracker::addUnit(this);
}

void ScytheRight::update(uint64 time)
{
   IW_CALLSTACK("ScytheRight::update");
}

void ScytheRight::draw()
{
   IW_CALLSTACK("ScytheRight::update");
}
