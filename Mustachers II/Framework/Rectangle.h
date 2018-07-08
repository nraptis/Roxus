#include "FPoint.h"

#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
public:
	
	Rectangle(){mX=0;mY=0;mWidth=0;mHeight=0;}
	Rectangle(float x, float y, float pWidth, float pHeight){mX=x;mY=y;mWidth=pWidth;mHeight=pHeight;}
	
	float mX;
	float mY;
	float mWidth;
	float mHeight;
	
	float			Left(){return mX;}
	float			Right(){return mX+mWidth;}
	float			Top(){return mY;}
	float			Bottom(){return mY+mHeight;}
	
	FPoint			TopLeft(){return FPoint(mX,mY);}
	FPoint			TopRight(){return FPoint(mX+mWidth,mY);}
	FPoint			BottomLeft(){return FPoint(mX,mY+mHeight);}
	FPoint			BottomRight(){return FPoint(mX+mWidth,mY+mHeight);}
	FPoint			Center(){return FPoint(mX+mWidth/2, mY+mHeight/2);}
	
	void			Size(float x, float y, float pWidth, float pHeight){mX=x;mY=y;mWidth=pWidth;mHeight=pHeight;}
	
	bool			Contains(float x, float y){return x>=mX && x<= (mX+mWidth) && y>=mY && y<= (mY+mHeight);}
	
	bool			Intersects(Rectangle &pRect){return Intersects(pRect.mX,pRect.mY,pRect.mWidth,pRect.mHeight);}
	bool			Intersects(float x, float y, float pWidth, float pHeight){return !((x+pWidth<=mX) || (y+pHeight<=mY) || (x>=mX+mWidth) || (y>=mY+mHeight));}
	
};

class IRectangle
{
public:
	
	int mX;
	int mY;
	int mWidth;
	int mHeight;
};

#endif