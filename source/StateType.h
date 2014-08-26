//
//
//
//   Project : Schrödinger's cat
//   File Name : StateType.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_STATETYPE_H)
#define _STATETYPE_H

#include <iostream>
#include <string>
#include <utility>
#include <ctime>
#include <cmath>
#include <stdlib.h>
#include "s3e.h"
#include "Iw2D.h"

enum StateType
{
   MENU,
   LOADING,
   PLAYING,
   DEBUG,
   PAUSED,
   MAINMENU,
   PAUSEDMENU,
   LEVELNAVIGATION,
   QUITMENU,
   SPLASHSCREEN,
   OPENINGCINEMATIC,
   CLOSINGCINEMATIC
};

#endif  //_STATETYPE_H
