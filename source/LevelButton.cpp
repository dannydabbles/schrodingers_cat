#include "LevelButton.h"

#define MAXLEVEL 26

LevelButton::LevelButton(CIwSVec2 menuPosition, CIwSVec2 offset, CIwSVec2 size, int num, int arrayIndex) : MenuButton()
{
	IW_CALLSTACK("LevelButton::LevelButton");
	this->arrayIndex = arrayIndex;
   this->i2Size = size;
   this->i2Offset = offset;
   this->i2RegionSize = CIwSVec2( 75, 75); 
   this->i2Position = menuPosition + this->i2Offset;
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);

   this->sName = "levelbutton";


   IwAssertMsg(MYAPP, num <= MAXLEVEL, ("Greater than max Level"));
   IwAssertMsg(MYAPP, num >= 0, ("Less than min Level"));

   if ( num == 0)
   {
      this->tTextureList.push_back(ImageManager::getImage("level_i" ));
      this->tTextureList.push_back(ImageManager::getImage("level_ib" ));
   }
   else
   {

      string name = "level_";
      std::stringstream ss;
      ss<<num;
      name += (ss.str());
      this->tTextureList.push_back(ImageManager::getImage(name.c_str()));
      name+= 'b';
      this->tTextureList.push_back(ImageManager::getImage(name.c_str()));
   }

	this->sSoundList.push_back(SoundManager::getSound("menu9"));

   ClassTracker::addUnit(this);

}


bool LevelButton::update(uint64 time, bool update)
{
	IW_CALLSTACK("LevelButton::update");

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
      this->bUpdate = false;
		SoundManager::playSound(this->sSoundList[0]);
      return true;
   }
   else
   {
      return false;
   }
}