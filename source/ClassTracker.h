#ifndef CLASS_TRACKER_H
#define CLASS_TRACKER_H

#include "box.h"
#include "Unit.h"
#include "iostream"

class Unit;

class ClassTracker
{
public:
	static int units;
	static int message;
	static int maps;
	static int catAI;
	static int grid;
	static int mouseAI;
	static int blood;
	static void print();
	static void addUnit(const Unit * unit);
	static void removeUnit(const Unit * unit);

	static CIwArray<string> unitsArray;
} ;



#endif
