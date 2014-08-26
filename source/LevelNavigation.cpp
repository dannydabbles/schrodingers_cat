//
//
//
//   Project : Schrödinger's cat
//   File Name : LevelNavigation.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "LevelNavigation.h"

LevelNavigation::LevelNavigation(CIwArray<string> theLevels): UserInterface() 
{
   IW_CALLSTACK("LevelNavigation::LevelNavigation");
   this->firstTut = false;
   this->mapNames = theLevels;
   this->page = 0;
   this->levelsPerPage = 12;
   this->iLevel = 0;
   this->totalLevels = mapNames.size();
   this->i2Position = CIwSVec2(0, 0);
   this->iTextureIndex = 0;
   this->tTextureList.push_back(ImageManager::getImage("levels_menu"));
   this->tTextureList.push_back(ImageManager::getImage("kittylock"));
   this->tTextureList.push_back(ImageManager::getImage("level_1_high"));
   this->i2Size = Screen::getSCREENSIZE();
   this->i2RegionSize = CIwSVec2(480, 320);
   this->levelButtonList = CIwArray<CIwArray<CIwArray<LevelButton*> > >();

   this->bgManager = new BackgroundManager();
   this->bgManager->loadBackground(this->page);

   this->numberOfPages = (float)this->totalLevels / (float)this->levelsPerPage;
   int inumberOfPages = this->totalLevels / this->levelsPerPage;
   int itemp = (int)numberOfPages;

   if(itemp != inumberOfPages)
   {
      this->numberOfPages += 1;
   }
   this->iWorld = 0;
   this->iWorldLevel = 0;
   this->worldPage = 0;
   this->numberOfPages = 0;


   int pageLevelCount = 0;
   this->firstTut = false;
   int tutorialCount = -1;
   int levelCount = 0;
   int levelsOnScreen = 0;
   CIwArray<LevelButton*> tempList = CIwArray<LevelButton*>();
   CIwArray<CIwArray<LevelButton*> > listtempList = CIwArray<CIwArray<LevelButton*> >();
   for(int i = 0; i < totalLevels; ++i,++levelCount)
   {
	   if((int)tempList.size() == levelsPerPage && this->mapNames[i].find("world") == string::npos)
	   {
		   listtempList.push_back(tempList);
		   tempList.clear();
		   pageLevelCount = 0;
		   this->firstTut = false;
		   this->numberOfPages++;
	   }
      if(this->mapNames[i].find("t_") != string::npos)
      {
         if(this->firstTut == false)
         {
            tempList.push_back(new LevelButton(this->i2Position, CIwSVec2(85 + (levelsOnScreen%4 * 77), 45 + ((levelsOnScreen/4)%3 * 77)), CIwSVec2(75,75), 0, levelCount));
            this->firstTut = true;
            pageLevelCount++;
            levelsOnScreen++;
         }
         ++tutorialCount;
      }
      else if(this->mapNames[i].find("world") == string::npos)
      {
         this->firstTut = false;
         pageLevelCount++;
         tempList.push_back(new LevelButton(this->i2Position, CIwSVec2(85 + (levelsOnScreen%4 * 77), 45 + ((levelsOnScreen/4)%3 * 77)), CIwSVec2(75,75),  levelCount - tutorialCount, levelCount) );			
         levelsOnScreen++;
      }
      else
      {
         listtempList.push_back(tempList);
         this->levelButtonList.push_back(listtempList);
         tempList.clear();
         listtempList.clear();
         pageLevelCount = 0;
         levelCount = -1;
         tutorialCount = -1;
         levelsOnScreen = 0;
         this->numberOfPages++;
		  continue;
      }

   }
   //this->levelButtonList.push_back(tempList);
   this->numberOfPages = this->numberOfPages;
   for(int i = 0; i <(int)this->levelButtonList.size();++i)
   {
      for(int j = 0;j < (int)this->levelButtonList[i].size();++j)
      {
         for(int k = 0; k < (int)this->levelButtonList[i][j].size();++k)
         {
            cout<<i<<"  "<<j<<"  "<<k<<"  "<<this->levelButtonList[i][j][k]->arrayIndex<<endl;
         }
      }
   }
   /*
   this->numberOfPages = 0;


   int pageLevelCount = 0;
   this->firstTut = false;
   int tutorialCount = -1;
   int levelCount = 0;
   int levelsOnScreen = 0;
   CIwArray<LevelButton*> tempList = CIwArray<LevelButton*>();
   for(int i = 0; i < totalLevels; ++i,++levelCount)
   {
   if(this->mapNames[i].find("t_") != string::npos)
   {
   if(this->firstTut == false)
   {
   tempList.push_back(new LevelButton(this->i2Position, CIwSVec2(85 + (levelsOnScreen%4 * 77), 40 + ((levelsOnScreen/4)%3 * 77)), CIwSVec2(75,75), 0,i));
   this->firstTut = true;
   pageLevelCount++;
   levelsOnScreen++;
   }
   ++tutorialCount;
   }
   else
   {
   this->firstTut = false;
   pageLevelCount++;
   tempList.push_back(new LevelButton(this->i2Position, CIwSVec2(85 + (levelsOnScreen%4 * 77), 40 + ((levelsOnScreen/4)%3 * 77)), CIwSVec2(75,75),  levelCount - tutorialCount, i) );			
   levelsOnScreen++;
   }
   if(tempList.size() == levelsPerPage )
   {
   this->levelButtonList.push_back(tempList);
   tempList.clear();
   pageLevelCount = 0;
   this->firstTut = false;
   this->numberOfPages++;
   }
   }
   this->levelButtonList.push_back(tempList);
   this->numberOfPages++;
   */
   // need to do special cases for first and last pages. Make three differnt UI's first page, middle page, last page
   this->back = new ArrowButton(this->i2Position, CIwSVec2(15, 260), CIwSVec2(50, 50), false);
   this->mainMenu = new MainMenuButton(this->i2Position, CIwSVec2(15, 260), CIwSVec2(50, 50)) ;
   this->foward = new ArrowButton(this->i2Position, CIwSVec2(405, 260), CIwSVec2(50, 50), true);
   this->mbHitList.push_back(this->foward); 
   this->mbHitList.push_back(this->mainMenu);
}

LevelNavigation::~LevelNavigation()
{
   //delete bgManager;
   //for ( int i = 0; i < (int)levelButtonList.size(); ++i)
   //{
   //   for ( int j = 0; j < (int)levelButtonList[i].size(); ++j)
   //   {
   //         LevelButton * temp = levelButtonList[i][j];
   //         delete temp;
   //   }
   //}
   this->levelButtonList.clear_optimised();
}

bool LevelNavigation::update(uint64 time, bool update)
{
   IW_CALLSTACK("LevelNavigation::update");

   this->iTime = time;
   this->iTimePassed += this->iTime;
   s3ePointerUpdate();
   s3ePointerGetState(S3E_POINTER_BUTTON_SELECT);
   CIwSVec2 touch = CIwSVec2(s3ePointerGetX(), s3ePointerGetY()); 

   if(GameState::getState() == GameState::PAGELEFT)
   {
      --this->page;
      --this->worldPage;
      if(this->worldPage < 0 && this->page > -1)
      {
         --this->iWorld;
         this->worldPage = this->levelButtonList[this->iWorld].size() - 1;
      }
      GameState::setState(GameState::LEVELNAVIGATION);
      if ( this->page == 0)
      {
         this->mbHitList.clear();
         this->mbHitList.push_back(this->mainMenu);
         this->mbHitList.push_back(this->foward);

      }
      else
      {
         this->mbHitList.clear();
         this->mbHitList.push_back(this->back);
         this->mbHitList.push_back(this->foward);
      }

      this->bgManager->loadBackground(this->iWorld);

   }
   else if(GameState::getState() == GameState::PAGERIGHT)
   {
      ++this->page;
      ++this->worldPage;
      if(this->worldPage >= (int)this->levelButtonList[this->iWorld].size())
      {
         this->worldPage = 0;
         this->iWorld ++;
      }
      GameState::setState(GameState::LEVELNAVIGATION);
      if(this->page >= this->numberOfPages - 1)
      {
         this->mbHitList.clear();
         this->mbHitList.push_back(this->back);
      }
      else
      {
         this->mbHitList.clear();
         this->mbHitList.push_back(this->back);
         this->mbHitList.push_back(this->foward);
      }

      this->bgManager->loadBackground(this->iWorld);
   }
   this->bgManager->update(time);
   UserInterface::update(time);

   for(int i = 0; i < (int)this->levelButtonList[this->iWorld][this->worldPage].size(); ++i)
   {
      this->levelButtonList[this->iWorld][this->worldPage][i]->setPosition(this->i2Position);

      this->levelButtonList[this->iWorld][this->worldPage][i]->bUpdate = this->levelButtonList[this->iWorld][this->worldPage][i]->hit(touch);
      if(PlayerProfile::getLock(this->iWorld,this->levelButtonList[this->iWorld][this->worldPage][i]->arrayIndex) != 1 || GameState::getDebugging() == true)
      {
         if(this->levelButtonList[this->iWorld][this->worldPage][i]->update(time, false))
         {
            this->iLevel = this->levelButtonList[this->iWorld][this->worldPage][i]->arrayIndex;
            PlayerProfile::setLevel(this->iWorld,this->iLevel);
            return true;
         }
      }
   }
   return false;
}

void LevelNavigation::draw()
{
   IW_CALLSTACK("LevelNavigation::draw");

   this->bgManager->draw();

   UserInterface::draw();
   for(int i = 0; i < (int)this->levelButtonList[this->iWorld][this->worldPage].size(); ++i)
   {
      if(PlayerProfile::getLock(this->iWorld,this->levelButtonList[this->iWorld][this->worldPage][i]->arrayIndex) != 1 || GameState::getDebugging() == true)
      {
         LevelButton* tempB = this->levelButtonList[this->iWorld][this->worldPage][i];
         this->levelButtonList[this->iWorld][this->worldPage][i]->draw();
         // if satisfied esrb glob butt behind button
         if(PlayerProfile::getLock(this->iWorld,this->levelButtonList[this->iWorld][this->worldPage][i]->arrayIndex) == 2)
         {
            Iw2DDrawImageRegion(this->tTextureList[2], tempB->getPosition(), tempB->getSize(), tempB->getRO(), tempB->getRS());
         }
      }
      else 
      {
         LevelButton* tempB = this->levelButtonList[this->iWorld][this->worldPage][i];
         Iw2DDrawImageRegion(this->tTextureList[1], tempB->getPosition(), tempB->getSize(), tempB->getRO(), tempB->getRS());
      }
   }
}

int LevelNavigation::getLevel()
{
   IW_CALLSTACK("LevelNavigation::getLevel");

   return this->iLevel;
}
