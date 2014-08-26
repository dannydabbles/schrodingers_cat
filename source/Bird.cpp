#include "Bird.h"

Bird::Bird( CIwSVec2 position, float velocity )
{

	IW_CALLSTACK("Bird::Bird");

	this->i2Position = position;
	this->f2AbsPosition = this->i2Position;
	

	this->sName = "bird";

	this->i2RegionSize = CIwSVec2(45, 60);

	int rand = IwRandMinMax(0, 3);

	// give a random size
	switch(rand)
	{
		case 0:
			this->i2Size = CIwSVec2(3, 4);
         this->f2Velocity.x = velocity;
			break;
		case 1:
			this->i2Size = CIwSVec2(6, 8);
         this->f2Velocity.x = 2 *  velocity;
			break;
		case 2:
			this->i2Size = CIwSVec2(12, 16);
         this->f2Velocity.x = 3 * velocity;
			break;
		default:
			this->i2Size = CIwSVec2(15, 20);
         this->f2Velocity.x = 4 * velocity;
	}
	rand = IwRandMinMax(0, 8);

	// give random offset so all birds dont flap at same time
   this->i2RegionOffset = CIwSVec2 ( rand * 45, 0);
	this->tTextureList.push_back(ImageManager::getImage("bird"));
}
