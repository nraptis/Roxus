//
//  LineSlash.cpp
//  DodgeDart
//
//  Created by Nick Raptis on 12/20/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//


#include "LineSlash.h"
#include "stdafx.h"

LineSlash::LineSlash()
{
    mX = 0;
    mY = 0;
    
    mNormalX = 0;
    mNormalY = 0;
    
    mDist = 0;
    
    mLength = 0;
    
    mCount = 0;
    mSize = 0;
}

LineSlash::~LineSlash()
{
    
}

void LineSlash::AddPoint(float x, float y)
{
    
	if(mCount==mSize)
	{
		mSize=mCount+mCount/2+1;
		
		float *aX=new float[mSize*8];
        float *aY = &(aX[mSize]);
        
        mNormalX = &(aY[mSize]);
        mNormalY = &(mNormalX[mSize]);
        
        mKinkX = &(mNormalY[mSize]);
        mKinkY = &(mKinkX[mSize]);
        
        mDist = &(mKinkY[mSize]);
        
        mAngle = &(mDist[mSize]);
        
		for(int i=0;i<mCount;i++)aX[i]=mX[i];
		for(int i=0;i<mCount;i++)aY[i]=mY[i];
        
        delete[]mX;
        
        mX=aX;
        mY=aY;
	}
    
	mX[mCount]=x;
	mY[mCount]=y;
    
	mCount++;
}

void LineSlash::Solve()
{
    float aX, aY;
    float aLastX, aLastY;
    float aDiffX, aDiffY, aDist;
    float aAngle;
    
    
    mLength = 0;
    
    if(mCount > 0)
    {
        mDist[0]=0;
        
        aLastX = mX[0];
        aLastY = mY[0];
        
        for(int i=1;i<mCount;i++)
        {
            aX=mX[i];
            aY=mY[i];
            
            aDiffX = aX - aLastX;
            aDiffY = aY - aLastY;
            
            mAngle[i] = atan2f(aX - aLastX, aY - aLastY);
            
            
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            
            //if(aDist > 0.25f)
            //{
                aDist = sqrtf(aDist);
                
                mLength += aDist;
                
                aDiffX /= aDist;
                aDiffY /= aDist;
                
                mNormalX[i] = -aDiffY;
                mNormalY[i] = aDiffX;
                mDist[i] = mLength;
            //}
            
            aLastX = aX;
            aLastY = aY;
        }
        
        int aCap = mCount - 1;
        
        for(int i=1;i<aCap;i++)
        {
            aAngle = (mAngle[i] + mAngle[i + 1]) * 0.5f;
            
            mNormalX[i] = -cos(aAngle);
            mNormalY[i] = sin(aAngle);
        }
    }
}

