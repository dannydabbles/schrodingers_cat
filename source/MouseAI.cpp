/*
*  MouseAI.cpp
*  Kitty
*
*  Created by Sam Medalen on 3/5/11.
*  Copyright 2011 __MyCompanyName__. All rights reserved.
*
*/

#include "MouseAI.h"

MouseAI::MouseAI(CIwArray<Mouse*> ulMouseList)
{
   IW_CALLSTACK("MouseAI::MouseAI");

   this->ulMouseList = ulMouseList;
}

void MouseAI::update(Cat * pcKitty)
{
   IW_CALLSTACK("MouseAI::update");

   for(int i = 0; i < (int)ulMouseList.size(); ++i)
   {
      if(ulMouseList[i]->getBDead() == false)
      {
         Box* tempBox = this->ulMouseList[i]->bBox;
         Box * catBox = pcKitty->bBox;
         bool btempdead = false;
         if(ulMouseList[i]->getBScared() == false)
         {
            if(ulMouseList[i]->getBMoveLeft() == true)
            {
               if(catBox == tempBox->bConnectList[7])
                  ulMouseList[i]->setBScared(true);
               else if(tempBox->bConnectList[7] != NULL && catBox == tempBox->bConnectList[7]->bConnectList[7])
                  ulMouseList[i]->setBScared(true);
            }
            else
            {
               if(catBox == tempBox->bConnectList[3])
                  ulMouseList[i]->setBScared(true);
               else if(tempBox->bConnectList[3] != NULL && catBox == tempBox->bConnectList[7]->bConnectList[3])
                  ulMouseList[i]->setBScared(true);
            }
            if(ulMouseList[i]->getBScared() == true)
               ulMouseList[i]->setBMoveLeft(!ulMouseList[i]->getBMoveLeft());
         }
         if(ulMouseList[i]->getBScared() == true)
         {
            if(ulMouseList[i]->getBMoveLeft() == true)
               btempdead =ulMouseList[i]->scaredMove(tempBox, tempBox->bConnectList[7]);
            else
               btempdead = ulMouseList[i]->scaredMove(tempBox, tempBox->bConnectList[3]);
         }
         else
            ulMouseList[i]->regularMove();
         if(catBox == tempBox)
         {
            //ulMouseList[i]->setBDead(true);
            ulMouseList[i]->bUpdate = true;
            //btempdead = true;
         }
         if(btempdead == true)
         {
            //ulMouseList[i]->setBDead(true);
            tempBox->removeUnit(ulMouseList[i]);
            ulMouseList.erase(i);
         }
      }
   }
}
