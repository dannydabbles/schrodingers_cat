//
//
//   Project : Schrödinger's cat
//   File Name : Cat.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Cat.h"
#define MEOW_INTERVAL 10000

Cat::Cat(CIwSVec2 i2Position)
{
   IW_CALLSTACK("Cat::Cat");
	
   this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
   this->tTextureList.push_back(ImageManager::getImage("catidling"));
   this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
   this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
	this->tTextureList.push_back(ImageManager::getImage("walking_left"));
   this->tTextureList.push_back(ImageManager::getImage("walking_right"));
	this->tTextureList.push_back(ImageManager::getImage("catjumping_left"));
	this->tTextureList.push_back(ImageManager::getImage("catjumping_right"));   //change this to jumping_right
	this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
   this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
	this->tTextureList.push_back(ImageManager::getImage("catlicking"));
	this->tTextureList.push_back(ImageManager::getImage("catrolling"));
	this->tTextureList.push_back(ImageManager::getImage("catscratchingself"));
	this->tTextureList.push_back(ImageManager::getImage("catstretching"));
	this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
   this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
	this->tTextureList.push_back(ImageManager::getImage("catbatting"));
	this->tTextureList.push_back(ImageManager::getImage("catbatting"));
	this->tTextureList.push_back(ImageManager::getImage("cattransition"));
   this->tTextureList.push_back(ImageManager::getImage("cattransition")); //eatingfood
   this->tTextureList.push_back(ImageManager::getImage("cattransition")); //pooping
	this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
   this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
	this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
	this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
	this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
   this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
   this->tTextureList.push_back(ImageManager::getImage("cattransition"));
   this->tTextureList.push_back(ImageManager::getImage("cattransition"));
	this->tTextureList.push_back(ImageManager::getImage("cattransition"));
	this->tTextureList.push_back(ImageManager::getImage("cattransition"));
	this->tTextureList.push_back(ImageManager::getImage("catlefttoright"));
	this->tTextureList.push_back(ImageManager::getImage("catlefttojumpleft"));
	this->tTextureList.push_back(ImageManager::getImage("cattransition"));
	this->tTextureList.push_back(ImageManager::getImage("cattransition"));
	this->tTextureList.push_back(ImageManager::getImage("catrighttoleft"));
	this->tTextureList.push_back(ImageManager::getImage("catrighttojumpright"));
	this->tTextureList.push_back(ImageManager::getImage("cattransition"));
   this->tTextureList.push_back(ImageManager::getImage("catjumplefttoidle"));
   this->tTextureList.push_back(ImageManager::getImage("catjumplefttoleft"));
	this->tTextureList.push_back(ImageManager::getImage("cattransition"));
	this->tTextureList.push_back(ImageManager::getImage("catjumprighttoidle"));
	this->tTextureList.push_back(ImageManager::getImage("catjumprighttoright"));
	this->tTextureList.push_back(ImageManager::getImage("cattransition"));
	this->tTextureList.push_back(ImageManager::getImage("cattransition"));
	this->tTextureList.push_back(ImageManager::getImage("cattransition"));
	this->tTextureList.push_back(ImageManager::getImage("cattransition"));
   this->tTextureList.push_back(ImageManager::getImage("DEFAULT"));
	
	this->sSoundList.push_back(SoundManager::getSound("cat_meow3")); //index 0
	this->sSoundList.push_back(SoundManager::getSound("cat_meow4"));
	this->sSoundList.push_back(SoundManager::getSound("cat_meow5"));
	this->sSoundList.push_back(SoundManager::getSound("cat_meow1"));
	this->sSoundList.push_back(SoundManager::getSound("cat_meow2"));
	this->sSoundList.push_back(SoundManager::getSound("cat_meow_short1"));
	this->sSoundList.push_back(SoundManager::getSound("cat_meow_short2"));  //index 6
	this->sSoundList.push_back(SoundManager::getSound("cat_purr"));
	this->sSoundList.push_back(SoundManager::getSound("cat_die1"));	//index 8
	this->sSoundList.push_back(SoundManager::getSound("cat_die2"));
	this->sSoundList.push_back(SoundManager::getSound("cat_die3"));
	this->sSoundList.push_back(SoundManager::getSound("cat_die4"));
	this->sSoundList.push_back(SoundManager::getSound("cat_die5"));	//index 12
	
   this->i2Position = i2Position;
   this->i2StartPosition = i2Position;
   this->sName = "cat";
   this->iAnimateTime = 32;
   this->bIsMoving = true;
   this->bHasMouse = false;
   this->i2PreJumpBoxPosition = i2Position;
   this->f2AbsPosition.x = i2Position.x;
   this->f2AbsPosition.y = i2Position.y;
   this->f2DefaultVelocity = CIwFVec2(0.1f, 0);
   this->f2Velocity = this->f2DefaultVelocity;
   this->fJumpSpeedMod = 0.05f;
   this->iDeathCount = 0;
   this->fGravC = 10.0f;
   this->iTimePassed = 0;
   this->iMeowTimePassed = 0;
   this->ceEvent = NULL;
   this->curves = NULL;
   CatState::setState(CatState::WALKINGRIGHT);
   this->iTextureIndex = CatState::getState();
	this->iSoundIndex = 0;
   this->piPathIndex = NULL;
   this->i2Size = CIwSVec2(38, 32);
   this->i2RegionSize = CIwSVec2(38, 32);
   this->i2RegionOffset = CIwSVec2(40, 0);
   this->brBoundingBox = BoundingRectangle(this->getPosition(), this->getSize(), CIwSVec2((int)(this->i2Size.x * 0.5f), (int)(this->i2Size.y * 0.5f)), true);

   ClassTracker::addUnit(this);
}

void Cat::deathMeow()
{
	IW_CALLSTACK("Cat::deathMeow");

	this->iSoundIndex = 7;
	while(iSoundIndex == 7)	//reject purring from death sounds
	{
		this->iSoundIndex = IwRandMinMax(0, 12);
	}
	SoundManager::playSound(this->sSoundList[iSoundIndex]);
	this->iMeowTimePassed = 0;
}

void Cat::playEventMeow()
{
	IW_CALLSTACK("Cat::playEventMeow");

	if(this->iMeowTimePassed >= MEOW_INTERVAL)
	{
		this->iSoundIndex = IwRandMinMax(3, 40);
		if(this->iSoundIndex <= 7)
		{
			SoundManager::playSound(this->sSoundList[this->iSoundIndex]);
			this->iMeowTimePassed = 0;
		}
	}
}

void Cat::playMeow()
{
	IW_CALLSTACK("Cat::playMeow");

	if(this->iMeowTimePassed >= MEOW_INTERVAL)
	{
		this->iSoundIndex = IwRandMinMax(0, 18);
		if(this->iSoundIndex <= 7)
		{
			SoundManager::playSound(this->sSoundList[iSoundIndex]);
			this->iMeowTimePassed = 0;
		}
	}
}

void Cat::regularMeow()
{
	IW_CALLSTACK("Cat::regularMeow");

	if(this->iMeowTimePassed >= MEOW_INTERVAL)
	{
		this->iSoundIndex = IwRandMinMax(0, 15);
		if(this->iSoundIndex <= 5)
		{
			SoundManager::playSound(this->sSoundList[iSoundIndex]);
			this->iMeowTimePassed = 0;
		}
	}
}

void Cat::moveJumpLeft()
{	
   IW_CALLSTACK("Cat::moveJump");
	
   //CatState::setState(CatState::JUMPINGLEFT);
	/*
	 //cout<<s3eTimerGetMs()<<endl;
	 if(i2Position.x < i2Finish.x)
	 this->iTextureIndex = 0;
	 else
	 this->iTextureIndex = 1;
	 */
   if(this->curves == NULL)
      IwAssertMsg(MYAPP, false, ("Invalid jump parameters: curves is NULL"));
   if(this->curves->empty())
      IwAssertMsg(MYAPP, false, ("Invalid jump parameters: curves is empty"));
	
   this->f2AbsPosition.x -= this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
   this->i2Position.x = (int)this->f2AbsPosition.x;
   if(this->i2Position.x <= this->i2Finish.x)
   {
      //if(this->i2Position.x < this->i2Finish.x) IwAssertMsg(MYAPP, false, ("Cat teleport!"));
      this->i2Position = this->i2Finish;
      this->f2AbsPosition.x = this->i2Finish.x;
      this->f2AbsPosition.y = this->i2Finish.y;
      this->f2Velocity = this->f2DefaultVelocity;
      this->i2PreJumpBoxPosition = this->i2Finish;
      if(this->piPathIndex != NULL && (*this->piPathIndex) != -1)
      {
         ++(*this->piPathIndex);
      }
		CatState::setState(CatState::TRANSITIONING);
      return;
   }
	
   float x = (float)(this->i2Position.x - this->i2PreJumpBoxPosition.x);
   float o = this->curves->front().x;
   float v = this->curves->front().y;
   float g = this->fGravC;
   float tano = tan(o*PI/180);
   float coso = cos(o*PI/180);
   this->i2Position.y = (int)-((x*tano)-((g*pow(x,2))/(2*pow(v,2)*pow(coso,2)))) + this->i2PreJumpBoxPosition.y;
   this->f2Velocity.x = v * coso * this->f2DefaultVelocity.x * this->fJumpSpeedMod;
   return;
	/*
	 this->i2PreJumpBoxPosition = this->i2Finish;
	 CatState::setState(CatState::TRANSITIONING);
	 return;
	 */
}

void Cat::moveJumpRight()
{	
   IW_CALLSTACK("Cat::moveJump");
	
	// CatState::setState(CatState::JUMPINGRIGHT);
	/*
	 //cout<<s3eTimerGetMs()<<endl;
	 if(i2Position.x < i2Finish.x)
	 this->iTextureIndex = 0;
	 else
	 this->iTextureIndex = 1;
	 */
   if(this->curves == NULL)
      IwAssertMsg(MYAPP, false, ("Invalid jump parameters: curves is NULL"));
   if(this->curves->empty())
      IwAssertMsg(MYAPP, false, ("Invalid jump parameters: curves is empty"));
	
   this->f2AbsPosition.x += this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
   this->i2Position.x = (int)this->f2AbsPosition.x;
   if(this->i2Position.x >= this->i2Finish.x)
   {
      //if(this->i2Position.x > this->i2Finish.x) IwAssertMsg(MYAPP, false, ("Cat teleport!"));
      this->i2Position = this->i2Finish;
      this->f2AbsPosition.x = this->i2Finish.x;
      this->f2AbsPosition.y = this->i2Finish.y;
      this->f2Velocity = this->f2DefaultVelocity;
      this->i2PreJumpBoxPosition = this->i2Finish;
      if(this->piPathIndex != NULL && (*this->piPathIndex) != -1)
      {
         ++(*this->piPathIndex);
      }
		CatState::setState(CatState::TRANSITIONING);
      return;
   }
   float x = (float)(this->i2Position.x - this->i2PreJumpBoxPosition.x);
   float o = this->curves->front().x;
   float v = this->curves->front().y;
   float g = this->fGravC;
   float tano = tan(o*PI/180);
   float coso = cos(o*PI/180);
   this->i2Position.y = (int)-((x*tano)-((g*pow(x,2))/(2*pow(v,2)*pow(coso,2)))) + this->i2PreJumpBoxPosition.y;
   this->f2Velocity.x = v * coso * this->f2DefaultVelocity.x * this->fJumpSpeedMod;
	
	/*
	 this->i2PreJumpBoxPosition = this->i2Finish;
	 CatState::setState(CatState::TRANSITIONING);
	 return;
	 */
}

void Cat::moveLeft()
{
   IW_CALLSTACK("Cat::moveLeft");
	
  // CatState::setState(CatState::WALKINGLEFT);

   this->f2AbsPosition.x -= this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
   this->i2Position.x = (int)this->f2AbsPosition.x;
   if(this->i2Position.x <= this->i2Finish.x)
   {
      //if(this->i2Position.x < this->i2Finish.x) IwAssertMsg(MYAPP, false, ("Cat teleport!"));
      this->i2Position = this->i2Finish;
      this->f2AbsPosition.x = this->i2Finish.x;
      this->f2AbsPosition.y = this->i2Finish.y;
      this->f2Velocity = this->f2DefaultVelocity;
      this->i2PreJumpBoxPosition = this->i2Finish;
      if(this->piPathIndex != NULL && (*this->piPathIndex) != -1)
      {
         ++(*this->piPathIndex);
      }
		CatState::setState(CatState::TRANSITIONING);
      //cout << "Move left just transitioned" << endl;
   }
}

void Cat::moveRight()
{
   IW_CALLSTACK("Cat::moveRight");

   //CatState::setState(CatState::WALKINGRIGHT);
	
   this->f2AbsPosition.x += this->f2Velocity.x * this->iTime * Screen::getMOVEMULTIPLIER().x;
   this->i2Position.x = (int)this->f2AbsPosition.x;
   if(this->i2Position.x >= this->i2Finish.x)
   {
      //if(this->i2Position.x > this->i2Finish.x) IwAssertMsg(MYAPP, false, ("Cat teleport!"));
      this->i2Position = this->i2Finish;
      this->f2AbsPosition.x = this->i2Finish.x;
      this->f2AbsPosition.y = this->i2Finish.y;
      this->f2Velocity = this->f2DefaultVelocity;
      this->i2PreJumpBoxPosition = this->i2Finish;
      if(this->piPathIndex != NULL && (*this->piPathIndex) != -1)
      {
            ++(*this->piPathIndex);
      }
		CatState::setState(CatState::TRANSITIONING);
      //cout << "Move right just transitioned" << endl;
   }
}

/*bool Cat::movePounce(CIwSVec2 i2Finish, bool bIsFilled, CIwFVec2 curve, uint64 time)
{	
   IW_CALLSTACK("Cat::moveJump");
   if(this->i2Position != i2Finish){
      if(i2Finish.x - this->i2Position.x > 0) ++this->i2Position.x;
      else if(i2Finish.x - this->i2Position.x < 0) --this->i2Position.x;
      else
      {
         this->i2Position = i2Finish;
         this->i2PreMovePos = i2Finish;
         this->bAnimateDone = true;
         return true;
      }
      float x = (float)(this->i2Position.x - this->i2PreMovePos.x);
      float o = curve.x;
      float v = curve.y;
      float g = this->fGravC;
      float tano = tan(o*PI/180);
      float coso = cos(o*PI/180);
      this->i2Position.y = (int)-((x*tano)-((g*pow(x,2))/(2*pow(v,2)*pow(coso,2)))) + this->i2PreMovePos.y;
      return false;
   }
   else
   {
      this->i2PreMovePos = i2Finish;
      //this->bAnimateDone = true;
      return true;
   }
   return true;
}*/

void Cat::performActions()
{
	IW_CALLSTACK("Cat::performActions");

   if(CatState::getState() == CatState::WALKINGLEFT)
   {
      this->moveLeft();
   }
   else if(CatState::getState() == CatState::WALKINGRIGHT)
   {
      this->moveRight();
   } 
   else if(CatState::getState() == CatState::JUMPINGRIGHT)
   {
		this->regularMeow();
      this->moveJumpRight();
   }
    else if(CatState::getState() == CatState::JUMPINGLEFT)
   {
		this->regularMeow();
      this->moveJumpLeft();
   }
}

void Cat::reset()
{
   IW_CALLSTACK("Cat::reset");

   ++this->iDeathCount;
	this->deathMeow();
   this->i2Position = this->i2StartPosition;
	this->f2AbsPosition.x = (float)this->i2StartPosition.x;
	this->f2AbsPosition.y = (float)this->i2StartPosition.y;
   this->i2Finish = this->i2Position;
   this->brBoundingBox.setPosition(this->i2StartPosition);
   this->i2PreJumpBoxPosition = this->i2StartPosition;
   this->curves = NULL;
}

void Cat::setCurves(CIwArray<CIwFVec2>* curves)
{
	IW_CALLSTACK("Cat::setCurves");

   /*if ( this->curves != NULL)
   {
      this->curves->clear_optimised();
   }*/
   this->curves = curves;
}

void Cat::setFinish(CIwSVec2 i2Finish)
{
	IW_CALLSTACK("Cat::setFinish");

   this->i2Finish = i2Finish;
}

void Cat::update(uint64 time)
{
   IW_CALLSTACK("Cat::update");
   
   this->iTime = time;
   this->iTimePassed += time;
	this->iMeowTimePassed += time;
	
   if(CatState::getState() == CatState::DEAD)
   {
		// this->die(); moved to grid
      return;
   } 
	
	if(CatState::isPlayingWith())
	{
		this->playMeow();
	}
	
	if(CatState::isPlayingWithEvent())
	{
		this->playEventMeow();
	}
	
   this->iTextureIndex = CatState::getState();

	this->performActions();
	
   if(!CatState::isMoving())
   {
      if(this->i2RegionOffset.x >= this->tTextureList[iTextureIndex]->GetWidth())//>= fixes for some random reason
      {
         CatState::setState(CatState::TRANSITIONING);
      }
   }
   
   if(this->ceEvent != NULL)
   {
	   this->ceEvent->i2Position = CIwSVec2(this->i2Position);
   }
   this->brBoundingBox.setPosition(this->getPosition(), true);
}

Cat::~Cat()
{
   //cout<<endl;
   //this->curves->clear_optimised();
   //cout<<this->curves<<endl;
   //delete this->curves;
}

void Cat::draw()
{
   if(GameState::getState() != GameState::LEVELBEATEN)
   {
      Unit::draw();
   }
}
