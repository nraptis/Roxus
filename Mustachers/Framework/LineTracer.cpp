//
//  LineTracer.cpp
//  Jiggle
//
//  Created by Nick Raptis on 9/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "LineTracer.h"

LineTracer::LineTracer()
{
	mWidth=1.5f;
    
    
    mX=0;
    mY=0;
    
    
    mCount=0;
    mSize=0;
    
    
    mChanged=false;
    mCircular=true;
}

LineTracer::~LineTracer()
{
	delete[]mX;
	mX=0;
}

void LineTracer::Clear()
{
    mCount=0;
    mBuffer.Clear();
    mChanged=true;
}

void LineTracer::Add(float pX, float pY)
{
    if(mCount==mSize)
	{
		mSize=mCount+mCount/2+1;
        
		float *aX=new float[mSize *2];// + (mSize * 4) + (mSize * 4)];
        float *aY=aX + mSize;
        
		for(int i=0;i<mCount;i++)aX[i]=mX[i];
        for(int i=0;i<mCount;i++)aY[i]=mY[i];

        delete[]mX;
        mX=aX;
        mY=aY;
	}
    
    mX[mCount]=pX;
    mY[mCount]=pY;
    mCount++;
    mChanged=true;
    
}

#define LINE_TRACER_MIN_DIST (0.5f)

void LineTracer::Calculate()
{
    mChanged=false;
    
    mBuffer.Clear();
    
    float aDiffX, aDiffY, aDist;
    float aNormX, aNormY;
    
    float aX1, aY1, aX2, aY2, aCornerX1, aCornerY1, aCornerX2, aCornerY2, aCornerX3, aCornerY3, aCornerX4, aCornerY4;
    
    
    float aLastCornerX1,aLastCornerY1,aLastCornerX2,aLastCornerY2;
    float aFirstCornerX1, aFirstCornerY1, aFirstCornerX2, aFirstCornerY2;
    
    int aCount = mCount;
    
    while(aCount > 0)
    {
        aX1=mX[0];
        aY1=mY[0];
        
        aX2=mX[aCount-1];
        aY2=mY[aCount-1];
        
        aDiffX = aX2 - aX1;
        aDiffY = aY2 - aY1;
        
        aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        
        if(aDist > LINE_TRACER_MIN_DIST)
        {
            aDist = sqrtf(aDist);
            aDiffX /= aDist;
            aDiffY /= aDist;
            
            aNormX=-aDiffY;
            aNormY=aDiffX;
            
            
            aCornerX1 = aX2 + aNormX * mWidth;
            aCornerY1 = aY2 + aNormY * mWidth;
            
            aCornerX2 = aX2 - aNormX * mWidth;
            aCornerY2 = aY2 - aNormY * mWidth;
            
            
            aCornerX3 = aX1 + aNormX * mWidth;
            aCornerY3 = aY1 + aNormY * mWidth;
            
            aCornerX4 = aX1 - aNormX * mWidth;
            aCornerY4 = aY1 - aNormY * mWidth;
            
            
            
            mBuffer.AddXYZ(aCornerX1,aCornerY1,0);
            mBuffer.AddXYZ(aCornerX2,aCornerY2,0);
            mBuffer.AddXYZ(aCornerX3,aCornerY3,0);
            
            mBuffer.AddXYZ(aCornerX4,aCornerY4,0);
            mBuffer.AddXYZ(aCornerX2,aCornerY2,0);
            mBuffer.AddXYZ(aCornerX3,aCornerY3,0);
            
            
            aLastCornerX1 = aCornerX3;
            aLastCornerY1 = aCornerY3;
            
            aLastCornerX2 = aCornerX4;
            aLastCornerY2 = aCornerY4;
            
            
            aFirstCornerX1=aCornerX1;
            aFirstCornerY1=aCornerY1;
            aFirstCornerX2=aCornerX2;
            aFirstCornerY2=aCornerY2;

            break;
        }
        else
        {
            aCount--;
        }
    }
    
    
    
    if(aCount <= 0)return;
    
    int aLast=0;
    
    for(int aStart=1;aStart<aCount;aStart++)
    {
        
        aX1=mX[aStart];
        aY1=mY[aStart];
        
        aX2=mX[aLast];
        aY2=mY[aLast];
        
        
        
        
        aDiffX = aX2 - aX1;
        aDiffY = aY2 - aY1;
        
        aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        
        if(aDist < LINE_TRACER_MIN_DIST)
        {
            aDist = 0;
            aDiffX = 0;
            aDiffY = 0;
        }
        else
        {
            aDist = sqrtf(aDist);
            aDiffX /= aDist;
            aDiffY /= aDist;
            
            aNormX=-aDiffY;
            aNormY=aDiffX;
            
            
            
            aCornerX1 = aX2 + aNormX * mWidth;
            aCornerY1 = aY2 + aNormY * mWidth;
            
            aCornerX2 = aX2 - aNormX * mWidth;
            aCornerY2 = aY2 - aNormY * mWidth;
            
            
            aCornerX3 = aX1 + aNormX * mWidth;
            aCornerY3 = aY1 + aNormY * mWidth;
            
            aCornerX4 = aX1 - aNormX * mWidth;
            aCornerY4 = aY1 - aNormY * mWidth;
            
            
            
            mBuffer.AddXYZ(aCornerX1,aCornerY1,0);
            mBuffer.AddXYZ(aCornerX2,aCornerY2,0);
            mBuffer.AddXYZ(aLastCornerX1,aLastCornerY1,0);
            
            
            mBuffer.AddXYZ(aLastCornerX2,aLastCornerY2,0);
            mBuffer.AddXYZ(aLastCornerX1,aLastCornerY1,0);
            mBuffer.AddXYZ(aCornerX1,aCornerY1,0);
            
            
            
            mBuffer.AddXYZ(aLastCornerX2,aLastCornerY2,0);
            mBuffer.AddXYZ(aLastCornerX1,aLastCornerY1,0);
            mBuffer.AddXYZ(aCornerX2,aCornerY2,0);
            
            mBuffer.AddXYZ(aCornerX1,aCornerY1,0);
            mBuffer.AddXYZ(aCornerX2,aCornerY2,0);
            mBuffer.AddXYZ(aLastCornerX2,aLastCornerY2,0);
            
            
            
            
            
            mBuffer.AddXYZ(aCornerX1,aCornerY1,0);
            mBuffer.AddXYZ(aCornerX2,aCornerY2,0);
            mBuffer.AddXYZ(aCornerX3,aCornerY3,0);
            
            mBuffer.AddXYZ(aCornerX4,aCornerY4,0);
            mBuffer.AddXYZ(aCornerX2,aCornerY2,0);
            mBuffer.AddXYZ(aCornerX3,aCornerY3,0);
            
            aLast = aStart;
            
            aLastCornerX1 = aCornerX3;
            aLastCornerY1 = aCornerY3;
            
            aLastCornerX2 = aCornerX4;
            aLastCornerY2 = aCornerY4;
            
        }
        
    }
    
    
    mBuffer.AddXYZ(aFirstCornerX1,aFirstCornerY1,0);
    mBuffer.AddXYZ(aFirstCornerX2,aFirstCornerY2,0);
    mBuffer.AddXYZ(aLastCornerX1,aLastCornerY1,0);
    
    
    mBuffer.AddXYZ(aLastCornerX2,aLastCornerY2,0);
    mBuffer.AddXYZ(aLastCornerX1,aLastCornerY1,0);
    mBuffer.AddXYZ(aFirstCornerX1,aFirstCornerY1,0);
    
    
    
    mBuffer.AddXYZ(aLastCornerX2,aLastCornerY2,0);
    mBuffer.AddXYZ(aLastCornerX1,aLastCornerY1,0);
    mBuffer.AddXYZ(aFirstCornerX2,aFirstCornerY2,0);
    
    mBuffer.AddXYZ(aFirstCornerX1,aFirstCornerY1,0);
    mBuffer.AddXYZ(aFirstCornerX2,aFirstCornerY2,0);
    mBuffer.AddXYZ(aLastCornerX2,aLastCornerY2,0);
    
}

void LineTracer::Draw()
{
    Graphics::DisableTexture();
    if(mChanged)Calculate();
    mBuffer.mMode = GL_TRIANGLES;
    mBuffer.Draw();
}