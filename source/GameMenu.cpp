//
//
//
//   Project : Schrödinger's cat
//   File Name : GameMenu.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "GameMenu.h"

#define CLOCK 0
#define TIME 1
#define DEATH_COUNT 2
#define LETTER_X 3
#define CAT_ICON 4
#define SKIP_BUTTON 1

GameMenu::GameMenu(): UserInterface()
{
   IW_CALLSTACK("GameMenu::GameMenu");

   this->mbHitList.push_back(new PauseButton());
   this->mbHitList.push_back(new SkipLevelButton(this->i2Position, CIwSVec2(Screen::getSCREENSIZE().x - Screen::getBOXSIZE().x, 0), CIwSVec2(Screen::getBOXSIZE().x, Screen::getBOXSIZE().y)));
   this->mMessageList = CIwArray<Message*>();

   CIwColour c;

   this->mMessageList.push_back(new Message( CIwSVec2( 0 , Screen::getSCREENSIZE().y * 0.905f ) ) );
   this->mMessageList[CLOCK]->setUseTexture(true);
   this->mMessageList[CLOCK]->setTexture("clock");
   this->mMessageList[CLOCK]->setSize(81, 32);
   this->mMessageList[CLOCK]->setRS(81, 32);
   this->mMessageList[CLOCK]->setRO(0,0);

   this->mMessageList.push_back( new Message( CIwSVec2((int) Screen::getSCREENSIZE().x * 0.01f, (int) Screen::getSCREENSIZE().y * 0.93f), "lcdfont") ); //time
   c.Set(0,255, 0 ,255);
   this->mMessageList[TIME]->setColor(c);

   this->mMessageList.push_back(new Message(CIwSVec2( Screen::getSCREENSIZE().x * 0.95f, Screen::getSCREENSIZE().y * 0.89f),"font_huge")); //deaths
   this->mMessageList.push_back(new Message(CIwSVec2( Screen::getSCREENSIZE().x * 0.90f, Screen::getSCREENSIZE().y * 0.88f), "font_huge"));
   this->mMessageList[LETTER_X]->setString("x");

   this->mMessageList.push_back(new Message(CIwSVec2(0,0))); // this is the dead cat icon mofo
   this->mMessageList[CAT_ICON]->setUseTexture(true);
   this->mMessageList[CAT_ICON]->setTexture("deadcat1");
   this->mMessageList[CAT_ICON]->setRS(32, 32);
   this->mMessageList[CAT_ICON]->setSize(32, 32);
   this->mMessageList[CAT_ICON]->setRO(0, 0);
   this->mMessageList[CAT_ICON]->setPosition(CIwSVec2(this->mMessageList[LETTER_X]->getPosition().x - this->mMessageList[CAT_ICON]->getSize().x * 1.2f,  this->mMessageList[DEATH_COUNT]->getPosition().y + Screen::getBOXSIZE().y * 0.1f));

   ClassTracker::addUnit(this);
}

void GameMenu::draw()
{
   IW_CALLSTACK("GameMenu::draw");

   uint64 time = PlayerProfile::getCurrTime() / 1000;

   int sec = (int)time % 60;
   int min = (int)time / 60;

   if(min >= 100)
   {
      min = 99;
      sec= 59;
   }
   this->ssHUD << setfill('0') << setw(2) << min << ":" << setfill('0') << setw(2) << sec;
   this->mMessageList[TIME]->setString(this->ssHUD.str());
   this->ssHUD.str("");

   if(PlayerProfile::getCurrDeath() == 1000)
   {
	   this->mMessageList[DEATH_COUNT]->setPosition( CIwSVec2(Screen::getSCREENSIZE().x * 0.80f, this->mMessageList[DEATH_COUNT]->getPosition().y));
      this->mMessageList[LETTER_X]->setPosition(  CIwSVec2(Screen::getSCREENSIZE().x * 0.75f, this->mMessageList[LETTER_X]->getPosition().y));
      this->mMessageList[CAT_ICON]->setPosition( CIwSVec2(this->mMessageList[DEATH_COUNT]->getPosition().x - this->mMessageList[CAT_ICON]->getSize().x * 1.2f,  this->mMessageList[DEATH_COUNT]->getPosition().y + Screen::getBOXSIZE().y * 0.2f));
   }
   else if (PlayerProfile::getCurrDeath() == 100)
   {
      this->mMessageList[DEATH_COUNT]->setPosition((CIwSVec2(Screen::getSCREENSIZE().x * 0.85f, this->mMessageList[DEATH_COUNT]->getPosition().y)));
      this->mMessageList[LETTER_X]->setPosition(CIwSVec2(Screen::getSCREENSIZE().x * 0.80f, this->mMessageList[LETTER_X]->getPosition().y));
      this->mMessageList[CAT_ICON]->setPosition( CIwSVec2(this->mMessageList[DEATH_COUNT]->getPosition().x - this->mMessageList[CAT_ICON]->getSize().x * 1.2f,  this->mMessageList[DEATH_COUNT]->getPosition().y + Screen::getBOXSIZE().y * 0.2f));
   }
   else if(PlayerProfile::getCurrDeath() == 10)
   {
      this->mMessageList[DEATH_COUNT]->setPosition((CIwSVec2(Screen::getSCREENSIZE().x * 0.90f, this->mMessageList[DEATH_COUNT]->getPosition().y)));
      this->mMessageList[LETTER_X]->setPosition(CIwSVec2(Screen::getSCREENSIZE().x * 0.85f, this->mMessageList[LETTER_X]->getPosition().y));
      this->mMessageList[CAT_ICON]->setPosition( CIwSVec2(this->mMessageList[DEATH_COUNT]->getPosition().x - this->mMessageList[LETTER_X]->getSize().x * 1.2f,  this->mMessageList[DEATH_COUNT]->getPosition().y + Screen::getBOXSIZE().y * 0.2f));
   }
   this->ssHUD << "" << PlayerProfile::getCurrDeath();
   this->mMessageList[DEATH_COUNT]->setString(this->ssHUD.str());
   this->ssHUD.str("");

   for(int i = 0; i < (int)this->mbHitList.size(); ++i)
   {
      if(i == SKIP_BUTTON && PlayerProfile::getCurrLevel() != 0)
      {
         continue;
      }
      this->mbHitList[i]->draw();
   }

   for(int i = 0; i < (int)this->mMessageList.size(); ++i)
   {
      this->mMessageList[i]->draw();
   }
}
