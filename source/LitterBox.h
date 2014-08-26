//
//
//
//   Project : Schrödinger's cat
//   File Name : LitterBox.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_LITTERBOX_H)
#define _LITTERBOX_H

#include "ShinyUnit.h"

class LitterBox : public ShinyUnit
{
public:
   LitterBox(CIwSVec2 i2Position);
	
	void update(uint64 time);
	
private:
   bool bFull;
};

#endif  //_LITTERBOX_H
