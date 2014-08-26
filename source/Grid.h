//
//
//
//   Project : Schrödinger's cat
//   File Name : Grid.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_GRID_H)
#define _GRID_H

#include "Lever.h"
#include "Screen.h"
#include "MechanicalWall.h"
#include "Block.h"
#include "Spike.h"
#include "Scythe.h"
#include "CatAI.h"
#include "ShinyUnit.h"
#include "PathFinder.h"

class CatAI;
class Cat;

class Grid
{
public:
	friend class CatAI;
   Grid();
   ~Grid();
   void draw();
   void drawGrid(); // debug use only
   void reset();
   void update(/*FILE * fAllOut,*/ uint64 time);	
   void loadBox(CIwArray<Unit*> uUnitList, int iBPosX, int iBPosY);
	void handleBlock(Block* bBlock);
   void changeUnitBox(Unit* uMover);
   Box* getBox(int iPosX, int iPosY);
	Box* getBox(int iIndX, int iIndY, bool bGridCoor);
   void intializePathing();
   void setCat(Cat* cCat);
   void setPathFinder(PathFinder* pfPathFinder);
   
   Box* bStart;
	Box* bFinish;
	bool bPressed;
	ShinyUnit* suShinyCollision;
   Cat* cCat;
	
private:
	ShinyUnit* getShiniestUnitInBox(Box* bBox);
	CIwColour cColor;
   CIwArray<CIwArray<Box*> > bBoxesList;
   CIwArray<Box*> bMovingList;
   CIwArray<Unit*> uCollisionArray;
   PathFinder* pfPathFinder;

   void buildCollisionList();
   void shinyCollisionHandler();
   bool collisionDetection(Unit* uPotentialCollidingUnit);
};

#endif  //_GRID_H
