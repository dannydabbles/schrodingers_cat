//
//
//
//   Project : Schrödinger's cat
//   File Name : Map.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_MAP_H)
#define _MAP_H

#include "Anvil.h"
#include "BearTrap.h"
#include "Block.h"
#include "Bucket.h"
#include "Buzzsaw.h"
#include "Cat.h"
#include "CatAI.h"
#include "CatEvent.h"
#include "CatNip.h"
#include "CatStateManager.h"
#include "EndBox.h"
#include "Food.h"
#include "GameState.h"
#include "Grid.h"
#include "LaserPointer.h"
#include "Lever.h"
#include "LitterBox.h" 
#include "MechanicalWall.h"
#include "Message.h"
#include "Mouse.h"
#include "MouseAI.h"
#include "MouseHole.h"
#include "Platform.h"
#include "PressurePlate.h"
#include "Rope.h"
#include "ScratchingPost.h"
#include "Scythe.h"
#include "ScytheLeft.h"
#include "ScytheRight.h"
#include "Spike.h"
#include "StartBox.h" 
#include "UnitManager.h"
#include "PlayerProfile.h"
#include "Blood.h"
#include "SuperShinyJumpOutofBoxShinyUnit.h"

class UnitManager;
class CatAI;
class MouseAI;
class Grid;

class Map
{
public:
	Map(string sLevelName, Blood* blood, Grid* grid, FILE* fAllout);
   ~Map();

	bool bDone;
   string sLevelName;

	FILE* fAllOutFile;
	
	pair<string, CIwArray<string> > getBackgroundNames();
	string getCutSceneName();
	
   void draw();
	void update(uint64 time);

   int getDeaths();
   int getExpected();
   uint64 getTime();
	
private:	
	bool bMapLoaded;

	int iCatDeath;
   int iTime;
	int iColorCode;

	uint64 tLevelTime;

	string sBackground;
	CIwArray<string> sBackgroundExtras;
	string sCutSceneName;
	string sBackgroundMusic;
	
	CIwArray<string> stBacklog;
	CIwArray<string> findVector(string label);
	CIwArray<CIwArray<string> > vvsInstruct;
	CIwArray<pair<string, CIwArray<string> > > pLabelList;
	
   Box* bBegin;
   Box* bEnd;
   Cat* cKitty;
   CatAI* cAI;
	CatStateManager* csmStateManager;
	Grid* gGrid;
   LaserPointer * laser;
	MouseAI * mAI;
	Unit* uCurrent;
	UnitManager* umManager;

	CIwArray<Mouse*> ulMouseList;
	CIwArray<ShinyUnit*> suShinyList;
	CIwArray<pair<pair<pair<char,char>,string>,pair<pair<int,int>,Box*> > > pMultiBoxEffectList;
   CIwArray<pair<pair<char,char>,Unit*> > pStructuresList;
	
	void catIsDead();
   void readLabels();
   void readMap();
   void readInteractions();
   void readFiles();
	void writeFile();
	
	int ConvertStringToInt(string s);
	
   Unit* getFirstInStruct(char a, char b);
	Unit* getUnit(string ObjectName, CIwSVec2 i2Position);
};

#endif  //_MAP_H
