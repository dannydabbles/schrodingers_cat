#ifndef CLOUD_H
#define CLOUD_H

#include "BackgroundUnit.h"

class Cloud : public BackgroundUnit
{
public:
	Cloud(CIwSVec2 position, float velocity, int type); 
	void draw();

} ;

#endif