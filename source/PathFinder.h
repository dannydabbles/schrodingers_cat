//
//
//
//   Project : Schrˆdinger's cat
//   File Name : PathFinder.h
//   Date : 1/21/2011
//   Author : P Productions
//
//

#if !defined(_PATHFINDER_H)
#define _PATHFINDER_H

#include "Box.h"
#include "Cat.h"

class PathFinder
{
public:
	PathFinder(Cat* cKitty);
  ~PathFinder();

  Cat* cKitty;
	
	float fGravC;
	
	CIwArray<Box*>* findPath(Box* start, Box* goal);
	CIwArray<CIwFVec2>* calcJump(Box* X, Box* Y, bool bLeft);
	CIwArray<CIwFVec2>* calcJumpi2(CIwSVec2 X, CIwSVec2 Y, bool bLeft);
	void addJumpsToPath(Box* X);
	void calcPlatform(Box* X);
	
private:
	CIwArray<Box*> *bPathList;
	CIwArray<Box*> bList;
	
	float fMaxJump;
   CIwArray<float> fJVelRange;
	bool bContFlag;
	
	float distance(Box* A, Box* B);
	CIwArray<Box*>* recPath_rec(CIwArray<Box*>* L, Box* curr);
	CIwArray<Box*>* recPath(Box* curr);
	float heuristic_est_dist(Box* A, Box* B);
	//bool checkJump(Box* X, Box* Y, float angle, float vec);
   bool checkJump(Box* bJumpFrom, Box* bJumpTo, float fAngle, float fVelocity)
   {
      IW_CALLSTACK("PathFinder::checkJump");

      if(bJumpFrom == NULL || bJumpTo == NULL)
      {
         return false;
      }
      if(bJumpFrom->bIsFilled || bJumpTo->bIsFilled)
      {
         return false;
      }
      if(bJumpFrom->bConnectList.contains(bJumpTo) && bJumpTo->bIsWalkable == true)
      {
         return true;
      }

      Box* bCheckBox = bJumpFrom;
      CIwSVec2 i2CheckPos = bCheckBox->i2Position;
      i2CheckPos.x += Screen::getBOXSIZE().x / 2;
      i2CheckPos.y += Screen::getBOXSIZE().y / 2;
      CIwSVec2 i2Start = bJumpFrom->i2Position;
      i2Start.x += Screen::getBOXSIZE().x / 2;
      i2Start.y += Screen::getBOXSIZE().y / 2;
      CIwSVec2 i2Finish = bJumpTo->i2Position;
      i2Finish.x += Screen::getBOXSIZE().x / 2;
      i2Finish.y += Screen::getBOXSIZE().y / 2;

      bool bLeft = (bJumpFrom->i2Position.x > bJumpTo->i2Position.x);

      for(;;)
      {
         if((bLeft == true && i2CheckPos.x < i2Finish.x) || (bLeft == false && i2CheckPos.x > i2Finish.x))
         {
            break;
         }
         if(bLeft == false)
         {
            i2CheckPos.x += 4;
         }
         else
         {
            i2CheckPos.x -= 4;
         }
         float fDistance = (float)i2CheckPos.x - (float)i2Start.x;
         float tano = tan(fAngle*PI/180);
         float coso = cos(fAngle*PI/180);
         i2CheckPos.y = (int)-((fDistance*tano)-((this->fGravC * pow(fDistance,2))/(2*pow(fVelocity,2) * pow(coso,2)))) + i2Start.y;
         CIwSVec2 i2NewPos = CIwSVec2(((i2CheckPos.x/Screen::getBOXSIZE().x) * Screen::getBOXSIZE().x), ((i2CheckPos.y/Screen::getBOXSIZE().y) * Screen::getBOXSIZE().y));
         if(i2NewPos.x == 9 * Screen::getBOXSIZE().x && (i2NewPos.y == 5 * Screen::getBOXSIZE().y || i2NewPos.y == 4 * Screen::getBOXSIZE().y)) //ZOMG MATH!?
         {
            //cout<<endl;
         }
         for(int i = 0; i < 8 ;++i)
         {
            if(bCheckBox->bConnectList[i] == NULL)
               continue;
            if(i2NewPos == bCheckBox->bConnectList[i]->i2Position)
            {
               bCheckBox = bCheckBox->bConnectList[i];
               break;
            }
         }

         if(bCheckBox == NULL)
         {
            return false;
         }

         //if(bCheckBox->bIsFilled || bCheckBox->bIsWalkable)
         //{
         //for(int i = 0; i < 8; ++i)
         //{
         //if(bCheckBox->bConnectList[i] != NULL)
         //{

         if((bCheckBox != bJumpFrom && bCheckBox != bJumpTo && bCheckBox->bIsWalkable) || bCheckBox->bIsFilled)
         {
            return false;
            for(int i = 0; i < (int)bCheckBox->uUnitList.size(); ++i)
            {
               //BoundingRectangle tmpBR = BoundingRectangle(i2CheckPos, cKitty->getSize(), this->cKitty->getBR().getSize(), true);

               if(bCheckBox->uUnitList[i]->sName.compare("platform") == 0 || 
                  bCheckBox->uUnitList[i]->sName.find("wall") != string::npos || 
                  bCheckBox->uUnitList[i]->sName.compare("block") == 0)
               {
                  //if(tmpBR.sphereCollision(bCheckBox->uUnitList[i]->getBR()) == true)
                  if(bCheckBox->uUnitList[i]->getBR().pointCollision(i2CheckPos) == true)
                  {
                     return false;
                  }
               }
            }
         }
         //}
         //}
         //}
      }
      return true;
   }
	CIwArray<Box*>* performAstar(Box* start, Box* goal);
	void doNotPathPastWalls();


};

#endif