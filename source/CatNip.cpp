//
//
//
//   Project : Schrödinger's cat
//   File Name : CatNip.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "CatNip.h"

CatNip::CatNip(CIwSVec2 i2Position): ShinyUnit() 
{
   IW_CALLSTACK("CatNip::CatNip");

   tTextureList.push_back(Iw2DCreateImageResource("cat_nip"));
   tTextureList.push_back(Iw2DCreateImageResource("platform"));
   this->i2Position = i2Position;
   this->sName="catnip";
   
}

void CatNip::update(uint64 time)
{
   IW_CALLSTACK("CatNip::update");

   if(bUpdate == true)
   {
      if(bEmpty == false)
      {
         bEmpty = true;
         this->changeTexture(1);
      }
      bUpdate = false;
   }
}