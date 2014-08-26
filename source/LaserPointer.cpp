//
//
//
//   Project : Schrödinger's cat
//   File Name : LaserPointer.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "LaserPointer.h"
//#include "Iw2D.h"
//#include "IwGx.h" 

#define PERIOD_LENGTH 100  // Decay rate of laser, bigger values means slow decay
#define MOVEMENT_SCALE 30 // used to scale to velocity 
#define MAXLIFE 500     // determines to length that the trail gets
#define SIZE 10          // default size of laser point
#define MINMOVECALCTIME 32

LaserPointer::LaserPointer(): ShinyUnit()
{
   IW_CALLSTACK("LaserPointer::LaserPointer");

   this->iTextureIndex = 0;
   this->sName = "laser";
   this->i2Size = CIwSVec2(SIZE, SIZE);
   this->i2Position = CIwSVec2(0,0);
   this->fShininess = 1;
   this->i2PositionList = CIwArray<CIwSVec2>();
   this->positionList = CIwArray<CIwSVec2>();
   this->lifeTimeList = CIwArray<int64>();
   this->i2PositionList.resize(2);
   this->i2PositionList[0] = this->i2PositionList[1] = this->i2Position;
   this->bIsShiny = true;
   //this->bUpdate = false;
   this->timer = 0; 
   this->alpha = 0xFF;
   this->color.Set(0xFF, 0, 0, this->alpha);
   this->trailThickness = 5;
   this->iStillTime = 0;
   this->iMoveCalcTimePassed;
   this->bIsMoving = true;
   this->bOn = true;
   this->fDistanceList = CIwArray<float>();

   for(int i = 0; i < PERIOD_LENGTH; ++i)
   {
      fDistanceList.push_back(0.0f);
   }
   this->brBoundingBox = BoundingRectangle(this->getPosition(), this->i2Size, this->i2Size, true);
   this->csPlayWith = CatState::BATTING;

   ClassTracker::addUnit(this);
}

void LaserPointer::update(uint64 time)
{
   IW_CALLSTACK("LaserPointer::update");


   this->iTime = time;
   this->iTimePassed += time;
   this->iMoveCalcTimePassed += time;
   ShinyUnit::update();
   this->bUpdate = false;

   if(s3ePointerGetX() < Screen::getSCREENSIZE().x &&
      s3ePointerGetX() > 0 &&
      s3ePointerGetY() < Screen::getSCREENSIZE().y &&
      s3ePointerGetY() > 0 &&
      s3ePointerGetTouchState(0) &&
      S3E_POINTER_TOUCH_EVENT)
   {
      this->i2Position.x = s3ePointerGetX();
      this->i2Position.y = s3ePointerGetY() - Screen::getBOXSIZE().y;
      this->bOn = true;

   }
   else
   {
      this->bOn = false;
      this->i2Position = CIwSVec2(0, -2 * Screen::getBOXSIZE().y);
      this->brBoundingBox.setPosition(this->i2Position);
      this->positionList.clear();
      this->lifeTimeList.clear();

      for(int i = 0; i < (int)this->fDistanceList.size(); ++i)
      {
         this->fDistanceList[i] = 0;
      }
      return;
   }
   //this->i2Position.x = IwRand() % Screen::getSCREENSIZE().x;
   //this->i2Position.y = IwRand() % Screen::getSCREENSIZE().y;

   this->brBoundingBox.setPosition(this->getPosition());

   if ( this->bOn == true)
   {
	   this->positionList.push_back(this->i2Position);
	   this->lifeTimeList.push_back(MAXLIFE);
   }

   for(int i = 0; i < (int)positionList.size(); ++i)
   {
      this->lifeTimeList[i] -= time;

      if(this->lifeTimeList[i] <= 0)
      {
         // there may be problems if the same position at different times is inside twice...
         this->lifeTimeList.find_and_remove(this->lifeTimeList[i]);
         this->positionList.find_and_remove(this->positionList[i]);
      }
   }

   // update laser pointer variables
   if(++this->timer >= PERIOD_LENGTH)
   {
      this->timer = 0;
   }
   if ( this->bOn == true)
   {
	   updatePositionList();
	   calculateMovement();
   }
}

// draw each alive particle
void LaserPointer::draw()
{
   IW_CALLSTACK("LaserPointer::draw");

   if(bOn == false)
   {
      return;
   }
   //Iw2DSetAlphaMode	(IW_2D_ALPHA_ADD); 
   Iw2DSetAlphaMode(IW_2D_ALPHA_HALF);
   Iw2DSetColour(this->color);
   //Iw2DSetAlphaMode(IW_2D_ALPHA_SUB); 
   //Iw2DDrawImage(this->tTextureList[this->iTextureIndex], this->i2Position);

   Iw2DFillArc(CIwSVec2(this->i2Position.x, this->i2Position.y), this->i2Size, IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);
   Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
   Iw2DFillArc(CIwSVec2(this->i2Position.x, this->i2Position.y), CIwSVec2(this->i2Size.x - 4, this->i2Size.y - 4), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);

   CIwSVec2 pos;
   CIwSVec2 pos2;

   for(int i = 0; i < (int)this->positionList.size(); ++i)
   {
      if(i < (int)this->positionList.size() - 1)
      {	
         Iw2DSetColour(this->color);

         pos.x = this->positionList[i].x; 
         pos.y = this->positionList[i].y; 
         pos2.x = this->positionList[i + 1].x; 
         pos2.y = this->positionList[i + 1].y; 

         for(int i = 0; i < this->trailThickness; ++i)
         {
            if(i == this->trailThickness / 2)
            {
               Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
            }
            else
            {
               Iw2DSetAlphaMode (IW_2D_ALPHA_HALF);
            }
            Iw2DDrawLine(CIwSVec2(pos.x, pos.y - i), CIwSVec2(pos2.x, pos2.y - i));
         }
      }
   }
   Iw2DSetColour(0xffffffff);
   Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);

   //CIwColour defaultColor;
   //defaultColor.Set(0,255,255,255);
   //Iw2DSetColour(defaultColor);
}


void LaserPointer::updatePositionList()
{
   IW_CALLSTACK("LaserPointer::updatePositionList");

   this->i2PositionList[1].x = this->i2PositionList[0].x;
   this->i2PositionList[1].y = this->i2PositionList[0].y;

   this->i2PositionList[0].x = this->i2Position.x;
   this->i2PositionList[0].y = this->i2Position.y;
}

// takes into consideration how fast the laser is moving in term of change in position
// has well has how quickly the user taps their fingers.
void LaserPointer::calculateMovement()
{
   IW_CALLSTACK("LaserPointer::calculateMovement");

   if(this->iMoveCalcTimePassed >= MINMOVECALCTIME)
   {
      float distance;

      if (this->i2PositionList[1] == CIwSVec2(0, -2 * Screen::getBOXSIZE().y) )
      {
         distance = 0;
      }
      else
      {
		  int dX = this->i2PositionList[1].x - this->i2PositionList[0].x;
		  int dY = this->i2PositionList[1].y - this->i2PositionList[0].y;

		  distance = sqrt ((double)(dX * dX + dY * dY));
      }

      /*if(bOn == false && distance != 0)
      {
      bOn = true;
      }*/
      // Detet if the laser point in being unmoved for a while
      if(bOn && distance  < 3)
      {
         this->iStillTime += this->iTime;
      }
      else
      {
         this->iStillTime = 0;
      }

      fDistanceList[this->timer] = distance * ((float)this->iMoveCalcTimePassed/(float)MINMOVECALCTIME);
      float sum = 0;

      for (int i = 0; i < PERIOD_LENGTH; ++i)
      {
         sum += fDistanceList[i];
      }
      this->velocity = sum / (float)PERIOD_LENGTH;
      this->iMoveCalcTimePassed = 0;

      //cout << "timer " << timer << "velocity " << velocity << endl;
   }
}
// returns the velocity times a scaling factor to make the velocity
// into the correct scale needed for shininess
float LaserPointer::getMovement()
{
   IW_CALLSTACK("LaserPointer::getMovement");

   return this->velocity * MOVEMENT_SCALE;
}

float LaserPointer::getShininess()
{
   IW_CALLSTACK("LaserPointer::getShininess");

   if(bOn == true)
   {
      //cout << "MOVEMENT OF LASER: " << this->getMovement()   << endl;
      return  this->fShininess * (this->getMovement() + 1);
   }
   else
   {
      return -1;
   }
}	

void LaserPointer::reset()
{
   IW_CALLSTACK("LaserPointer::reset");

   this->bOn = false;
}
