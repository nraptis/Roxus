#include "Math.h"
#include "stdafx.h"

float Distance(float x1, float y1, float x2, float y2)
{
	float aXDiff=x1-x2;
	float aYDiff=y1-y2;
	return sqrtf(aXDiff*aXDiff+aYDiff*aYDiff);
}

float DistanceSquared(float x1, float y1, float x2, float y2)
{
	float aXDiff=x1-x2;
	float aYDiff=y1-y2;
	return aXDiff*aXDiff+aYDiff*aYDiff;
}


float DistanceSquared(float x1, float y1, float z1, float x2, float y2, float z2)
{
    float aXDiff=x1-x2;
	float aYDiff=y1-y2;
    float aZDiff=z1-z2;
	return aXDiff*aXDiff+aYDiff*aYDiff+aZDiff*aZDiff;
}

bool CircleCircleIntersect(FPoint pPos1, float pRadius1, FPoint pPos2, float pRadius2)
{
	float aRadiiSum=pRadius1+pRadius2;
	return DistanceSquared(pPos1,pPos2)<=aRadiiSum*aRadiiSum;
}

FPoint AngleToVector(float pDegrees)
{
    return FPoint(Sin(pDegrees),Cos(pDegrees));
}


Vector3 AngleToVector3D(float pDegrees)
{
    return Vector3(Sin(pDegrees),Cos(pDegrees),0.0f);
}

bool IsPowerOfTwo(int pNumber){return(pNumber&-pNumber)==pNumber;}

int ClosestPowerOfTwo(int pNumber)
{
	unsigned int aReturn=1;
	while((unsigned int)pNumber<aReturn&&aReturn!=0x40000000)aReturn=(aReturn<<1);
	return (int)aReturn;
}

int SideOfLine(float pTestX, float pTestY, float pLineX1, float pLineY1, float pLineX2, float pLineY2)
{
    float aCross = (pLineX2 - pLineX1) * (pTestY - pLineY1) - (pLineY2 - pLineY1) * (pTestX - pLineX1);
    if(aCross > 0)return 1;
    else if(aCross < 0)return -1;
    else return 0;
    
}


float Sin(float pDegrees){return sin(D_R*pDegrees);}

float Cos(float pDegrees){return cos(D_R*pDegrees);}

float Tan(float pDegrees){return tan(D_R*pDegrees);}

float DistanceBetweenAngles(float theDegrees1, float theDegrees2)
{
	float aDifference = theDegrees1 - theDegrees2;
	aDifference = (float)fmod(aDifference,360);
	if(aDifference < 0)aDifference+=360;
	if(aDifference > 180)return 360 - aDifference;
	else return -aDifference;
}

float FaceTarget(float pOriginX, float pOriginY, float pTargetX, float pTargetY)//(FPoint &pPos, FPoint &pTarget)
{
	return atan2f(pTargetX-pOriginX,pTargetY-pOriginY)*(-R_D);
}

float Trim(float pNum, float pMin, float pMax)
{
	float aReturn=pNum;
	if(aReturn<pMin)aReturn=pMin;
	if(aReturn>pMax)aReturn=pMax;
	return aReturn;
}

float MinC(float pNum, float pMin)
{
	if(pNum > pMin)return pNum;
	else return pMin;
}

float MaxC(float pNum, float pMax)
{
	if(pNum < pMax)return pNum;
	else return pMax;
}

bool TriangleIsClockwise(float pX1, float pY1, float pX2, float pY2, float pX3, float pY3)
{
    return (pX2-pX1)*(pY3-pY2)-(pX3-pX2)*(pY2-pY1) > 0;
}

bool QuadContainsPoint(float pPointX, float pPointY, float pX1, float pY1, float pX2, float pY2, float pX3, float pY3, float pX4, float pY4)
{
    float aX[4];
    float aY[4];
    
    aX[0]=pX1;
    aX[1]=pX2;
    aX[2]=pX3;
    aX[3]=pX4;
    
    aY[0]=pY1;
    aY[1]=pY2;
    aY[2]=pY3;
    aY[3]=pY4;
    
    bool aReturn = false;
	for(int aStart=0,aEnd=3;aStart<4;aEnd=aStart++)
	{
		if ((((aY[aStart]<=pPointY) && (pPointY<aY[aEnd]))||
             ((aY[aEnd]<=pPointY) && (pPointY<aY[aStart])))&&
			(pPointX < (aX[aEnd] - aX[aStart])*(pPointY - aY[aStart])
             /(aY[aEnd] - aY[aStart]) + aX[aStart]))
        {
			aReturn=!aReturn;
        }
    }
    
	return aReturn;
    
}

FPoint PivotPoint(FPoint pPoint, float pDegrees, FPoint pCenter, float pScale)
{
    FPoint aReturn;
    
    float aDiffX = pCenter.mX - pPoint.mX;
    float aDiffY = pCenter.mY - pPoint.mY;
    
    float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
    
    if(aDist > 0.25f)
    {
        
        aDist=sqrtf(aDist);
        
        float aRotation = FaceTarget(aDiffX, aDiffY);
        aRotation = pDegrees + aRotation;
        
        //if(aRotation < -360.0f || aRotation > 360.0f)
        //{
        //    aRotation = fmodf(aRotation, 360.0f);
        //}
        
        aReturn.mX = pCenter.mX + Sin(180.0f -aRotation) * pScale * aDist;
        aReturn.mY = pCenter.mY + Cos(180.0f -aRotation) * pScale * aDist;
        
    }
    else
    {
        aReturn = pPoint;
        
        aDiffX=0.0f;
        aDiffY=0.0f;
        
        aDist=0.0f;
    }
    return aReturn;
}

FPoint PivotPoint(FPoint pPoint, float pDegrees)
{
    return PivotPoint(pPoint, pDegrees, FPoint(0,0), 1.0f);
}

Vector3 Rotate3D(Vector3 pPoint, Vector3 pAxis, float pDegrees)
{	
	Vector3 aCentroid=pPoint;
	Vector3 aDir=Vector3(pAxis.mX,pAxis.mY,pAxis.mZ);
	
	float aLength = aDir.Length();
	
	if(aLength > 0.015f)
	{
		aDir /= aLength;
	}
	else
	{
		aDir.mX=1;
		aDir.mY=0;
		aDir.mZ=0;
	}
	
	float aDirX=aDir.mX;
	float aDirY=aDir.mY;
	float aDirZ=aDir.mZ;
	
	float aX=aCentroid.mX;
	float aY=aCentroid.mY;
	float aZ=aCentroid.mZ;
	
	float aCos = Cos(pDegrees);
	float aSin = Sin(pDegrees);
	float aCosInv=1-aCos;
	
	float xy = aDirX*aDirY*aCosInv;
	float xz = aDirX*aDirZ*aCosInv;
	float yz = aDirY*aDirZ*aCosInv;
	
	float xs = aDirX*aSin;
	float ys = aDirY*aSin;
	float zs = aDirZ*aSin;

	aCentroid.mX = (aDirX*aDirX*aCosInv+aCos) * aX + (xy-zs) * aY + (xz+ys) * aZ;
	aCentroid.mY = (xy+zs) * aX + (aDirY*aDirY*aCosInv+aCos) * aY + (yz-xs) * aZ;
	aCentroid.mZ = (xz+ys) * aX + (yz-xs) * aY + (aDirZ*aDirZ*aCosInv+aCos) * aZ;
    
	return aCentroid;
}



//float aTargetRot=FaceTarget(mPos, mRobot->mPos);
//printf("Rotating From (%f,%f) To (%f,%f) = %f Vector(%f, %f)\n", mPos.mX, mPos.mY, mRobot->mPos.mX, mRobot->mPos.mY, FaceTarget(mPos, mRobot->mPos), AngleToVector(FaceTarget(mPos, mRobot->mPos)).mX, AngleToVector(FaceTarget(mPos, mRobot->mPos)).mY);
//mGunRotation=atan2(mRobot->mPos.mX-mPos.mX,mRobot->mPos.mY-mPos.mY)*R_D;




float TriangleArea(float x1, float y1, float x2, float y2, float x3, float y3)
{
	return (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
}

bool Between(float x1, float y1, float x2, float y2, float x3, float y3)
{
	if (x1 != x2)return (x1 <= x3 && x3 <= x2) || (x1 >= x3 && x3 >= x2);
	else return (y1 <= y3 && y3 <= y2) || (y1 >= y3 && y3 >= y2);
}

bool SegmentsIntersect(FPoint theStart1, FPoint theEnd1, FPoint theStart2, FPoint theEnd2)
{
	float aArea1, aArea2, aArea3, aArea4;
	if((aArea1 = TriangleArea(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theStart2.mX, theStart2.mY)) == 0)
	{
		if (Between(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theStart2.mX, theStart2.mY))
		{
			return true;
		}
		else
		{
			if (TriangleArea(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theEnd2.mX, theEnd2.mY) == 0)
			{
				if(Between(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theStart1.mX, theStart1.mY))
				{
					return true;
				}
				if(Between (theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theEnd1.mX, theEnd1.mY))
				{
					return true;
				}
				return false;
			}
			else return false;
		}
	}
	if ((aArea2 = TriangleArea(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theEnd2.mX, theEnd2.mY)) == 0)
	{
		return Between(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theEnd2.mX, theEnd2.mY);
	}
	if ((aArea3 = TriangleArea(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theStart1.mX, theStart1.mY)) == 0)
	{
		if (Between(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theStart1.mX, theStart1.mY))
		{
			return true;
		}
		else
		{
			if (TriangleArea(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theEnd1.mX, theEnd1.mY) == 0)
			{
				if(Between(theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theStart2.mX, theStart2.mY))
				{
					return true;
				}
				if(Between (theStart1.mX, theStart1.mY, theEnd1.mX, theEnd1.mY, theEnd2.mX, theEnd2.mY))
				{
					return true;
				}
				return false;
			}
			return false;
		}
	}
	if ((aArea4 = TriangleArea(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theEnd1.mX, theEnd1.mY)) == 0)
	{
        return Between(theStart2.mX, theStart2.mY, theEnd2.mX, theEnd2.mY, theEnd1.mX, theEnd1.mY);
	}
	return (((aArea1 > 0) ^ (aArea2 > 0)) && ((aArea3 > 0) ^ (aArea4 > 0)));
}
