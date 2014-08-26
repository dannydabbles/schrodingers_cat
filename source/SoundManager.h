//
//
//
//   Project : Schrˆdinger's cat
//   File Name : SoundManager.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_SOUNDMANAGER_H)
#define _SOUNDMANAGER_H

#include <string>
#include "s3e.h"
#include "IwSound.h"
#include "IwSoundInst.h"
#include "IwSoundSpec.h"
#include "ImageManager.h"

using namespace std;

class SoundManager
{
public:	
	static void Init();
	static void reset();
	static void playSound(CIwSoundSpec* sSound);
	static void ToggleSound();
	static void setMusic(string sMusicName);
	static void ShutDown();	
	static void update(uint64 time);
	
	static bool getSound();

	static CIwSoundSpec* getSound(string sSoundName);
	
private:
	static bool bIsPlaying;
	static bool bSoundOn;
	static bool bIsFadingOut;
	
	static int iCurrentVolume;
	static int iMusicVolume;
	static uint64 iTimePassed;
	
	static float fFadeOut;
	
	static string sCurrentMusicName;
	static string sQueueMusicName;

	static CIwResGroup* soundGroup;
	

	static CIwSoundSpec* sCurrentMusic;
	static CIwSoundInst* sMusicInstance;
	
	static HashTable<CIwSoundSpec*> tsSoundLibrary;
	
};

#endif