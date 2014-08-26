//
//
//
//   Project : Schrödinger's cat
//   File Name : MouseHole.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "MouseHole.h"

MouseHole::MouseHole(CIwSVec2 i2Position): Unit()
{
   IW_CALLSTACK("MouseHole::MouseHole");

   tTextureList.push_back(ImageManager::getImage("mouse_hole"));
   this->i2Position = i2Position;
   sName = "mousehole";

   ClassTracker::addUnit(this);
}

void MouseHole::update(uint64 time)
{
   IW_CALLSTACK("MouseHole::update");
}
