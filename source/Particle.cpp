/*
*  Particle.cpp
*  Kitty
*
*  Created by Sam Medalen on 4/11/11.
*  Copyright 2011 __MyCompanyName__. All rights reserved.
*
*/

#include "Particle.h"

CIw2DImage* Particle::tTexture = NULL;

Particle::Particle() : Unit()
{
   IW_CALLSTACK("Particle::Particle");

   this->iLife = IwRandMinMax(1000, 4000);
   this->i2Size = CIwSVec2(1, 1);
   this->i2RegionOffset = CIwSVec2(0, 0);
   this->i2RegionSize = CIwSVec2(1, 1);
   this->i2Position = CIwSVec2(0, 0);
   this->f2AbsPosition = CIwFVec2(0.0f, 0.0f);
   this->f2Velocity = CIwFVec2(0.0f, 0.0f);
   this->iTime = 0;
   this->iTimePassed = 0;
   this->bDead = false;
   this->sName = "bloodparticle";

   ClassTracker::addUnit(this);
}

void Particle::update(uint64 time)
{
   IW_CALLSTACK("Particle::moveParticle");

   if(this->iTimePassed > this->iLife)
   {
      this->bDead = true;
      return;
   }
   this->iTime = time;
   this->iTimePassed += time;

   this->f2Velocity.x = (float)IwRandMinMax(-500, 501) / 1000.0f;
   this->f2Velocity.y = (float)IwRandMinMax(-500, 501) / 1000.0f;

   this->f2AbsPosition.x += this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
   this->i2Position.x = (int)this->f2AbsPosition.x;
   this->f2AbsPosition.y += this->f2Velocity.y * this->iTime * Screen::getMOVEMULTIPLIER().y;
   this->i2Position.y = (int)this->f2AbsPosition.y;

   // if particle is off screen, kill it 
   // to prevent possible vector overflows and so they dont get drawn
   if ( this->i2Position.x < 0 || this->i2Position.y < 0 || this->i2Position.y > Screen::getSCREENSIZE().x || this->i2Position.y > Screen::getSCREENSIZE().y)
   {
	   this->bDead = true;
   }
}

void Particle::setPosition(CIwSVec2 i2Position)
{
   IW_CALLSTACK("Particle::setPosition");

   this->i2Position = i2Position;
   this->f2AbsPosition = CIwFVec2((float)this->i2Position.x, (float)this->i2Position.y);
   this->bDead = false;
   this->iTimePassed = 0;
}

void Particle::draw()
{
   IW_CALLSTACK("Particle::draw");

   if(this->bDead == false)
   {
      Iw2DSetAlphaMode(IW_2D_ALPHA_HALF);
      Iw2DDrawImageRegion(tTexture, this->i2Position, this->i2Size, this->i2RegionOffset, this->i2RegionSize);
      Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
   }
}
