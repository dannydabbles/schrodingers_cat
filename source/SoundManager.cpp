//
//
//
//   Project : Schrˆdinger's cat
//   File Name : UserInterface.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//

#include <iostream>

#include "SoundManager.h"

//S3EAUDIO VALUES: 1, 8
#define FADEOUT_RATE 2000.0f
#define DEFAULT_VOLUME 4096

using namespace std;

bool SoundManager::bIsPlaying = false;

bool SoundManager::bSoundOn = true;

bool SoundManager::bIsFadingOut = false;

int SoundManager::iCurrentVolume = DEFAULT_VOLUME;

int SoundManager::iMusicVolume = DEFAULT_VOLUME;

uint64 SoundManager::iTimePassed = 0;

float SoundManager::fFadeOut = FADEOUT_RATE;

//string SoundManager::sCurrentMusicFile = "/sounds/Catzophrenia.mp3";
string SoundManager::sCurrentMusicName = "Catzophrenia";

string SoundManager::sQueueMusicName = string();

CIwResGroup* SoundManager::soundGroup = NULL;
CIwSoundSpec* SoundManager::sCurrentMusic = NULL;

HashTable<CIwSoundSpec*> SoundManager::tsSoundLibrary = HashTable<CIwSoundSpec*>();

void SoundManager::Init()
{
   IW_CALLSTACK("SoundManager::Init");

   IwSoundInit();
   IwGetResManager()->AddHandler(new CIwResHandlerWAV);
   IwGetResManager()->LoadGroup("sounds.group");
   soundGroup = IwGetResManager()->GetGroupNamed("sounds");	
}

void SoundManager::playSound(CIwSoundSpec* sSound)
{
   IW_CALLSTACK("SoundManager::playSound");

   /*if(bSoundOn == false) 
   {
   return;
   }*/
   IwGetSoundManager()->Update();
   if(sSound == NULL)
   {
      IwAssertMsg(MYAPP, false, ("playSound given a NULL sound"));
      return;
   }	
   sSound->Play();
}


void SoundManager::reset()
{
   IW_CALLSTACK("SoundManager::reset");

   tsSoundLibrary.clear();
}

void SoundManager::setMusic(string sMusicName)
{
   IW_CALLSTACK("SoundManager::setMusic");

   if(sCurrentMusicName.compare(sMusicName) == 0 && bIsFadingOut == false)		//if you're trying to play music that's already playing, do nothing
   {
      return;
   }
   else																	//else queue the new music to play once the current one has faded out
   {
      sQueueMusicName = sMusicName;				
   }
}

void SoundManager::ToggleSound()
{
   if(bSoundOn == false)
   {
      bSoundOn = true;
      iCurrentVolume = DEFAULT_VOLUME;
   }
   else 
   {
      bSoundOn = false;
      iCurrentVolume = 0;
   }
	IwGetSoundManager()->SetMasterVol(iCurrentVolume);
   IwGetSoundManager()->Update();
}

bool SoundManager::getSound()
{
   return bSoundOn;
}

CIwSoundSpec* SoundManager::getSound(string sSoundName)
{
   IW_CALLSTACK("SoundManager::getSound");

   CIwSoundSpec* sTmpSound = tsSoundLibrary.get(sSoundName);
   if(sTmpSound == NULL)	//add the indicated sound file to the library if it's not already there
   {
      sTmpSound = (CIwSoundSpec*)soundGroup->GetResNamed(sSoundName.c_str(), IW_SOUND_RESTYPE_SPEC);

      if(sTmpSound == NULL)
      {
         IwAssertMsg(MYAPP, false, ("getSound could not find sound file %s", sSoundName.c_str()));
         return NULL;
      }
      pair<string, CIwSoundSpec*> newPair = pair<string, CIwSoundSpec*>(sSoundName, sTmpSound);
      tsSoundLibrary.insert(newPair);
   }
   return sTmpSound;
}

void SoundManager::ShutDown()
{
   IW_CALLSTACK("SoundManager::ShutDown");

   tsSoundLibrary.clear();
   IwGetResManager()->DestroyGroup("sounds");
}

void SoundManager::update(uint64 time)
{
   IW_CALLSTACK("SoundManager::update");

   /*		USING S3EAUDIO

   if(isPlaying == false || (s3eAudioGetInt(S3E_AUDIO_POSITION) == 0 && iTimePassed > 2000))			//if no music is currently playing, play the current music file
   {
   s3eAudioStop();
   iTimePassed = 0;
   s3eAudioPlay(sCurrentMusicFile.c_str(), 0);
   s3eAudioSetInt(S3E_AUDIO_VOLUME, DEFAULT_VOLUME);
   isPlaying = true;
   }
   if(sQueueMusicFile.empty() == false)	//if there is music waiting to play, fade out the current track
   {		
   iTimePassed += time;
   if(iTimePassed >= 128)
   {
   s3eAudioSetInt(S3E_AUDIO_VOLUME, s3eAudioGetInt(S3E_AUDIO_VOLUME) - FADEOUT_RATE);
   iTimePassed = 0;
   }
   if(s3eAudioGetInt(S3E_AUDIO_VOLUME) <= 0)		//once the current music has faded out completely, set the new track to start playing
   {															
   s3eAudioStop();
   iTimePassed = 0;
   sCurrentMusicFile = sQueueMusicFile;
   sQueueMusicFile.clear();
   isPlaying = false;
   }
   }	

   USING SOUNDENGINE*/

   //cout << "VOLUME: " << IwGetSoundManager()->GetMasterVol() << endl;
   //cout << "CURRENT: " << sCurrentMusicName << endl;
   //cout << "QUEUE: " << sQueueMusicName << endl;

   IwGetSoundManager()->SetMasterVol(iCurrentVolume);

   if(bIsPlaying == false)
   {
      iTimePassed = 0;
      sCurrentMusic = getSound(sCurrentMusicName);
      playSound(sCurrentMusic);
      iMusicVolume = iCurrentVolume;
      sCurrentMusic->GetGroup()->SetVol(iCurrentVolume);
      bIsPlaying = true;
   }
   if(sQueueMusicName.empty() == false)
   {
      iTimePassed += time;
      if(iTimePassed >= 128)
      {
         iMusicVolume -= (int)fFadeOut;
         sCurrentMusic->GetGroup()->SetVol(iMusicVolume);
         iTimePassed = 0;
         fFadeOut = (float)MAX((fFadeOut/2), 10.0);
         bIsFadingOut = true;
      }
      if(iMusicVolume <= 0)
      {
         IwGetSoundManager()->StopSoundSpec(sCurrentMusic);
         iTimePassed = 0;
         fFadeOut = FADEOUT_RATE; 
         sCurrentMusicName = sQueueMusicName;
         sQueueMusicName.clear();
         bIsPlaying = false;
         bIsFadingOut = false;
      }
   }
   IwGetSoundManager()->Update();
}
