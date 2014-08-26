//
//
//
//   Project : Schrödinger's cat
//   File Name : Food.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Food.h"

#define SHININESS 3

Food::Food(CIwSVec2 i2Position): ShinyUnit()
{
   IW_CALLSTACK("Food::Food");

   this->tTextureList.push_back(ImageManager::getImage("cat_food"));
   this->tTextureList.push_back(ImageManager::getImage("platform"));

   this->sSoundList.push_back(SoundManager::getSound("foodmunch1"));
   this->sSoundList.push_back(SoundManager::getSound("foodmunch1"));
   this->sSoundList.push_back(SoundManager::getSound("foodmunch2"));
   this->sSoundList.push_back(SoundManager::getSound("foodmunch2"));
   this->sSoundList.push_back(SoundManager::getSound("foodmunch3"));
   this->sSoundList.push_back(SoundManager::getSound("foodmunch3"));

   this->i2Position = i2Position;
   this->fShininess = SHININESS;
   this->sName = "food";
   this->brBoundingBox = BoundingRectangle(this->getPosition(), this->getSize(), CIwSVec2((int)(this->getSize().x * 0.7f), (int)(this->getSize().y * 0.7f)), true);
   this->csPlayWith = CatState::EATINGFOOD;
   this->bEmpty = false;

   ClassTracker::addUnit(this);
}

void Food::update(uint64 time)
{
   IW_CALLSTACK("Food::update");

   this->iTime = time;
   this->iTimePassed += time;

   if(this->bAffectUpdate == true)
   {
      if(this->iTextureIndex == 0)
         this->bEmpty = false;
      if(this->bEmpty == false)
         this->setShiny();
      this->bAffectUpdate = false;
   }
   if(this->bUpdate == true)
   {
      if(this->bEmpty == false)
      {
         this->bEmpty = true;
         this->iSoundIndex = IwRandMinMax(0, 5);			
         this->changeTexture(1);
         this->bUpdate = false;
         this->setNotShiny();

         for(int i = 0; i <(int)uAffectList.size(); ++i)
         {
            this->uAffectList[i]->bAffectUpdate = true;
         }
         for( int i = 0; i < (int)this->uAttatchedToList.size(); ++i)
         {
            int x = this->uAttatchedToList.size();
            if(dynamic_cast<Food*>(uAttatchedToList[i])->bEmpty == false)
            {
               dynamic_cast<Food*>(this->uAttatchedToList[i])->setNotShiny();
               dynamic_cast<Food*>(this->uAttatchedToList[i])->bEmpty = true;
            }
         }
      }
      ShinyUnit::update();
      this->bUpdate = false;
   }
}
