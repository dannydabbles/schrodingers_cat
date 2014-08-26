//
//
//
//   Project : Schrödinger's cat
//   File Name : EndBox.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "EndBox.h"

EndBox::EndBox(CIwSVec2 i2Position): Platform(i2Position)
{
   IW_CALLSTACK("EndBox::EndBox");

   this->tTextureList.clear_optimised();
   this->tTextureList.push_back(ImageManager::getImage("finish"));
   this->i2Position = i2Position;
   this->i2Position.y -= Screen::getBOXSIZE().y;
   this->sName = "endbox";
   this->brBoundingBox = BoundingRectangle(this->i2Position + CIwSVec2(0, (int)(Screen::getBOXSIZE().y * 0.5f)), this->i2Size, CIwSVec2((int)(this->i2Size.x * 0.5f), (int)(this->i2Size.y * 0.5f)), true);
   this->i2Position.y += Screen::getBOXSIZE().y;

   ClassTracker::addUnit(this);
}
void EndBox::update(uint64 time)
{
   IW_CALLSTACK("EndBox::update");

   this->iTime = time;
   this->iTimePassed += time;

   if(this->bUpdate == true)
   {
      //IwAssertMsg(MYAPP, false, ("you win!!"));
      GameState::setState(GameState::LEVELBEATEN);
   }
}
