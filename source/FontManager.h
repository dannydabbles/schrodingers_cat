//
//
//
//   Project : Schrˆdinger's cat
//   File Name : SoundManager.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_FONTMANAGER_H)
#define _FONTMANAGER_H

#include <string>
#include "s3e.h"
#include "Iw2D.h"
#include "IwGxFont.h"
#include "Iw2D.h"
#include "IwResManager.h"
#include "HashTable.h"

using namespace std;

class FontManager
{

public:	
	static void Init();
	static void reset();
	static void update(uint64 time);
	static void ShutDown();
	static CIw2DFont * getFont(string sFontName);
		
private:	
	static HashTable< CIw2DFont*> tiFontLibrary;
   static CIwResGroup * fontGroup;
  
};

#endif