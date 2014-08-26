//
//
//
//   Project : Schrˆdinger's cat
//   File Name : CatStates.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//

#include "GameState.h"

GameState::State GameState::gsCurrent = MAINMENU;
bool GameState::bReInitializePathing = true;
bool GameState::bDebugging = false;
bool GameState::bReset = false;
bool GameState::bResume = false;

void GameState::setDebugging(bool b)
{
   IW_CALLSTACK("GameState::setDebugging");

   GameState::bDebugging = b;
}

void GameState::setReInitializePathing(bool bReInit)
{
   IW_CALLSTACK("GameState::setReInitializePathing");

   bReInitializePathing = bReInit;
}

void GameState::setReset(bool bSetReset)
{
   IW_CALLSTACK("GameState::setReset");

   GameState::bReset = bSetReset;
}

void GameState::setResume(bool bSetResume)
{
   IW_CALLSTACK("GameState::setResume");

   GameState::bResume = bSetResume;
}

void GameState::setState(GameState::State state)
{
   IW_CALLSTACK("GameState::setState");

   gsCurrent = state;
}

bool GameState::getDebugging()
{
   IW_CALLSTACK("GameState::getDebugging");

   return GameState::bDebugging;
}

bool GameState::getReInitializePathing()
{
   IW_CALLSTACK("GameState::getReInitializePathing");

   return bReInitializePathing;
}

bool GameState::getResume()
{
   IW_CALLSTACK("GameState::getResume");

   return bResume;
}

bool GameState::getReset()
{
   IW_CALLSTACK("GameState::getReset");

   return bReset;
}

GameState::State GameState::getState()
{
   IW_CALLSTACK("GameState::getState");

   return gsCurrent;
}
