//
//
//
//   Project : Schrödinger's cat
//   File Name : UserInterfaceManager.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "UserInterfaceManager.h"

UserInterfaceManager::UserInterfaceManager(CIwArray<string> theLevels)
{
   IW_CALLSTACK("UserInterfaceManager::UserInterfaceManager");

   this->gmMenu = new GameMenu();
   this->pmMenu = new PauseMenu();
   this->lnMenu = new LevelNavigation(theLevels);
   this->mmMenu = new MainMenu();
   this->emMenu = new EndOfLevelMenu();
   this->cmMenu = new CreditMenu();
   this->fmMenu = new FinishedGameMenu();
}

UserInterfaceManager::~UserInterfaceManager()
{
   IW_CALLSTACK("UserInterfaceManager::~UserInterfaceManager");

   delete this->gmMenu;
   delete this->pmMenu;
   delete this->lnMenu;
   delete this->mmMenu;
   delete this->emMenu;
   delete this->cmMenu;
}

bool UserInterfaceManager::update(uint64 time)
{
   IW_CALLSTACK("UserInterfaceManager::update");

   if(GameState::getState() == GameState::MAINMENU)
   {
      SoundManager::setMusic("Catzophrenia");
      this->mmMenu->update(time);
   }
   else if(GameState::getState() == GameState::CREDITMENU || GameState::getState() == GameState::CREDITMENUBACK)
   {
      this->cmMenu->update(time);
   }
   else if(GameState::getState() == GameState::PLAY)
   {
      this->gmMenu->update(time);
   }
   else if(GameState::getState() == GameState::PAUSE || GameState::getState() == GameState::LEVELNAVIGATION)
   {
      this->pmMenu->update(time);
   }
   else if(GameState::getState() == GameState::LEVELBEATEN)
   {
      this->emMenu->update(time);
   }
   else if(GameState::getState() == GameState::GAMEOVER)
   {
      this->fmMenu->update(time);
   }
   if(GameState::getState() == GameState::LEVELNAVIGATION || 
      GameState::getState() == GameState::PAGELEFT || 
      GameState::getState() == GameState::PAGERIGHT)
   {
      return this->lnMenu->update(time, false);
   }
   return false;
}

void UserInterfaceManager::draw()
{
   IW_CALLSTACK("UserInterfaceManager::draw");

   if(GameState::getState() == GameState::MAINMENU)
   {
      this->mmMenu->draw();
   }
   else if(GameState::getState() == GameState::CREDITMENU || GameState::getState() == GameState::CREDITMENUBACK)
   {
      this->mmMenu->draw();
      this->cmMenu->draw();
   }
   else if(GameState::getState() == GameState::PLAY)
   {
      this->gmMenu->draw();
   }
   else if(GameState::getState() == GameState::PAUSE)
   {
      //this->gmMenu->draw();
      this->pmMenu->draw();
   }
   else if(GameState::getState() == GameState::GAMEOVER)
   {
      this->fmMenu->draw();
   }
   else if(GameState::getState() == GameState::LEVELNAVIGATION ||
      GameState::getState() == GameState::PAGELEFT        || 
      GameState::getState() == GameState::PAGERIGHT)
   {
      this->lnMenu->draw();
   }
   else if(GameState::getState() == GameState::LEVELBEATEN)
   {
      //this->gmMenu->draw();  //Show score and pause button
      this->emMenu->draw();
   }
}

void UserInterfaceManager::reset()
{
   IW_CALLSTACK("UserInterfaceManager::reset");
}

int UserInterfaceManager::getLevel()
{
   IW_CALLSTACK("UserInterfaceManager::getLevel");

   return this->lnMenu->getLevel();
}

void UserInterfaceManager::setWin(int e, int d, uint64 t)
{
   IW_CALLSTACK("UserInterfaceManager::setWin");

   this->emMenu->setWin(e,d,t);
   this->fmMenu->setWin();
}

void UserInterfaceManager::resetLevel()
{
   IW_CALLSTACK("UserInterfaceManager::resetLevel");

   //this->pmMenu = new PauseMenu();
   //this->pbButton = new PauseButton();
}
