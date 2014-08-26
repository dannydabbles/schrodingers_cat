/*
 *  MouseAI.h
 *  Kitty
 *
 *  Created by Sam Medalen on 3/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#if !defined(_MOUSEAI_H)
#define _MOUSEAI_H


#include "Grid.h"
#include "Mouse.h"

class Grid;

using namespace std;

class MouseAI{
public:
	MouseAI(CIwArray<Mouse*> ulMouseList);
	virtual void update(Cat * pcKitty);
	CIwArray<Mouse*> ulMouseList;
};

#endif  //_MOUSEAI_H