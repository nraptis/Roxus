/*
 *  Shapes.cpp
 *  Darts
 *
 *  Created by Nick Raptis on 11/24/10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "Shapes.h"

#include "stdafx.h"

Line::Line(FPoint pPoint1, FPoint pPoint2)
{
	mPoint1=pPoint1;
	mPoint2=pPoint2;
}

Line::Line(float x1, float y1, float x2, float y2)
{
    mPoint1=FPoint(x1,y1);
	mPoint2=FPoint(x2,y2);
}

Line &Line::operator=(const Line &pLine)
{
	mPoint1=pLine.mPoint1;
	mPoint2=pLine.mPoint2;
	return *this;
}

Line::Line(const Line& pLine) 
{
	mPoint1=pLine.mPoint1;
	mPoint2=pLine.mPoint2;
}

FPoint Line::ClosestPoint(FPoint pPoint)
{
	FPoint aFactor1=pPoint-mPoint1;
	FPoint aFactor2=mPoint2-mPoint1;
	float aLength=aFactor2.Length();
	
	if(aLength <= 0.025f)
	{
		return mPoint1;
	}
	else
	{
		aFactor2 /= aLength;
		float aScalar=aFactor2.Dot(aFactor1);
		if(aScalar<0)return mPoint1;
		if(aScalar>aLength)return mPoint2;
		return mPoint1+aFactor2*aScalar;
	}
}

Circle::Circle()
{
	mRadius=0;
}

Circle::Circle(FPoint pCenter, float pRadius)
{
	mRadius=pRadius;
	mCenter=pCenter;
}

Circle::Circle(const Circle&pCircle)
{
	mRadius=pCircle.mRadius;
	mCenter=pCircle.mCenter;
}

Ellipse::Ellipse()
{
	mRadiusX=0;
	mRadiusY=0;
}

Ellipse::Ellipse(FPoint pCenter, float pRadiusX, float pRadiusY)
{
	mCenter=pCenter;
	mRadiusX=pRadiusX;
	mRadiusY=pRadiusY;
}

Ellipse::Ellipse(FPoint pCenter, FPoint pRadii)
{
	mCenter=pCenter;
	mRadiusX=pRadii.mX;
	mRadiusY=pRadii.mY;
}

Ellipse::Ellipse(const Ellipse& pEllipse)
{
	mCenter=pEllipse.mCenter;
	mRadiusX=pEllipse.mRadiusX;
	mRadiusY=pEllipse.mRadiusY;
}

bool Ellipse::IntersectsFPoint(FPoint pPoint)
{
	pPoint-=mCenter;
	float aMajorAxis=mRadiusX;
    float aMinorAxis=mRadiusX;
    if(mRadiusY > aMajorAxis)
    {
        aMajorAxis=mRadiusY;
    }
    else
    {
        aMinorAxis=mRadiusY;
    }
    
	float aAxisRatio=aMinorAxis/aMajorAxis;
	if(aMajorAxis==mRadiusX)pPoint.mX*=aAxisRatio;
	if(aMajorAxis==mRadiusY)pPoint.mY*=aAxisRatio;
	return pPoint.Length()<=aMinorAxis;
}

bool Ellipse::IntersectsLine(Line pLine)
{
    
	return IntersectsFPoint(pLine.ClosestPoint(mCenter));
}


