//
//
//
//   Project : Schrödinger's cat
//   File Name : Unit.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_UNIT_H)
#define _UNIT_H

#include "Box.h"
#include "CatState.h"
#include "GameState.h"
#include "BoundingRectangle.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "ClassTracker.h"
#include "PlayerProfile.h"

#ifdef DEBUG
#include "ClassTracker.h"
#endif

class Box;

class Unit
{
public:
   Unit();
   ~Unit();
	
   virtual void update(uint64 time) = 0;
   void addUnit(Unit* u);
   virtual void draw(); 
   virtual CIwSVec2 getPosition(); 
   void changeTexture(int i);
   CIwSVec2 getSize();
	CIwSVec2 getRS();
	CIwSVec2 getRO();
   BoundingRectangle& getBR();
	
	void setSize(int,int);
	void setRS(int,int);
	void setRO(int,int);

   string sName;
   CIwArray<Unit*> uAttatchedToList;
   CIwSVec2 i2Position;
   CIwArray<Unit*> uAffectList;

   bool bTop;
   bool bDrawn;
   bool bUpdate;
   bool bIsShiny;
   bool bIsMoving;
   bool bAffectUpdate;

   Box* bBox;

protected:
	int iSoundIndex;
   int iTextureIndex;
   int iOldTextureIndex;
   uint64 iAnimateTime;
	uint64 iTime;
   uint64 iTimePassed;
   CIwFVec2 f2Velocity;
   CIwFVec2 f2AbsPosition;
   CIwSVec2 i2Size;
   CIwVec2 i2Center;
   CIwSVec2 i2RegionOffset;
   CIwSVec2 i2RegionSize;
   CIwArray<CIwSoundSpec*> sSoundList;
	CIwArray<CIw2DImage*> tTextureList;

   BoundingRectangle brBoundingBox; // can be used as a sphere too

   // for things with lights
   int lightSize;
   int lSize;
   uint64 blinkTime;
   bool up;
};

#endif  //_UNIT_H
