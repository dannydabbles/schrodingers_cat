//
//
//
//   Project : Schrˆdinger's cat
//   File Name : Message.h
//   Date : 1/21/2011
//   Author : P Productions
//
//


#if !defined(_MESSAGE_H)
#define _MESSAGE_H

#include <iomanip>
#include "Unit.h"
#include "PlayerProfile.h"
#include "IwGx.h"
#include "IwGxFont.h"
#include "FontManager.h"
#include "HashTable.h"

class Message : public Unit
{
public:
	Message(CIwSVec2 i2Position);
	Message(CIwSVec2, string);
   ~Message();
		
	bool bUseTexture;
	string sInstructions;
	CIwArray<float> iInstructY;
	CIwArray<int> bInstructions;
	int offset;
	CIw2DFont* fFont;
//	HashTable<int> hXOffset;
	void generateHash();

	void addString(string sAddedInstructions);
	void setFont(string sFontName);
	void setString(string sInstructions);
	void setTexture(string sTextureName);
	void setTexture(int d);
   void setColor(CIwColour color);
	void setUseTexture(bool bUseTexture);
	void setPosition(CIwSVec2);
	void scrollUp(float y);
	void update(uint64 time);
   void draw();
   void drawCenter(CIwColour);
	void drawLeft(CIwColour);

private:
   CIwColour color;
	bool bDance;
};

#endif  //_MESSAGE_H