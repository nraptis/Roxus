//
//  FInterp.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/14/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#include "FInterp.h"
#include "core_includes.h"


FInterp::FInterp()
{
    
}

FInterp::~FInterp()
{
    
}

void FInterp::Add(float pPercent)
{
    mPercentList.Add(pPercent);
}

void FInterp::Reset()
{
    mPercentList.Reset();
}

void FInterp::Clear()
{
    mPercentList.Clear();
}

float FInterp::Get(float pPercent, float pMaxPercent, int &pIndexStart, int &pIndexEnd)
{
    float aResult = 0.0f;
    
    pIndexStart = 0;
    pIndexEnd = 0;
    
    
    if(mPercentList.mCount > 1)
    {
        
        /*
        int aSearchIndexStart = 0;
        int aSearchIndexEnd = mPercentList.mCount - 1;
        int aIndex = 0;
        
        while(aSearchIndexStart < aSearchIndexEnd)
        {
            aIndex = (aSearchIndexStart + aSearchIndexEnd) / 2;  //aMin+(aMax-aMin)/2;
            
            if(pPercent > mPercentList.mData[aIndex])
            {
                aSearchIndexStart = aIndex + 1;
            }
            else if(pPercent < mPercentList.mData[aIndex])
            {
                aSearchIndexEnd = aIndex - 1;
            }
            else
            {
                break;
            }
        }
        
        if(aIndex < 0)
        {
            Log("aIndex < 0\n\n");
            
            aIndex = 0;
        }
        
        if(aIndex >= mPercentList.mCount)
        {
            Log("aIndex >= mPercentList.mCount\n\n");
            
            aIndex = mPercentList.mCount - 1;
        }
        
        pIndexStart = (aIndex - 1);
        pIndexEnd = (aIndex);
        */
        
        
        while(pIndexEnd < mPercentList.mCount)
        {
            
            if(mPercentList.mData[pIndexEnd] >= pPercent)
            {
                break;
            }
            else
            {
                pIndexEnd++;
            }
        }
        
        if(pIndexEnd >= mPercentList.mCount)pIndexEnd = 0;
        
        
        
        
        bool aLoopStart = false;
        
        pIndexStart = (pIndexEnd - 1);
        if(pIndexStart < 0)
        {
            aLoopStart = true;
            pIndexStart = (mPercentList.mCount - 1);
        }
        //while(
        
        //aLength
        
        
        
        
        
        float aPercentStart = mPercentList.mData[pIndexStart];
        float aPercentEnd = mPercentList.mData[pIndexEnd];
        
        if(aLoopStart)
        {
            aPercentEnd += pMaxPercent;
        }
        //if(aPercentStart)
        
        
        
        double aRange = aPercentEnd - aPercentStart;
        
        
        if(aRange > 0.0025f)
        {
            aResult = (float)(((double)(pPercent - aPercentStart)) / aRange);
            
        }
    }
    
    
    
    return aResult;
}


