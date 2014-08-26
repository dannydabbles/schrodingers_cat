/*
*  EndOfLevelMenu.cpp
*  Kitty
*
*  Created by Sam Medalen on 5/16/11.
*  Copyright 2011 __MyCompanyName__. All rights reserved.
*
*/

#include "EndOfLevelMenu.h"

EndOfLevelMenu::EndOfLevelMenu()
{
   IW_CALLSTACK("EndOfLevelMenu::EndOfLevelMenu");


   this->goldColor.Set(236, 216, 114, 255);
   this->blackColor.Set(0, 0, 0, 255);
   this->greenColor.Set(0, 255, 0 ,255);

   this->i2Position = CIwSVec2(0, 0);
   this->i2Size = CIwSVec2(Screen::getSCREENSIZE().x, Screen::getSCREENSIZE().y);
   this->i2RegionSize = this->i2Size;
   this->i2RegionOffset = CIwSVec2(0, 0);
   this->tTextureList.push_back(ImageManager::getImage("levels_menu"));

   this->mbHitList.push_back(new NextLevelButton(this->i2Position, CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.75f) - 25, (int)(Screen::getSCREENSIZE().y * 0.8f) - 25), CIwSVec2(50, 50)));
   this->mbHitList.push_back(new ReplayButton(this->i2Position, CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.25f) - 25, (int)(Screen::getSCREENSIZE().y * 0.8f) - 25), CIwSVec2(50, 50)));
   this->mbHitList.push_back(new LevelNavigationButton(this->i2Position, CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.5f) - 25, (int)(Screen::getSCREENSIZE().y * 0.8f) - 25), CIwSVec2(50, 50), false));
   this->mMessageList = CIwArray<Message*>();

   // your current rating
   this->mRating = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.53f), (int)(Screen::getSCREENSIZE().y * 0.2f)));
   this->mRating->setSize(86, 125);
   this->mRating->setRO(0, 0);
   this->mRating->setRS(160, 224);
   this->mMessageList.push_back(this->mRating);

   // your best rating
   this->mBestRating = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.29f), (int)(Screen::getSCREENSIZE().y * 0.2f)));
   this->mBestRating->setSize(86,125);
   this->mBestRating->setRO(0,0);
   this->mBestRating->setRS(160, 224);
   this->mMessageList.push_back(this->mBestRating);


   // "Your Currrent Score"
   this->CurrentString = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.62f) - 50, (int)(Screen::getSCREENSIZE().y * 0.12f)), "lcdfont");
   this->CurrentString->setString("Current");
   this->CurrentString->setColor(this->blackColor);
   this->mMessageList.push_back(this->CurrentString);

   // "Your best Score"
   this->mBestString = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.42f) - 45, (int)(Screen::getSCREENSIZE().y * 0.12f)), "lcdfont");
   this->mBestString->setString("Best");
   this->mBestString->setColor(this->goldColor);
   this->mMessageList.push_back(this->mBestString);


   // best clockl
   this->mBestClock = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.3f) - 3, (int)(Screen::getSCREENSIZE().y * 0.62f) - 2));
   this->mBestClock->setUseTexture(true);
   this->mBestClock->setTexture("clock");
   this->mBestClock->setSize(81, 32);
   this->mBestClock->setRS(81, 32);
   this->mBestClock->setRO(0,0);
   this->mMessageList.push_back(this->mBestClock);

   // current clock
   this->mCurrentClock = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.52f) + 11, (int)(Screen::getSCREENSIZE().y * 0.62f) - 2));
   this->mCurrentClock->setUseTexture(true);
   this->mCurrentClock->setTexture("clock");
   this->mCurrentClock->setSize(81, 32);
   this->mCurrentClock->setRS(81, 32);
   this->mCurrentClock->setRO(0, 0);
   this->mMessageList.push_back(this->mCurrentClock);

   // best time
   this->mBestTime = new Message(CIwSVec2(mBestClock->getPosition().x + 4, mBestClock->getPosition().y + 7), "lcdfont");
   this->mBestTime->setColor(this->goldColor);
   this->mMessageList.push_back( this->mBestTime);

   // current time
   this->mCurrentTime = new Message(CIwSVec2(mCurrentClock->getPosition().x + 4, mCurrentClock->getPosition().y + 7), "lcdfont");
   this->mCurrentTime->setColor(this->greenColor);
   this->mMessageList.push_back( this->mCurrentTime);

   // check on current rating
   this->mCurrentCheck = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.59f), (int)(Screen::getSCREENSIZE().y * 0.5f) - 75));
   this->mCurrentCheck->setUseTexture(false);
   this->mCurrentCheck->setTexture("level_1_high");
   this->mCurrentCheck->setRS(75, 75);
   this->mCurrentCheck->setSize(75, 75);
   this->mCurrentCheck->setRO(0, 0);
   this->mMessageList.push_back(mCurrentCheck);

   // check on best rating
   this->mBestCheck = new Message(CIwSVec2((int)(Screen::getSCREENSIZE().x * 0.35f), (int)(Screen::getSCREENSIZE().y * 0.5f) - 75));
   this->mBestCheck->setUseTexture(false);
   this->mBestCheck->setTexture("level_1_high");
   this->mBestCheck->setRS(75, 75);
   this->mBestCheck->setSize(75, 75);
   this->mBestCheck->setRO(0, 0);
   this->mMessageList.push_back(mBestCheck);

   // for dimming
   this->opaqueColor.Set(0, 0, 0, 200);
   this->opaquePos = CIwSVec2(0, 0);
   this->opaqueSize = CIwSVec2(Screen::getSCREENSIZE().x, Screen::getSCREENSIZE().y);

   this->sSoundList.push_back(SoundManager::getSound("cheer"));
   this->sSoundList.push_back(SoundManager::getSound("goodtime"));

   ClassTracker::addUnit(this);
}

void EndOfLevelMenu::setWin(int e, int d, uint64 t)
{
   IW_CALLSTACK("EndOfLevelMenu::setWin");

   // find out whether best death have been acheive to deivde whether to play checks or not
   if(PlayerProfile::getDeath() <= e)
   {
      this->dispalyBestCheck = true;
   }
   else
   {
      this->dispalyBestCheck = false;
   }

   if(PlayerProfile::getCurrDeath() <= e)
   {
      this->disaplyCurrentCheck = true;
   }
   else
   {
      this->disaplyCurrentCheck = false;
   }

   // set esrb rating
   this->mRating->setUseTexture(true);
   this->mRating->setTexture(d);
   this->mBestRating->setUseTexture(true);
   this->mBestRating->setTexture(PlayerProfile::getDeath());

   stringstream ss;
   // best time caluculations
   uint64 bestTime = PlayerProfile::getTime() / 1000;
   int bestsec = (int)bestTime % 60;
   int bestmin = (int)bestTime / 60;
   if(bestmin >= 100)
   {
      bestmin = 99;
      bestsec= 59;
   }
   ss << setfill('0') << setw(2) << bestmin << ":" << setfill('0') << setw(2) << bestsec;
   this->mBestTime->setString( ss.str() );

   ss.str("");

   // current time calculateions
   uint64 currTime = PlayerProfile::getCurrTime() / 1000;
   int cursec = (int)currTime % 60;
   int curmin = (int)currTime / 60;
   if(curmin >= 100)
   {
      curmin = 99;
      cursec= 59;
   }
   ss << setfill('0') << setw(2) << curmin << ":" << setfill('0') << setw(2) << cursec;
   this->mCurrentTime->setString( ss.str() );

   // set color and play sound if besttime acheived
   if ( curmin <= bestmin &&  cursec <= bestsec )
   {
      this->CurrentString->setColor(this->goldColor);
      this->mCurrentTime->setColor(this->goldColor);
      SoundManager::playSound(this->sSoundList[1]);

   }
   else
   {
      this->CurrentString->setColor(this->greenColor);
      this->mCurrentTime->setColor(this->greenColor);
   }

   // reset various variables needed for update
   this->iTimePassed = 0;
   this->bestDeathSoundPlayed = false;
   this->mCurrentCheck->setUseTexture(false);
   this->mBestCheck->setUseTexture(false);
}

void EndOfLevelMenu::update(uint64 time)
{
   IW_CALLSTACK("EndOfLevelMenu::update");

   this->iTime = time;
   this->iTimePassed += this->iTime;

   if ( this->iTimePassed > 2000 && this->dispalyBestCheck)
   {
      this->mBestCheck->setUseTexture(true);
   }

   if (iTimePassed > 4000 && this->disaplyCurrentCheck && this->bestDeathSoundPlayed == false)
   {
       this->bestDeathSoundPlayed = true;
       SoundManager::playSound(this->sSoundList[0]);
       this->mCurrentCheck->setUseTexture(true);
   }
   UserInterface::update(this->iTime);

   if(GameState::getReset() == true)
   {
      GameState::setState(GameState::RESET);
      GameState::setReset(false);
   }
}

void EndOfLevelMenu::draw()
{
   Iw2DSetColour(this->opaqueColor);
   Iw2DFillRect(this->opaquePos, this->opaqueSize); 
   Iw2DSetColour(0xffffffff);

   UserInterface::draw();
}
