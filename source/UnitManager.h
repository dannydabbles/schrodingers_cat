//
//
//
//   Project : Schrˆdinger's cat
//   File Name : UnitManager.h
//   Date : 1/21/2011
//   Author : P Productions
//
//

#if !defined(_UNITMANAGER_H)
#define _UNITMANAGER_H

#include "UserInterface.h"
#include "PauseMenu.h"
#include "QuitMenu.h"
#include "LevelNavigation.h"
#include "MainMenu.h"
#include "LaserPointer.h"
#include "Grid.h"
#include "Map.h"
//#include "ParticleCannon.h"
#include "Blood.h"
//#include "ShinyUnit.h"

class ShinyUnit;
class Grid;

class UnitManager
{
public:
   friend class Map;

   UnitManager(Grid* gGrid, LaserPointer * laser, Blood* blood);
   ~UnitManager();

   void update(uint64 time);

   void draw();
   void drawBoxes();

   void setCollisionList(CIwArray<Unit*> uCollisionList);
   void setUnitListOrder();

private:
   Grid* gGrid;
   CIwArray<Unit*> uUnitList;
   CIwArray<Unit*> uCollisionList;
   
   Blood* blood;
   LaserPointer * laser;
};

#endif  //_UNITMANAGER_H