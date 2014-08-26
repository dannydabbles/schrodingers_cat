//
//
//
//   Project : Schrödinger's cat
//   File Name : LitterBox.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "LitterBox.h"

LitterBox::LitterBox(CIwSVec2 i2Position): ShinyUnit()
{
   IW_CALLSTACK("LitterBox::LitterBox");

   this->bFull = true;
   this->fShininess = -1;
   this->tTextureList.push_back(ImageManager::getImage("litter_box"));
   this->tTextureList.push_back(ImageManager::getImage("litter_box_poop"));

   this->sSoundList.push_back(SoundManager::getSound("litterbox1"));
   this->sSoundList.push_back(SoundManager::getSound("litterbox1"));
   this->sSoundList.push_back(SoundManager::getSound("litterbox2"));
   this->sSoundList.push_back(SoundManager::getSound("litterbox2"));
   this->sSoundList.push_back(SoundManager::getSound("litterbox2"));

   this->i2Position = i2Position;
   this->sName = "litterbox";
   this->brBoundingBox = BoundingRectangle(this->getPosition(), this->getSize(), this->getSize(), true);
   this->csPlayWith = CatState::POOPING;

   ClassTracker::addUnit(this);
}

void LitterBox::update(uint64 time)
{
   IW_CALLSTACK("LitterBox::update");

   if (GameState::getState() != GameState::PLAY)
   {
      return;
   }
   this->iTime = time;
   this->iTimePassed += time;

   if(this->bAffectUpdate == true)
   {
      if(this->iTextureIndex == 0)
         this->bFull = false;
      if(this->bFull == false)
         this->setShiny();
      this->bAffectUpdate = false;
   }
   if(this->bUpdate == true)
   {
      if(this->bFull == false)
      {
         this->iSoundIndex = IwRandMinMax(0, 4);
         this->bFull = true;
         this->changeTexture(1);
         for( int i = 0; i <(int) this->uAffectList.size(); ++i)
         {
            this->uAffectList[i]->bAffectUpdate = true;
         }
         for(int i = 0; i <(int)this->uAttatchedToList.size(); ++i)
         {
            dynamic_cast<ShinyUnit*>( this->uAttatchedToList[i])->setNotShiny();
            dynamic_cast<LitterBox*>(this->uAttatchedToList[i])->bFull = true;
         }
      }
      ShinyUnit::update();
      this->bUpdate = false;
   }    
}
