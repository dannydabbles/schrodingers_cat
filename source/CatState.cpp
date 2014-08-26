//
//
//
//   Project : Schrˆdinger's cat
//   File Name : CatStates.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//
#include "CatState.h"

CatState::State CatState::csCurrent = WALKINGRIGHT;

void CatState::setState(State state)
{
   IW_CALLSTACK("CatEventt::setState");

   csCurrent = state;
}

CatState::State CatState::getState()
{
   IW_CALLSTACK("CatEventt::getState");

   return csCurrent;
}

bool CatState::isIdle()
{
   IW_CALLSTACK("CatEventt::isIdle");

   return csCurrent == IDLING;
}

bool CatState::isMoving()
{
   IW_CALLSTACK("CatEventt::isMoving");

   return csCurrent > __START_MOVEMENT_STATES__ && csCurrent < CatState::__END_MOVEMENT_STATES__;
}

bool CatState::isPlayingWithEvent()
{
   IW_CALLSTACK("CatEventt::isPlayingWithEvent");

   return csCurrent > __START_CATEVENT_STATES__ && csCurrent < CatState::__END_CATEVENT_STATES__;
}

bool CatState::isPlayingWith()
{
   IW_CALLSTACK("CatEventt::isPlayingWith");

   return csCurrent > __START_PLAYWITH_STATES__ && csCurrent < CatState::__END_PLAYWITH_STATES__;
}

bool CatState::isInterrupting()
{
   IW_CALLSTACK("CatEventt::isInterrupting");

   return csCurrent > __START_INTERRUPT_STATES__ && csCurrent < CatState::__END_INTERRUPT_STATES__;
}
