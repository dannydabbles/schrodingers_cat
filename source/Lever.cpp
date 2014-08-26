//
//
//
//   Project : Schrödinger's cat
//   File Name : Lever.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Lever.h"

Lever::Lever(CIwSVec2 i2Position): Unit()
{
   IW_CALLSTACK("Lever::Lever");

   this->bOn = false;
   this->bCooldown = false;
   this->tTextureList.push_back(ImageManager::getImage("lever"));
   this->tTextureList.push_back(ImageManager::getImage("lever2"));
   this->sSoundList.push_back(SoundManager::getSound("lever"));

   this->i2Position = i2Position;
   this->iTextureIndex = 0;
   this->sName = "lever";
   this->cColor.Set(0, 0, 0, 0);
   //this->brBoundingBox = BoundingRectangle(this->getPosition(), this->getSize(),this->getSize() / 2, true);
   this->brBoundingBox =BoundingRectangle(CIwSVec2(this->i2Position.x + this->i2Size.x / 2, this->i2Position.y + (int)(this->i2Size.y * 0.66f)), this->i2Size, CIwSVec2(1, 1));

   ClassTracker::addUnit(this);

}

CIwColour Lever::getColor()
{
   return this->cColor;
}

void Lever::setColor(int cColor)
{
   switch(cColor)
   {
   case 0:  //lello
      this->cColor.Set(255, 255, 0, 255);
      break;  
   case 1: //blark
      this->cColor.Set(0, 0, 225, 255);
      break;
   case 2:  //grum
      this->cColor.Set(0, 255, 0, 255);
      break;
   case 3:  //urple
      this->cColor.Set(200, 10, 255, 255);
      break;
   case 4:  //weight
      this->cColor.Set(255, 255, 255, 255);
      break;
   case 5:  //Cyan
      this->cColor.Set(0, 255, 255, 255);
      break;
   case 6:  //broange
      this->cColor.Set(255, 128, 0, 255);
      break;
	case 7:  //hot pink is sexies
		   this->cColor.Set(255,105,180,255);
	  break;
	case 8: //red
		   this->cColor.Set(266, 0, 0, 255);
	  break;
   }
}

void Lever::update(uint64 time)
{
   IW_CALLSTACK("Lever::update");

   this->iTime = time;
   this->iTimePassed += time;

   this->lightCalulation(time);

   if(this->bUpdate == true)
   {
      if(bCooldown == true) 
      {
         bUpdate = false;
         return;
      }
      bCooldown = true;

      if(bOn == false) 
      {
         bOn = true;
         this->iTextureIndex = 1;
      }
      else
      {
         bOn = false;
         this->iTextureIndex = 0;
      }
      SoundManager::playSound(this->sSoundList[0]);

      for(int i = 0; i < (int)uAffectList.size(); ++i) 
      {

         if (uAffectList[i]->sName == "block" || uAffectList[i]->sName == "anvil")
         {
            uAffectList[i]->bAffectUpdate = true;
         }
         else if(uAffectList[i]->sName.find("mechwall") != string::npos )
         {
            MechanicalWall * mechwall =  dynamic_cast<MechanicalWall*>(uAffectList[i]);

            if ( uAffectList[i]->bAffectUpdate == true )
               mechwall->ToggleMidMove();

            uAffectList[i]->bAffectUpdate = true;
         }
         else if(uAffectList[i]->sName == "buzzsaw")
         {
            Buzzsaw* tempBuzz = dynamic_cast<Buzzsaw*>(uAffectList[i]);
            tempBuzz->toggleOn();
         }
      }
      bUpdate = true;
   }
}

void Lever::draw()
{
   IW_CALLSTACK("Lever::draw");

   Unit::draw();
   int xPos = this->i2Position.x;
   int yPos = this->i2Position.y + 5;
   if(this->iTextureIndex == 0)
   {
      xPos += 4;
   }
   else
   {
      xPos += 27;
   }
   Iw2DSetColour(this->cColor);
   Iw2DSetAlphaMode(IW_2D_ALPHA_HALF);
   Iw2DFillArc(CIwSVec2(xPos, yPos), CIwSVec2(this->lightSize, this->lightSize), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);
   Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
   Iw2DFillArc(CIwSVec2(xPos, yPos), CIwSVec2(Screen::getBOXSIZE().x/16 ,Screen::getBOXSIZE().x/16), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);
   Iw2DSetColour(0xffffffff);
}

void Lever::lightCalulation(uint64 time)
{

   this->blinkTime += time;

   if(this->blinkTime > 125)
   {
      if(this->up)
         ++this->lSize;
      else 
         --this->lSize;

      if(this->lSize >= 5 || this->lSize < 0)
      {
         this->blinkTime = 0;
         this->up = !this->up;
      }
   }

   switch(this->lSize)
   {
   case 0:
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 0.2f);
      break;
   case 1:
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 0.4f);
      break;
   case 2:
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 0.6f);
      break;
   case 3:
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 0.8f);
      break;
   case 4:
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 1.0f);
      break;
   case 5:
      this->lightSize = (int)(Screen::getBOXSIZE().x * 0.125f * 1.2f);
      break;
   }
}
