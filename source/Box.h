//
//
//
//   Project : Schrödinger's cat
//   File Name : Box.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_BOX_H)
#define _BOX_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <utility>
#include <cmath>
#include <stdlib.h>
#include "s3e.h"
#include "Iw2D.h"
#include "Screen.h"
#include "Unit.h"
//#include "HashTable.h"
#include "Memory.h"

using namespace std;

class Unit;

class Box
{
public:
   Box(CIwSVec2 index, CIwSVec2 position);
	~Box();
	
   void reset();
	
   bool bIsEdge;
   bool bIsEdgeL;
   bool bIsEdgeR;
   bool bIsVis;
   bool bIsWalkable;
   bool bIsFilled;
   bool bIsAPath;
	bool bJumpCalced;
	bool bPlatformCalced;
	
	float f_dScore;
	float g_dScore;
   float h_dScore;
	
	CIwColour c3Colorc;
	CIwSVec2 i2Index;
   CIwSVec2 i2Position;
	
	Box *bParent;
	CIwArray<Box*> bConnectList;
	CIwArray<Box*> bPlatformList;
	CIwArray<Unit*> uUnitList;
	map<Box*, CIwArray<CIwFVec2>*> jumpMap;
	
	void loadUnitList(CIwArray<Unit*> uUnitList);
   void addUnit(Unit* newUnit);
   void removeUnit(Unit* uRemove);
	
	bool CheckPosition(int x);
	
   Unit* getUnit(string sName);
};

#endif  //_BOX_H
