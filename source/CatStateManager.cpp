//
//
//   Project : Schrödinger's cat
//   File Name : CatStateManager.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "CatStateManager.h"
#include <iostream>

using namespace std;

CatStateManager::CatStateManager()
{
   IW_CALLSTACK("CatStateManager::CatStateManager");

   CatState::setState(CatState::IDLING);
   this->csPrevious = CatState::IDLING;
   this->csNext = CatState::WALKINGRIGHT;
}

CatState::State CatStateManager::getPrevious()
{
	IW_CALLSTACK("CatEventt::getPrevious");

   return this->csPrevious;
}

CatState::State CatStateManager::getNext()
{
	IW_CALLSTACK("CatEventt::getNext");

   return this->csNext;
}

void CatStateManager::pushState(CatState::State state)
{
   IW_CALLSTACK("CatStateManager::pushState");

   if(CatState::isInterrupting() == false)
   {
      this->csPrevious = CatState::getState();
   }
   this->csNext = state;
}

void CatStateManager::update()
{
   IW_CALLSTACK("CatStateManager::update");
   if(CatState::getState() == CatState::DEAD)
   {
      //this->reset(); moved to grid
      return;
   }
  /* cout << "\nBefore:\nPrevious State: " << this->csPrevious << endl
        << "Current State: " << CatState::getState() << endl
        << "Next State: " << this->csNext << endl; */

   if(CatState::getState() == CatState::TRANSITIONING)
   {
      /*if(this->csNext != this->csPrevious || 
         this->csPrevious == CatState::JUMPINGLEFT || 
         this->csPrevious == CatState::JUMPINGRIGHT)
      {*/
         this->resolveStates();
      /*}
      else
      {
         CatState::setState(this->csNext);
      }*/
   }
  /* cout << "\nAfter:\nPrevious State: " << this->csPrevious << endl
        << "Current State: " << CatState::getState() << endl
        << "Next State: " << this->csNext << endl; */
   /*
   if(CatState::getState() == CatState::TRANSITIONING)
      IwAssertMsg(MYAPP,false, ("CatStateManager update exited with interrupt state"));
   if(this->csPrevious == CatState::TRANSITIONING)
      IwAssertMsg(MYAPP,false, ("CatStateManager update exited with previous as TRANSITIONING"));*/
}

void CatStateManager::resolveStates()
{
   IW_CALLSTACK("CatStateManager::resolveStates");

   if(this->csPrevious == CatState::IDLING)
   {
      this->idling();
   }
   else if(this->csPrevious == CatState::WALKINGLEFT)
   {
      this->walkingLeft();
   }
   else if(this->csPrevious == CatState::WALKINGRIGHT)
   {
      this->walkingRight();
   }
   else if(this->csPrevious == CatState::JUMPINGLEFT)
   {
      this->jumpingLeft();
   }
   else if(this->csPrevious == CatState::JUMPINGRIGHT)
   {
      this->jumpingRight();
   }
   else if(this->csPrevious > CatState::__START_CATEVENT_STATES__ && 
           this->csPrevious < CatState::__END_PLAYWITH_STATES__)
   {
      this->playing();
   }
   else if(this->csPrevious == CatState::IDLETOLEFT)
   {
      this->idleToLeft();
   }
   else if(this->csPrevious == CatState::IDLETORIGHT)
   {
      this->idleToRight();
   }
   else if(this->csPrevious == CatState::IDLETOPLAY)
   {
      this->idleToPlay();
   }
   else if(this->csPrevious == CatState::LEFTTOIDLE)
   {
      this->leftToIdle();
   }
   else if(this->csPrevious == CatState::LEFTTORIGHT)
   {
      this->leftToRight();
   }
   else if(this->csPrevious == CatState::LEFTTOJUMPLEFT)
   {
      this->leftToJumpLeft();
   }
   else if(this->csPrevious == CatState::LEFTTOPLAY)
   {
      this->leftToPlay();
   }
   else if(this->csPrevious == CatState::RIGHTTOIDLE)
   {
      this->rightToIdle();
   }
   else if(this->csPrevious == CatState::RIGHTTOLEFT)
   {
      this->rightToLeft();
   }
   else if(this->csPrevious == CatState::RIGHTTOJUMPRIGHT)
   {
      this->rightToJumpRight();
   }
   else if(this->csPrevious == CatState::RIGHTTOPLAY)
   {
      this->rightToPlay();
   }
   else if(this->csPrevious == CatState::JUMPLEFTTOIDLE)
   {
      this->jumpLeftToIdle();
   }
   else if(this->csPrevious == CatState::JUMPLEFTTOLEFT)
   {
      this->jumpLeftToLeft();
   }
   else if(this->csPrevious == CatState::JUMPLEFTTOPLAY)
   {
      this->jumpLeftToPlay();
   }
   else if(this->csPrevious == CatState::JUMPRIGHTTOIDLE)
   {
      this->jumpRightToIdle();
   }
   else if(this->csPrevious == CatState::JUMPRIGHTTORIGHT)
   {
      this->jumpRightToRight();
   }
   else if(this->csPrevious == CatState::JUMPRIGHTTOPLAY)
   {
      this->jumpRightToPlay();
   }
   else if(this->csPrevious == CatState::PLAYTOIDLE)
   {
      this->playToIdle();
   }
   else if(this->csPrevious == CatState::PLAYTOLEFT)
   {
      this->playToLeft();
   }
   else if(this->csPrevious == CatState::PLAYTORIGHT)
   {
      this->playToRight();
   }

   if(CatState::getState() > CatState::__START_TRANSITION_STATES__ &&
      CatState::getState() < CatState::__END_TRANSITION_STATES__)
   {
      csPrevious = CatState::getState();
   }
   if(CatState::getState() == CatState::TRANSITIONING)
      IwAssertMsg(MYAPP,false, ("CatStateManager resolveStates exited with TRANSITIONING"));
}

void CatStateManager:: idling()
{
	IW_CALLSTACK("CatStateManager::idling");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::IDLING);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::IDLETOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in IDLE fell through"));
   }
}

void CatStateManager::walkingLeft()
{
	IW_CALLSTACK("CatStateManager::walkingleft");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::LEFTTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::WALKINGLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::LEFTTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::LEFTTOJUMPLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::LEFTTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::LEFTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in LEFT fell through"));
   }
}

void CatStateManager::walkingRight()
{
	IW_CALLSTACK("CatStateManager::walkingright");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::RIGHTTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::RIGHTTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::WALKINGRIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::RIGHTTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::RIGHTTOJUMPRIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::RIGHTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in RIGHT fell through"));
   }
}

void CatStateManager::jumpingLeft()
{
	IW_CALLSTACK("CatStateManager::jumpingleft");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::JUMPLEFTTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::JUMPLEFTTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::JUMPLEFTTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      //CatState::setState(CatState::TOJUMPLEFT);
      CatState::setState(CatState::JUMPLEFTTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::JUMPLEFTTOLEFT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::JUMPLEFTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in JUMPLEFT fell through"));
   }
}

void CatStateManager::jumpingRight()
{
	IW_CALLSTACK("CatStateManager::jumpingright");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::JUMPRIGHTTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::JUMPRIGHTTORIGHT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::JUMPRIGHTTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::JUMPRIGHTTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      //CatState::setState(CatState::TOJUMPRIGHT);
      CatState::setState(CatState::JUMPRIGHTTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::JUMPRIGHTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in JUMPRIGHT fell through"));
   }
}

void CatStateManager::playing()
{
	IW_CALLSTACK("CatStateManager::playing");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::PLAYTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(this->csNext);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in *blah* fell through"));
   }
}

void CatStateManager::idleToLeft()
{
	IW_CALLSTACK("CatStateManager::idletoleft");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::LEFTTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::WALKINGLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::LEFTTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::LEFTTOJUMPLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::LEFTTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::LEFTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in IDLETOLEFT fell through"));
   }
}

void CatStateManager::idleToRight()
{
	IW_CALLSTACK("CatStateManager::idletoright");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::RIGHTTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::RIGHTTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::WALKINGRIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::RIGHTTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::JUMPINGRIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::RIGHTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in IDLETORIGHT fell through"));
   }
}

void CatStateManager::idleToPlay()
{
	IW_CALLSTACK("CatStateManager::idletoplay");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::PLAYTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(this->csNext);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in IDLETOPLAY fell through"));
   }
}

void CatStateManager::leftToIdle()
{
	IW_CALLSTACK("CatStateManager::lefttoidle");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::IDLING);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::IDLETOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in LEFTTOIDLE fell through"));
   }
}

void CatStateManager::leftToRight()
{
	IW_CALLSTACK("CatStateManager::lefttoright");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::RIGHTTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::RIGHTTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::WALKINGRIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::RIGHTTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::RIGHTTOJUMPRIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::RIGHTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in LEFTTORIGHT fell through"));
   }
}

void CatStateManager::leftToJumpLeft()
{
	IW_CALLSTACK("CatStateManager::lefttojumpleft");

   CatState::setState(CatState::JUMPINGLEFT); // I think this is causing bugs
   this->csPrevious = CatState::JUMPINGLEFT;
}

void CatStateManager::leftToPlay()
{
	IW_CALLSTACK("CatStateManager::lefttoplay");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::PLAYTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(this->csNext);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in LEFTTOPLAY fell through"));
   }
}

void CatStateManager::rightToIdle()
{
	IW_CALLSTACK("CatStateManager::righttoidle");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::IDLING);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::IDLETOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in RIGHTTOIDLE fell through"));
   }
}

void CatStateManager::rightToLeft()
{
	IW_CALLSTACK("CatStateManager::righttoleft");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::LEFTTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::WALKINGLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::LEFTTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::LEFTTOJUMPLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::LEFTTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::LEFTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in RIGHTTOLEFT fell through"));
   }
}

void CatStateManager::rightToJumpRight()
{
	IW_CALLSTACK("CatStateManager::righttojumpright");

   CatState::setState(CatState::JUMPINGRIGHT); // I think this is causing bugs
   this->csPrevious = CatState::JUMPINGRIGHT;
}

void CatStateManager::rightToPlay()
{
	IW_CALLSTACK("CatStateManager::righttoplay");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::PLAYTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(this->csNext);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in RIGHTTOPLAY fell through"));
   }
}

void CatStateManager::jumpLeftToIdle()
{
	IW_CALLSTACK("CatStateManager::jumplefttoidle");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::IDLING);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::IDLETOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in JUMPLEFTTOIDLE fell through"));
   }
}

void CatStateManager:: jumpLeftToLeft()
{
	IW_CALLSTACK("CatStateManager::jumplefttoleft");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::LEFTTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::WALKINGLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::LEFTTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::LEFTTOJUMPLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::LEFTTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::LEFTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in JUMPLEFTTOLEFT fell through"));
   }
}

void CatStateManager::jumpLeftToPlay()
{
	IW_CALLSTACK("CatStateManager::jumplefttoplay");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::PLAYTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(this->csNext);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in JUMPLEFTTOPLAY fell through"));
   }
}

void CatStateManager::jumpRightToIdle()
{
	IW_CALLSTACK("CatStateManager::jumprighttoidle");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::IDLING);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::IDLETOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in JUMPRIGHTTOIDLE fell through"));
   }
}

void CatStateManager::jumpRightToRight()
{
	IW_CALLSTACK("CatStateManager::jumprighttoright");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::RIGHTTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::RIGHTTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::WALKINGRIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::RIGHTTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::RIGHTTOJUMPRIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::RIGHTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in JUMPRIGHTTORIGHT fell through"));
   }
}

void CatStateManager::jumpRightToPlay()
{
	IW_CALLSTACK("CatStateManager::jumprighttoplay");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::PLAYTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::PLAYTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::PLAYTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(this->csNext);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in JUMPRIGHTTOPLAY fell through"));
   }
}

void CatStateManager::playToIdle()
{
	IW_CALLSTACK("CatStateManager::playtoidle");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::IDLING);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::IDLETOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::IDLETORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::IDLETOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in PLAYTOIDLE fell through"));
   }
}

void CatStateManager::playToLeft()
{
	IW_CALLSTACK("CatStateManager::playtoleft");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::LEFTTOIDLE);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::WALKINGLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::LEFTTORIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::LEFTTOJUMPLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::LEFTTORIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::LEFTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in PLAYTOLEFT fell through"));
   }
}

void CatStateManager::playToRight()
{
	IW_CALLSTACK("CatStateManager::playtoright");

   if(this->csNext == CatState::IDLING)
   {
      CatState::setState(CatState::IDLING);
   }
   else if(this->csNext == CatState::WALKINGLEFT)
   {
      CatState::setState(CatState::RIGHTTOLEFT);
   }
   else if(this->csNext == CatState::WALKINGRIGHT)
   {
      CatState::setState(CatState::WALKINGRIGHT);
   }
   else if(this->csNext == CatState::JUMPINGLEFT)
   {
      CatState::setState(CatState::RIGHTTOLEFT);
   }
   else if(this->csNext == CatState::JUMPINGRIGHT)
   {
      CatState::setState(CatState::RIGHTTOJUMPRIGHT);
   }
   else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
      this->csNext < CatState::__END_PLAYWITH_STATES__)
   {
      CatState::setState(CatState::RIGHTTOPLAY);
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("CatStateManager: Case in PLAYTORIGHT fell through"));
   }
}

void CatStateManager::reset()
{
	IW_CALLSTACK("CatStateManager::reset");

   this->csPrevious = CatState::IDLING;
   this->csNext = CatState::IDLING;
}

/* TEMPLATE:
if(this->csNext == CatState::IDLING)
{
CatState::setState(CatState::TOIDLE);
}
else if(this->csNext == CatState::WALKINGLEFT)
{
CatState::setState(CatState::TOLEFT);
}
else if(this->csNext == CatState::WALKINGRIGHT)
{
CatState::setState(CatState::TORIGHT);
}
else if(this->csNext == CatState::JUMPINGLEFT)
{
CatState::setState(CatState::TOJUMPLEFT);
}
else if(this->csNext == CatState::JUMPINGRIGHT)
{
CatState::setState(CatState::TOJUMPRIGHT);
}
else if(this->csNext > CatState::__START_CATEVENT_STATES__ && 
this->csNext < CatState::__END_PLAYWITH_STATES__)
{
CatState::setState(CatState::TOPLAY);
}
else
{
IwAssertMsg(MYAPP, false, ("CatStateManager: Case in *blah* fell through"));
}
*/
