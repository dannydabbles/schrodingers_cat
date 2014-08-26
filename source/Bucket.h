//
//
//
//   Project : Schrödinger's cat
//   File Name : Bucket.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_BUCKET_H)
#define _BUCKET_H

#include "Buzzsaw.h"

class Bucket : public Unit
{
public:
   Bucket(CIwSVec2 i2Position);
	
   void setCap(int iC);
   void setMoveDist(int iMoveDist);
	
   void update(uint64 time);
	
private:
	bool bFall;
	bool bFilled;
	
	int iCapDeathCount;
   int iCurrentDeathCount;
	int iMoveDist;
	
	CIwSVec2 i2CurrentPosition;
   CIwSVec2 i2FinalPosition;
};

#endif  //_BUCKET_H
