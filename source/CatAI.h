//
//
//
//   Project : Schrödinger's cat
//   File Name : CatAI.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_CATAI_H)
#define _CATAI_H

#include "Cat.h"
#include "CatStateManager.h"
#include "Grid.h"
#include "PathFinder.h"
#include "ShinyHandler.h"
#include "UnitManager.h"

class Grid;
class ShinyHandler;
class UnitManager;

class CatAI
{
public:
	CatAI(Box* bBegin, Box* bEnd, Cat* pcKitty, Grid* gGrid, CIwArray<ShinyUnit*> suShinyList, CatStateManager* csmStateManager, LaserPointer* lp);
	~CatAI();
	Grid* gGrid;	
	
	void reset();
	
	void update(uint64 time);
   PathFinder* getPathFinder();
	
private:
	bool bIsLunging;
   int iPathIndex;
   float fLungeDist;
	
	CIwArray<CIwFVec2>* angles;
	
	Cat* cKitty;
   Box* bBegin;
   Box* bCurr;
   Box* bEnd;
	Box* bGoFrom;
   Box* bGoTo;
   Box* bGoJump;
	CatStateManager* csmStateManager;
	LaserPointer* lp;

	PathFinder* pfFinder;
	ShinyHandler* shHandler;
	CIwArray<Box*> * bPathList;
	pair<Box*, Box*>* pbGoal;

   CatState::State state;
	
	void debugOutput();
	void doLunging(CIwSVec2 i2LungePoint);
   void doMovement();
	void moveShiny(Box* shine);
};

#endif  //_CATAI_H
