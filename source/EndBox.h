//
//
//
//   Project : Schrödinger's cat
//   File Name : EndBox.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_ENDBOX_H)
#define _ENDBOX_H

#include "GameState.h"
#include "Platform.h"

class EndBox : public Platform
{
public:
   EndBox(CIwSVec2 i2Position);
   
	
   void update(uint64 time);
};

#endif  //_ENDBOX_H
