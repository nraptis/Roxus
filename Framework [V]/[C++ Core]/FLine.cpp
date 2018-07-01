/*
 *  FLine.cpp
 *  Fiat
 *
 *  Created by Nick Raptis on 6/20/11.
 *  Copyright 2011 Nick Raptis. All rights reserved.
 *
 */

#include "core_includes.h"
#include "FLine.h"
#include "FMath.h"

FLine::FLine(float x1,float y1,float x2,float y2)
{
    Make(x1,y1,x2,y2);
}

FLine::FLine()
{
    Make(0,0,0,0);
}

FLine::~FLine()
{
    
}

void FLine::Make(float x1,float y1,float x2,float y2)
{
    mX1=x1;
    mY1=y1;
    
    mX2=x2;
    mY2=y2;
    
    mDiffX=mX2-mX1;
    mDiffY=mY2-mY1;
    
    mLength=mDiffX*mDiffX+mDiffY*mDiffY;
    
    if(mLength > SQRT_EPSILON)
    {
        mLength=sqrtf(mLength);
        
        mDirX=mDiffX/mLength;
        mDirY=mDiffY/mLength;
    }
    else
    {
        mLength=0;
        
        mDiffX=1;
        mDiffY=0;
        
        mDirX=mDiffX;
        mDirY=mDiffY;
    }
    
    mNormalX = -mDirY;
    mNormalY = mDirX;
    
    mCross=(-PHYSICS_DOT(mX1,mY1,mNormalX,mNormalY));
}

bool FLine::SegmentSegmentIntersection(float pL_1_x1, float pL_1_y1, float pL_1_x2, float pL_1_y2,
                                       float pL_2_x1, float pL_2_y1, float pL_2_x2, float pL_2_y2,
                                       float &pCollideX, float &pCollideY, float &pCollideDistance)
{
    float aPlaneX = pL_2_x1;
    float aPlaneY = pL_2_y1;
    
    float aPlaneDirX = pL_2_x2 - pL_2_x1;
    float aPlaneDirY = pL_2_y2 - pL_2_y1;
    
    float aPlaneLength = (aPlaneDirX * aPlaneDirX) + (aPlaneDirY * aPlaneDirY);
    
    if(aPlaneLength >= 0.1f)
    {
        aPlaneLength = sqrtf(aPlaneLength);
        
        aPlaneDirX /= aPlaneLength;
        aPlaneDirY /= aPlaneLength;
    }
    
    bool aResult = false;
    
    if(SegmentPlaneIntersection(pL_1_x1, pL_1_y1, pL_2_x2, pL_2_y2, aPlaneX, aPlaneY, aPlaneDirX, aPlaneDirY, pCollideX, pCollideY, pCollideDistance))
    {
        aResult = true;
    }
    
    return aResult;
    
}

bool FLine::SegmentPlaneIntersection(float pL_1_x1, float pL_1_y1, float pL_1_x2, float pL_1_y2,
                                     float pPlaneX, float pPlaneY, float pPlaneDirX, float pPlaneDirY,
                                     float &pCollideX, float &pCollideY, float &pCollideDistance)
{
    
    float aLineSpanX = pL_1_x2 - pL_1_x1;
    float aLineSpanY = pL_1_y2 - pL_1_y1;
    
    float aLineLength = aLineSpanX * aLineSpanX + aLineSpanY * aLineSpanY;
    
    float aLineDirX = aLineSpanX;
    float aLineDirY = aLineSpanY;
    
    if(aLineLength > SQRT_EPSILON)
    {
        aLineLength = sqrtf(aLineLength);
        aLineDirX /= aLineLength;
        aLineDirY /= aLineLength;
    }
    else
    {
        aLineDirX = 0;
        aLineDirY = -1;
    }
    
    float aLineNormX = -aLineDirY;
    float aLineNormY = aLineDirX;
    
    float aLineCross = (-PHYSICS_DOT(pL_1_x1, pL_1_y1, aLineNormX, aLineNormY));
    
    float aDenom = pPlaneDirX * aLineNormX + pPlaneDirY * aLineNormY;
    float aNumer = aLineNormX * pPlaneX + aLineNormY * pPlaneY + aLineCross;
    
    if((aDenom < (-SQRT_EPSILON)) || (aDenom > SQRT_EPSILON))
    {
        float aDist = -(aNumer/aDenom);

        pCollideX = pPlaneX + pPlaneDirX * aDist;
        pCollideY = pPlaneY + pPlaneDirY * aDist;
        pCollideDistance = aDist;
        
        FLine aLine;
        aLine.Make(pL_1_x1, pL_1_y1, pL_1_x2, pL_1_y2);
        
        float aClosestCollideX = pCollideX;
        float aClosestCollideY = pCollideY;
        
        if(FLine::SegmentClosestPoint(pL_1_x1, pL_1_y1, pL_1_x2, pL_1_y2, pCollideX, pCollideY, aClosestCollideX, aClosestCollideY))
        {
            return true;
        }
    }
    
    return false;
}

bool FLine::SegmentClosestPoint(float pLineX1, float pLineY1, float pLineX2, float pLineY2, float pPointX, float pPointY, float &pClosestX, float &pClosestY)
{
    bool aResult = false;
    
    pClosestX = pLineX1;
    pClosestY = pLineY1;
    
    float aFactor1X = (pPointX - pLineX1);
    float aFactor1Y = (pPointY - pLineY1);
    
    float aFactor2X = pLineX2 - pLineX1;
    float aFactor2Y = pLineY2 - pLineY1;
    
    
    float aLineDiffX = (pLineX2 - pLineX1);
    float aLineDiffY = (pLineY2 - pLineY1);
    
    float aLineLength = (aLineDiffX * aLineDiffX) + (aLineDiffY * aLineDiffY);
    
    if(aLineLength > SQRT_EPSILON)
    {
        aLineLength = sqrtf(aLineLength);
        
        aFactor2X /= aLineLength;
        aFactor2Y /= aLineLength;
        
        float aScalar = aFactor2X * aFactor1X + aFactor2Y * aFactor1Y;
        
        if(aScalar < 0)
        {
            pClosestX = pLineX1;
            pClosestY = pLineY1;
        }
        else if(aScalar > aLineLength)
        {
            pClosestX = pLineX2;
            pClosestY = pLineY2;
        }
        else
        {
            
            pClosestX = pLineX1 + aFactor2X * aScalar;
            pClosestY = pLineY1 + aFactor2Y * aScalar;
            
            aResult = true;
        }
    }
    
    return aResult;
}

bool FLine::SegmentRayIntersection(float pL_1_x1, float pL_1_y1, float pL_1_x2, float pL_1_y2,
                                   float pRayX, float pRayY, float pRayDirX, float pRayDirY, float pRayLength,
                                   float &pCollideX, float &pCollideY, float &pCollideDistance)
{
    FLine aLine;
    
    aLine.Make(pL_1_x1, pL_1_y1, pL_1_x2, pL_1_y2);
    
    
    
    float aPlaneDist = aLine.RayPlaneDist(pRayX, pRayY, pRayDirX, pRayDirY);
    
    if((aPlaneDist > pRayLength) || (aPlaneDist < 0.0f))
    {
        return false;
    }
    
    pCollideX = pRayX + pRayDirX * aPlaneDist;
    pCollideY = pRayY + pRayDirY * aPlaneDist;
    
    pCollideDistance = aPlaneDist;
    
    return true;
}


float FLine::RayPlaneDist(float x, float y, float pDirX, float pDirY)
{
    float aDenom=pDirX*mNormalX+pDirY*mNormalY;
    if(aDenom <= SQRT_EPSILON && aDenom>=0)return 0;
    if(aDenom >= SQRT_EPSILON && aDenom<=0)return 0;
    float aCosAlpha=mCross;
    float aNumer=mNormalX*x+mNormalY*y + aCosAlpha;
    return -(aNumer/aDenom);
}

void FLine::ClosestPoint(float x, float y, float &pClosestX, float &pClosestY)
{
    pClosestX = mX1;
    pClosestY = mY1;
    
    float aFactor1X = (x - mX1);
    float aFactor1Y = (y - mY1);
    
    float aFactor2X = mX2 - mX1;
    float aFactor2Y = mY2 - mY1;
    
    float aLength = mLength;
    
    if(aLength > SQRT_EPSILON)
    {
        aFactor2X /= mLength;
        aFactor2Y /= mLength;
        
        float aScalar=aFactor2X*aFactor1X+aFactor2Y*aFactor1Y;
        
        if(aScalar<0)
        {
            pClosestX = mX1;
            pClosestY = mY1;
        }
        else if(aScalar>mLength)
        {
            pClosestX = mX2;
            pClosestY = mY2;
        }
        else
        {
            pClosestX=mX1+aFactor2X*aScalar;
            pClosestY=mY1+aFactor2Y*aScalar;
        }
    }
}

float FLine::GetDist(float x, float y, int &pIndex)
{
    float aDiffX, aDiffY, aDist1, aDist2;
    
    aDiffX=x-mX1;
    aDiffY=y-mY1;
    aDist1=aDiffX*aDiffX+aDiffY*aDiffY;
    aDiffX=x-mX2;
    aDiffY=y-mY2;
    aDist2=aDiffX*aDiffX+aDiffY*aDiffY;
    
    float aDist;
    
    if(aDist1<aDist2)
    {
        pIndex=0;
        aDist=aDist1;
    }
    else
    {
        pIndex=1;
        aDist=aDist2;
    }
    
    if(aDist > SQRT_EPSILON)
    {
        //aDist = SquareRoot(aDist);
        aDist = sqrtf(aDist);
        
    }
    else
    {
        aDist=0;
    }
    
    return aDist;
    
}

int FLine::GetPoint(float x, float y, float pDist)
{
    int aResult=-1;
    
    float aDiffX, aDiffY, aDist1, aDist2;
    
    aDiffX=x-mX1;
    aDiffY=y-mY1;
    
    aDist1=aDiffX*aDiffX+aDiffY*aDiffY;
    
    aDiffX=x-mX2;
    aDiffY=y-mY2;
    
    aDist2=aDiffX*aDiffX+aDiffY*aDiffY;
    
    if(aDist1<aDist2)
    {
        if(aDist1 < pDist*pDist)
        {
            aResult=0;
        }
    }
    else
    {
        if(aDist2 < pDist*pDist)
        {
            aResult=1;
        }
    }
    
    return aResult;
    
}

void FLine::SetPoint(int pIndex, float x, float y)
{
    if(pIndex==0)Make(x,y,mX2,mY2);
    else Make(mX1,mY1,x,y);
}

void FLine::Draw()
{
	Graphics::SetColor(0, 0, 0);
    
	Graphics::DrawLine(mX1, mY1, mX2, mY2);

}











