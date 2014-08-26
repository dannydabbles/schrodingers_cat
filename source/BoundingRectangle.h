#ifndef BOUNDING_RECTANGLE_H
#define BOUNDING_RECTANGLE_H


#include "s3e.h"
#include "Iw2D.h"

// class can be used as a boundingBox or a sphere
// to be used as boundingbox use collide functions
// to be used as boudingSphere use sphereCollision
// the sphere collision will used i2Size.x/2 as the radius
// the need to center bools are so function calls can take the lefthand position
// and the class will automatically adjust it to be the center of the sprite
// or function call can take absolute position


class BoundingRectangle
{
public:
	BoundingRectangle();
	BoundingRectangle(CIwSVec2 pos, CIwSVec2 size);
	BoundingRectangle(int posX, int posY, int sizeX, int sizeY); 
	BoundingRectangle(CIwSVec2 pos, CIwSVec2 spriteSize, CIwSVec2 size, bool needToCenter = false);

   void draw();
   void setPosition(CIwSVec2, bool needToCenter = false);

	bool rectangleCollision(BoundingRectangle rec);
	bool pointCollision(CIwSVec2 point);
	bool sphereCollision(BoundingRectangle);

   CIwSVec2 getSize();

private:
	CIwSVec2 i2Position;
	CIwSVec2 i2SpriteSize;
	CIwSVec2 i2Size;
	
   bool bRectangle;
};

#endif