#ifndef BACKGROUND_MANAGER_H
#define BACKGROUND_MANAGER_H

#include <string>
#include <sstream>
#include <ctime>
#include "s3e.h"
#include "Iw2D.h"
#include "Screen.h"
#include "BackgroundUnit.h"
#include "Cloud.h"
#include "Bird.h"
#include "Gear.h"
#include "Spiral.h"

using namespace std;

class BackgroundManager
{
public:
	BackgroundManager();
   ~BackgroundManager();

	void loadBackground(string backgroundName, CIwArray<string> extras);
	void loadBackground(int pageNum);
	void draw();
	void update(uint64 time);

private:
	CIwArray<CIw2DImage*> backgroundSegments;
	CIwArray<CIwSVec2> positionArray;
	CIwArray<BackgroundUnit*> units;
	CIwSVec2 i2Size;
} ;

#endif