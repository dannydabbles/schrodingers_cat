#ifndef Spiral_H
#define Spiral_H

#include "BackgroundUnit.h"

class Spiral: public BackgroundUnit
{
public:
	Spiral(CIwSVec2 position); 
	void update(uint64 time);
	void draw();

	
private:
	 CIwMat2D mRot;
	 CIwVec2 rotAxsis;
	 int iRot;

} ;

#endif