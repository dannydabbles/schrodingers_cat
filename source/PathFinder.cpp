//
//
//
//   Project : Schrˆdinger's cat
//   File Name : PathFinder.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//

#include "PathFinder.h"

PathFinder::PathFinder(Cat* cKitty)
{
   IW_CALLSTACK("PathFinder::PathFinder");

   this->cKitty = cKitty;
   this->fGravC = 10.0;
   this->fJVelRange = CIwArray<float>();
   this->fJVelRange.push_back(100.0f);
   this->fJVelRange.push_back(0.0f);
   this->fJVelRange.push_back(35.0f); //35 is a good number
   this->fMaxJump = 3;
   this->bList = CIwArray<Box*>();
   this->bContFlag = false;
   this->bPathList = new CIwArray<Box*>();
}

float PathFinder::distance(Box* A, Box* B)
{
   IW_CALLSTACK("PathFinder::distance");

   return heuristic_est_dist(A, B);
}

CIwArray<Box*>* PathFinder::recPath_rec(CIwArray<Box*>* L, Box* curr)
{
   IW_CALLSTACK("PathFinder::recPath_rec");

   if(curr == NULL)
   {
      //cout<<"Bottom out!!!!!"<<endl;
      return L;
   }
   L->insert_slow(curr, 0);
   //cout<<L->size()<<endl;
   return recPath_rec(L, curr->bParent);
}

CIwArray<Box*>* PathFinder::recPath(Box* curr)
{
   IW_CALLSTACK("PathFinder::recPath");

   //cout << "Called recPath..." << endl;
   this->bList = CIwArray<Box*>();
   return recPath_rec(&bList, curr);
}

float PathFinder::heuristic_est_dist(Box* A, Box*B)
{
   IW_CALLSTACK("PathFinder::heuristic_est_dist");

   float temp = sqrt(abs(pow(float(B->i2Position.x - A->i2Position.x), 2) + pow(float(B->i2Position.x - A->i2Position.y), 2)));
   return temp;
}

void PathFinder::calcPlatform(Box* X)
{
   IW_CALLSTACK("PathFinder::calcPlatform");

   if(X == NULL || X->bIsWalkable == false || X->bIsFilled ||X->bPlatformCalced == true)
   {
      return;
   }
   Box* bLeftB = X;
   Box* bRightB = X;
   for(Box* bCurrB = X; bCurrB != NULL && bCurrB->bIsWalkable && !bCurrB->bIsFilled ;bCurrB = bCurrB->bConnectList[7])
   {
      bCurrB->bIsEdge = false;
      bCurrB->bIsEdgeL = false;
      bCurrB->bIsEdgeR = false;
      bLeftB = bCurrB;
   }
   for(Box* bCurrB = bLeftB; bCurrB != NULL && bCurrB->bIsWalkable && !bCurrB->bIsFilled ;bCurrB = bCurrB->bConnectList[3])
   {
      bCurrB->bIsEdge = false;
      bCurrB->bIsEdgeL = false;
      bCurrB->bIsEdgeR = false;
      bLeftB->bPlatformList.push_back(bCurrB);
      bRightB = bCurrB;
   }
   bLeftB->bPlatformCalced = true;

   if(bLeftB == NULL || bRightB == NULL)
   {
      IwAssertMsg(MYAPP, false, ("Platform calculation error."));
   }

   bLeftB->bIsEdge = false;
   bLeftB->bIsEdgeR = false;
   bLeftB->bIsEdgeL = false;
   bRightB->bIsEdge = false;
   bRightB->bIsEdgeR = false;
   bRightB->bIsEdgeL = false;

   if(bLeftB->bConnectList[7] != NULL && !bLeftB->bConnectList[7]->bIsFilled)
   {
      bLeftB->bIsEdge = true;
      bLeftB->bIsEdgeL = true;
   }
   else
   {
      bLeftB->bIsEdgeL = false;
   }
   if(bRightB->bConnectList[3] != NULL && !bRightB->bConnectList[3]->bIsFilled)
   {
      bRightB->bIsEdge = true;
      bRightB->bIsEdgeR = true;
   }
   else
   {
      bRightB->bIsEdgeR = false;
   }
   for(int i = 0; i < (int)bLeftB->bPlatformList.size(); ++i)
   {      
      if(bLeftB->bPlatformList[i] == bLeftB)
      {
         continue;
      }
      bLeftB->bPlatformList[i]->bPlatformList = bLeftB->bPlatformList;
      bLeftB->bPlatformList[i]->bPlatformCalced = true;
   }
}

/*
bool PathFinder::checkJump(Box* bJumpFrom, Box* bJumpTo, float fAngle, float fVelocity)
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
         ++i2CheckPos.x;
      }
      else
      {
         --i2CheckPos.x;
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
*/
void PathFinder::addJumpsToPath(Box* X)
{
   IW_CALLSTACK("Cat::addJumpsToPath");
   //return;
   if(X->bJumpCalced)
   {
      return;
   }
   if(!X->bIsWalkable || X->bIsFilled)
   {
      return;
      //IwAssertMsg(MYAPP, false, ("Trying to jump from non-walkable Box."));
   }
   if(!X->bPlatformCalced)
   {
      this->calcPlatform(X);
   }
   CIwArray<Box*> lbChecklist = CIwArray<Box*>();
   for(int i = 0; i < this->fMaxJump; ++i)
   {
      CIwArray<Box*> lbTList = CIwArray<Box*>();
      if(i == 0)
      {
         for(int j = 0; j < 8; ++j)
         {
            if(X->bConnectList[j] == NULL)
            {
               continue;
            }
            //if(!(i==1 && X->bConnectList[j]->bIsWalkable))
            if(!(X->i2Index.y > X->bConnectList[j]->i2Index.y && X->bConnectList[j]->bIsWalkable) &&
               !(X->i2Index.y < X->bConnectList[j]->i2Index.y && X->bIsWalkable))
            {
               lbTList.push_back(X->bConnectList[j]);
            }
         }
      }
      else
      {
         for(CIwArray<Box*>::iterator itor = lbChecklist.begin(); itor != lbChecklist.end(); ++itor)
         {
            Box* Y = *itor;
            if(Y == NULL) continue;
            for(int j = 0; j < 8; ++j)
            {
               if(Y->bConnectList[j] == NULL) continue;
               if(Y->bConnectList[j] == X) continue;
               if(lbChecklist.contains(Y->bConnectList[j])) continue;
               if(lbTList.contains(Y->bConnectList[j])) continue;
               if(!(i==1 && Y->bConnectList[j]->bIsWalkable))
               {
                  lbTList.push_back(Y->bConnectList[j]);
               }
            }
         }
      }
      lbChecklist.append(lbTList);
      lbTList.clear();
   }
   for(CIwArray<Box*>::iterator itor = lbChecklist.begin(); itor != lbChecklist.end() ;)
   {
      Box* Y = *itor;
      if(Y->bIsWalkable && Y != X) ++itor;
      else itor = lbChecklist.erase(itor);
   }
   for(CIwArray<Box*>::iterator itor = lbChecklist.begin(); itor != lbChecklist.end() ;)
   {
      Box* Y = *itor;
      calcPlatform(Y);
      int iJumpDir = Y->i2Index.x - X->i2Index.x;
      /*
      if(X->bIsEdgeL && X->bIsEdgeR)
      {
      ++itor;
      continue;
      }*/
      if(Y->i2Index.y <= X->i2Index.y &&
         ((iJumpDir > 0 && Y->bIsEdgeL) || (iJumpDir < 0 && Y->bIsEdgeR)))
      {
         ++itor;
         continue;
      }
      else if(Y->i2Index.y > X->i2Index.y && 
         ((iJumpDir > 0 && X->bIsEdgeR) || (iJumpDir < 0 && X->bIsEdgeL)))
      {
         ++itor;
         continue;
      }
      itor = lbChecklist.erase(itor);
   }
   for(CIwArray<Box*>::iterator itor = lbChecklist.begin(); itor != lbChecklist.end(); ++itor)
   {
      Box* Y = *itor;
      if(Y == NULL) continue;
      if(!Y->bIsWalkable) continue;
      //cout<<lbChecklist.size()<<endl;
      CIwArray<CIwFVec2>* angles = new CIwArray<CIwFVec2>();
      float x = (float)(Y->i2Position.x - X->i2Position.x);
      float y = (float)(-(Y->i2Position.y - X->i2Position.y));
      //if(y == 0.0) continue;
      float gx2 = this->fGravC * pow(x, 2);
      float gx = this->fGravC * x;
      float g = this->fGravC;
      for(int i = 1; i <= (int)this->fJVelRange[0]; ++i)
      {
         float v = (this->fJVelRange[2] - this->fJVelRange[1]) * (1 / this->fJVelRange[0]) * i + this->fJVelRange[1];
         float v2 = pow(v, 2);
         float root = pow(v2, 2) - g * (gx2 + 2 * y * v2);

         //cout<<"root:"<<root<<endl;
         if(root >= 0)
         {
            float fThetaP =	(float)atan((v2 + (float)(sqrt(root)))/gx) * (180.0f/PI);
            //cout<<"fThetaP:"<<fThetaP<<endl;
            float fThetaN =	(float)atan((v2 - (float)(sqrt(root)))/gx) * (180.0f/PI);
            //cout<<"fThetaN:"<<fThetaN<<endl;
            if((fThetaP < 89 && fThetaP > -89) && checkJump(X, Y, fThetaP, v)) 
               angles->push_back(CIwFVec2(fThetaP,v));
            //cout<<"fThetaP:"<<fThetaP<<" v:"<<v<<endl;
            if((fThetaN < 89 && fThetaN > -89) && checkJump(X, Y, fThetaN, v)) 
               angles->push_back(CIwFVec2(fThetaN,v));
            //cout<<"fThetaN:"<<fThetaN<<" v:"<<v<<endl;
            int blah = 0;
         }
      }

      if(angles->empty())
      {
         //cout<<"No angles"<<endl;
         delete angles;
         continue;
      }
      bool blah1 = (X->jumpMap[Y] == NULL);
      //IwMemBucketPush(BOX);

      if(X->jumpMap[Y] != this->cKitty->curves)
      {
         delete X->jumpMap[Y]; // super sketch
      }
      X->jumpMap[Y] = angles;
      //IwMemBucketPop();
      bool blah2 = (X->jumpMap[Y] == NULL);
      if(!X->bConnectList.contains(Y)) X->bConnectList.push_back(Y);
      //CIwColour col = CIwColour();
      //col.Set(255,0,0);
      //Iw2DSetColour(col);
      //Iw2DDrawLine(X->i2Corner, Y->i2Corner);
      //col.Set(255);
      //Iw2DSetColour(col);
      //cout<<"Should work!"<<endl;

   }
   lbChecklist.clear();
   X->bJumpCalced = true;

}

CIwArray<Box*>* PathFinder::performAstar(Box* start, Box* goal)
{
   IW_CALLSTACK("PathFinder::performAstar");

   if(start == NULL )
   {      
      IwAssertMsg(MYAPP, false, ("start is null"));
      return new CIwArray<Box*>();
   }

   if (goal == NULL)
   {
      goal = start;

      cout << "Goal is null; set to start" <<endl;
      return new CIwArray<Box*>();
   }

   if(!start->bIsWalkable || !goal->bIsWalkable)
   {
      cout<<"Can't walk that path."<<endl;
      return new CIwArray<Box*>();
   }

   if(this->bContFlag == true){
      if(!this->bPathList->empty())
      {
         start = this->bPathList->back();
      }
   }
   int blah = 0;
   start->bParent = NULL;
   CIwArray<Box*> cset = CIwArray<Box*>();
   CIwArray<Box*> oset = CIwArray<Box*>();
   start->g_dScore = 0;
   start->h_dScore = heuristic_est_dist(start, goal);
   start->f_dScore = start->h_dScore;
   oset.push_back(start);
   while(!oset.empty())
   {
      Box *test = oset.front();
      for(int i = 0; i < (int)oset.size(); ++i)
      {
         if(oset[i]->f_dScore < test->f_dScore)
         {
            test = oset[i];
         }
      }
      Box *X = test;
      if(X == goal)
      {
         if(this->bContFlag == true)
         {
            CIwArray<Box*>* temp = recPath(goal);
            if(this->bPathList->empty()) return temp;
            temp->erase(0);
            for(CIwArray<Box*>::iterator itor = temp->begin(); itor != temp->end() ;++itor){
               this->bPathList->push_back(*itor);
            }				 
            return this->bPathList;
         }
         else
         {
            return recPath(goal);
         }
      }
      oset.find_and_remove(X);
      cset.push_back(X);
      addJumpsToPath(X);
      for(int i = 0; i < (int)X->bConnectList.size(); ++i)
      {
         Box *Y = X->bConnectList[i];
         if(Y == NULL) continue;
         if(!Y->bIsWalkable || Y->bIsFilled) continue;
         //cout<<"Blah: "<<++blah<<endl;
         if(cset.contains(Y)) continue;
         //calcJumps(Y);
         float tent_g_score = 0.0;
         if(X->bConnectList[3] == Y || X->bConnectList[7] == Y)
         {
            tent_g_score = X->g_dScore + distance(X, Y);
         }
         else
         {
            if(X->jumpMap[Y] == NULL) continue;
            tent_g_score = X->g_dScore + 0.5f * PI * distance(X, Y);
         }
         bool tent_better = false;
         if(!oset.contains(Y))
         {	
            oset.push_back(Y);
            tent_better = true;
         }
         else
         { 
            if(tent_g_score < Y->g_dScore)
            {
               tent_better = true;
            }
            else
            {
               tent_better = false;
            }
         }
         if(tent_better)
         {
            if(Y != start)
            {
               Y->bParent = X;
            }
            Y->g_dScore = tent_g_score;
            if(X->bConnectList[3] == Y || X->bConnectList[7] == Y)
            {
               Y->h_dScore = heuristic_est_dist(Y, goal);
            }
            else
            {
               if(X->jumpMap[Y] == NULL)
               Y->h_dScore = heuristic_est_dist(Y, goal);
            }
            Y->f_dScore = Y->g_dScore + Y->h_dScore;
         }
      }
   }
   //cout << "No path found!" << endl;
   return new CIwArray<Box*>();
}

void PathFinder::doNotPathPastWalls()
{
   IW_CALLSTACK("PathFinder::doNotPathPastWalls");

   Box* temp = NULL;
   for(int i = 0; i < (int)this->bPathList->size(); ++i)
   {
      if ((*this->bPathList)[i]->bIsFilled == true || (*this->bPathList)[i]->bIsWalkable == false)
      {
         temp = (*this->bPathList)[i];
      }
   }

   for(;temp != NULL;)
   {
      if(this->bPathList->back() == temp) 
      {
         this->bPathList->pop_back();
         break;
      }
      this->bPathList->pop_back();
   }
}

CIwArray<Box*>* PathFinder::findPath(Box* start, Box* goal)
{
   IW_CALLSTACK("PathFinder::findPath");

   CIwArray<Box*>* tempList = this->bPathList;
   this->bPathList = performAstar(start, goal);
   doNotPathPastWalls();

   return this->bPathList;
}

CIwArray<CIwFVec2>* PathFinder::calcJump(Box* X, Box* Y, bool bLeft)
{
   IW_CALLSTACK("PathFinder::calcJump");

   if(Y == NULL || Y == X) return new CIwArray<CIwFVec2>();
   CIwArray<CIwFVec2>* angles = new CIwArray<CIwFVec2>();
   float x = 0.0;
   if(bLeft)
   {
      x = (float)(Y->i2Position.x - X->i2Position.x);
   }
   else
   {
      x = (float)(Y->i2Position.x - X->i2Position.x);
   }
   float y = (float)(-(Y->i2Position.y - X->i2Position.y));
   //if(y == 0.0) continue2
   float gx2 = this->fGravC * pow(x, 2);
   float gx = this->fGravC * x;
   float g = this->fGravC;
   for(int i = 1; i <= (int)this->fJVelRange[0] ; ++i){
      float v = (this->fJVelRange[2] - this->fJVelRange[1]) * (1 / this->fJVelRange[0]) * i + this->fJVelRange[1];
      float v2 = pow(v, 2);
      float root = pow(v2, 2) - g * (gx2 + 2 * y * v2);

      //cout<<"root:"<<root<<endl;
      if(root >= 0)
      {
         float fThetaP =	(float)atan((v2 + (float)(sqrt(root)))/gx) * (180.0f/PI);
         //cout<<"fThetaP:"<<fThetaP<<endl;
         float fThetaN =	(float)atan((v2 - (float)(sqrt(root)))/gx) * (180.0f/PI);
         //cout<<"fThetaN:"<<fThetaN<<endl;
         if((fThetaP < 89 && fThetaP > -89) && checkJump(X, Y, fThetaP, v))
            angles->push_back(CIwFVec2(fThetaP,v));
         //cout<<"fThetaP:"<<fThetaP<<" v:"<<v<<endl;
         if((fThetaN < 89 && fThetaN > -89) && checkJump(X, Y, fThetaN, v))
            angles->push_back(CIwFVec2(fThetaN,v));
         //cout<<"fThetaN:"<<fThetaN<<" v:"<<v<<endl;
         int blah = 0;
      }
   }
   return angles;
}

CIwArray<CIwFVec2>* PathFinder::calcJumpi2(CIwSVec2 X, CIwSVec2 Y, bool bLeft)
{
   IW_CALLSTACK("PathFinder::calcJump");

   CIwArray<CIwFVec2>* angles = new CIwArray<CIwFVec2>();
   float x = 0.0;
   if(bLeft)
      x = (float)(Y.x - Screen::getBOXSIZE().x - X.x);
   else
      x = (float)(Y.x + Screen::getBOXSIZE().x - X.x);
   float y = (float)(-(Y.y - X.y));
   //if(y == 0.0) continue2
   float gx2 = this->fGravC * pow(x, 2);
   float gx = this->fGravC * x;
   float g = this->fGravC;
   for(int i = 1; i <= (int)this->fJVelRange[0] ;++i)
   {
      float v = (this->fJVelRange[2] - this->fJVelRange[1]) * (1 / this->fJVelRange[0]) * i + this->fJVelRange[1];
      float v2 = pow(v, 2);
      float root = pow(v2, 2) - g * (gx2 + 2 * y * v2);

      //cout<<"root:"<<root<<endl;
      if(root >= 0)
      {
         float fThetaP =	(float)atan((v2 + (float)(sqrt(root)))/gx) * (180.0f/PI);
         //cout<<"fThetaP:"<<fThetaP<<endl;
         float fThetaN =	(float)atan((v2 - (float)(sqrt(root)))/gx) * (180.0f/PI);
         //cout<<"fThetaN:"<<fThetaN<<endl;
         if((fThetaP < 89 && fThetaP > -89)) 
            angles->push_back(CIwFVec2(fThetaP,v));
         //cout<<"fThetaP:"<<fThetaP<<" v:"<<v<<endl;
         if((fThetaN < 89 && fThetaN > -89)) 
            angles->push_back(CIwFVec2(fThetaN,v));
         //cout<<"fThetaN:"<<fThetaN<<" v:"<<v<<endl;
         int blah = 0;
      }
   }
   return angles;
}

PathFinder::~PathFinder()
{
   this->bPathList->clear();
}
