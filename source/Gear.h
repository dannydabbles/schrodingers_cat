#ifndef GEAR_H
#define GEAR_H

#include "BackgroundUnit.h"

class Gear: public BackgroundUnit
{
public:
	Gear(int type); 
	void update(uint64 time);
	void draw();

	
private:
	 CIwMat2D mRot;
	 CIwVec2 rotAxsis;
	 int iRot;

} ;

#endif