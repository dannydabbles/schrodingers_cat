//
//
//
//   Project : Schrödinger's cat
//   File Name : Box.cpp
//   Date : 1/21/2011
//   Author : P Productions
//
//


#include "Box.h"

Box::Box(CIwSVec2 index, CIwSVec2 position)
{	
   IW_CALLSTACK("Box::Box");

//   IwMemBucketPush(MAPMANAGER1);

   this->uUnitList = CIwArray<Unit*>();
   this->bConnectList = CIwArray<Box*>();
    //  IwMemBucketPush(MAP);
   for(int i = 0; i < 8 ;++i)this->bConnectList.push_back((Box*)NULL);
    //  IwMemBucketPop();
   this->jumpMap = map<Box*, CIwArray<CIwFVec2>* >();

   this->bPlatformList = CIwArray<Box*>();
   bParent = NULL;
   i2Index = CIwSVec2(index.x, index.y);
   i2Position = CIwSVec2(position.x, position.y);
   c3Colorc = CIwColour();
   c3Colorc.Set(0, 0, 0);
   bJumpCalced = false;
   bPlatformCalced = false;
   bIsEdge = false;
   bIsEdgeL = false;
   bIsEdgeR = false;
   bIsVis = false;
   bIsWalkable = false;
   bIsFilled = false;
   bIsAPath = false;
   g_dScore = numeric_limits<float>::max();
   h_dScore = numeric_limits<float>::max();
   f_dScore = numeric_limits<float>::max();
 //  IwMemBucketPop();
}

Box::~Box()
{
	IW_CALLSTACK("Box::~Box");
	
	
}

bool Box::CheckPosition(int x)
{
    IW_CALLSTACK("Box::CheckPosition");

   if(i2Index.x == x)
   {
      return true;
   }
   return false;
}

void Box::loadUnitList(CIwArray<Unit*> uUnitList)
{
    IW_CALLSTACK("Box::loadUnitList");

   this->uUnitList = uUnitList;
	cout << (int)this->uUnitList.size() << endl;
   for(int i = 0; i < (int)this->uUnitList.size(); ++i)
	{
	   if(this->uUnitList[i]->sName.compare("platform") == 0) this->bIsWalkable = true;
	}
}

void Box::addUnit(Unit* newUnit)
{
	IW_CALLSTACK("Box::addUnit");
	this->uUnitList.push_back(newUnit);
}

void Box::removeUnit(Unit* uRemove) 
{
    IW_CALLSTACK("Box::removeUnit");
	
	for(int i = 0; i < (int)this->uUnitList.size(); ++i) 
	{
		if(uUnitList[i]->sName.compare(uRemove->sName) == 0)
		{
			uUnitList.erase(uUnitList.begin() + i);
		}
	}
}

Unit* Box::getUnit(string sName)
{
    IW_CALLSTACK("Box::getUnit");

   for(int i = 0;i<(int)uUnitList.size();++i)
   {
      if(uUnitList[i]->sName == sName)
         return uUnitList[i];
   }
   return NULL;
}

void Box::reset()
{
   this->uUnitList.clear();
   this->bPlatformList.clear();
   this->bParent = NULL;
   this->bJumpCalced = false;
   this->bPlatformCalced = false;
   this->bIsEdge = false;
   this->bIsEdgeL = false;
   this->bIsEdgeR = false;
   this->bIsVis = false;
   this->bIsWalkable = false;
   this->bIsFilled = false;
   this->bIsAPath = false;
         
   while((int)this->bConnectList.size() != 8)
   {
      this->bConnectList.pop_back();
   }
   this->g_dScore = numeric_limits<float>::max();
   this->h_dScore = numeric_limits<float>::max();
   this->f_dScore = numeric_limits<float>::max();
}
