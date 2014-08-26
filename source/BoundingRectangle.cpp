#include "BoundingRectangle.h"

BoundingRectangle::BoundingRectangle()
{
	IW_CALLSTACK("BoundingRectangle::BoundingRectangle");

	this->i2Position = CIwSVec2(0, 0);
	this->i2Size = CIwSVec2(0, 0);
   this->bRectangle = false;
}

BoundingRectangle::BoundingRectangle(CIwSVec2 pos, CIwSVec2 size)
{
	IW_CALLSTACK("BoundingRectangle::BoundingRectangle");

	this->i2Position = pos;
	this->i2Size = size;
   this->bRectangle = true;
}

BoundingRectangle::BoundingRectangle(int posX, int posY, int sizeX, int sizeY)
{
	IW_CALLSTACK("BoundingRectangle::BoundingRectangle");

	this->i2Position = CIwSVec2(posX, posY);
	this->i2Size = CIwSVec2(sizeX, sizeY);
   this->bRectangle = false;
}

BoundingRectangle::BoundingRectangle(CIwSVec2 pos, CIwSVec2 spriteSize, CIwSVec2 size, bool needToCenter)
{
	IW_CALLSTACK("BoundingRectangle::BoundingRectangle");

	this->i2SpriteSize = spriteSize;
	if(needToCenter) 
	{	
		pos.x = pos.x + (int)(this->i2SpriteSize.x * 0.5f);
		pos.y = pos.y + (int)(this->i2SpriteSize.y * 0.5f);
	}
	this->i2Position = pos;
	this->i2Size = size;
   this->bRectangle = false;
}

bool BoundingRectangle::rectangleCollision(BoundingRectangle rec)
{
	IW_CALLSTACK("BoundingRectangle::collide");

   CIwSVec2 PosTL = this->i2Position;
   CIwSVec2 PosTR(this->i2Position.x + this->i2Size.x, this->i2Size.y);
   CIwSVec2 PosBL(this->i2Position.x, this->i2Position.y + this->i2Size.y);
   CIwSVec2 PosBR(this->i2Position.x + this->i2Size.y, this->i2Position.x + this->i2Size.x);

   CIwSVec2 thatPosTL = rec.i2Position;
   CIwSVec2 thatPosBR (rec.i2Position.x + rec.i2Size.x, rec.i2Position.y + rec.i2Size.y);

   if (PosTL.x == thatPosTL.x && PosTL.y == thatPosTL.y)
      return true;


   if(PosTL.x >= thatPosTL.x && PosTL.x <= thatPosBR.x &&
      PosTL.y >= thatPosTL.y && PosTL.y <= thatPosBR.y)
      return true;
   else if (PosBL.x >= thatPosTL.x && PosBL.x <= thatPosBR.x &&
      PosBL.y >= thatPosTL.y   && PosBL.y <= thatPosBR.y)
      return true; 
   else if (PosTR.x >= thatPosTL.x && PosTR.x <= thatPosBR.x &&
      PosTR.y >= thatPosTL.y   && PosTR.y <= thatPosBR.y)
      return true; 
   else if (PosBR.x >= thatPosTL.x && PosBR.x <= thatPosBR.x &&
      PosBR.y >= thatPosTL.y   && PosBR.y <= thatPosBR.y)
      return true; 

   return false;
}

bool BoundingRectangle::pointCollision(CIwSVec2 point)
{
	IW_CALLSTACK("BoundingRectangle::collide");

	if(point.x > this->i2Position.x && point.x < this->i2Position.x + this->i2Size.x)
	{
		if(point.y > this->i2Position.y && point.y < this->i2Position.y + this->i2Size.y)
			return true;
	}
	return false;
}

bool BoundingRectangle::sphereCollision(BoundingRectangle that)
{
	IW_CALLSTACK("BoundingRectangle::sphereCollision");

	if((float)(this->i2Position - that.i2Position).GetLength() <= (float)this->i2Size.x * 0.5f + (float)that.i2Size.x * 0.5)
	{
		return true;
	}
	return false;	
}

void BoundingRectangle::setPosition(CIwSVec2 newPos, bool needToCenter)
{
	IW_CALLSTACK("BoundingRectangle::setPosition");

	if(needToCenter)
	{
		newPos.x = newPos.x + (int)(this->i2SpriteSize.x * 0.5f);
		newPos.y = newPos.y + (int)(this->i2SpriteSize.y * 0.5f);
	}
	this->i2Position = newPos;
}

void BoundingRectangle::draw()
{
	IW_CALLSTACK("BoundingRectangle::draw");

   Iw2DSetAlphaMode(IW_2D_ALPHA_NONE);
	Iw2DSetColour(0xFFFF0F80);

   if(this->bRectangle == false)
   {
	   Iw2DDrawArc(CIwSVec2(this->i2Position.x, this->i2Position.y), CIwSVec2((int)(this->i2Size.x * 0.5f), (int)(this->i2Size.x * 0.5f)), IW_ANGLE_FROM_DEGREES(0),IW_ANGLE_FROM_DEGREES(360),100);
   }
   else
   {
      Iw2DDrawRect(this->i2Position, this->i2Size);
   }
   Iw2DSetColour(0xffffffff);
}

CIwSVec2 BoundingRectangle::getSize()
{
   return this->i2Size;
}
