//
//
//
//   Project : Schrödinger's cat
//   File Name : Game.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//

#include "Game.h"

Game:: Game()
{
   IW_CALLSTACK("Game");

   Screen::init(); // need to set screen resolution
   mmController = NULL;
   this->uimManager = NULL;
   // initial position must be both less than 0. If want
   // to change then must change code in grid::update() about moveObjectUpdate()
   lpFinger = new LaserPointer();
   //sState = NULL;
   bool bUpdated = false;
}

void Game::Init()
{   
   IW_CALLSTACK("Game::Init");

   mmController = new MapManager();
   //GameState::setState(GameState::MAINMENU);
   uimManager = new UserInterfaceManager(mmController->getList());
   //if(GameState::getDebugging() == true)
   //PlayerProfile::setProfile(mmController->getList());
   //else
   PlayerProfile::readProfile(mmController->getList());
   PlayerProfile::writeProfile();
}

void Game::ShutDown()
{
   IW_CALLSTACK("Game::ShutDown");

   delete uimManager;
   delete mmController;
   delete lpFinger;

   ClassTracker::print();
}

void Game::Update(uint64 time)
{
   IW_CALLSTACK("Game::Update");

   bool tempcheck = this->uimManager->update(time);

   if(GameState::getState() == GameState::PLAY || GameState::getState() == GameState::CUTSCENE || GameState::getState() == GameState::SKIPLEVEL)
   {
      this->bUpdated = false;
      mmController->update(time);
   }
   else if(GameState::getState() == GameState::RESET)
   {
      this->mmController->reset();
   }
   else if(GameState::getState() == GameState::LEVELNAVIGATION)
   {
      if(tempcheck == true)
      {
         //mmController->loadLevel(this->uimManager->getLevel());
         mmController->loadLevel(PlayerProfile::getLevel());
         GameState::setState(GameState::PLAY);

         // if first level
         //if(this->uimManager->getLevel() == 0)
         if(PlayerProfile::getLevel() == 0)
         {
            GameState::setState(GameState::CUTSCENE);
         }
      }
   }

   if((GameState::getState() == GameState::LEVELBEATEN || GameState::getState() == GameState::GAMEOVER) && this->bUpdated == false)
   {
      this->bUpdated = true;
      this->uimManager->setWin(this->mmController->getMap()->getExpected(),this->mmController->getMap()->getDeaths(), this->mmController->getMap()->getTime());
   }
}

void Game::Draw()
{
   IW_CALLSTACK("Game::Draw");

   if(GameState::getState() != GameState::LEVELNAVIGATION  && GameState::getState() != GameState::PAGELEFT && 
      GameState::getState() != GameState::PAGERIGHT && GameState::getState() != GameState::MAINMENU && 
      GameState::getState() != GameState::CREDITMENU && GameState::getState() != GameState::CREDITMENUBACK)
   {
      mmController->draw();
   }
   this->uimManager->draw();

   Iw2DFinishDrawing();
   IwGxFlush();
   IwGxSwapBuffers();
   IwGxSetSortMode(IW_GX_SORT_BY_SLOT);

}
