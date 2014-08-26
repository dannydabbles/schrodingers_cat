#include "Gear.h"



Gear::Gear(int type)
{

   IW_CALLSTACK("Gear::Gear");

   //this->i2Position = position;

   this->f2Velocity.x = 10; //velocity;
   this->iRot = 0;
   this->mRot.SetRot(0);

   this->sName = "gear";

   if ( type == 0 )
   {
      this->tTextureList.push_back(ImageManager::getImage("gear_lg"));
      this->i2RegionSize = CIwSVec2(203, 203);
      this->i2Position = CIwSVec2(Screen::getSCREENSIZE().x * 0.077f, Screen::getSCREENSIZE().y * 0.02f);
   }
   else if ( type == 1)
   {
      this->tTextureList.push_back(ImageManager::getImage("gear_med"));
      this->i2RegionSize = CIwSVec2(172, 172);
      this->i2Position = CIwSVec2(Screen::getSCREENSIZE().x * 0.40f, Screen::getSCREENSIZE().y * 0.4f);
      this->f2Velocity.x = -10;
   }
   else
   {
      this->tTextureList.push_back(ImageManager::getImage("gear_sm"));
      this->i2RegionSize = CIwSVec2(138, 138);
      this->i2Position = CIwSVec2(Screen::getSCREENSIZE().x * 0.62f, Screen::getSCREENSIZE().y * 0.08f);
   }

   this->f2AbsPosition = this->i2Position;
   this->i2Size = this->i2RegionSize;
   this->rotAxsis = CIwVec2(this->i2Position.x + this->i2Size.x/2, this->i2Position.y + this->i2Size.y/2);

}

void Gear::update(uint64 time)
{

   IW_CALLSTACK("Gear::Update");

   this->iTime = time;
   this->iTimePassed += this->iTime;

   this->f2AbsPosition.x += (this->f2Velocity.x * time * 0.001f);
   this->iRot = (int)this->f2AbsPosition.x;

   while( this->iRot >= 360 )
   {
      this->iRot -= 360;
   }

   this->mRot.SetRot(IW_ANGLE_FROM_DEGREES(this->iRot), this->rotAxsis);
}

void Gear::draw()
{
   IW_CALLSTACK("Gear::Draw");

   Iw2DSetTransformMatrix(mRot);
   Iw2DDrawImage(this->tTextureList[0], this->i2Position);
   Iw2DSetTransformMatrix(CIwMat2D::g_Identity);
}
