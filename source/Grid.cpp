//
//
//
//   Project : Schrödinger's cat
//   File Name : Grid.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//
#include "Grid.h"

Grid::Grid()
{
   IW_CALLSTACK("Grid::Grid");

   this->bPressed = false;
   this->bBoxesList = CIwArray<CIwArray<Box*> >();
   this->bMovingList = CIwArray<Box*>();
   this->uCollisionArray = CIwArray<Unit*>();
   this->bStart = NULL;
   this->bFinish = NULL;
   this->suShinyCollision = NULL;

   for(int i = 0; i < Screen::getGRIDSIZE().x; ++i)
   {
      CIwArray<Box*> bTempList = CIwArray<Box*>();

      for(int j = -2; j < Screen::getGRIDSIZE().y - 2; ++j)
      {
         CIwSVec2 index(i, j);
         CIwSVec2 position(Screen::getBOXSIZE().x * i, Screen::getBOXSIZE().y * j);
         bTempList.push_back(new Box(index, position));
      }
      bBoxesList.push_back(bTempList);
   }

   for(int i = 0; i < Screen::getGRIDSIZE().x; ++i)
   {
      for(int j = 0; j < Screen::getGRIDSIZE().y; ++j)
      {
         if(i - 1 >= 0 && j - 1 >= 0)
         {
            this->bBoxesList[i][j]->bConnectList[0] = this->bBoxesList[i - 1][j - 1];
         }
         if(j - 1 >= 0)
         {
            this->bBoxesList[i][j]->bConnectList[1] = this->bBoxesList[i][j - 1];
         }
         if(i + 1 < Screen::getGRIDSIZE().x && j - 1 >= 0)
         {
            this->bBoxesList[i][j]->bConnectList[2] = this->bBoxesList[i + 1][j - 1];
         }
         if(i + 1 < Screen::getGRIDSIZE().x)
         {
            this->bBoxesList[i][j]->bConnectList[3] = this->bBoxesList[i + 1][j];  
         }
         if(i + 1 < Screen::getGRIDSIZE().x && j + 1 < Screen::getGRIDSIZE().y)
         {
            this->bBoxesList[i][j]->bConnectList[4] = this->bBoxesList[i + 1][j + 1];
         }
         if(j + 1 < Screen::getGRIDSIZE().y)
         {
            this->bBoxesList[i][j]->bConnectList[5] = this->bBoxesList[i][j + 1];
         }
         if(i - 1 >= 0 && j + 1 < Screen::getGRIDSIZE().y)
         {
            this->bBoxesList[i][j]->bConnectList[6] = this->bBoxesList[i - 1][j + 1];
         }
         if(i - 1 >= 0)
         {
            this->bBoxesList[i][j]->bConnectList[7] = this->bBoxesList[i - 1][j];
         }
      }
   }
}

Grid::~Grid()
{
   for ( int i = 0; i < (int)this->bBoxesList.size(); ++i)
   {
      for ( int j = 0; j < (int)this->bBoxesList[i].size(); ++j)
      {
         Box * b = this->bBoxesList[i][j];
         delete b;
      }


   }


}

void Grid::draw()
{	
   IW_CALLSTACK("Grid::draw");
}

void Grid::loadBox(CIwArray<Unit*> uUnitList, int iBPosX, int iBPosY)
{
   IW_CALLSTACK("Grid::loadBox");

   bBoxesList[iBPosX][iBPosY]->loadUnitList(uUnitList);
}

Box* Grid::getBox(int iPosX, int iPosY)
{
   IW_CALLSTACK("Grid::getBox");

   if(iPosX < Screen::getSCREENSIZE().x && iPosY < Screen::getSCREENSIZE().y && iPosX >= 0 && iPosY >= -Screen::getBOXSIZE().y * 2)
   {
      return bBoxesList[iPosX / Screen::getBOXSIZE().x][iPosY / Screen::getBOXSIZE().y + 2];
   }
   //IwAssertMsg(MYAPP, false, ("getBox: %i, %i returning NULL", iPosX, iPosY));
   return NULL;
}

Box* Grid::getBox(int iIndX, int iIndY, bool bGridCoor)
{
   IW_CALLSTACK("Grid::getBox");

   return bBoxesList[iIndX][iIndY];
}

ShinyUnit* Grid::getShiniestUnitInBox(Box* bBox)
{
   IW_CALLSTACK("Grid::getShiniestUnitInBox");

   ShinyUnit* suShiniestUnit = NULL;
   for(int i = 0; i < (int)bBox->uUnitList.size(); ++i)
   {
      if(bBox->uUnitList[i]->bIsShiny)
      {
         if(suShiniestUnit == NULL)
         {	
            suShiniestUnit = dynamic_cast<ShinyUnit*>(bBox->uUnitList[i]);
         }
         else 
         {
            if((dynamic_cast<ShinyUnit*>(bBox->uUnitList[i]))->getShininess() > suShiniestUnit->getShininess())
            {
               suShiniestUnit = dynamic_cast<ShinyUnit*>(bBox->uUnitList[i]);
            }
         }
      }
   }
   return suShiniestUnit;
}

void Grid::reset()
{
   IW_CALLSTACK("Grid::reset");

   this->bPressed = false;
   this->bMovingList.empty();
   this->uCollisionArray.empty();
   this->bStart = NULL;
   this->bFinish = NULL;
   this->suShinyCollision = NULL;

   for(int i = 0; i < Screen::getGRIDSIZE().x; ++i)
   {
      for(int j = 0; j < Screen::getGRIDSIZE().y; ++j)
      {
         this->bBoxesList[i][j]->reset();
      }
   }
}

void Grid::changeUnitBox(Unit* uMover)
{
   IW_CALLSTACK("Grid::changeUnitBox");

   Box* bOldPosition = NULL;
   Box* bNewPosition = NULL;

   bOldPosition = uMover->bBox;
   bNewPosition = this->getBox(uMover->getPosition().x, uMover->getPosition().y);

   if(bOldPosition != NULL && bNewPosition != NULL)
   {
      if(bOldPosition->i2Position != bNewPosition->i2Position)
      {
         bNewPosition->addUnit(uMover);
         bOldPosition->removeUnit(uMover);
         uMover->bBox = bNewPosition;
      }
      if(bOldPosition->bIsFilled == true && uMover->sName.find("wall") != string::npos)
      {
         bOldPosition->bIsFilled = false;
         bNewPosition->bIsFilled = true;
      }

      /*if (uMover->sName.compare("cat") == 0)
      {
      this->cCat->bBox = bNewPosition;
      }*/
   }
   else if(bNewPosition != NULL)
   {
      bNewPosition->addUnit(uMover);
      uMover->bBox = bNewPosition;
   }
   else 
   {
      //IwAssertMsg(MYAPP, false, ("%s did not change boxes", uMover->sName.c_str()));
      //IwAssertMsg(MYAPP, false, ("Moving from %i, %i", bOldPosition->i2Index.x, bOldPosition->i2Index.y));
      //if(bNewPosition != NULL) IwAssertMsg(MYAPP, false, ("Moving to %i, %i", bNewPosition->i2Index.x, bNewPosition->i2Index.y));
   }
}

void Grid::update(uint64 time)
{
   IW_CALLSTACK("Grid::update");

   if(GameState::getReInitializePathing() == true)
   {
      this->intializePathing();
      GameState::setReInitializePathing(false);
   }

   if(CatState::getState() == CatState::DEAD)
   {
      return;
   }
   buildCollisionList();
}

void Grid::intializePathing()
{
   IW_CALLSTACK("Grid::initializePathing");

   for(int i = 0; i < Screen::getGRIDSIZE().x; ++i)
   {
      for(int j = 0; j < Screen::getGRIDSIZE().y; ++j)
      {
         //cout<<"Initializing Box["<<i<<"]["<<j<<"]"<<endl;

         map<Box*, CIwArray<CIwFVec2>* >::iterator itor = this->bBoxesList[i][j]->jumpMap.begin();

         for(; itor != this->bBoxesList[i][j]->jumpMap.end(); ++itor)
         {
            if(itor->second != NULL && itor->second != this->cCat->curves)
            {
               itor->second->clear();
               delete itor->second;
               itor->second = NULL;
            }
         }
         this->bBoxesList[i][j]->jumpMap.clear();
         this->bBoxesList[i][j]->jumpMap = map<Box*, CIwArray<CIwFVec2>* >();

         this->bBoxesList[i][j]->bParent = NULL;
         this->bBoxesList[i][j]->bJumpCalced = false;
         this->bBoxesList[i][j]->bIsAPath = false;
         this->bBoxesList[i][j]->bIsEdge = false;
         this->bBoxesList[i][j]->bIsEdgeL = false;
         this->bBoxesList[i][j]->bIsEdgeR = false;
         this->bBoxesList[i][j]->bPlatformCalced = false;
         this->bBoxesList[i][j]->bPlatformList.clear();
         this->pfPathFinder->calcPlatform(this->bBoxesList[i][j]);

         while((int)this->bBoxesList[i][j]->bConnectList.size() != 8)
         {
            this->bBoxesList[i][j]->bConnectList.pop_back();
         }
         this->bBoxesList[i][j]->g_dScore = numeric_limits<float>::max();
         this->bBoxesList[i][j]->h_dScore = numeric_limits<float>::max();
         this->bBoxesList[i][j]->f_dScore = numeric_limits<float>::max();
      }
   }
   for(int i = 0; i < Screen::getGRIDSIZE().x; ++i)
   {
      for(int j = 0; j < Screen::getGRIDSIZE().y; ++j)
      {
         this->pfPathFinder->addJumpsToPath(this->bBoxesList[i][j]);
      }
   }
}

void Grid::shinyCollisionHandler()
{
   IW_CALLSTACK("Grid::shinyCollisionHandler");

   for(int i = 0; i < (int)uCollisionArray.size(); ++i)
   {
      if(uCollisionArray[i]->bIsShiny)
      {
         Unit* tempyUnit = uCollisionArray[i];
         if(getShiniestUnitInBox(uCollisionArray[i]->bBox) != NULL)
         {
            if(getShiniestUnitInBox(uCollisionArray[i]->bBox) == uCollisionArray[i])
            {
               this->suShinyCollision = dynamic_cast<ShinyUnit*>(uCollisionArray[i]);
            }
         }
      }
   }
}

void Grid::buildCollisionList()
{
   IW_CALLSTACK("Grid::buildCollisionList");

   // empty old collision list
   this->uCollisionArray.clear();

   // Insert all units in adjecent boxes in collision list
   for(int i = 0; i < 8; ++i) // resets levers ability to switch
   {
      if(this->cCat->bBox->bConnectList[i] != NULL)
      {
         for(int j = 0; j < (int)cCat->bBox->bConnectList[i]->uUnitList.size(); ++j)
         {
            if(!this->uCollisionArray.contains(this->cCat->bBox->bConnectList[i]->uUnitList[j]) && CatState::getState() != CatState::DEAD) //stops the cat from colliding with anything else after he dies
            {   
               bool collision = collisionDetection(this->cCat->bBox->bConnectList[i]->uUnitList[j]);
               if (collision)
               {
                  this->uCollisionArray.push_back(this->cCat->bBox->bConnectList[i]->uUnitList[j]);
                  this->cCat->bBox->bConnectList[i]->uUnitList[j]->bUpdate = true;
               }
               else if(collision == false && this->cCat->bBox->bConnectList[i]->uUnitList[j]->sName == "lever")
               {
                  dynamic_cast<Lever*>(this->cCat->bBox->bConnectList[i]->uUnitList[j])->bCooldown = false;
               }
            }
         }
      }
   }

   // insert units in cat's box into collision list
   for(int i = 0; i < (int)this->cCat->bBox->uUnitList.size(); ++i)
   {
      if(this->cCat->bBox->uUnitList[i]->sName != "cat")
      {
         if(!this->uCollisionArray.contains(this->cCat->bBox->uUnitList[i])&& CatState::getState() != CatState::DEAD) //stops the cat from colliding with anything else after he dies
         {   
            bool collision = collisionDetection(this->cCat->bBox->uUnitList[i]);
            if(collision)
            {
               this->uCollisionArray.push_back(this->cCat->bBox->uUnitList[i]);
               this->cCat->bBox->uUnitList[i]->bUpdate = true;
            }
            else if(collision == false && this->cCat->bBox->uUnitList[i]->sName == "lever")
            {
               dynamic_cast<Lever*>(this->cCat->bBox->uUnitList[i])->bCooldown = false;
            }
         }
      }
   }
}

bool Grid::collisionDetection(Unit* unit)
{
   IW_CALLSTACK("Grid::collisionDetection");

   // bounding boxes must be updated by their respective units
   // and attention must be paid to which part of the animation it is in
   // its gonna be lots of fun to make all the bounding boxes!!
   if(this->cCat == unit)
   {
      return false;
   }
   //if (unit->sName.compare("scythe")== 0)
   //return this->scytheCollision(unit);

   if(this->cCat->getBR().sphereCollision(unit->getBR()))
   {
      return true;
   }
   return false;
}

void Grid::drawGrid()
{
   IW_CALLSTACK("Grid::drawGrid");

   for(int i = 0 ; i < Screen::getSCREENSIZE().x; i += Screen::getBOXSIZE().x)
   {
      for( int j = 0; j < Screen::getSCREENSIZE().y; j += Screen::getBOXSIZE().y)
      {
         if(ShinyUnit::getShiniestUnit() != NULL && this->getBox(i, j) == ShinyUnit::getShiniestUnit()->bBox ||
            this->getBox(i, j) == ShinyUnit::getShinyDropDownBox())
         {
            continue;
         }
         else if(this->getBox(i, j)->bIsFilled)
         {
            continue;
         }
         else if(this->getBox(i, j)->bIsWalkable)
         {
            continue;
         }
         else
         {
            this->cColor.Set(0, 0, 255, 255);
         }
         Iw2DSetColour(this->cColor);
         Iw2DDrawRect(CIwSVec2(i, j), Screen::getBOXSIZE());
      }
   }
   for(int i = 0 ; i < Screen::getSCREENSIZE().x; i += Screen::getBOXSIZE().x)
   {
      for( int j = 0; j < Screen::getSCREENSIZE().y; j += Screen::getBOXSIZE().y)
      {
         if(ShinyUnit::getShiniestUnit() != NULL && this->getBox(i, j) == ShinyUnit::getShiniestUnit()->bBox ||
            this->getBox(i, j) == ShinyUnit::getShinyDropDownBox())
         {
            continue;
         }
         else if(this->getBox(i, j)->bIsFilled)
         {
            continue;
         }
         else if(this->getBox(i, j)->bIsWalkable)
         {
            this->cColor.Set(0, 255, 0, 255);
         }
         else
         {
            continue;
         }
         Iw2DSetColour(this->cColor);
         Iw2DDrawRect(CIwSVec2(i, j), Screen::getBOXSIZE());
      }
   }
   for(int i = 0 ; i < Screen::getSCREENSIZE().x; i += Screen::getBOXSIZE().x)
   {
      for( int j = 0; j < Screen::getSCREENSIZE().y; j += Screen::getBOXSIZE().y)
      {
         if(ShinyUnit::getShiniestUnit() != NULL && this->getBox(i, j) == ShinyUnit::getShiniestUnit()->bBox ||
            this->getBox(i, j) == ShinyUnit::getShinyDropDownBox())
         {
            continue;
         }
         else if(this->getBox(i, j)->bIsFilled)
         {
            this->cColor.Set(255, 0, 0, 255);
         }
         else if(this->getBox(i, j)->bIsWalkable)
         {
            continue;
         }
         else
         {
            continue;
         }
         Iw2DSetColour(this->cColor);
         Iw2DDrawRect(CIwSVec2(i, j), Screen::getBOXSIZE());
      }
   }
   for(int i = 0 ; i < Screen::getSCREENSIZE().x; i += Screen::getBOXSIZE().x)
   {
      for( int j = 0; j < Screen::getSCREENSIZE().y; j += Screen::getBOXSIZE().y)
      {
         if(ShinyUnit::getShiniestUnit() != NULL && this->getBox(i, j) == ShinyUnit::getShiniestUnit()->bBox ||
            this->getBox(i, j) == ShinyUnit::getShinyDropDownBox())
         {
            this->cColor.Set(255, 255, 0, 255);
         }
         else if(this->getBox(i, j)->bIsFilled)
         {
            continue;
         }
         else if(this->getBox(i, j)->bIsWalkable)
         {
            continue;
         }
         else
         {
            continue;
         }
         Iw2DSetColour(this->cColor);
         Iw2DDrawRect(CIwSVec2(i, j), Screen::getBOXSIZE());
      }
   }
   Iw2DSetColour(0xffffffff);
}

void Grid::setCat(Cat* Cat)
{
   IW_CALLSTACK("Grid:setCat");

   this->cCat = Cat;
}

void Grid::setPathFinder(PathFinder* pfPathFinder)
{
   IW_CALLSTACK("Grid:setPathFinder");

   this->pfPathFinder = pfPathFinder;
}
