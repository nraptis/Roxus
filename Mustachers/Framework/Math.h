#ifndef MATH_H
#define MATH_H

#define D_R 0.01745329251994329576923690768488
#define R_D 57.2957795130823208767981548141052

#define PI 3.1415926535897932384626433832795028841968
#define PI2 (2 * PI)
#define PI_2 (PI / 2.0f)

#include <math.h>
#include "FPoint.h"


float Distance(float x1, float y1, float x2, float y2);
inline float Distance(float x1, float y1, FPoint p2){return Distance(x1,y1,p2.mX,p2.mY);}
inline float Distance(FPoint p1, float x2, float y2){return Distance(p1.mX,p1.mY,x2,y2);}
inline float Distance(FPoint p1, FPoint p2){return Distance(p1.mX,p1.mY,p2.mX,p2.mY);}


float DistanceSquared(float x1, float y1, float x2, float y2);
inline float DistanceSquared(float x1, float y1, FPoint p2){return DistanceSquared(x1,y1,p2.mX,p2.mY);}
inline float DistanceSquared(FPoint p1, float x2, float y2){return DistanceSquared(p1.mX,p1.mY,x2,y2);}
inline float DistanceSquared(FPoint p1, FPoint p2){return DistanceSquared(p1.mX,p1.mY,p2.mX,p2.mY);}


float DistanceSquared(float x1, float y1, float z1, float x2, float y2, float z2);
inline float DistanceSquared(Vector3 p1, Vector3 p2){return DistanceSquared(p1.mX,p1.mY,p1.mZ,p2.mX,p2.mY,p2.mZ);}

bool CircleCircleIntersect(FPoint pPos1, float pRadius1, FPoint pPos2, float pRadius2);

FPoint AngleToVector(float pDegrees);

Vector3 AngleToVector3D(float pDegrees);

float Sin(float pDegree);
float Cos(float pDegrees);
float Tan(float pDegrees);

bool IsPowerOfTwo(int pNumber);

int ClosestPowerOfTwo(int pNumber);

float DistanceBetweenAngles(float theDegrees1, float theDegrees2);

float FaceTarget(float pOriginX, float pOriginY, float pTargetX=0, float pTargetY=0);
inline float FaceTarget(FPoint pPos, FPoint pTarget=FPoint(0,0)){return FaceTarget(pPos.mX, pPos.mY, pTarget.mX, pTarget.mY);}


FPoint PivotPoint(FPoint pPoint, float pDegrees, FPoint pCenter, float pScale=1.0f);

FPoint PivotPoint(FPoint pPoint, float pDegrees);

float MinC(float pNum, float pMin);
float MaxC(float pNum, float pMax);
float Trim(float pNum, float pMin=-10000000.0f, float pMax=10000000.0f);

//(Bx - Ax) * (Cy - Ay) - (By - Ay) * (Cx - Ax)
int SideOfLine(float pTestX, float pTestY, float pLineX1, float pLineY1, float pLineX2, float pLineY2);

Vector3 Rotate3D(Vector3 pPoint, Vector3 pAxis, float pDegrees);

bool TriangleIsClockwise(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3);

bool QuadContainsPoint(float pPointX, float pPointY, float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4);


float TriangleArea(float x1, float y1, float x2, float y2, float x3, float y3);
bool Between(float x1, float y1, float x2, float y2, float x3, float y3);
bool SegmentsIntersect(FPoint theStart1, FPoint theEnd1, FPoint theStart2, FPoint theEnd2);


/*
bool EllipseIntersectLine(FPoint pCenter, FPoint pRadii, FPoint pLineStart, , FPoint pLineEnd)
{
	//
	// Get the closest point on the line to the center of the ellipse.
	//
	Point aClosest=theLine.ClosestPoint(theCenter);
	
	//
	// Move it into ellipse space
	//
	aClosest-=theCenter;
	
	//
	// Figure out some ellipse stuff
	//
	float aMajorAxis=max(theRadius.mX,theRadius.mY);
	float aMinorAxis=min(theRadius.mX,theRadius.mY);
	float aAxisRatio=aMinorAxis/aMajorAxis;
	
	//
	// Scale our point
	//
	if (aMajorAxis==theRadius.mX) aClosest.mX*=aAxisRatio;
	if (aMajorAxis==theRadius.mY) aClosest.mY*=aAxisRatio;
	
	//
	// Is it in the circle?
	//
	if (aClosest.Length()<=aMinorAxis) return true;
	return false;
}
 */

#endif