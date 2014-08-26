//
//
//
//   Project : Schrödinger's cat
//   File Name : CatAI.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "CatAI.h"

CatAI::CatAI(Box* begin, Box* end, Cat* cKitty, Grid* gGrid, CIwArray<ShinyUnit*> suShinyList, CatStateManager* csmStateManager, LaserPointer* lp)
{
   IW_CALLSTACK("CatAI::CatAI");

   IwAssertMsg(MYAPP, end != NULL, ("end is NULL in CatAI"));
   this->bEnd = end;
   this->pbGoal = new pair<Box*, Box*>(end, end);

   IwAssertMsg(MYAPP, begin != NULL, ("begin is NULL in CatAI"));
   this->bBegin = begin;

   IwAssertMsg(MYAPP, cKitty != NULL, ("cat is NULL in CatAI"));
   this->cKitty = cKitty;

   IwAssertMsg(MYAPP, gGrid != NULL, ("grid is NULL in CatAI"));
   this->gGrid = gGrid;

   IwAssertMsg(MYAPP, cKitty->bBox != NULL, ("cat box is NULL in CatAI"));
   this->bCurr = cKitty->bBox;

   IwAssertMsg(MYAPP, csmStateManager != NULL, ("CSM is NULL in CatAI"));
   this->csmStateManager = csmStateManager;

   this->bGoTo = this->bBegin;
   this->bGoFrom = this->bBegin;
   //this->bContFlag = false;
   this->bIsLunging = false;
   this->bPathList =  new CIwArray<Box*>();
   this->iPathIndex = -1;
   this->fLungeDist = 60.0;
   this->pfFinder = new PathFinder(this->cKitty);
   this->shHandler = new ShinyHandler(cKitty, suShinyList);
   this->lp = lp;
   this->state = CatState::WALKINGRIGHT;
   this->angles = new CIwArray<CIwFVec2>();  


}

void CatAI::moveShiny(Box* shine)
{
   IW_CALLSTACK("CatAI::moveShiny");

   this->pbGoal = new pair<Box*, Box*>(shine, shine);
}

void CatAI::doLunging(CIwSVec2 i2LungePoint)
{
   IW_CALLSTACK("CatAI::doLunging");

   Box* bSaveGoTo = this->bGoTo;
   Box* bSaveGoFrom = this->bGoFrom;         //save some variables
   if(!this->bIsLunging)         //if you're not already jumping, you need to jump
   {
      //calculate end position
      Box* bTempFrom = this->cKitty->bBox;
      Box* bTempTo = this->pbGoal->second;
      if(bTempFrom->bPlatformList.contains(bTempTo))       //??? Seems like if you can't jump to something...but the way it knows to get there is if it IS in the connect list of the start position.
      {

         this->angles->clear();    
      }
      else
      {
         //delete angles; // probably shouldnt do this but whatever
         CIwSVec2 temp = CIwSVec2(bTempFrom->i2Position.x + Screen::getBOXSIZE().x/2, bTempFrom->i2Position.y + Screen::getBOXSIZE().y/2);
         if(temp.x > i2LungePoint.x)
            this->angles = this->pfFinder->calcJumpi2(temp, i2LungePoint, true);
         else                                                     //??? Seems like if you can jump to it, calculate the curves   
            this->angles = this->pfFinder->calcJumpi2(temp, i2LungePoint, false);
      }
      if(!this->angles->empty())
      {
         //this->bPathList->clear_optimised();     //this is resetting the path--why would you do that?
         //this->iPathIndex = -1;
         //this->bGoFrom = cKitty->bBox;
         int pre_x = this->cKitty->i2Position.x + Screen::getBOXSIZE().x/2;
         int pre_y = this->cKitty->i2Position.y + Screen::getBOXSIZE().y/2;
         int anglenum = 0;
         bool bRight = (i2LungePoint.x - this->cKitty->i2Position.x > 0) && abs(i2LungePoint.x - this->cKitty->i2Position.x > 1);
         for(int pos_x = 0; ; bRight ? ++pos_x : --pos_x)
         {
            float x = (float)pos_x;
            float o = (*this->angles)[anglenum].x;
            float v = (*this->angles)[anglenum].y;
            float g = this->pfFinder->fGravC;
            float tano = tan(o*PI/180);
            float coso = cos(o*PI/180);
            int y = (int)-((x*tano)-((g*pow(x,2))/(2*pow(v,2)*pow(coso,2))));                            //ZOMGMATH
            this->bGoTo = this->gGrid->getBox((int)x + pre_x, (int)y + pre_y);
            if(this->bGoTo == NULL)
            {
               break;
            }
            if(this->bGoTo != NULL && this->bGoTo != this->bGoFrom && this->bGoTo->bIsFilled)
            {
               ++anglenum;
               if(anglenum >= (int)this->angles->size())
               {
                  break;
               }
               else
               {
                  continue;
               }
            }
            if(this->bGoTo != NULL && this->bGoTo != bSaveGoFrom && this->bGoTo->bIsWalkable)
            {
               break;
            }
         }
         this->angles->clear_optimised();
         this->bIsLunging = true;
      }
      // delete this->angles;
      if(this->bGoTo != NULL && this->bGoTo != this->cKitty->bBox)
      {
         //CIwSVec2 temp = CIwSVec2(this->cKitty->bBox->i2Position.x + Screen::getBOXSIZE().x/2, this->cKitty->bBox->i2Position.y + Screen::getBOXSIZE().y/2);
         //this->angles = this->pfFinder->calcJump(this->gGrid->getBox(temp.x, temp.y), this->bGoTo, true);    
         this->angles = this->pfFinder->calcJump(this->cKitty->bBox, this->bGoTo, true);         //I got lost in the above code: at this point I just have no fucking clue.
      }
      else
      {
         this->angles->clear_optimised();
      }
   }
   if(!this->angles->empty())
   {
      cKitty->setCurves(this->angles);
      cKitty->setFinish(this->bGoTo->i2Position);
      this->bPathList->clear_optimised();
      this->iPathIndex = -1;
      this->bIsLunging = false;
      if(this->cKitty->i2Position.x < this->bGoTo->i2Position.x)
      {
         this->state = CatState::JUMPINGRIGHT;
      }
      else if(this->cKitty->i2Position.x > this->bGoTo->i2Position.x)
      {
         this->state = CatState::JUMPINGLEFT;
      }
      if(this->cKitty->i2Position.x == this->bGoTo->i2Position.x)
      {
         IwAssertMsg(MYAPP, false, ("Lunging given invalid GoTo"));
      }
   }
   else
   {
      this->bGoTo = bSaveGoTo;
      this->bGoFrom = bSaveGoFrom;
      this->bIsLunging = false;
   }
}

void CatAI::doMovement()
{
   IW_CALLSTACK("CatAI::doMovement");

   if(this->bCurr->bConnectList[3] == this->bGoTo) //if box to your right is the same as goto
   {
      //cout << "PathSize: " << this->bPathList->size() << endl;      
      this->state = CatState::WALKINGRIGHT;
   }
   else if(this->bCurr->bConnectList[7] == this->bGoTo) //if box to your right is the same as goto
   {
      this->state = CatState::WALKINGLEFT;
   }
   else // else if jumping
   {
      if(this->bGoFrom->jumpMap.find(this->bGoTo) == this->bGoFrom->jumpMap.end())
      {
         this->pfFinder->addJumpsToPath(this->bGoFrom);
      }
      if(this->bGoFrom->jumpMap.find(this->bGoTo) == this->bGoFrom->jumpMap.end())
      {
         return;
      }
      this->cKitty->setCurves(this->bGoFrom->jumpMap[this->bGoTo]);

      if(this->cKitty->i2Position.x < this->bGoTo->i2Position.x)
      {
         this->state = CatState::JUMPINGRIGHT;
      }
      else if(this->cKitty->i2Position.x > this->bGoTo->i2Position.x)
      {
         this->state = CatState::JUMPINGLEFT;
      }
   }
   this->cKitty->setFinish(this->bGoTo->i2Position);

   /*
   if((this->csmStateManager->getPrevious() == CatState::RIGHTTOJUMPRIGHT || 
   this->csmStateManager->getPrevious() == CatState::LEFTTOJUMPLEFT) ||
   (this->state != CatState::JUMPINGLEFT) &&
   (this->state != CatState::JUMPINGRIGHT))
   {
   // ++this->iPathIndex;
   }
   if(iPathIndex >= (int)this->bPathList.size())
   {
   this->bPathList.clear_optimised(); //do we need to do this?
   this->bGoFrom = this->bCurr;
   this->bGoTo = this->bCurr;
   }
   else
   {
   this->bGoFrom = this->bCurr;
   this->bGoTo = this->bPathList[iPathIndex];
   }
   */

   /*
   if(this->csmStateManager->getPrevious() > CatState::__START_TRANSITION_STATES__ && 
   this->csmStateManager->getPrevious() < CatState::__END_TRANSITION_STATES__)
   {
   this->bGoFrom = this->bGoTo;
   ++this->iPathIndex;
   if(iPathIndex >= (int)this->bPathList.size())
   {
   this->bPathList.clear_optimised(); //do we need to do this?
   }
   else
   {
   this->bGoTo = this->bPathList[iPathIndex];
   }
   }
   */
}

void CatAI::update(uint64 time)
{
   IW_CALLSTACK("CatAI::update");

   /*if(GameState::getReInitializePathing())
   {
   for(int i = 0; i < Screen::getGRIDSIZE().x; ++i)
   {
   for(int j = 0; j < Screen::getGRIDSIZE().y; ++j)
   {
   this->pfFinder->addJumpsToPath(this->gGrid->bBoxesList[i][j]);
   }
   }
   }*/

   if(CatState::getState() == CatState::DEAD)
   {
      //this->reset(); moved to grid
      return;
   }

   if(CatState::getState() != CatState::TRANSITIONING ||
      this->csmStateManager->getPrevious() == CatState::RIGHTTOJUMPRIGHT ||
      this->csmStateManager->getPrevious() == CatState::LEFTTOJUMPLEFT)
   {
      return;
   }
   else
   {
      //cout<<"Transitioning..."<<endl;
   }

   //this->gGrid->intializePathing();

   this->cKitty->piPathIndex = &this->iPathIndex;

   this->state = CatState::IDLING;

   this->bCurr = this->cKitty->bBox;

   pair<Box*, Box*>* pbNewGoal = this->shHandler->calcShiniest(this->bBegin, this->bEnd);


   if(this->iPathIndex >= (int)this->bPathList->size() || this->iPathIndex <= -1)
   {
      this->iPathIndex = -1;
      this->bGoFrom = this->bCurr;
      this->bGoTo = this->bCurr;
      if(this->bCurr == this->gGrid->bStart)
      {
         this->state = CatState::WALKINGRIGHT;
         this->cKitty->setFinish(this->gGrid->bStart->bConnectList[3]->i2Position);
         this->csmStateManager->pushState(this->state);
         return;
      }
      if(shHandler->suGoal != NULL && this->bCurr == this->shHandler->suGoal->bBox)
      {
         this->csmStateManager->pushState(this->shHandler->suGoal->getPlayWith());
         return;
      }
   }
   else
   {
      this->bGoFrom = this->bCurr;
      this->bGoTo = (*this->bPathList)[iPathIndex];
   }

   // Old if: (pbGoal->first == NULL && pbNewGoal->first != NULL) || ((pbGoal->first != NULL && pbNewGoal->first != NULL) && (pbGoal->first->i2Index != pbNewGoal->first->i2Index)))//
   //Works better if unconditional //pbNewGoal->first != NULL && (pbGoal->first != pbNewGoal->first || this->bPathList->empty())) //
   if(pbNewGoal->first != NULL && 
      (pbGoal->first != pbNewGoal->first))
   {
      this->pbGoal = pbNewGoal;
      if(this->pbGoal != NULL)
      {
         /*
         if(this->bShiny->second == NULL || this->bShiny->second->suShiniestUnit == NULL) cout << "FUCK" << endl;
         else cout << "SHINIEST THING IS: " << this->bShiny->second->suShiniestUnit->sName << " SHININESS: " << this->bShiny->second->suShiniestUnit->getShininess() << endl;
         //cout<<"X:"<<this->bShiny->i2Index.x<<"Y:"<<this->bShiny->i2Index.y<<endl;*/
      }
      /*
      if(GameState::getReInitializePathing())
      {
      this->gGrid->intializePathing();
      GameState::setReInitializePathing(false);
      }
      */
      //delete this->bPathList;
      this->bPathList->clear();
      this->iPathIndex = -1;
      //s3eFree(this->bPathList);
      this->bPathList = this->pfFinder->findPath(this->bCurr, this->pbGoal->first);
      if((int)this->bPathList->size() > 1) //if a path exists do some basic initializing
      {
         this->iPathIndex = 1;
         this->bGoTo = (*this->bPathList)[1];
         this->bGoFrom = this->bCurr;
      }
      else //else set it up to not call movement
      {		  
         //this->bPathList->clear();
         this->iPathIndex = -1;
         this->bGoTo = this->bCurr;
         this->bGoFrom = this->bCurr;
      }
   }
   else
   {
      if(this->iPathIndex <= -1 || 
         (int)this->bPathList->size() <= 1 || 
         this->iPathIndex >= (int)this->bPathList->size()) //if no path exists do some basic initializing
      {
         //this->bPathList->clear();
         this->iPathIndex = -1;
         this->bGoTo = this->bCurr;
         this->bGoFrom = this->bCurr;
      }
      else //else set it up to not call movement
      {		  
         this->bGoTo = (*this->bPathList)[this->iPathIndex];
         this->bGoFrom = this->bCurr;
      }
   }
   CIwSVec2 i2LungePoint = this->lp->i2Position;
   if(this->gGrid->getBox(i2LungePoint.x, i2LungePoint.y) == this->bEnd)
   {
      i2LungePoint = this->bEnd->i2Position;
      i2LungePoint.x = i2LungePoint.x + Screen::getBOXSIZE().x/2;
      i2LungePoint.y = i2LungePoint.y + Screen::getBOXSIZE().y/2;
   }
   CIwSVec2 distTemp = CIwSVec2(0,0);
   distTemp.x = i2LungePoint.x - (this->cKitty->i2Position.x + Screen::getBOXSIZE().x/2);
   distTemp.y = i2LungePoint.y - (this->cKitty->i2Position.y + Screen::getBOXSIZE().y/2);
   float distance = sqrt(pow((float)distTemp.x, 2) + pow((float)distTemp.y, 2));
   if(this->shHandler->suGoal != NULL &&
      this->pbGoal->second != this->bEnd &&
      //((this->pbGoal->second->bIsWalkable == false)||
      //(!this->cKitty->bBox->bPlatformList.contains(this->pbGoal->second))) &&
      (this->pbGoal->second != NULL &&   //if the absolute position of the goal has been set
       this->pbGoal->second->bIsWalkable == false &&
       this->pbGoal->second == this->gGrid->getBox(i2LungePoint.x, i2LungePoint.y) &&
       (this->bIsLunging == true /*????*/ || 
       (distance  < this->fLungeDist &&           //if the target is close enough to jump at
        this->cKitty->bBox != this->pbGoal->second))))   //if the cat's box is not the box of the absolute goal    
   {      //this entire statement seems to add up to: you need to jump...or already are...
      this->doLunging(i2LungePoint);
   }
   if(!this->bIsLunging)
   {
      //cout<<"Current Cat State is "<<CatState::getState()<<endl;
      if(this->iPathIndex > -1 && this->iPathIndex < (int)this->bPathList->size())
      {
         this->doMovement();
      }
      else
      {
         //this->bPathList->clear();
         this->iPathIndex = -1;
      }
   }
   //this->debugOutput();
	if(this->state == CatState::IDLING)
		{
			//IwAssertMsg(MYAPP, false, ("About to push IDLING.."));
		}
   this->csmStateManager->pushState(this->state);
}

void CatAI::reset()
{
   IW_CALLSTACK("CatAI::reset");

   this->iPathIndex = -1;
   this->bPathList->clear_optimised();
   this->bCurr = NULL;
   this->bGoFrom = this->bBegin;
   this->bGoTo = this->bBegin;
}

void CatAI::debugOutput()
{
   IW_CALLSTACK("CatAI::debugOutput");

   cout << endl;
   cout << "CatAI Debug Output" << endl;
   cout << "Cat Poition: " << this->cKitty->bBox->i2Index.x << ", " << this->cKitty->bBox->i2Index.y << endl;
   cout << "Cat Pix: " << this->cKitty->i2Position.x << ", " << this->cKitty->i2Position.y << endl;
   cout << "BCurr: " << this->bCurr->i2Index.x << ", " << this->bCurr->i2Index.y << endl;
   cout << "BGoFrom: " << this->bGoFrom->i2Index.x << ", " << this->bGoFrom->i2Index.y << endl;
   cout << "BGoto: " << this->bGoTo->i2Index.x << ", " << this->bGoTo->i2Index.y << endl;
   cout << "BGoto Pix: " << this->bGoTo->i2Position.x << ", " << this->bGoTo->i2Position.y << endl;
	
   if(this->pbGoal != NULL)
   {
      if(this->pbGoal->first != NULL)
		{
			if(this->shHandler->suGoal != NULL)
			{	
				cout << "Goal Is: " << this->shHandler->suGoal->sName << endl;
			}
         cout << "Goal Position: " << this->pbGoal->first->i2Index.x << ", " << this->pbGoal->first->i2Index.y << endl;
		}
      if(this->pbGoal->second != NULL)
         cout << "Goal Abs Position: " << this->pbGoal->second->i2Index.x << ", " << this->pbGoal->second->i2Index.y << endl;
   }
   cout << "LaserPointer Position: " << this->lp->bBox->i2Index.x <<  ", " << this->lp->bBox->i2Index.y << endl;
   cout << "PATHLIST: " << endl;
   for(int i = 0; i < (int)this->bPathList->size(); ++i)
   {
      cout << "PathList[" << i << "]: " << (*this->bPathList)[i]->i2Index.x << ", " << (*this->bPathList)[i]->i2Index.y << endl;
   }
   cout << endl;

   /*cout << "SHINYLIST: " << endl;
   for(int i = 0; i < (int)this->suShinyList.size(); ++i)
   {
   if(suShinyList[i]->bBox != NULL)
   cout << "ShinyList[" << i <<"]: " << this->suShinyList[i]->sName << " : " << this->suShinyList[i]->bBox->i2Index.x << ", " << this->suShinyList[i]->bBox->i2Index.y << endl; 
   }
   cout << endl;*/
}

PathFinder* CatAI::getPathFinder()
{
   return this->pfFinder;
}

CatAI::~CatAI()
{
   IW_CALLSTACK("CatAI::~CatAI");

   this->bPathList->clear_optimised();
   delete this->pbGoal;
   delete this->angles;
   delete this->pfFinder;
   delete this->shHandler;
}
