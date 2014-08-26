/*
*  ParticleCannon.cpp
*  Kitty
*
*  Created by Sam Medalen on 4/11/11.
*  Copyright 2011 __MyCompanyName__. All rights reserved.
*
*/

#include "ParticleCannon.h"

ParticleCannon::ParticleCannon(uint64 time, int life, CIwSVec2 i2Position, bool full, particle_mode mode, double dangle)
{
	IW_CALLSTACK("ParticleCannon::ParticleCannon");

   this->tTextureList = CIwArray<CIw2DImage*>();
   this->tTextureList.push_back(ImageManager::getImage("particle"));
   this->iCLife = 30;
   this->iCTime = 0;
   this->iMinLife = 0;
   this->iMaxLife = 20;
   this->iLife = life;
   this->iTime = time;
   this->uLife = life;
   this->dProductionRate = 0;
   this->iProductionCap = 3000;
   this->iTotalCap = (IwRandMinMax(iProductionCap, iProductionCap + iProductionCap / 2));
   this->iTotal = 0;
   this->i2Position = i2Position;
   this->dMinVelocity = 1;
   this->dMaxVelocity = 2;
   //this->dMinLife = 0;
   //this->dMaxLife = 1;
   this->dAngle = dangle;
   this->move = 0;
   this->moveRate = 1;
   this->bDone = false;
   this->mode = mode;
//   IwMemBucketPush(GRID);
   while((int)apCannon.size() < this->iProductionCap)
   {
      apCannon.push_back(makeParti());
      iTotal += 1;
   }
  // IwMemBucketPop();
}

ParticleCannon::ParticleCannon(uint64 time, int life, CIwSVec2 i2Position, bool full, particle_mode mode, CIwSVec2 goal)
{
	IW_CALLSTACK("ParticleCannon::ParticleCannon");

   this->iGoal = goal;
   int x = i2Position.x - this->iGoal.x;
   int y = i2Position.y - this->iGoal.y;
   double angle = asin((double)x/y);
   if(y < 0)
      angle = 90;
   else
      angle = 270;
   ParticleCannon(time, life, i2Position, full, mode, angle);
}

void ParticleCannon::reset(CIwSVec2 newPos)
{
   this->i2Position = newPos;
   this->bDone = false;
   this->iCTime = 0;
   this->iTimePassed = 0;
   this->apCannon.clear_optimised();
   for(int i = 0; i < this->iProductionCap; ++i)
   {
      apCannon.push_back(makeParti());
   }
}

Particle* ParticleCannon::makeParti()
{
	IW_CALLSTACK("ParticleCannon::makeParti");

   CIwSVec2 Direction = CIwSVec2(0, 0);
   float vx,vy;
   float fVelocity = (float)IwRandMinMax(1, 5);
   //double iVelocity = dMinVelocity + (IwRandMinMax(0, 100) /((dMaxVelocity - dMinVelocity) * 100));
   if(mode == PARTICLE_BASIC)
   {
      dAngle = IwRandMinMax(0, 359);

      while(dAngle < 90 || dAngle > 270)
      {
         int temp = IwRandMinMax(0, 5);

         if(temp > 0)
         {
            dAngle = IwRandMinMax(0, 359);
         }
         else
         {
            break;
         }
      }
      dAngle *= 3.14159265f * 0.0055f; // 1 / 180
      vx = (float)sin(dAngle) * fVelocity;
      vy = (float)cos(dAngle) * fVelocity;
      Direction = CIwSVec2((int)sin(dAngle), (int)cos(dAngle));
   }
   if(mode ==PARTICLE_DIRECTIONAL || mode == PARTICLE_DIRECTIONAL_GRAVITY)
   {
      dAngle += (IwRandMinMax(-50, 50) / 100);
      vx = (float)sin(dAngle) * fVelocity;
      vy = (float)cos(dAngle) * fVelocity;
      Direction = CIwSVec2((int)sin(dAngle), (int)cos(dAngle));
   }
   int life = (int)dMinLife + IwRandMinMax(0, (int)this->dMaxLife);
   int iLife = IwRandMinMax(iMinLife,iMaxLife);
   return new Particle(this->i2Position, Direction, vx, vy, this->iTimePassed, this->iTimePassed + life, iLife);
}

void ParticleCannon::update(uint64 time)
{
	IW_CALLSTACK("ParticleCannon::update");

   if (GameState::getState() != GameState::PLAY)
   {
      return;
   }
   this->iTime = time;
   this->iTimePassed += time;
   this->iCTime++;
   move++;
   if(/*this->uTime >= uLife ||*/ this->iCTime > this->iCLife && this->iCLife != 0)
   {
      this->bDone = true;
      return;
   }
   if(move >= moveRate)
   {
      move = 0;
      for(int i = 0; i < (int)apCannon.size(); ++i)
      {
         if(PARTICLE_GRAVITY || PARTICLE_DIRECTIONAL_GRAVITY)
         {
            if(!apCannon[i]->moveParticle(iTimePassed, true))
            {
               apCannon[i]->kill();
               deadParticles.push_back(apCannon[i]);
               apCannon.find_and_remove(apCannon[i]);
            }
         }
         else if(PARTICLE_BASIC)
         {
            if(!apCannon[i]->moveParticle(iTimePassed, false))
            {
               apCannon[i]->kill();
               deadParticles.push_back(apCannon[i]);
               apCannon.find_and_remove(apCannon[i]);
            }
         }
      }
      if((int)this->apCannon.size() < this->iProductionCap && this->iTotal <= this->iTotalCap)
      {
         apCannon.push_back(makeParti());
         ++this->iTotal;
      }
   }
   for(int i = 0; i < (int)this->deadParticles.size(); ++i)
   {
      deadParticles[i]->moveDeadParticle(time);
   }
}

void ParticleCannon::draw()
{
	IW_CALLSTACK("ParticleCannon::draw");

   for(int i = (int)apCannon.size()-1; i >= 0; --i)
   {
      apCannon[i]->draw(this->tTextureList[0]);
   }
   for(int i = 0; i < (int)deadParticles.size(); ++i)
   {
      //deadParticles[i]->draw(this->tTextureList[0]);
   }
}