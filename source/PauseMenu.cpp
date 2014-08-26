//
//
//
//   Project : Schrödinger's cat
//   File Name : PauseMenu.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "PauseMenu.h"

PauseMenu::PauseMenu(): UserInterface()
{
   IW_CALLSTACK("PauseMenu::PauseMenu");

   this->tTextureList.push_back(ImageManager::getImage("pause_menu"));
   this->i2Size = CIwSVec2((int)(Screen::getBOXSIZE().x * 3.2f), Screen::getBOXSIZE().y * 10);
   this->i2RegionSize = CIwSVec2(164, 320);
   this->i2RegionOffset = CIwSVec2(0, 0);
   this->i2Position = CIwSVec2(-this->i2Size.x, 0);
   this->f2AbsPosition = CIwFVec2((float)this->i2Position.x, (float)this->i2Position.y);
   this->iTextureIndex = 0;
   this->f2Velocity = CIwFVec2(0.6f, 0.0f);

   this->mbHitList.push_back(new ResumeButton(this->i2Position, CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.05f), 45), CIwSVec2(50, 50)));
   this->mbHitList.push_back(new ReplayButton(this->i2Position, CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.05f), 115), CIwSVec2(50, 50)));
   this->mbHitList.push_back(new LevelNavigationButton (this->i2Position, CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.05f), 180), CIwSVec2(50, 50), false));
   this->mbHitList.push_back(new SoundButton(this->i2Position, CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.05f), 250),CIwSVec2(50, 50)));
   this->mMessageList.push_back(new Message(this->i2Position,"torrid"));

   CIwColour color;
   color.Set(236, 216, 114, 255);

   
  // the message arent pushed onto a list
 //becuase for some reason setPoistion is called on all messages
   // be sure to call explicity
   this->mHighScore = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.47f), (int)(Screen::getSCREENSIZE().y * 0.2f)), "lcdfont");
   this->mHighScore->setString("High Score");
   this->mHighScore->setColor(color);

   this->mHighScoreDeath = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.5f), (int)(Screen::getSCREENSIZE().y * 0.42f)),  "lcdfont");
   this->mHighScoreDeath->setColor(color);

   this->mX = new Message(CIwSVec2(this->mHighScoreDeath->getPosition().x - (int)(Screen::getBOXSIZE().x * 0.5f), (int)(Screen::getSCREENSIZE().y * 0.42f)), "lcdfont");
   this->mX->setString("x");
   this->mX->setColor(color);

   this->mDeadCat = new Message(CIwSVec2(this->mX->getPosition().x - (int)(Screen::getBOXSIZE().x * 1.2f), (int)(Screen::getSCREENSIZE().y * 0.4f)));
   this->mDeadCat->setUseTexture(true);
   this->mDeadCat->setTexture("deadcat1");
   this->mDeadCat->setRS(32, 32);
   this->mDeadCat->setSize(32, 32);
   this->mDeadCat->setRO(0, 0);

   this->mClock = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.7f), (int)(Screen::getSCREENSIZE().y * 0.39f)));
   this->mClock->setUseTexture(true);
   this->mClock->setTexture("clock");
   this->mClock->setRS(81, 32);
   this->mClock->setSize(81, 32);
   this->mClock->setRO(0, 0);
 

   this->mHighScoreTime = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.71f), (int)(Screen::getSCREENSIZE().y * 0.41f)), "lcdfont");
   this->mHighScoreTime->setColor(color);
   
   this->opaqueColor.Set(0, 0, 0, 200);
   this->opaquePos = CIwSVec2(0, 0);
   this->opaqueSize = CIwSVec2(Screen::getSCREENSIZE().x, Screen::getSCREENSIZE().y);

   ClassTracker::addUnit(this);
}

// this deconstructor is different than others becauye the message arent pushed onto a list
//becuase for some reason setPoistion is called on all messages
PauseMenu::~PauseMenu()
{
   delete this->mHighScore;
   delete this->mHighScoreDeath;
   delete this->mDeadCat;
   delete this->mX;
   delete this->mHighScoreTime;
   delete this->mClock;
}

void PauseMenu::update(uint64 time)
{
   IW_CALLSTACK("PauseMenu::update");

   UserInterface::update(time);
   stringstream ss;
   int world = PlayerProfile::getWorld() +1;
   int level = PlayerProfile::getCurrLevel();

   if(PlayerProfile::getCurrLevel() != 0)
      ss << " lvl: "<<world<<"-"<<level;
   else
      ss << " Tutorial";
   this->mMessageList[0]->setString(ss.str());

   ss.str("");
   ss << PlayerProfile::getDeath();
   this->mHighScoreDeath->setString(ss.str());


   ss.str("");
   uint64 bestTime = PlayerProfile::getTime() / 1000;

   int sec = (int)bestTime % 60;
   int min = (int)bestTime / 60;

   if(min >= 100)
   {
      min = 99;
      sec= 59;
   }
   ss<< setfill('0') << setw(2) << min << ":" << setfill('0') << setw(2) << sec;
   this->mHighScoreTime->setString( ss.str() );
   


   if(GameState::getReset() == true || GameState::getResume() == true || GameState::getState() == GameState::LEVELNAVIGATION)
   {
      this->f2AbsPosition.x -= this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
      this->i2Position.x = (int)this->f2AbsPosition.x;

      if(this->i2Position.x <= (int)(-1.5f * i2Size.x)) //To get menu completely off screen
      {
         if(GameState::getReset() == true)
         {
            GameState::setState(GameState::RESET);
            GameState::setReset(false);
         }
         else if(GameState::getResume() == true)
         {
            GameState::setState(GameState::PLAY);
            GameState::setResume(false);
         }
         this->i2Position.x = -i2Size.x;
         this->f2AbsPosition.x = (float)this->i2Position.x;
      }

      if(this->i2Position.x > 0)
      {
         this->i2Position.x = 0;
         this->f2AbsPosition.x = (float)this->i2Position.x;
      }
   }
   else
   {
      this->f2AbsPosition.x += this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
      this->i2Position.x = (int)this->f2AbsPosition.x;

      if(this->i2Position.x >= 0)
      {
         this->i2Position.x = 0;
         this->f2AbsPosition.x = (float)this->i2Position.x;
      }
   }

   for(int i = 0; i < (int)this->mbHitList.size(); ++i)
   {
      this->mbHitList[i]->setPosition(this->i2Position);
   }
   for(int i = 0; i < (int)this->mMessageList.size(); ++i)
   {
      this->mMessageList[i]->setPosition(this->i2Position);
   }
}

void PauseMenu::draw()
{
   Iw2DSetColour(this->opaqueColor);
   Iw2DFillRect(this->opaquePos, this->opaqueSize); 
   Iw2DSetColour(0xffffffff);

   if(PlayerProfile::getTime() != 0)
   {
      this->mHighScore->draw();
      this->mHighScoreDeath->draw();
      this->mX->draw();
      this->mDeadCat->draw();
      this->mClock->draw();
      this->mHighScoreTime->draw();
   }
   UserInterface::draw();
}
