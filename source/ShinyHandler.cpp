/*
*  ShinyHandler.cpp
*  Kitty
*
*  Created by Tom Anderson on 4/27/11.
*  Copyright 2011 __MyCompanyName__. All rights reserved.
*
*/

#include "ShinyHandler.h"

ShinyHandler::ShinyHandler(Cat* cCat, CIwArray<ShinyUnit*> suShinyList)
{
   IW_CALLSTACK("ShinyHandler::ShinyHandler");

   this->cKitty = cCat;
   this->suShinyList = suShinyList;
   this->suGoal = NULL;
}

pair<Box*, Box*>* ShinyHandler::calcShiniest(Box* bStartBox, Box* bFinishBox) //Start/Finish boxes are the actual boxes 
{
   IW_CALLSTACK("ShinyHandler::calcShiniest");

   Box* bGoal = NULL;
   float fMostInteresting = 0;
   int iInterestingIndex = -1;
   this->suGoal = NULL;

   for(int i = 0; i < (int)this->suShinyList.size(); ++i)
   {
      //if(suShinyList[i]->sName.compare("laser") != 0) continue;
      float fEffectiveShininess = this->suShinyList[i]->getShininess() - this->suShinyList[i]->getTimeSpentWithCat();
      float fCatInterest = fEffectiveShininess / (this->suShinyList[i]->getDistanceFromCat(this->cKitty->i2Position) + 1);

      cout << "SHINY " << this->suShinyList[i]->sName << " IS " << fEffectiveShininess << " SHINY" << endl;
      cout << "I LIKE IT " << fCatInterest << " MUCH" << endl;
	
      if(fCatInterest > fMostInteresting)
      {
         cout << fCatInterest << " is more interesting than " << fMostInteresting << endl;
         fMostInteresting = fCatInterest;
         bGoal = this->suShinyList[i]->bBox;
         this->suGoal = suShinyList[i];

         /*
         //stops direct lunging and movement to a filled position
         if(bGoal->bIsFilled == true && iInterestingIndex != -1)
         bGoal = this->gGrid->getBox(this->gGrid->uShinyList[iInterestingIndex]->getPosition().x, this->gGrid->uShinyList[iInterestingIndex]->getPosition().y);
         else if(bGoal->bIsFilled == true)
         bGoal = NULL;
         iInterestingIndex = i;
         */
      }
   }

   ShinyUnit::setShiniestUnit(this->suGoal);

   Box* bGoal_Abs = bGoal;
   Box* bGoalTemp = bGoal;

   if(bGoal == bFinishBox) //Fixing pathing to end box
   {
      bGoal = bFinishBox->bConnectList[1];
      bGoal_Abs = bFinishBox;
      ShinyUnit::setShinyDropDownBox(bGoal);
      return new pair<Box*, Box*>(bGoal, bGoal_Abs);
   }

   if(bGoal != NULL)
   {
      //this->bShinyChange = true;
      if(!bGoal->bIsWalkable || bGoal->bIsFilled)
      {
         for(int i = 0; bGoal != NULL && i < 6;++i)
         {
            if(bGoal->i2Index.y < 0) break;
            if(bGoal->bConnectList[5] != NULL && bGoal->bConnectList[5]->bIsWalkable 
               && !bGoal->bConnectList[5]->bIsFilled)
            {
               //  cout<<"Testerific!5"<<endl;
               bGoal = bGoal->bConnectList[5];
               break;
            }
            if(bGoal->bConnectList[7] != NULL && bGoal->bConnectList[7]->bIsWalkable 
               && !bGoal->bConnectList[5]->bIsFilled)
            {
               //    cout<<"Testerific!7"<<endl;
               bGoal = bGoal->bConnectList[7];
               break;
            }
            if(bGoal->bConnectList[3] != NULL && bGoal->bConnectList[3]->bIsWalkable 
               && !bGoal->bConnectList[5]->bIsFilled)
            {
               //   cout<<"Testerific!3"<<endl;
               bGoal = bGoal->bConnectList[3];
               break;
            }
            if(bGoal->bConnectList[6] != NULL && bGoal->bConnectList[6]->bIsWalkable 
               && !bGoal->bConnectList[5]->bIsFilled)
            {
               //   cout<<"Testerific!6"<<endl;
               bGoal = bGoal->bConnectList[6];
               break;
            }
            if(bGoal->bConnectList[4] != NULL && bGoal->bConnectList[4]->bIsWalkable 
               && !bGoal->bConnectList[5]->bIsFilled)
            {
               //      cout<<"Testerific!4"<<endl;
               bGoal = bGoal->bConnectList[4];
               break;
            }
            //    cout<<"Testerific!Down"<<endl;
            bGoal = bGoal->bConnectList[5];
         }
         //if(bGoal != NULL) cout<<"X:"<<bGoal->i2Index.x<<"Y:"<<bGoal->i2Index.y<<endl;
      }
   }
   if(bGoal == NULL)
   {
      bGoal = bGoalTemp;
   }
   ShinyUnit::setShinyDropDownBox(bGoal);
   //if(bGoal != NULL)cout << "CalcShiniest: MY GOAL IS AT: " << bGoal->i2Index.x << ", " << bGoal->i2Index.y << endl;
   //if(bGoal_Abs != NULL)cout << "CalcShiniest: MY ABS GOAL IS AT: " << bGoal_Abs->i2Index.x << ", " << bGoal_Abs->i2Index.y << endl;

   //   IwAssertMsg(MYAPP, bGoal != NULL, ("YO CAT I HERD YOU LIEK NULL GOALS SO I PUT A NULL GOAL IN YER PAIR OF BOXES SO YOU CAN BREAK WHILE YOU PLAY SCHRODINGER'S CAT."));
   return new pair<Box*, Box*>(bGoal, bGoal_Abs);
}

ShinyHandler::~ShinyHandler()
{
   this->suShinyList.clear();
}
