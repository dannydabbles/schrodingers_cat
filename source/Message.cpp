/*
*  Message.cpp
*  Kitty
*
*  Created by Sam Medalen on 2/23/11.
*  Copyright 2011 __MyCompanyName__. All rights reserved.
*
*/

#include "Message.h"

Message::Message(CIwSVec2 i2Position): Unit()
{
   IW_CALLSTACK("Message::Message");
   /*
   tTextureList.push_back(ImageManager::getImage("catmove"));
   tTextureList.push_back(ImageManager::getImage("catjump"));
   tTextureList.push_back(ImageManager::getImage("catdistract"));
   tTextureList.push_back(ImageManager::getImage("catdeath1"));
   tTextureList.push_back(ImageManager::getImage("catdeath2"));
   tTextureList.push_back(ImageManager::getImage("catlever"));
   tTextureList.push_back(ImageManager::getImage("catspike"));
   tTextureList.push_back(ImageManager::getImage("catbucket"));
   tTextureList.push_back(ImageManager::getImage("catblockpath"));
   tTextureList.push_back(ImageManager::getImage("catblockfall"));
   */
   this->sName = "message";
   this->sInstructions = "";
   this->bUseTexture = true;
   this->i2Position = i2Position;
   fFont = Iw2DCreateFont("lindsey-bold.gxfont");
   Iw2DSetFont(fFont);
   this->bDance = false;
   this->iInstructY = CIwArray<float>();
   this->bInstructions = CIwArray<int>();
   this->offset = 4;
   //	this->hXOffset = HashTable<int>();
   //	this->generateHash();
   this->color.Set(00,00,00);

   ClassTracker::addUnit(this);

}

Message::Message(CIwSVec2 i2Position, string s): Unit()
{
   IW_CALLSTACK("Message::Message");
   /*
   tTextureList.push_back(ImageManager::getImage("catmove"));
   tTextureList.push_back(ImageManager::getImage("catjump"));
   tTextureList.push_back(ImageManager::getImage("catdistract"));
   tTextureList.push_back(ImageManager::getImage("catdeath1"));
   tTextureList.push_back(ImageManager::getImage("catdeath2"));
   tTextureList.push_back(ImageManager::getImage("catlever"));
   tTextureList.push_back(ImageManager::getImage("catspike"));
   tTextureList.push_back(ImageManager::getImage("catbucket"));
   tTextureList.push_back(ImageManager::getImage("catblockpath"));
   tTextureList.push_back(ImageManager::getImage("catblockfall"));
   */
   this->sName = "message";
   
   this->i2Position = i2Position;
   fFont = FontManager::getFont(s);
   Iw2DSetFont(fFont);
   this->iInstructY = CIwArray<float>();
   this->bInstructions = CIwArray<int>();
   this->offset = 4;
   this->bDance = true;
   this->sInstructions = "";
   this->bUseTexture = false;
   //	this->hXOffset = HashTable<int>();
   //	this->generateHash();
   this->color.Set(0, 0, 0, 255);
   this->brBoundingBox = BoundingRectangle(this->i2Position, this->i2Size);
}

void Message::generateHash()
{
   /*
   this->hXOffset.insert(pair<string, int>("a",18));
   this->hXOffset.insert(pair<string, int>("b",18));
   this->hXOffset.insert(pair<string, int>("c",18));
   this->hXOffset.insert(pair<string, int>("d",18));
   this->hXOffset.insert(pair<string, int>("e",18));
   this->hXOffset.insert(pair<string, int>("f",18));
   this->hXOffset.insert(pair<string, int>("g",18));
   this->hXOffset.insert(pair<string, int>("h",18));
   this->hXOffset.insert(pair<string, int>("i",18));
   this->hXOffset.insert(pair<string, int>("j",18));
   this->hXOffset.insert(pair<string, int>("k",18));
   this->hXOffset.insert(pair<string, int>("l",10));
   this->hXOffset.insert(pair<string, int>("m",18));
   this->hXOffset.insert(pair<string, int>("o",18));
   this->hXOffset.insert(pair<string, int>("p",18));
   this->hXOffset.insert(pair<string, int>("q",18));
   this->hXOffset.insert(pair<string, int>("r",18));
   this->hXOffset.insert(pair<string, int>("s",18));
   this->hXOffset.insert(pair<string, int>("t",18));
   this->hXOffset.insert(pair<string, int>("u",18));
   this->hXOffset.insert(pair<string, int>("v",18));
   this->hXOffset.insert(pair<string, int>("w",18));
   this->hXOffset.insert(pair<string, int>("x",18));
   this->hXOffset.insert(pair<string, int>("y",18));
   this->hXOffset.insert(pair<string, int>("z",18));
   this->hXOffset.insert(pair<string, int>("A",18));
   this->hXOffset.insert(pair<string, int>("B",18));
   this->hXOffset.insert(pair<string, int>("C",18));
   this->hXOffset.insert(pair<string, int>("D",18));
   this->hXOffset.insert(pair<string, int>("E",18));
   this->hXOffset.insert(pair<string, int>("F",18));
   this->hXOffset.insert(pair<string, int>("G",18));
   this->hXOffset.insert(pair<string, int>("I",18));
   this->hXOffset.insert(pair<string, int>("J",18));
   this->hXOffset.insert(pair<string, int>("K",18));
   this->hXOffset.insert(pair<string, int>("L",18));
   this->hXOffset.insert(pair<string, int>("M",18));
   this->hXOffset.insert(pair<string, int>("N",18));
   this->hXOffset.insert(pair<string, int>("O",18));
   this->hXOffset.insert(pair<string, int>("P",18));
   this->hXOffset.insert(pair<string, int>("Q",18));
   this->hXOffset.insert(pair<string, int>("R",18));
   this->hXOffset.insert(pair<string, int>("S",18));
   this->hXOffset.insert(pair<string, int>("T",18));
   this->hXOffset.insert(pair<string, int>("U",18));
   this->hXOffset.insert(pair<string, int>("V",18));
   this->hXOffset.insert(pair<string, int>("W",18));
   this->hXOffset.insert(pair<string, int>("X",18));
   this->hXOffset.insert(pair<string, int>("Y",18));
   this->hXOffset.insert(pair<string, int>("Z",18));
   this->hXOffset.insert(pair<string, int>("0",18));
   this->hXOffset.insert(pair<string, int>("1",18));
   this->hXOffset.insert(pair<string, int>("2",18));
   this->hXOffset.insert(pair<string, int>("3",18));
   this->hXOffset.insert(pair<string, int>("4",18));
   this->hXOffset.insert(pair<string, int>("5",18));
   this->hXOffset.insert(pair<string, int>("6",18));
   this->hXOffset.insert(pair<string, int>("7",18));
   this->hXOffset.insert(pair<string, int>("8",18));
   this->hXOffset.insert(pair<string, int>("9",18));
   this->hXOffset.insert(pair<string, int>(".",18));
   this->hXOffset.insert(pair<string, int>(",",18));
   this->hXOffset.insert(pair<string, int>(" ",18));
   */
}

void Message::update(uint64 time)
{
   IW_CALLSTACK("Message::update");

   this->iTime = time;
   this->iTimePassed += time;

   if(bAffectUpdate == true)
   {
      this->bDrawn = !this->bDrawn;
      bAffectUpdate = false;

   }


   //legitly tied to clock
      this->iTimePassed = 0;
      for( int i = 0; i <(int)this->sInstructions.size(); ++i)
      {
         int a = (IwRandMinMax(0,99) % 3) - 1;
         //this->iInstructY[i] += a;
         if(this->iInstructY[i] > this->offset)
         {
            this->bInstructions[i] = 0;
            this->iInstructY[i] = (float)offset;
         }
         if(this->iInstructY[i] < -this->offset)
         {
            this->iInstructY[i] = (float)-offset;
            this->bInstructions[i] = 1;
         }
         if(this->bInstructions[i] == 1)
            this->iInstructY[i] += ( this->iTime * 0.007f); // <- make this decimal bigger to move faster, smaller to get slower dance
         else
            this->iInstructY[i] -= ( this->iTime * 0.007f);

      }
   
}

void Message::setTexture(string sTextureName)
{
   IW_CALLSTACK("Message::setTexture");

   cout << sTextureName << endl;
   this->tTextureList.push_back(ImageManager::getImage(sTextureName.c_str()));
   this->iTextureIndex = (int)tTextureList.size() - 1;
   cout<<iTextureIndex<<endl;
}

void Message::setTexture(int d)
{
   IW_CALLSTACK("Message::setTexture");
   if(d == 0)
      this->tTextureList.push_back(ImageManager::getImage("e"));
   else if(d > 0 && d < 3)
      this->tTextureList.push_back(ImageManager::getImage("e10"));
   else if(d > 2 && d < 5)
      this->tTextureList.push_back(ImageManager::getImage("t"));
   else if(d > 4 && d < 8)
      this->tTextureList.push_back(ImageManager::getImage("m"));
   else if(d > 7 && d)
      this->tTextureList.push_back(ImageManager::getImage("ao"));
   this->iTextureIndex = (int)tTextureList.size() - 1;
}

void Message::setUseTexture(bool bUseTexture)
{
   IW_CALLSTACK("Message::setUseTexture");

   this->bUseTexture = bUseTexture;
}

void Message::setString(string sInstruction)
{
   IW_CALLSTACK("Message::setString");
   if(this->bDrawn == false)
   {
      this->iInstructY.clear();
      this->bInstructions.clear();
      this->sInstructions = sInstruction;
      int diff = -this->offset;
      bool up = true;
      for(int i = 0; i < (int)this->sInstructions.size(); ++i)
      {
         if(up == true)
         {
            ++diff;
            if(diff > this->offset)
            {
               up = false;
               diff = this->offset - 1;
            }
         }
         if(up == false)
         {
            --diff;
            if(diff < -this->offset)
            {
               up = true;
               diff = -this->offset+1;
            }
         }
         this->iInstructY.push_back((float)diff);
         this->bInstructions.push_back(up);
      }
   }
}

void Message::addString(string sAddInstructions)
{
   IW_CALLSTACK("Message::addString");

   this->sInstructions += sAddInstructions;
   this->iInstructY.clear();
   this->bInstructions.clear();
   for(int i = 0; i <(int)this->sInstructions.size(); ++i)
   {
      this->iInstructY.push_back((float)IwRandMinMax(-this->offset, this->offset));
      this->bInstructions.push_back(0);
   }
}

void Message::setFont(string sFontName)
{
   IW_CALLSTACK("Message::setFont");

   //fFont = Iw2DCreateFont(sFontName.c_str());
   this->fFont = FontManager::getFont(sFontName);
   this->bDance = true;
}

void Message::setColor(CIwColour color)
{
   this->color = color;
}

void Message::scrollUp(float y)
{
   this->f2AbsPosition.y -= y;
   this->i2Position.y = (int)this->f2AbsPosition.y;
}

void Message::setPosition(CIwSVec2 p)
{
   this->i2Position = p;
}

void Message::draw()
{
   IW_CALLSTACK("Message::draw");

   if(this->bUseTexture == false)
   {
      CIwSVec2 region(400, 66);
      Iw2DSetColour(this->color);
      Iw2DSetFont(this->fFont);
      if(this->bDrawn == false && this->bDance == true)
      {
         Iw2DDrawString(this->sInstructions.c_str(), this->i2Position, region, IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);
      }
      else if (this->bDrawn == false)
      {
         int yoffset = 0;
         int xoffset = 0;
         for(int i = 0, j = 0; i < (int)this->sInstructions.size(); ++i, ++j)
         {
            if(i != 0 && sInstructions[i - 1] == '/')
            {
               j = 0;
               xoffset = 0;
               yoffset += 30;
            }
            if(sInstructions[i] == '/')
               continue;
            Iw2DDrawString(sInstructions.substr(i,1).c_str(),CIwSVec2( this->i2Position.x+ xoffset , this->i2Position.y + this->iInstructY[i] + yoffset), region, IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_TOP);
            xoffset += PlayerProfile::getHash(sInstructions.substr(i,1));
         }
      }
      Iw2DSetColour(0xffffffff);
   }
   else 
   {
      if((int)this->tTextureList.size() != 0)
         Unit::draw();
      //Iw2DDrawImage(this->tTextureList[this->iTextureIndex], this->i2Position);
   }
}

void Message::drawCenter(CIwColour c)
{
   CIwSVec2 region(480,320);
   Iw2DSetColour(c); 
   Iw2DSetFont(this->fFont);
   Iw2DDrawString(this->sInstructions.c_str(), this->i2Position, region, IW_2D_FONT_ALIGN_CENTRE, IW_2D_FONT_ALIGN_CENTRE);
}

void Message::drawLeft(CIwColour c)
{
   CIwSVec2 region(640, 320);
   Iw2DSetColour(c); 
   Iw2DSetFont(this->fFont);
   Iw2DDrawString(this->sInstructions.c_str(), this->i2Position, region, IW_2D_FONT_ALIGN_LEFT, IW_2D_FONT_ALIGN_CENTRE);
}

Message::~Message()
{
   // messages dont need a font, so check null first
   // actually fonts shold be destroyed in hashtable
}
