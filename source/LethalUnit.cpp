#include "LethalUnit.h"

LethalUnit::LethalUnit(): Unit()
{
   IW_CALLSTACK("LethalUnit::LethalUnit");

   this->iDeathCount = 0;
   this->iCapDeathCount = 0;
   this->sSoundList.push_back(SoundManager::getSound("bloodydeath1"));
   this->sSoundList.push_back(SoundManager::getSound("bloodydeath2"));
   this->sSoundList.push_back(SoundManager::getSound("bloodydeath3"));
   this->sSoundList.push_back(SoundManager::getSound("bloodydeath4"));
   this->sSoundList.push_back(SoundManager::getSound("bloodydeath5"));
}

void LethalUnit::deathSound()
{
   IW_CALLSTACK("LethalUnit::deathSound");

   if(this->iSoundIndex >= 0)
   {
      SoundManager::playSound(this->sSoundList[this->iSoundIndex]);
   }
   SoundManager::playSound(this->sSoundList[IwRandMinMax(0, 4)]);
}

void LethalUnit::update()
{
   IW_CALLSTACK("LethalUnit::update");

   if(this->iDeathCount < this->iCapDeathCount || this->iCapDeathCount == 1000) //1000 means infinite deaths
   {
      CatState::setState(CatState::DEAD);
      this->deathSound();

      if(this->iTextureIndex < (int)this->tTextureList.size() - 1)
      {
         this->changeTexture(++this->iTextureIndex);
      }
      ++this->iDeathCount;
   }
   this->bUpdate = false;
}

int LethalUnit::getDeathCount()
{
   IW_CALLSTACK("LethalUnit::getDeathCount");

   return this->iDeathCount;
}
