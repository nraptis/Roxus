//
//  FPointList.cpp
//  LizDash
//
//  Created by Nick Raptis on 3/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "FPointList.h"



FPointList::FPointList()
{
    mCount=0;
    mSize=0;
    
    mX=0;
    mY=0;
    mZ=0;
}

FPointList::~FPointList()
{
    
}



void FPointList::Clear()
{
    delete [] mX;
    
    mCount=0;
    mSize=0;
    
    mX=0;
    mY=0;
    mZ=0;
}

void FPointList::Add(float pX, float pY, float pZ)
{
    if(mCount >= mSize)
    {
        Size(mCount + (mCount / 2) + 1);
    }
    
    mX[mCount] = pX;
    mY[mCount] = pY;
    mZ[mCount] = pZ;
    
    //printf("Centroid Found [%f %f %f] @ %d\n", pX, pY, pZ, mCount);
    
    mCount++;
}

void FPointList::Size(int pSize)
{
    float *aNewX = new float[pSize * 3 + 1];
    float *aNewY = aNewX + pSize;
    float *aNewZ = aNewY + pSize;
    
    for(int i=0;i<mCount;i++)aNewX[i]=mX[i];
    for(int i=0;i<mCount;i++)aNewY[i]=mY[i];
    for(int i=0;i<mCount;i++)aNewZ[i]=mZ[i];
    
    delete[]mX;
    
    mX = aNewX;
    mY = aNewY;
    mZ = aNewZ;
    
    mSize = pSize;
}



void FPointList::Load(ModelDataSequence *pSequence, int pStartIndex, int pEndIndex)
{
    Clear();
    
    int aCount = pSequence->mCount;
    
    if(pStartIndex <= 0)pStartIndex = 0;
    if(pEndIndex == -1)pEndIndex = (aCount - 1);
    
    float aCentroidX, aCentroidY, aCentroidZ;
    
    for(int i=0;i<aCount;i++)
    {
        if((i >= pStartIndex) && (i <= pEndIndex))
        {
            pSequence->GetCentroid(i, aCentroidX, aCentroidY, aCentroidZ);
            
            Add(aCentroidX, aCentroidY, aCentroidZ);
        }
    }
}

void FPointList::Save(const char *pFile)
{
    Buffer aBuffer;
    
    aBuffer.WriteInt(mCount);
    
    for(int i=0;i<mCount;i++)
    {
        aBuffer.WriteFloat(mX[i]);
        aBuffer.WriteFloat(mY[i]);
        aBuffer.WriteFloat(mZ[i]);
    }
    aBuffer.Save(pFile);
}

void FPointList::Load(const char *pFile)
{
    Clear();
    
    Buffer aBuffer;
    aBuffer.Load(pFile);
    
    int aCount = aBuffer.ReadInt();
    Size(aCount);
    
    float aReadX, aReadY, aReadZ;
    
    for(int i=0;i<aCount;i++)
    {
        aReadX = aBuffer.ReadFloat();
        aReadY = aBuffer.ReadFloat();
        aReadZ = aBuffer.ReadFloat();
        
        Add(aReadX, aReadY, aReadZ);
    }    
}

float FPointList::GetX(float pFrame)
{
    float aReturn=0;
    int aIndex = (int)pFrame;
    if((aIndex >= 0) && (aIndex < mCount))
    {
        aReturn = mX[aIndex];
    }
    return aReturn;
}

float FPointList::GetY(float pFrame)
{
    float aReturn=0;
    int aIndex = (int)pFrame;
    if((aIndex >= 0) && (aIndex < mCount))
    {
        aReturn = mY[aIndex];
    }
    return aReturn;
}

float FPointList::GetZ(float pFrame)
{
    float aReturn=0;
    int aIndex = (int)pFrame;
    if((aIndex >= 0) && (aIndex < mCount))
    {
        aReturn = mZ[aIndex];
    }
    return aReturn;
}

