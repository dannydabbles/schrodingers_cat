#ifndef CUT_SCENE_MANAGER_H
#define CUT_SCENE_MANAGER_H

#include <string>
#include <sstream>
#include "s3e.h"
#include "s3ePointer.h"
#include "Iw2D.h"
#include "Screen.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "GameState.h"

using namespace std;

class CutSceneManager
{

public:
	CutSceneManager();
	void LoadCutScene(string sceneName);
   void update(uint64 time);
	void draw();
	void reset();
	

private:
	
	CIwArray<CIwArray<CIw2DImage*> > imageSegments;
	CIwArray<CIwSVec2> positionArray; // used for position of each image segment
   CIwArray<uint64> frameTime;
	CIwSVec2 i2Size; // size of each segment
	CIwSVec2 i2RegionOffset;
	CIwSVec2 i2RegionSize;
	uint64 time;
	int iCurrentImage;
	bool bFinished;
	string sceneName;
	

};

#endif