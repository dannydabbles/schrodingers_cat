//
//
//
//   Project : Schrödinger's cat
//   File Name : PressurePlate.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "PressurePlate.h"

PressurePlate::PressurePlate(CIwSVec2 i2Position, string sName): Unit()
{
   IW_CALLSTACK("PressurePlate::PressurePlate");

   this->tTextureList.push_back(ImageManager::getImage("buttonup"));
   this->tTextureList.push_back(ImageManager::getImage("buttondown"));
   this->sSoundList.push_back(SoundManager::getSound("pressureplate"));

   this->i2Position = i2Position;
   this->sName = sName;
   this->bDown = false;
   this->cColor.Set(0, 0, 0, 0);
   this->brBoundingBox = BoundingRectangle(this->i2Position,this->i2Size, CIwSVec2(1, 1), true);

   ClassTracker::addUnit(this);
}

CIwColour PressurePlate::getColor()
{
   return this->cColor;
}

void PressurePlate::setColor(int iColor)
{
	switch(iColor)
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
			this->cColor.Set(255, 0, 0, 255);
			break;
	}
}

void PressurePlate::update(uint64 time)
{
   IW_CALLSTACK("PressurePlate::update");

   if (GameState::getState() != GameState::PLAY)
   {
      return;
   }
   this->iTime = time;
   this->iTimePassed += time;

   if(this->bUpdate == true)
   {
      if(bDown == false) 
      {
         if(this->bDrawn == false)
            SoundManager::playSound(this->sSoundList[0]);
         bDown = true;
         for(int i = 0; i < (int)uAffectList.size(); ++i) 
         {
            //if(uAffectList[i]->sName.find("mechwall") != string::npos || uAffectList[i]->sName == "block" || uAffectList[i]->sName == "anvil")
            //   uAffectList[i]->bUpdate = true;
            if(uAffectList[i]->sName == "buzzsaw")
            {
               Buzzsaw* temp = dynamic_cast<Buzzsaw*>(uAffectList[i]);
               temp->toggleOn();
            }
            else if (uAffectList[i]->sName == "mechwall")
            {
               MechanicalWall * mechwall =  dynamic_cast<MechanicalWall*>(uAffectList[i]);

               if ( uAffectList[i]->bAffectUpdate == true )
                  mechwall->ToggleMidMove();

               uAffectList[i]->bAffectUpdate = true;

            }
            else
               uAffectList[i]->bAffectUpdate = true;
         }
         ++this->iTextureIndex;
      }
      bUpdate = false;
   }
}

void PressurePlate::draw()
{
   IW_CALLSTACK("PressurePlate::draw");

   Iw2DSetAlphaMode(IW_2D_ALPHA_HALF);
   Iw2DSetColour(this->cColor);
   if(this->bDown == false && this->bDrawn == false)
   {
      Iw2DFillArc(CIwSVec2(this->i2Position.x + Screen::getBOXSIZE().x/2, this->i2Position.y + Screen::getBOXSIZE().y - 8), CIwSVec2(14, 14), IW_ANGLE_FROM_DEGREES(-90), IW_ANGLE_FROM_DEGREES(90), 100);
   }
   Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
   Unit::draw();
   Iw2DSetColour(0xffffffff);
}
