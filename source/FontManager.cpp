//
//
//
//   Project : Schrˆdinger's cat
//   File Name : GraphicsManager.h
//   Date : 1/21/2011
//   Author : P Productions
//
//

#include "FontManager.h"

HashTable<CIw2DFont*> FontManager::tiFontLibrary = HashTable<CIw2DFont*>();

void FontManager::Init()
{
   IW_CALLSTACK("FontManager::Init");
   IwGxFontInit();
}

void FontManager::reset()
{
   IW_CALLSTACK("FontManager::reset");

   tiFontLibrary.clear();
}

void FontManager::ShutDown()
{
   IW_CALLSTACK("FontManager::ShutDown");

   tiFontLibrary.clear();
   IwGxFontTerminate();
}

CIw2DFont* FontManager::getFont(string sFontName)
{
   IW_CALLSTACK("FontManager::getFont");

   CIw2DFont* iTmpFont = tiFontLibrary.get(sFontName);

   if(iTmpFont == NULL)	//add the indicated Font file to the library if it's not already there
   {
      iTmpFont = Iw2DCreateFont((sFontName + ".gxfont").c_str());   

      if(iTmpFont == NULL)
      {
         IwAssertMsg(MYAPP, false, ("getFont could not find Font file %s", sFontName.c_str()));
         return NULL;
      }
      pair<string, CIw2DFont*>newPair = pair<string, CIw2DFont*>(sFontName, iTmpFont);
      tiFontLibrary.insert(newPair);
      return iTmpFont;
   }
   return iTmpFont;
}
