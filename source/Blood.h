//
//
//
//   Project : Schrödinger's cat
//   File Name : Blood.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_BLOOD_H)
#define _BLOOD_H

#include "Unit.h"
#include "Particle.h"

class Blood : public Unit
{
public:
   Blood();
   ~Blood();

	void update(uint64 time);
   void draw();
   void setPosition(CIwSVec2 i2Position);

private:
   int iTextureCount;
   int iParticleCount;
   CIwArray<Particle*> pBloodList;
   CIwMat2D mRot;
   

};

#endif  //_BLOOD_H