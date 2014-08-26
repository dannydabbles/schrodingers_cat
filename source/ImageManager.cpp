//
//
//
//   Project : Schrˆdinger's cat
//   File Name : GraphicsManager.h
//   Date : 1/21/2011
//   Author : P Productions
//
//

#include "ImageManager.h"

HashTable<CIw2DImage*> ImageManager::tiImageLibrary = HashTable<CIw2DImage*>();

void ImageManager::Init()
{
   IW_CALLSTACK("ImageManager::Init");

   IwGetResManager()->LoadGroup("sprites.group");
}

void ImageManager::reset()
{
   IW_CALLSTACK("ImageManager::reset");

   tiImageLibrary.clear();
}

void ImageManager::ShutDown()
{
   IW_CALLSTACK("ImageManager::ShutDown");

   tiImageLibrary.clear();
   IwGetResManager()->DestroyGroup("Objects");
}

CIw2DImage* ImageManager::getImage(string sImageName)
{
   IW_CALLSTACK("ImageManager::getImage");

   CIw2DImage* iTmpImage = tiImageLibrary.get(sImageName);
   if(iTmpImage == NULL)	//add the indicated image file to the library if it's not already there
   {
      iTmpImage = Iw2DCreateImageResource(sImageName.c_str());

      if(iTmpImage == NULL)
      {
         IwAssertMsg(MYAPP, false, ("getImage could not find image file %s", sImageName.c_str()));
         return NULL;
      }
      pair<string, CIw2DImage*>newPair = pair<string, CIw2DImage*>(sImageName, iTmpImage);
      tiImageLibrary.insert(newPair);
      return iTmpImage;
   }
   return iTmpImage;
}

void ImageManager::removeImage(string name)
{
   ImageManager::tiImageLibrary.remove(name);
}
