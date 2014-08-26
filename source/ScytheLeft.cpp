//
//
//
//   Project : Schrödinger's cat
//   File Name : ScytheLeft.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "ScytheLeft.h"

ScytheLeft::ScytheLeft(CIwSVec2 i2Position): Unit()
{
   IW_CALLSTACK("ScytheLeft::ScytheLeft");


   this->i2Position = i2Position;
   this->sName="scytheleft";

   ClassTracker::addUnit(this);

}

void ScytheLeft::update(uint64 time)
{
   //nothing !
}

void ScytheLeft::draw()
{
   //nothing !
}
