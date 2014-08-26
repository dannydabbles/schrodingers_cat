//
//
//
//   Project : Schrödinger's cat
//   File Name : MainMenu.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "MainMenu.h"

MainMenu::MainMenu(): UserInterface()
{
   IW_CALLSTACK("MainMenu::MainMenu");

   this->i2Position = CIwSVec2(0, 0);
   this->i2Size = Screen::getSCREENSIZE();
   this->i2RegionSize = CIwSVec2(480, 320);
   this->iTextureIndex = -1;
   //this->tTextureList.push_back(ImageManager::getImage("main_menu")); // background manager instread
   this->f2Velocity = CIwFVec2(0.5f, 0);
   this->mbHitList.push_back(new LevelNavigationButton (this->i2Position, CIwSVec2(150,180), CIwSVec2(120,55), true));
   this->mbHitList.push_back(new CreditButton(this->i2Position, CIwSVec2(410,260), CIwSVec2(50,50), false));
   this->mbHitList.push_back(new SoundButton(this->i2Position, CIwSVec2(20, 260), CIwSVec2(50,50)));

   this->bgManager = new BackgroundManager();
   this->bgManager->loadBackground("main_menu", CIwArray<string>());
   //this stuff is the credit UI
   //this->mbHitList.push_back(new CreditButton(this->i2Position, CIwSVec2(300,30),  CIwSVec2(412,268), true) );
   //this->mbHitList.push_back(new MenuButton(this->i2Position, CIwSVec2(365,55),  CIwSVec2(50,50), -7) );

   ClassTracker::addUnit(this);
}

MainMenu::~MainMenu()
{
   delete this->bgManager;
}

/*
bool MainMenu::hit()
{
s3ePointerUpdate();

CIwSVec2 r = CIwSVec2(s3ePointerGetX(), s3ePointerGetY());
if(this->mbPlay->hit(r))
{
if(this->mbCurrent == NULL)
{
this->mbCurrent = this->mbPlay;
return false;
}
else if(this->mbCurrent == this->mbPlay)
{
this->mbCurrent = NULL;
return true;
}
}
else if(this->mbSound->hit(r))
{
if(this->mbCurrent == NULL)
{
this->mbCurrent = this->mbSound;
return false;
}
else if(this->mbCurrent == this->mbSound)
{
GameState::setSound(!GameState::getSound());
}
}
else if(this->mbInfo->hit(r))
{
if(this->mbCurrent == NULL)
{
this->mbCurrent = this->mbInfo;
return false;
}
else if(this->mbCurrent == this->mbInfo)
{
//this->mbCurrent = NULL;
//return true;
this->bMoveBack = true;
}
}
else if(this->mbBack->hit(r))
{
if(this->mbCurrent == NULL)
{
this->mbCurrent = this->mbBack;
return false;
}
else if(this->mbCurrent == this->mbBack)
{
//this->mbCurrent = NULL;
//return true;
this->bMoveForward = true;
}
}
this->mbCurrent = NULL;
return false;
}*/

/*
void MainMenu::update(uint64 time)
{
SoundManager::setMusic("Catzophrenia");
this->iTime = time;
this->iTimePassed += time;

if(GameState::getState() == GameState::GAMEMENU)
{
if (startCheck == 0)
{
this->mbCredits->i2Position.x += 180;
this->mbBack->i2Position.x += 180;
startCheck = 1;
}
if (this->bMoveBack == true && this->mbCredits->i2Position.x != 290)
{
this->mbCredits->moveLeft(this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x);
this->mbBack->moveLeft(this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x);
}
if (this->mbCredits->i2Position.x <= 290)
{
this->bMoveBack = false;
}
if (this->bMoveForward == true && this->mbCredits->i2Position.x != 481)
{
this->mbCredits->moveRight(this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x);
this->mbBack->moveRight(this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x);
}
if (this->mbCredits->i2Position.x >= 481)
{
this->bMoveForward = false;
}
}
}*/

/*
void MainMenu::draw()
{
Iw2DDrawImageRegion(this->tTextureList[this->iTextureIndex], this->i2Position, this->i2Size, this->i2RegionOffset, this->i2RegionSize);
this->mbPlay->draw();
this->mbSound->draw();
this->mbInfo->draw();
this->mbCredits->draw();
this->mbBack->draw();

if(this->mbCurrent != NULL)
this->mbCurrent->drawSelect();
else
{
this->mbPlay->draw();
this->mbSound->draw();
this->mbInfo->draw();
this->mbCredits->draw();
this->mbBack->draw();
}
}

void MainMenu::play() {

}

void MainMenu::options() {

}
*/

void MainMenu::draw()
{
   this->bgManager->draw();
   UserInterface::draw();
}
