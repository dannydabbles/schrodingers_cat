#include "BackgroundUnit.h"


void BackgroundUnit::update(uint64 time)
{
   IW_CALLSTACK("BackgroundUnit::Update");

   this->updatedOnce = true;

   this->iTime = time;
   this->iTimePassed += this->iTime;


   this->f2AbsPosition.x += (this->f2Velocity.x * this->iTime * 0.001f);
   this->i2Position.x = (int)this->f2AbsPosition.x;

   if ( this->i2Position.x > Screen::getSCREENSIZE().x + Screen::getSCREENSIZE().x * 0.3f)
   {
      this->i2Position.x = -this->tTextureList[0]->GetWidth();
      this->i2Position.y = IwRandMinMax(0, (int)(Screen::getSCREENSIZE().y * 0.33f));
      this->f2AbsPosition = this->i2Position;
   }

}

void BackgroundUnit::draw()
{
   IW_CALLSTACK("BackgroundUnit::Draw");

   Unit::draw();
}
