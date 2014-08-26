/*
*  PlayerProfile.cpp
*  Kitty
*
*  Created by Sam Medalen on 5/17/11.
*  Copyright 2011 __MyCompanyName__. All rights reserved.
*
*/

#include "PlayerProfile.h"


int PlayerProfile::iCurrentLevel = 0;
int PlayerProfile::iTotalDeath = 0;
uint64 PlayerProfile::uCurrentTime = 0;
int PlayerProfile::iCurrentDeath = 0;
CIwArray<int> PlayerProfile::aiLocked = CIwArray<int>();
CIwArray<uint64> PlayerProfile::auScore = CIwArray<uint64>();
CIwArray<int> PlayerProfile::aiScore = CIwArray<int>();
CIwArray<int> PlayerProfile::iLevelNum = CIwArray<int>();
CIwArray<CIwArray<int> > PlayerProfile::iIndexArray = CIwArray<CIwArray<int> >();
HashTable<int> PlayerProfile::hXOffset = HashTable<int>();
int PlayerProfile::iWorld = 0;
int PlayerProfile::iLevel = 0;

void PlayerProfile::setProfile(CIwArray<string> levels)
{
   IW_CALLSTACK("PlayerProfile::setProfile");

   int tempLevelNum = -1;
   bool flip = false;
	int worlds = 0;
   CIwArray<int> tempArray = CIwArray<int>();
   for(int i = 0, levelCount = 0 ; i < (int)levels.size(); ++i, ++levelCount)
   {
      if(levels[i].find("t_") != string::npos)
      {
         if(flip == false)
         {
            PlayerProfile::aiLocked.push_back(0);
			 flip = true;
         }
         else
         {
            PlayerProfile::aiLocked.push_back(1);
         }

         PlayerProfile::auScore.push_back(0);
         PlayerProfile::aiScore.push_back(-1);
         PlayerProfile::iLevelNum.push_back(0);
         ++tempLevelNum;
         tempArray.push_back(i);
      }
      else if(levels[i].find("world") == string::npos)
      {
         PlayerProfile::iLevelNum.push_back(levelCount-tempLevelNum);
         if(i != 0 && flip == false && levels[i -1].find("t_") != string::npos)
         {
            PlayerProfile::aiLocked.push_back(0);
            flip = true;
         }
         else
         {
            PlayerProfile::aiLocked.push_back(1);
         }

         PlayerProfile::auScore.push_back(0);
         PlayerProfile::aiScore.push_back(-1);
         tempArray.push_back(i-worlds);
      }
      else
      {
         iIndexArray.push_back(tempArray);
         tempArray.clear();
		  levelCount = 0;
		  tempLevelNum = 0;
		  ++worlds;
      } 
   }
}

void PlayerProfile::readProfile(CIwArray<string> levels)
{
   IW_CALLSTACK("PlayerProfile::readProfile");
   CIwArray<int> tempArray = CIwArray<int>();
   int worlds = 0;
   for(int i = 0; i < (int)levels.size(); ++i)
   {
      if(levels[i].find("world") == string::npos)
      {
         tempArray.push_back(i-worlds);
      }
      else
      {
         iIndexArray.push_back(tempArray);
         tempArray.clear();
         ++worlds;
      }
   }
   for(int i = 0; i < (int)iIndexArray.size();++i)
   {
      for(int j = 0;j < (int)iIndexArray[i].size(); ++j)
      {
         cout<<iIndexArray[i][j]<<endl;
      }
   }
   CIwArray<CIwArray<string> > vvsInstruct = CIwArray<CIwArray<string> >();
   string path = "profile.txt";
   ifstream fFile(path.c_str());
   if(fFile.is_open())
   {
      char buffer[1024];
      CIwArray<string> vtempString = CIwArray<string>();
      string temp = "";
      while(fFile.good())
      {
         cout<<"\n";
         fFile.getline(buffer,1024);
         for(int i = 0; ; ++i)
         {
            if(buffer[i] == '\r' || buffer[i] == '\n' || buffer[i] == 0)
            {
               vtempString.push_back(temp);
               cout<<"\n"<<temp<<"\n";
               temp.clear();
               break;
            }
            if(buffer[i] != '_')
               temp+=buffer[i];
            else if(buffer[i] == '_'){
               vtempString.push_back(temp);
               cout<<"\n"<<temp<<"\n";
               temp.clear();
            }

         }
         vvsInstruct.push_back(vtempString);
         vtempString.clear();
      }
      PlayerProfile::iTotalDeath = atoi(vvsInstruct[0][0].c_str());
      for(int i = 1; i < (int)vvsInstruct.size(); ++i)
      {
         PlayerProfile::iLevelNum.push_back(atoi( vvsInstruct[i][0].c_str()));
         PlayerProfile::aiLocked.push_back(atoi(vvsInstruct[i][1].c_str())); //?
         PlayerProfile::auScore.push_back(atoi(vvsInstruct[i][2].c_str()));
         PlayerProfile::aiScore.push_back(atoi(vvsInstruct[i][3].c_str()));
      }
   }
}

void PlayerProfile::writeProfile()
{
   IW_CALLSTACK("PlayerProfile::writeProfile");

   string stemppath = "profile.txt";
   FILE * fReWrite = fopen(stemppath.c_str(),"w");
   fprintf(fReWrite, "%i\n", PlayerProfile::iTotalDeath);
   for(int i = 0; i <(int)PlayerProfile::iLevelNum.size(); ++i)
   {
      stringstream ss;
      ss<<PlayerProfile::aiScore[i];
      string s= ss.str();
      int itemp = PlayerProfile::aiLocked[i];

      if(i == (int)PlayerProfile::iLevelNum.size() - 1)
      {
         fprintf(fReWrite, "%i_%i_%i_%i",PlayerProfile::iLevelNum[i], itemp, (int)PlayerProfile::auScore[i],PlayerProfile::aiScore[i]);
      }
      else
      {
         fprintf(fReWrite, "%i_%i_%i_%i\n",PlayerProfile::iLevelNum[i], itemp, (int)PlayerProfile::auScore[i],PlayerProfile::aiScore[i]);
      }
   }
   fclose(fReWrite);
}

void PlayerProfile::setHash()
{
   PlayerProfile::hXOffset.insert(pair<string, int>("a",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("b",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("c",12));
   PlayerProfile::hXOffset.insert(pair<string, int>("d",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("e",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("f",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("g",15));
   PlayerProfile::hXOffset.insert(pair<string, int>("h",15));
   PlayerProfile::hXOffset.insert(pair<string, int>("i",9));
   PlayerProfile::hXOffset.insert(pair<string, int>("j",12));
   PlayerProfile::hXOffset.insert(pair<string, int>("k",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("l",9));
   PlayerProfile::hXOffset.insert(pair<string, int>("m",17));
   PlayerProfile::hXOffset.insert(pair<string, int>("n",13));
   PlayerProfile::hXOffset.insert(pair<string, int>("o",11));
   PlayerProfile::hXOffset.insert(pair<string, int>("p",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("q",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("r",12));
   PlayerProfile::hXOffset.insert(pair<string, int>("s",11));
   PlayerProfile::hXOffset.insert(pair<string, int>("t",15));
   PlayerProfile::hXOffset.insert(pair<string, int>("u",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("v",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("w",17));
   PlayerProfile::hXOffset.insert(pair<string, int>("x",12));
   PlayerProfile::hXOffset.insert(pair<string, int>("y",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("z",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("A",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("B",20));
   PlayerProfile::hXOffset.insert(pair<string, int>("C",12));
   PlayerProfile::hXOffset.insert(pair<string, int>("D",17));
   PlayerProfile::hXOffset.insert(pair<string, int>("E",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("F",19));
   PlayerProfile::hXOffset.insert(pair<string, int>("G",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("H",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("I",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("J",17));
   PlayerProfile::hXOffset.insert(pair<string, int>("K",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("L",12));
   PlayerProfile::hXOffset.insert(pair<string, int>("M",20));
   PlayerProfile::hXOffset.insert(pair<string, int>("N",15));
   PlayerProfile::hXOffset.insert(pair<string, int>("O",17));
   PlayerProfile::hXOffset.insert(pair<string, int>("P",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("Q",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("R",19));
   PlayerProfile::hXOffset.insert(pair<string, int>("S",11));
   PlayerProfile::hXOffset.insert(pair<string, int>("T",19));
   PlayerProfile::hXOffset.insert(pair<string, int>("U",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("V",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("W",18));
   PlayerProfile::hXOffset.insert(pair<string, int>("X",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("Y",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("Z",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("0",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("1",10));
   PlayerProfile::hXOffset.insert(pair<string, int>("2",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("3",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("4",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("5",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("6",14));
   PlayerProfile::hXOffset.insert(pair<string, int>("7",16));
   PlayerProfile::hXOffset.insert(pair<string, int>("8",17));
   PlayerProfile::hXOffset.insert(pair<string, int>("9",17));
   PlayerProfile::hXOffset.insert(pair<string, int>(".",10));
   PlayerProfile::hXOffset.insert(pair<string, int>(",",10));
   PlayerProfile::hXOffset.insert(pair<string, int>(" ",10));
}

int PlayerProfile::getHash(string s)
{
   return PlayerProfile::hXOffset.get(s);
}
int PlayerProfile::getLevel()
{
   IW_CALLSTACK("PlayerProfile::getLevel");

   return PlayerProfile::iCurrentLevel;
}

void PlayerProfile::nextLevel(bool b)
{
   if(b)
   {
      iCurrentLevel++;
      iLevel++;
      if(iLevel >= (int)PlayerProfile::iIndexArray[iWorld].size())
      {
         iLevel = 0;
         iWorld++;
      }
   }
   else
   {
      iCurrentLevel--;
      iLevel--;
      if(iLevel < 0 && iWorld != 0)
      {
         iWorld--;
         iLevel = PlayerProfile::iIndexArray[iWorld].size();
      }
	   else if(iCurrentLevel < 0)
	   {
		   iWorld = PlayerProfile::iIndexArray.size()-1;
		   iLevel = PlayerProfile::iIndexArray[iWorld].size()-1;
		   iCurrentLevel = PlayerProfile::iIndexArray[iWorld][iLevel];
	   }
   }
}

int PlayerProfile::getCurrLevel()
{
   IW_CALLSTACK("PlayerProfile::getCurrLevel");
   return PlayerProfile::iLevelNum[PlayerProfile::iCurrentLevel];
}

int PlayerProfile::getWorld()
{
	return PlayerProfile::iWorld;
}

 int PlayerProfile::getWorldLevel()
{
	return PlayerProfile::iLevel;
}

void PlayerProfile::setLevel(int iworld,int ilevel)
{
   IW_CALLSTACK("PlayerProfile::setLevel");
   PlayerProfile::iWorld = iworld;
   PlayerProfile::iLevel = ilevel;
   PlayerProfile::iCurrentLevel = PlayerProfile::iIndexArray[iworld][ilevel];
   PlayerProfile::iCurrentDeath = 0;
   PlayerProfile::uCurrentTime = 0;
}

void PlayerProfile::addDeath(int i)
{
   IW_CALLSTACK("PlayerProfile::addDeath");

   PlayerProfile::iTotalDeath += i;
   PlayerProfile::iCurrentDeath ++;
}

void PlayerProfile::setDeath(int i)
{
   IW_CALLSTACK("PlayerProfile::setDeath");

   PlayerProfile::iCurrentDeath = 0;
}

int PlayerProfile::getCurrDeath()
{
   IW_CALLSTACK("PlayerProfile::getCurrDeath");

   return PlayerProfile::iCurrentDeath;
}

int PlayerProfile::getCurrLock()
{
   IW_CALLSTACK("PlayerProfile::getCurrDeath");

   return PlayerProfile::aiLocked[PlayerProfile::iCurrentLevel];
}

int PlayerProfile::getDeath()
{
   IW_CALLSTACK("PlayerProfile::getDeath");
   return PlayerProfile::aiScore[PlayerProfile::iCurrentLevel];
}

int PlayerProfile::getTotalDeath()
{
   IW_CALLSTACK("PlayerProfile::getTotalDeath");

   return PlayerProfile::iTotalDeath;
}

void PlayerProfile::setLock(int i,int j, int b)
{
   IW_CALLSTACK("PlayerProfile::setLock");

   PlayerProfile::aiLocked[PlayerProfile::iIndexArray[i][j]] = b;   
}

int PlayerProfile::getLock(int i,int j)
{
   IW_CALLSTACK("PlayerProfile::getLock");

   return PlayerProfile::aiLocked[PlayerProfile::iIndexArray[i][j]];
}

void PlayerProfile::setWin(int mapsExpectedDeaths)
{
   IW_CALLSTACK("PlayerProfile::setWin");
   bool change = false;
   int i = PlayerProfile::iCurrentDeath;
   uint64 t = PlayerProfile::uCurrentTime;
   if(PlayerProfile::aiScore[PlayerProfile::iCurrentLevel] == -1 || PlayerProfile::aiScore[PlayerProfile::iCurrentLevel] > i)
   {
      PlayerProfile::aiScore[PlayerProfile::iCurrentLevel] = i;
      change = true;
   }
   if(PlayerProfile::auScore[PlayerProfile::iCurrentLevel] == 0 || PlayerProfile::auScore[PlayerProfile::iCurrentLevel] > t)
   {
      PlayerProfile::auScore[PlayerProfile::iCurrentLevel] = t;
      change = true;
   }

   int templevel = iCurrentLevel;
   templevel++;
   if(PlayerProfile::aiLocked[ templevel] == 1 && templevel < (int)PlayerProfile::aiScore.size())
   {
      PlayerProfile::aiLocked[templevel] =  0;
      change = true;
   }

   if ( PlayerProfile::getCurrDeath() <= mapsExpectedDeaths)
   {
	   if(PlayerProfile::iLevelNum[PlayerProfile::iCurrentLevel] != 0)
      {
         PlayerProfile::aiLocked[PlayerProfile::iCurrentLevel] = 2;
         change = true;
      }
   }
   if(PlayerProfile::iLevelNum[iCurrentLevel] == 0)
   {
      templevel = PlayerProfile::iCurrentLevel;
      bool allComplete = true;
      while( templevel <= (int)PlayerProfile::aiScore.size() && PlayerProfile::iLevelNum[templevel] == 0)
      {
         if(PlayerProfile::aiScore[templevel] == -1)
            allComplete = false;
         templevel++;
      }
      templevel = PlayerProfile::iCurrentLevel;
      while(templevel >= 0 && PlayerProfile::iLevelNum[templevel] == 0)
      {
         if(PlayerProfile::aiScore[templevel] == -1)
            allComplete = false;
         templevel--;
      }
      templevel++;
      if(allComplete == true)
      {
         //while(templevel <= (int)PlayerProfile::aiScore.size() && PlayerProfile::iLevelNum[templevel] == 0)
         //{
         PlayerProfile::aiLocked[templevel] = 2;

         //}
      }
   }

   if(change == true)
      PlayerProfile::writeProfile();
}

void PlayerProfile::unlock()
{
   bool change = false;
   int templevel = iCurrentLevel;
   templevel++;
   /*while(PlayerProfile::aiLocked[templevel] == 1 && PlayerProfile::iLevelNum[templevel] == 0)
   {
   PlayerProfile::aiLocked[templevel] =  0;
   templevel++;
   change = true;
   }
   */
   if(PlayerProfile::aiLocked[ templevel] == 1 && templevel < (int)PlayerProfile::aiScore.size())
   {
      PlayerProfile::aiLocked[templevel] =  0;
      change = true;
   }

   if(change == true)
      PlayerProfile::writeProfile();
}

void PlayerProfile::setTime(uint64 t)
{
   IW_CALLSTACK("PlayerProfile::setTime");

   PlayerProfile::uCurrentTime = t;
}

uint64 PlayerProfile::getCurrTime()
{
   IW_CALLSTACK("PlayerProfile::getCurrTime");

   return PlayerProfile::uCurrentTime;
}

uint64 PlayerProfile::getTime()
{
   IW_CALLSTACK("PLayerProfile::getTime");
   return PlayerProfile::auScore[PlayerProfile::iCurrentLevel];
}
