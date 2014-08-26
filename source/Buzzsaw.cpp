//
//
//
//   Project : Schrödinger's cat
//   File Name : Buzzsaw.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Buzzsaw.h"

Buzzsaw::Buzzsaw(CIwSVec2 i2Position): LethalUnit() 
{
   IW_CALLSTACK("Buzzsaw::Buzzsaw");

   this->tTextureList.push_back(ImageManager::getImage("buzzsaw2"));
   this->tTextureList.push_back(ImageManager::getImage("buzzsaw2_bloody"));
	this->sSoundList.push_back(SoundManager::getSound("buzzsaw1"));
	this->sSoundList.push_back(SoundManager::getSound("buzzsaw_off"));
	this->sSoundList.push_back(SoundManager::getSound("buzzsaw_on"));

   this->i2Position = i2Position;
   this->iRot = 1;
   this->sName = "buzzsaw";
   this->iCapDeathCount = 1000;
   this->iTextureIndex = 0;
   this->iDefaultCap = 1000;
   this->bIsMoving = true;
   this->i2Size = CIwSVec2((int)(Screen::getBOXSIZE().x /* 0.875f*/), (int)(Screen::getBOXSIZE().y/* * 0.875f*/));
   this->brBoundingBox = BoundingRectangle(this->getPosition(), this->getSize(), CIwSVec2((int)(this->getSize().x * 0.5f), this->getSize().y), true);
	this->iSoundIndex = 5;
   this->cColor = CIwArray<CIwColour>();

   ClassTracker::addUnit(this);
}

Buzzsaw::~Buzzsaw()
{
   this->cColor.clear_optimised();
}

void Buzzsaw::draw()
{	
   IW_CALLSTACK("Buzzsaw::draw");
	
	CIwSVec2 baseSize = this->i2Size;
	CIwSVec2 basePos = this->i2Position;
	for(int i = 0; i < (int)this->cColor.size(); ++i)
	{
		if(this->cColor[i].r == 255 && this->cColor[i].g == 255 && this->cColor[i].b == 255)
		{
			Iw2DSetAlphaMode(IW_2D_ALPHA_ADD);
		}
		else 
		{
			Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
		}

		Iw2DSetColour(this->cColor[i]);
		this->i2Center = CIwSVec2(i2Position.x + (int)(i2Size.x * 0.5f), i2Position.y + (int)(i2Size.y * 0.5f));
		iwfixed angle = iRot * IW_FIXED(0.01);
		CIwMat2D mRot = CIwMat2D();
		mRot.SetRot(angle, i2Center);
		Iw2DSetTransformMatrix(mRot);
      Iw2DDrawImageRegion(ImageManager::getImage("buzzsaw"), this->i2Position, this->i2Size, this->i2RegionOffset, this->i2RegionSize);
		Iw2DSetTransformMatrix(CIwMat2D::g_Identity);
		this->i2Size.x = baseSize.x - (6 * (i + 1) );
		this->i2Position.x = basePos.x + (3 * (i + 1) );
		this->i2Size.y = baseSize.y - (6 * (i + 1) );
		this->i2Position.y = basePos.y + (3 * (i + 1) );
	}
	Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
	Iw2DSetColour(0xffffffff);
	this->i2Center = CIwSVec2(i2Position.x + (int)(i2Size.x * 0.5f), i2Position.y + (int)(i2Size.y * 0.5f));
	iwfixed angle = iRot * IW_FIXED(0.01);
	CIwMat2D mRot = CIwMat2D();
	mRot.SetRot(angle, i2Center);
	Iw2DSetTransformMatrix(mRot);
   Unit::draw();
	Iw2DSetTransformMatrix(CIwMat2D::g_Identity);
	this->i2Size = baseSize;
	this->i2Position = basePos;
	
	/*int xPos;
	int yPos = this->i2Position.y + (int)(Screen::getBOXSIZE().x * 0.25f);
	int heightMultiplier = 0;
   for(int i = 0; i < (int)this->cColor.size(); ++i)
   {
		if(i % 2 == 0)
		{
			xPos = this->i2Position.x + (int)(Screen::getBOXSIZE().x * 0.25f);
			yPos += heightMultiplier * (Screen::getBOXSIZE().x * 0.41);
			++heightMultiplier;
		}
		else
		{
			xPos = this->i2Position.x + (int)(Screen::getBOXSIZE().x * 0.656f);
		}
		Iw2DSetColour(this->cColor[i]);
		Iw2DSetAlphaMode(IW_2D_ALPHA_HALF);
		Iw2DFillArc(CIwSVec2(xPos, yPos), CIwSVec2(this->lightSize, this->lightSize), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);
		Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
		Iw2DFillArc(CIwSVec2(xPos, yPos), CIwSVec2(Screen::getBOXSIZE().x/16, Screen::getBOXSIZE().y/16), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);   
   
   for(int i = (int)this->cColor.size() - 1; i >= 0 ; --i)
   {
      CIwSVec2 LightPos = CIwSVec2(this->i2Position.x + this->getSize().x/2, this->i2Position.y + this->getSize().y/2);
      int radius = this->i2Position.x/16 + i;
      
      Iw2DSetColour(this->cColor[i]);
     
      //Iw2DDrawArc(LightPos, CIwSVec2(Screen::getBOXSIZE().x/16, Screen::getBOXSIZE().y/16), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);
       Iw2DFillArc(LightPos, CIwSVec2(radius, radius), IW_ANGLE_FROM_DEGREES(0), IW_ANGLE_FROM_DEGREES(360), 100);
      Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
     
      Iw2DSetColour(0xffffffff);
   }
	Iw2DSetColour(0xffffffff);*/
}

void Buzzsaw::setColor(CIwColour cColor)
{
   this->cColor.push_back(cColor);
}

void Buzzsaw::toggleOn()
{
   IW_CALLSTACK("Buzzsaw::toggleOn");

   if(this->iDeathCount < this->iCapDeathCount)
   {
		SoundManager::playSound(this->sSoundList[6]);
      this->iCapDeathCount = 0;
   }
   else
   {
		SoundManager::playSound(this->sSoundList[7]);
      this->iCapDeathCount = this->iDefaultCap;
   }
}

void Buzzsaw::setCap(int iC)
{
   IW_CALLSTACK("Buzzsaw::setCap");

   
   this->iCapDeathCount = 2;
   this->iDefaultCap = 2;
   if(iC != 1000)
   {
      this->tTextureList.clear();
      this->tTextureList.push_back(ImageManager::getImage("buzzsaw"));
      this->tTextureList.push_back(ImageManager::getImage("buzzsaw_bloody"));
   }
}

void Buzzsaw::update(uint64 time)
{
   IW_CALLSTACK("Buzzsaw::update");
	
   if (GameState::getState() != GameState::PLAY)
   {
      return;
   }
   this->iTime = time;
   this->iTimePassed += time;

	if(this->iDeathCount < this->iCapDeathCount)
   {
		this->iRot += 4 * (int)this->iTime;
   }
	if(this->iDeathCount == this->iCapDeathCount - 1)
	{
		this->iSoundIndex = 6;
	}

   if(this->bAffectUpdate == true)
   {
      this->toggleOn();
      this->bAffectUpdate = false;
   }

   if(this->bUpdate == true)
   {
	   for(int i = 0; i < (int)this->uAffectList.size(); ++i)
	   {
		   this->uAffectList[i]->bAffectUpdate = true;
	   }

      LethalUnit::update();
   }
}
