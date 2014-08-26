#include "Cloud.h"

Cloud::Cloud(CIwSVec2 position, float velocity, int type) : BackgroundUnit()
{
   IW_CALLSTACK("Cloud::Cloud");

   this->i2Position = position;
   this->f2AbsPosition = this->i2Position;

   this->f2Velocity.x = velocity;

   this->sName = "cloud";

   string str;
   stringstream s;
   s << type;
   str = s.str();
   this->tTextureList.push_back( ImageManager::getImage( ("cloud"+str).c_str() ) );

   this->i2RegionSize = CIwSVec2( this->tTextureList[0]->GetWidth(), this->tTextureList[0]->GetHeight() );
   this->i2Size = CIwSVec2( this->i2RegionSize.x , this->i2RegionSize.y );
   this->i2RegionOffset = CIwSVec2(this->i2RegionSize.x, 0);

}

void Cloud::draw()
{
   IW_CALLSTACK("Cloud::Draw");

   if ( this->updatedOnce == true)
   {
    Iw2DDrawImage(this->tTextureList[0], this->i2Position);
   }
}
