//
//
//
//   Project : Schrödinger's cat
//   File Name : CreditMenu.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_CREDITMENU_H)
#define _CREDITMENU_H

#include "UserInterface.h"

class CreditMenu : public UserInterface
{
public:
   CreditMenu();

   void update(uint64 time);
	void draw();

private:
   CIwSVec2 i2FinalPosition;
};

#endif  //_CREDITMENU_H