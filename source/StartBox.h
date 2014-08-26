//
//
//
//   Project : Schrödinger's cat
//   File Name : StartBox.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_STARTBOX_H)
#define _STARTBOX_H

#include "Unit.h"

class StartBox : public Unit
{
public:
   StartBox(CIwSVec2 i2Position);
	void update(uint64 time);
};

#endif  //_STARTBOX_H
