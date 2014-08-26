#include "SkipLevelButton.h"



SkipLevelButton::SkipLevelButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size) : MenuButton()
{
	IW_CALLSTACK("SkipLevelButton::SkipLevelButton");
	
	this->i2Size = size;
	this->i2RegionSize = CIwSVec2(50, 50);
	this->i2Offset = offset;
	this->i2Position = menuPosition + this->i2Offset;
	this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);
	
	this->sName = "nextlevelbutton";
	
	this->tTextureList.push_back(ImageManager::getImage("kittybutton_right"));
	this->tTextureList.push_back(ImageManager::getImage("kittybutton_right2"));
	
	this->sSoundList.push_back(SoundManager::getSound("menu1"));
	
	ClassTracker::addUnit(this);
}

void SkipLevelButton::update(uint64 time)
{
	IW_CALLSTACK("SkipLevelButton::update");
	if(PlayerProfile::getCurrLevel() != 0)
		return;
	this->iTime = time;
	this->iTimePassed += time;
	
	if(this->bPressed == true)
	{
		this->iTextureIndex = 1;
	}
	else
	{
		this->iTextureIndex = 0;
	}
	
	if(this->bUpdate == true)
	{
		SoundManager::playSound(this->sSoundList[0]);
		GameState::setState(GameState::SKIPLEVEL);
		this->bUpdate = false;
		PlayerProfile::unlock();
		//PlayerProfile::nextLevel(true);
	}
}