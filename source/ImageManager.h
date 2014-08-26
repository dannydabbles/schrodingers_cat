//
//
//
//   Project : Schrˆdinger's cat
//   File Name : GraphicsManager.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_IMAGEMANAGER_H)
#define _IMAGEMANAGER_H

#include <string>
#include "Iw2D.h"
#include "IwResManager.h"
#include "HashTable.h"

using namespace std;

class ImageManager
{
public:	
	static void Init();
	static void reset();
	static void update(uint64 time);
	static void ShutDown();
	static CIw2DImage* getImage(string sImageName);
	static void removeImage(string sImageName);
	
private:	
	static HashTable<CIw2DImage*> tiImageLibrary;
};

#endif