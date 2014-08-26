//
//
//
//   Project : Schrödinger's cat
//   File Name : Blood.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Blood.h"

Blood::Blood(): Unit()
{
   IW_CALLSTACK("Blood::Blood");

   this->tTextureList.push_back(ImageManager::getImage("BloodSpriteSheet1"));
   this->tTextureList.push_back(ImageManager::getImage("BloodSpriteSheet2"));
   this->tTextureList.push_back(ImageManager::getImage("BloodSpriteSheet3"));
   this->tTextureList.push_back(ImageManager::getImage("BloodSpriteSheet4"));
   this->tTextureList.push_back(ImageManager::getImage("BloodSpriteSheet5"));
   Particle::tTexture = ImageManager::getImage("particle");
   this->i2Position = CIwSVec2(0, 0);
   this->sName = "blood";
   this->i2Size = CIwSVec2(Screen::getBOXSIZE().x * 8, Screen::getBOXSIZE().y * 8);
   this->i2RegionSize = CIwSVec2(256, 256);
   this->i2RegionOffset = this->i2RegionSize;
   this->iTextureCount = (int)this->tTextureList.size();
   this->iAnimateTime = 128;
   this->iParticleCount = 4000;
   this->pBloodList = CIwArray<Particle*>();
   

   for(int i = 0; i < iParticleCount; ++i)
   {
      this->pBloodList.push_back(new Particle());
   }

   ClassTracker::addUnit(this);
}

Blood::~Blood()
{

   IW_CALLSTACK("Blood::~Blood");

   for ( int i = 0; i < (int)pBloodList.size(); ++i)
   {
      Particle * p = this->pBloodList[i];
      delete p;
   }

   this->pBloodList.clear_optimised();
}

void Blood::update(uint64 time)
{
   IW_CALLSTACK("Blood::update");

   if(this->bUpdate == true)
   {
      this->iTime = time;
      this->iTimePassed += time;

      for(int i = 0; i < (int)this->pBloodList.size(); ++i)
      {
         this->pBloodList[i]->update(time);
      }
   }
}

void Blood::setPosition(CIwSVec2 i2Position)
{
   IW_CALLSTACK("Blood::setPosition");

   this->i2Position = i2Position + CIwSVec2((int)(Screen::getBOXSIZE().x * 0.5f), (int)(Screen::getBOXSIZE().y * 0.5f)) - CIwSVec2((int)(i2Size.x * 0.5f), (int)(i2Size.y * 0.5f));

   for(int i = 0; i < (int)this->pBloodList.size(); ++i)
   {
      this->pBloodList[i]->setPosition(i2Position + CIwSVec2((int)(Screen::getBOXSIZE().x * 0.3f), (int)(Screen::getBOXSIZE().y * 0.5f)));
   }
}

void Blood::draw()
{
   IW_CALLSTACK("Blood::draw");

   if(this->bUpdate == true)
   {
	  
      if(this->i2RegionOffset.x >= this->tTextureList[iTextureIndex]->GetWidth())
      {
         this->i2RegionOffset.x = this->i2RegionSize.x;
         ++iTextureIndex;
      }

      if(iTextureIndex >= this->iTextureCount)
      {
         this->bUpdate = false;
         this->iTextureIndex = 0;
         this->iTimePassed = 0;
         return;
      }
      Iw2DDrawImageRegion(this->tTextureList[this->iTextureIndex], this->i2Position, this->i2Size, this->i2RegionOffset, this->i2RegionSize);

	  // randomly rotate another sprite behind sprite to give a more epic blood splatter
	  // random rotation from 0 to 2pi , about its center
      int numberofBloodshit = IwRandMinMax(1, 5);

      for ( int i = 0; i < numberofBloodshit; ++i)
      {
	     mRot.SetRot(IW_ANGLE_FROM_RADIANS((int)( IwRandMinMax(0, 6280) / 1000.f) ), CIwVec2(this->i2Position.x + this->getSize().x/2,this->i2Position.y + this->getSize().y/2 ) );
	     Iw2DSetTransformMatrix(mRot); 
	     Iw2DDrawImageRegion(this->tTextureList[this->iTextureIndex], this->i2Position, this->i2Size, this->i2RegionOffset, this->i2RegionSize);
	     Iw2DSetTransformMatrix(CIwMat2D::g_Identity); 
      }

   
      if(this->iTimePassed >= this->iAnimateTime)
      {
         this->i2RegionOffset.x += this->i2RegionSize.x;
         this->iTimePassed = 0;
      }

      for(int i = 0; i < (int)this->pBloodList.size(); ++i)
      {
         this->pBloodList[i]->draw();
      }
   }
}
