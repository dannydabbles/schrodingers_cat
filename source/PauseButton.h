/*
 *  PauseButton.h
 *  Kitty
 *
 *  Created by DrLight on 4/8/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#if !defined(_PAUSEBUTTON_H)
#define _PAUSEBUTTON_H

#include "Unit.h"
#include "UserInterface.h"
#include "GameState.h"

class PauseButton : public MenuButton
{
public:
	PauseButton();
	void update(uint64 time);
};

#endif  //_PAUSEBUTTON_H