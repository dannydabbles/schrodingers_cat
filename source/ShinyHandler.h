//
//
//
//   Project : Schrˆdinger's cat
//   File Name : ShinyHandler.h
//   Date : 1/21/2011
//   Author : P Productions
//
//

#if !defined(_SHINYHANDLER_H)
#define _SHINYHANDLER_H

#include "ShinyUnit.h"
#include "Cat.h"
#include "CatAI.h"

class ShinyHandler
{
public:
   friend class CatAI;

	ShinyHandler(Cat* cCat, CIwArray<ShinyUnit*> suShinyList);
   ~ShinyHandler();
	
	pair<Box*, Box*>* calcShiniest(Box* bStartBox, Box* bFinishBox);
	
private:
	Cat* cKitty;
   ShinyUnit* suGoal;

	CIwArray<ShinyUnit*> suShinyList;
   
};
#endif