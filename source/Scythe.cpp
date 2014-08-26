//
//
//
//   Project : Schrödinger's cat
//   File Name : Scythe.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//
#include "Scythe.h"

#define GRAVC 10.8f // Higher values make the scythe move faster
#define ROPETHICKNESS 6

Scythe::Scythe(CIwSVec2 i2Position): LethalUnit()
{
   IW_CALLSTACK("Scythe::Scythe");

   this->tTextureList.push_back(ImageManager::getImage("scythe"));
   this->tTextureList.push_back(ImageManager::getImage("bloodyscythe"));

   this->sSoundList.push_back(SoundManager::getSound("scythe_kill"));
   this->sSoundList.push_back(SoundManager::getSound("swoosh3"));

   this->iSoundIndex = 5;

   this->i2Position = i2Position;
   this->sName="scythe";
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size, CIwSVec2((int)(this->i2Size.x * 0.7f), (int)(this->i2Size.y * 0.7f)));
   this->bUpdate = false;
   this->bIsMoving = true;
   this->bDrawn = false;
   this->mRot = CIwMat2D();
   this->iLength = 0;
   this->fAngularAcceleration = 0;
   this->fAngularVel = 0;
   this->fAngle = 0;
   this->iCapDeathCount = 1000;

   this->DarkGreen.Set(46, 139, 87, 255);
   this->LightGreen.Set(0, 255, 127, 255);
   this->green = IwRandMinMax(0 , 255);
   this->up = true;

   ClassTracker::addUnit(this);
}

void Scythe::update(uint64 time)
{
   IW_CALLSTACK("Scythe::update");

   if (GameState::getState() != GameState::PLAY)
   {
      return;
   }
   this->iTime = time;
   this->iTimePassed += time;

   // time from milliseconds to seconds 
   double t = (double)this->iTime * 0.001; 

   if ( t > 1 ) // to avoid lag spikes
   {
      t = 0;
   }

   // calulate the change in angle 
   this->fAngularAcceleration = -this->fGDividedByLength * sin(this->fAngle);
   this->fAngularVel += this->fAngularAcceleration * t;
   this->fAngle += this->fAngularVel * t;

   // in case of emergency reset the scythe
   if ( this->fAngularAcceleration > 10 || this->fAngularVel > 10|| this->fAngle > 10)
   {
	   this->fAngle =  this->fMaxLeft;
	   this->fAngularAcceleration = 0;
	   this->fAngularVel;
   }

   //update rotation matrix and boundingbox
   this->mRot.SetRot(IW_ANGLE_FROM_RADIANS(this->fAngle), this->rotAxis);
   this->brBoundingBox.setPosition(getRotatedCoords(CIwSVec2(this->i2Position.x + (int)(this->i2Size.x * 0.5f), this->i2Position.y + (int)(this->i2Size.y * 0.75f))));

   if (this->bUpdate == true)
      LethalUnit::update();
}

void Scythe::draw()
{
   IW_CALLSTACK("Scythe::draw");

   if(this->bDrawn) return;

   // TODO: Add some colors to ropes, if we want to keep the ropes like this at all
   this->DarkGreen.Set(0 , this->green, 127, 255 );
   this->LightGreen.Set( 0, 255 - this->green, 127, 255);
   for(int i = -ROPETHICKNESS; i < ROPETHICKNESS; ++i)
   {
      if(i == -ROPETHICKNESS || i == ROPETHICKNESS || i == ROPETHICKNESS / 2)
      {
         Iw2DSetColour(this->LightGreen);
      }
      else Iw2DSetColour(this->DarkGreen);

      Iw2DDrawLine(this->getRotatedCoords(CIwSVec2(this->i2Position.x + this->i2Size.x/2, this->i2Position.y - i)), CIwSVec2(this->rotAxis.x, this->rotAxis.y - i/2));
   }
   Iw2DSetColour(0xFFFFFFFF);


   if ( this->iTimePassed > 32)
   {
      if ( this->up )
      {
         ++this->green;
      }
      else
      {
         --this->green;

      }

      if ( this->green >= 255 || this->green <= 0)
      {
         this->up = !this->up;
      }

      this->iTimePassed = 0;
   }

   Iw2DSetTransformMatrix(mRot); //pushmatrix
   Unit::draw();
   Iw2DSetTransformMatrix(CIwMat2D::g_Identity); //popmatrix
}

void Scythe::calculateMaxRotation()
{
   IW_CALLSTACK("Scythe::calculateMaxRotation");

   // calculate max rotation to the left
   float deltaY =  this->i2Position.y;  //this->uAttatchedToList[0]->i2Position.y - this->i2Position.y;
   float deltaX =  (float)abs(this->uAttatchedToList[0]->i2Position.x - this->i2Position.x);
   float rads = atan(deltaX/deltaY);
   this->fMaxLeft = rads;

   // caculate max rotation to the right
   /*deltaY =  this->i2Position.y;  //abs(this->uAttatchedToList[1]->i2Position.y - this->i2Position.y);
   deltaX =  (float)abs(this->uAttatchedToList[1]->i2Position.x - this->i2Position.x);
   rads = atan(deltaX/deltaY);
   this->fMaxRight = rads;*/



   // swinging scythe
   this->rotAxis.x = this->i2RegionSize.x/2 + this->i2Position.x; //(this->uAttatchedToList[0]->i2Position.x + this->uAttatchedToList[1]->i2Position.x)/2;
   this->rotAxis.y = this->uAttatchedToList[0]->i2Position.y /*+ this->uAttatchedToList[1]->i2Position.y)/2*/ + Screen::getBOXSIZE().y;

   this->fAngle =  this->fMaxLeft; //(this->fMaxLeft + this->fMaxRight)* 0.5f;
   this->iLength = (int)((this->i2Position.y - this->rotAxis.y) * 0.5f); // plus 2 to avoid divide by zero.

   if ( this->iLength == 0)
   {
      IwAssertMsg(MYAPP, false, ("scythe With length of zero, move more than one box lower than rotation point"));
   }

   this->fGDividedByLength = GRAVC/(float)this->iLength;
   //this->fperoid = 6.28 * sqrt((float)this->iLength/GRAV);
   this->mRot.SetRot(IW_ANGLE_FROM_RADIANS(this->fAngle), this->rotAxis);
}

CIwSVec2 Scythe::getPosition()
{
   IW_CALLSTACK("Scythe::getPosition");

   return getRotatedCoords(this->i2Position);
}

CIwSVec2 Scythe::getRotatedCoords(CIwSVec2 pos)
{
   IW_CALLSTACK("Scythe::getRotatedCoords");

   // Transform matrix by rotation matrix and find what the suppplied position would 
   // be in new post rotation coordinate system
   Iw2DSetTransformMatrix(mRot); 
   CIwMat2D transformationMatrix = Iw2DGetTransformMatrix();
   CIwVec2 transformedPosition = transformationMatrix.TransformVec(pos); 
   Iw2DSetTransformMatrix(CIwMat2D::g_Identity); 

   return CIwSVec2(transformedPosition);
}
