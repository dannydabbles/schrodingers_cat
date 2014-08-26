#include "Spiral.h"

Spiral::Spiral(CIwSVec2 position)
{

   IW_CALLSTACK("Spiral::Spiral");

   this->i2Position = position;

   this->f2Velocity.x = 100; //velocity;
   this->iRot = 0;
   this->mRot.SetRot(0);

   this->sName = "spiral";
   this->tTextureList.push_back(ImageManager::getImage("trippyspiral"));
   this->i2Size = CIwSVec2(268/2, 268/2);
   this->i2RegionSize = CIwSVec2(this->i2Size.x, this->i2Size.y);
   this->i2RegionOffset = CIwSVec2(0,0);

   this->f2AbsPosition = this->i2Position;
   this->i2Size = this->i2RegionSize;
   this->rotAxsis = CIwVec2(Screen::getSCREENSIZE().x/2, Screen::getSCREENSIZE().y/2);

}

void Spiral::update(uint64 time)
{

   IW_CALLSTACK("Spiral::Update");

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

void Spiral::draw()
{
   IW_CALLSTACK("Spiral::Spiral");

   Iw2DSetTransformMatrix(mRot);
   Iw2DDrawImage(this->tTextureList[0], this->i2Position);
   Iw2DSetTransformMatrix(CIwMat2D::g_Identity);
}
