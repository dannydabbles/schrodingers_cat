#ifndef BACKGROUND_UNIT_H
#define BACKGROUND_UNIT_H

#include "Box.h"

class BackgroundUnit : public Unit
{
public:
   BackgroundUnit() { this->updatedOnce = false; }
	virtual void update(uint64 time);
	virtual void draw();

protected:
   bool updatedOnce;

};

#endif