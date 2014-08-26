//
//
//
//   Project : Schrödinger's cat
//   File Name : MapManager.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_MAPMANAGER_H)
#define _MAPMANAGER_H

#include "Map.h"
#include "Grid.h"
#include "s3eKeyboard.h"
#include "BackgroundManager.h"
#include "CutSceneManager.h"
#include "ClassTracker.h"

class MapManager
{
public:
   MapManager();
   ~MapManager();

   void draw();
   void loadLevel(int i);
	void nextLevel(bool);
   void update(uint64 time);
   void reset();
   Map* getMap();

   CIwArray<string> getList();

private:	
   bool bPressed;
   int level;
   int timer;

   FILE * fAllOutFile;

   CIwArray<string> sMapNameList;
	CIwArray<string> sRealMapNameList;

   BackgroundManager* bmManager;
   CutSceneManager* csManager;
   Map* mCurrent;
   Blood* blood;
   Grid* grid;
};

#endif  //_MAPMANAGER_H
