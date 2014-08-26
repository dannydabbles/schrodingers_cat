//
//
//
//   Project : Schrödinger's cat
//   File Name : UserInterface.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "UserInterface.h"

UserInterface::UserInterface(): Unit()
{
   IW_CALLSTACK("UserInterface::UserInterface");

   this->mbHitList = CIwArray<MenuButton*>();
   this->mMessageList = CIwArray<Message*>();
   this->i2RegionOffset = CIwSVec2(0, 0);
   this->sName = "UI";
}

UserInterface::~UserInterface()
{
   IW_CALLSTACK("UserInterface::~UserInterface");

   for ( int i = 0; i < (int)this->mbHitList.size(); ++i)
   {
      MenuButton * b = this->mbHitList[i];

      if ( b->sName.compare("arrowbutton") == 0 )
      {
         ArrowButton * ab = dynamic_cast<ArrowButton *>(b);
         delete ab;
      }
      else if ( b->sName.compare("creditbutton") == 0 )
      {
         CreditButton * cb = dynamic_cast<CreditButton *>(b);
         delete cb;
      }
      else if ( b->sName.compare("levelbutton") == 0 )
      {
         LevelButton * lb = dynamic_cast<LevelButton *>(b);
         delete lb;
      }
      else if ( b->sName.compare("levelnavigationbutton") == 0 )
      {
         LevelNavigationButton * lnb = dynamic_cast<LevelNavigationButton *>(b);
         delete lnb;
      }
      else if ( b->sName.compare("mainmenubutton") == 0 )
      {
         MainMenuButton * cb = dynamic_cast<MainMenuButton *>(b);
         delete cb;
      }
      else if ( b->sName.compare("nextlevelbutton") == 0 )
      {
         NextLevelButton * cb = dynamic_cast<NextLevelButton *>(b);
         delete cb;
      }
      else if ( b->sName.compare("pausebutton") == 0 )
      {
         PauseButton * cb = dynamic_cast<PauseButton *>(b);
         delete cb;
      }
      else if ( b->sName.compare("replaybutton") == 0 )
      {
         ReplayButton * cb = dynamic_cast<ReplayButton *>(b);
         delete cb;
      }

      else if ( b->sName.compare("resumebutton") == 0 )
      {
         ResumeButton * cb = dynamic_cast<ResumeButton *>(b);
         delete cb;
      }
      else if ( b->sName.compare("soundbutton") == 0 )
      {
         SoundButton * cb = dynamic_cast<SoundButton *>(b);
         delete cb;
      }
      else
      {
         IwAssertMsg(MYAPP, false, ("Menubutton deconstruct %s unaccounted", b->sName));
      }


   }

   for ( int i = 0; i < (int)this->mMessageList.size(); ++i)
   {
      Message * m = this->mMessageList[i];
      delete m;
   }

   this->mbHitList.clear_optimised();
   this->mMessageList.clear_optimised();
}

void UserInterface::update(uint64 time)
{
   IW_CALLSTACK("UserInterface::update");

   this->iTime = time;
   this->iTimePassed += time;
   s3ePointerUpdate();
   s3ePointerGetState(S3E_POINTER_BUTTON_SELECT);
   CIwSVec2 touch = CIwSVec2(s3ePointerGetX(), s3ePointerGetY()); 

   for(int i = 0; i < (int)this->mbHitList.size(); ++i)
   {
      this->mbHitList[i]->setPosition(this->i2Position);
      this->mbHitList[i]->bUpdate = this->mbHitList[i]->hit(touch);
      this->mbHitList[i]->update(time);
   }
}

void UserInterface::draw()
{
   IW_CALLSTACK("UserInterface::draw");

   if ( this->iTextureIndex != -1)
   {
      Iw2DDrawImageRegion(this->tTextureList[this->iTextureIndex], this->i2Position, this->i2Size, this->i2RegionOffset, this->i2RegionSize);
   }

   for(int i = 0; i < (int)this->mbHitList.size(); ++i)
   {
      this->mbHitList[i]->draw();
   }

   for(int i = 0; i < (int)this->mMessageList.size(); ++i)
   {
      this->mMessageList[i]->draw();
   }
}
