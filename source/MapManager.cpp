//
//
//
//   Project : Schrödinger's cat
//   File Name : MapManager.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "MapManager.h"


MapManager::MapManager()
{
   IW_CALLSTACK("MapManager::MapManager");

   this->timer = 0;
   this->level = 0;
   this->bPressed = false;
   this->mCurrent = NULL;
   this->sMapNameList = CIwArray<string>();
   this->bmManager = new BackgroundManager();
   this->csManager = new CutSceneManager();
   this->fAllOutFile = fopen("map_data.txt", "w");
   this->blood = new Blood();
   this->grid = new Grid();

   ifstream fFile("all.map");

   if(fFile.good())
   {
      char buffer[1024];
      while(fFile.good())
      {
         string sLevName = "";
         fFile.getline(buffer, 1024);

         for(int i = 0; buffer[i] != '\n' && buffer[i] != '\r' && buffer[i] != 13 && buffer[i] != 0; ++i)
         {
            sLevName += buffer[i];
         }
         if(sLevName.find("world") == string::npos)
            this->sRealMapNameList.push_back(sLevName);
         this->sMapNameList.push_back(sLevName);
      }
   }
   else
   {
      IwAssertMsg(MYAPP, false, ("Error: Could Not Read 'all.map' File"));
   }
   fFile.close();
   //this->loadLevel(level);
}

MapManager::~MapManager()
{
   delete this->csManager;
   delete this->bmManager;
   delete this->blood;
   delete this->grid;

   if ( this->mCurrent != NULL)
   {
      delete this->mCurrent;
   }
}
CIwArray<string> MapManager::getList()
{
   IW_CALLSTACK("MapManager::getList");

   return this->sMapNameList;
}

void MapManager::update(uint64 time)
{
   IW_CALLSTACK("MapManager::update");

   if(GameState::getState() == GameState::RESET)
   {
      this->reset();
      GameState::setState(GameState::PLAY);
      return;
   }
   GameState::State a = GameState::getState();

   if (GameState::getState() == GameState::CUTSCENE)
   {
      this->csManager->update(time);
      return;
   }

   if(GameState::getState() != GameState::PAUSE && this->mCurrent->bDone != true)
   {
      this->bmManager->update(time);
      this->mCurrent->update(time);
   }

   if(GameState::getState() != GameState::LEVELBEATEN)
   {
      if(this->mCurrent->bDone == true)
      {
         this->nextLevel(true);
      }
   }
   if(GameState::getState() == GameState::SKIPLEVEL)
   {
      this->nextLevel(true);
   }
   s3eKeyboardUpdate();
   if(bPressed == false)
   {
      if(s3eKeyboardGetState(s3eKeyLeft) && S3E_KEY_STATE_DOWN)
      {
         this->bPressed = true;
         /*
         --this->level;
         this->bPressed = true;
         if(this->level >= 0)
         {
         PlayerProfile::setLevel(this->level);
         this->loadLevel(this->level);
         }
         else
         {
         PlayerProfile::setLevel((int)this->sMapNameList.size() - 1);
         this->level = (int)this->sMapNameList.size() - 1;
         this->loadLevel(level);
         }
         */
         this->nextLevel(false);
      }
      if(s3eKeyboardGetState(s3eKeyRight) && S3E_KEY_STATE_DOWN)
      {
         this->mCurrent->bDone = true;
         this->bPressed = true;
         /*
         ++this->level;
         if(this->level < (int)this->sMapNameList.size())
         {
         PlayerProfile::setLevel(this->level);
         this->loadLevel(this->level);
         }
         else
         {
         PlayerProfile::setLevel(0);
         this->level = 0;
         this->loadLevel(level);
         }
         */
         this->nextLevel(true);
      }
      if(s3eKeyboardGetState(s3eKeyR) && S3E_KEY_STATE_DOWN)
      {
         this->level = 0;
         this->bPressed = true;
         this->loadLevel(this->level);
      }
      if(s3eKeyboardGetState(s3eKeyD) && S3E_KEY_STATE_DOWN)
      {
         this->bPressed = true;
         GameState::setDebugging(!GameState::getDebugging());
      }
   }
   else
   {
      if(!s3eKeyboardGetState(s3eKeyLeft) && !s3eKeyboardGetState(s3eKeyRight) && !s3eKeyboardGetState(s3eKeyR) && !s3eKeyboardGetState(s3eKeyD))
      {
         this->bPressed = false;
      }
   }
}

void MapManager::reset()
{
   IW_CALLSTACK("MapManager::reset");

   this->loadLevel(this->level);
   PlayerProfile::setTime(0);
   PlayerProfile::setDeath(0);
}

void MapManager::loadLevel(int i)
{
   IW_CALLSTACK("MapManager::loadLevel");

   this->level = i;

   Map* tmp = this->mCurrent;

   ImageManager::reset();
   SoundManager::reset();
   FontManager::reset();

   if ( tmp!= NULL)
      delete tmp;

   this->mCurrent =	new Map(this->sRealMapNameList[i], this->blood, this->grid, this->fAllOutFile);
   this->bmManager->loadBackground(this->mCurrent->getBackgroundNames().first, this->mCurrent->getBackgroundNames().second);

   // for now, eventually there should be something in the first level's file that indicates the cutscene being played
   if (this->level != 0)
   {
      this->csManager->LoadCutScene(this->mCurrent->getCutSceneName());
   }
   else
   {
      this->csManager->LoadCutScene("screen");
   }
}

void MapManager::nextLevel(bool b)
{
   IW_CALLSTACK("MapManager::nextLevel");
   if(b)
      ++this->level;
   else
      --this->level;
   if(this->level < (int)this->sRealMapNameList.size() && this->level >= 0)
   {
      PlayerProfile::nextLevel(b);
      this->loadLevel(this->level);
   }
   else
   {

      if(b)
      {
         //this->level = 0;
         GameState::setState(GameState::GAMEOVER);
      }
      else
      {
         this->level = (int)this->sRealMapNameList.size() - 1;
         //PlayerProfile::setLevel(this->level);
         this->loadLevel(this->level);
      }
   }
}

void MapManager::draw()
{
   IW_CALLSTACK("MapManager::draw");

   if(GameState::getState() == GameState::CUTSCENE)
   {
      this->csManager->draw();
      return;
   }

   this->bmManager->draw();
   this->mCurrent->draw(); 
}

Map* MapManager::getMap()
{
   return this->mCurrent;
}
