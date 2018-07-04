//
//  FMotionKeySequence.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/9/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#include "FMotionKeySequence.h"
#include "FAnimation.h"

FMotionKeySequence::FMotionKeySequence(float *pX, float *pY) : FMotionKeySequence()
{
    mTargetX = pX;
    mTargetY = pY;
}

FMotionKeySequence::FMotionKeySequence()
{
    mKey = 0;
    mKeyTime = 0;
    mKeySize = 0;
    mKeyCount = 0;
    
    mTargetX = 0;
    mTargetY = 0;
    
    mTime = 0;
    
    mInterpLHS = 0;
    mInterpRHS = 0;
    mInterpPercent = 0.0f;
}

FMotionKeySequence::~FMotionKeySequence()
{
    Clear();
}

void FMotionKeySequence::Clear()
{
    for(int i=0;i<mKeyCount;i++)delete mKey[i];
    delete[]mKey;
    delete[]mKeyTime;
    mKeyTime = 0; mKey = 0; mKeyCount = 0; mKeySize = 0;
}

void FMotionKeySequence::Add(FMotionKeyPosition *pKey, int pTime)
{
    if(mKeyCount >= mKeySize)
    {
        mKeySize = (mKeySize + mKeySize / 2 + 1);
        FMotionKeyPosition **aNew = new FMotionKeyPosition*[mKeySize];
        for(int i = 0; i < mKeyCount; i++)aNew[i] = mKey[i];
        delete[] mKey;
        mKey = aNew;
        
        int *aNewTime = new int[mKeySize];
        for(int i = 0; i < mKeyCount; i++)aNewTime[i] = mKeyTime[i];
        delete[] mKeyTime;
        mKeyTime = aNewTime;
    }
    mKey[mKeyCount] = pKey;
    mKeyTime[mKeyCount] = pTime;
    mKeyCount++;
}

void FMotionKeySequence::Add(float pX, float pY, int pTime, int pFunction)
{
    FMotionKeyPosition *aKey = new FMotionKeyPosition();
    aKey->mX = pX;
    aKey->mY = pY;
    aKey->mFunction = pFunction;
    Add(aKey, pTime);
}

void FMotionKeySequence::Update()
{
    mTime++;
    Refresh();
}

void FMotionKeySequence::Refresh()
{
    mInterpPercent = 0.0f;
    
    mInterpLHS = 0;
    mInterpRHS = 0;
    
    int aIndexLHS = -1;
    int aIndexRHS = -1;
    
    for(int i = 0; i < mKeyCount; i++)if(mKeyTime[i] <= mTime)aIndexLHS = i;// mInterpLHS = mKey[i];
    
    if(aIndexLHS != -1)
    {
        for(int i = (mKeyCount - 1); i >= aIndexLHS; i--)if(mKeyTime[i] > mTime)aIndexRHS = i; //mInterpRHS = mKey[i];
    }
    
    if((aIndexLHS != -1) && (aIndexRHS != -1))
    {
        mInterpLHS = mKey[aIndexLHS];
        mInterpRHS = mKey[aIndexRHS];
        
        
        
        
        int aTimeStart = mKeyTime[aIndexLHS];
        int aTimeEnd = mKeyTime[aIndexRHS];
        int aSpan = (aTimeEnd - aTimeStart);
        
        
        if(aSpan > 0)
        {
            mInterpPercent = ((float)(mTime - aTimeStart)) / ((float)aSpan);
        }
        
        mInterpPercent = FAnimation::ApplyFunction(mInterpRHS->mFunction, mInterpPercent);
        
        if(mTargetX)*mTargetX = mInterpLHS->mX + (mInterpRHS->mX - mInterpLHS->mX) * mInterpPercent;
        if(mTargetY)*mTargetY = mInterpLHS->mY + (mInterpRHS->mY - mInterpLHS->mY) * mInterpPercent;
    }
    else
    {
        if(aIndexLHS != -1)
        {
            mInterpLHS = mKey[aIndexLHS];
            mInterpPercent = 0.0f;
            
            if(mTargetX)*mTargetX = mInterpLHS->mX;
            if(mTargetY)*mTargetY = mInterpLHS->mY;
            
        }
        else if(aIndexRHS != -1)
        {
            mInterpRHS = mKey[aIndexRHS];
            mInterpPercent = 1.0f;
            
            if(mTargetX)*mTargetX = mInterpRHS->mX;
            if(mTargetY)*mTargetY = mInterpRHS->mY;
        }
    }
}


void FMotionKeySequence::SetTarget(float *pX, float *pY)
{
    mTargetX = pX;
    mTargetY = pY;
}



