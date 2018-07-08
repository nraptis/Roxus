/*
 *  Shapes.h
 *  Darts
 *
 *  Created by Nick Raptis on 11/24/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef SHAPES_H
#define SHAPES_H

#include "FPoint.h"

class Line
{
public:
	Line(void){}
	Line(FPoint pPoint1, FPoint pPoint2);
    Line(float x1, float y1, float x2, float y2);
	Line(Line &pLine){*this=pLine;}
	Line(const Line& pLine);
	
	virtual			~Line(void){}
	
	Line			&operator=(const Line &pLine);
	FPoint			mPoint1;
	FPoint			mPoint2;
	
	FPoint			ClosestPoint(FPoint pPoint);
};

class Circle
{
public:
	Circle();
	Circle(FPoint pCenter, float pRadius);
	Circle(Circle &pCircle){*this=pCircle;}
	Circle(const Circle& pCircle);
	
	virtual			~Circle(void){}
	
	float			mRadius;
	FPoint			mCenter;
};

class Ellipse
{
public:
	Ellipse();
	Ellipse(FPoint pCenter, float pRadiusX, float pRadiusY);
	Ellipse(FPoint pCenter, FPoint pRadii);
	Ellipse(Ellipse &pEllipse){*this=pEllipse;}
	Ellipse(const Ellipse& pEllipse);
	
	virtual			~Ellipse(void){}
	
	FPoint			mCenter;
	float			mRadiusX;
	float			mRadiusY;
	
	bool			IntersectsFPoint(FPoint pPoint);
	bool			IntersectsLine(Line pLine);
};

#endif