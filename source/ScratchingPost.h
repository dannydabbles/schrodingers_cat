//
//
//
//   Project : Schrödinger's cat
//   File Name : ScratchingPost.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_SCRATCHINGPOST_H)
#define _SCRATCHINGPOST_H

#include "ShinyUnit.h"

class ScratchingPost : public ShinyUnit
{
public:
   ScratchingPost(CIwSVec2 i2Position);
	void update(uint64 time);
};

#endif  //_SCRATCHINGPOST_H
