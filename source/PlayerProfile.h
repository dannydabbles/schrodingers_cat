/*
 *  PlayerProfile.h
 *  Kitty
 *
 *  Created by Sam Medalen on 5/17/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef _PLAYERPROFILE_H
#define _PLAYERPROFILE_H

#include "s3e.h"
#include "HashTable.h"
#include "Iw2D.h"
#include <stdlib.h>
#include <utility>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

class PlayerProfile
{
public:
	static void setProfile(CIwArray<string> levels);
	static void readProfile(CIwArray<string> levels);
	static void writeProfile();
   static void setHash();
   static int getHash(string);
	static void setLevel(int , int);
	static int getLevel();
	static void nextLevel(bool);
	static int getCurrLevel();
	static int getWorld();
	static int getWorldLevel();
	static void addDeath(int i);
	static void setDeath(int);
	static int getCurrDeath();
	static int getDeath();
	static int getTotalDeath();
	static void setLock(int i,int j,int b);
	static int getLock(int i,int j);
   static int getCurrLock();
	static void setWin(int expectedDeaths);
	static void setTime(uint64);
	static uint64 getCurrTime();
	static uint64 getTime();
	static void unlock();
private:
	static int iCurrentLevel;
	static uint64 uCurrentTime;
	static int iTotalDeath;
	static int iCurrentDeath;
	static CIwArray<int> aiLocked;
   static CIwArray<uint64> auScore;
	static CIwArray<int> aiScore;
	static CIwArray<int> iLevelNum;
   static HashTable<int> hXOffset;
	static CIwArray<CIwArray<int> > iIndexArray;
	static int iWorld;
	static int iLevel;
};

#endif