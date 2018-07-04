//
//  BoardGenericMatch.cpp
//  Digplex
//
//  Created by Nick Raptis on 9/20/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "BoardGenericMatch.h"
#include "core_includes.h"

BoardGenericMatch::BoardGenericMatch()
{
    mLeft = 0;
    mRight = 0;
    mTop = 0;
    mBottom = 0;
    
    mCenterX = 0;
    mCenterY = 0;
    
    mTagged = false;
    
    mProcScore = 0;
    mProcProbability = 0.0f;
    
    mX = 0;
    mY = 0;
    mDist = 0;
    
    mCount = 0;
    mListSize = 0;
}

BoardGenericMatch::~BoardGenericMatch()
{
    delete [] mX;
    delete [] mY;
    delete [] mDist;
    
    mX = 0;
    mY = 0;
    mDist = 0;
    
    mListSize = 0;
    mCount = 0;
}

BoardGenericMatch *BoardGenericMatch::Clone()
{
    BoardGenericMatch *aClone = new BoardGenericMatch();
    
    
    Clone(aClone);
    
    
    
    return aClone;
}

void BoardGenericMatch::Clone(BoardGenericMatch *pMatch)
{
    if(pMatch)
    {
        pMatch->mCount = mCount;
        
        pMatch->mLeft = mLeft;
        pMatch->mRight = mRight;
        pMatch->mTop = mTop;
        pMatch->mBottom = mBottom;
        
        pMatch->mTagged = true;
        
        pMatch->mCenterX = mCenterX;
        pMatch->mCenterY = mCenterY;
        
        pMatch->mProcProbability = mProcProbability;
        pMatch->mProcScore = mProcScore;
        
        if(mListSize > 0)
        {
            pMatch->mX = new int[mListSize];
            pMatch->mY = new int[mListSize];
            pMatch->mDist = new float[mListSize];
            
            pMatch->mListSize = mListSize;
            
            for(int i=0;i<mCount;i++)
            {
                pMatch->mX[i] = mX[i];
                pMatch->mY[i] = mY[i];
                
                pMatch->mDist[i] = mDist[i];
            }
            
        }
    }
}

void BoardGenericMatch::Add(int pGridX, int pGridY)
{
    if(mCount == mListSize)
    {
        mListSize = mCount + mCount / 2 + 1;
        
        int *aX = new int[mListSize];
        for(int i=0;i<mCount;i++)aX[i] = mX[i];
        delete [] mX;
        mX = aX;
        
        
        int *aY = new int[mListSize];
        for(int i=0;i<mCount;i++)aY[i] = mY[i];
        delete [] mY;
        mY = aY;
        
        float *aDist = new float[mListSize];
        for(int i=0;i<mCount;i++)aDist[i] = mDist[i];
        delete [] mDist;
        mDist = aDist;
        
        
    }
    
    mX[mCount] = pGridX;
    mY[mCount] = pGridY;
    mDist[mCount] = 0.0f;
    
    mCount++;
}

void BoardGenericMatch::Reset()
{
    mCount = 0;
    mTagged = false;
    
    mProcScore = 0;
    mProcProbability = 0.0f;
}


void BoardGenericMatch::Compute(int pGridStartX, int pGridStartY, int pGridEndX, int pGridEndY)
{
    if(mCount > 0)
    {
        mLeft = mX[0];
        mRight = mX[0];
        mTop = mY[0];
        mBottom = mY[0];
        
        mCenterX = mX[0];
        mCenterY = mY[0];
        
        int aAverageCenterX = mX[0];
        int aAverageCenterY = mY[0];
        
        
        for(int i=1;i<mCount;i++)
        {
            if(mX[i] < mLeft)mLeft = mX[i];
            if(mX[i] > mRight)mRight = mX[i];
            
            if(mY[i] < mTop)mTop = mY[i];
            if(mY[i] > mBottom)mBottom = mY[i];
            
            aAverageCenterX += mX[i];
            aAverageCenterY += mY[i];
        }
        
        float aTrueCenterX = ((float)aAverageCenterX) / ((float)mCount);
        float aTrueCenterY = ((float)aAverageCenterY) / ((float)mCount);
        
        
        float aDiffX = mX[0] - aTrueCenterX;
        float aDiffY = mY[0] - aTrueCenterY;
        
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        mDist[0] = aDist;
        
        float aBestDist = aDist;
        int aBestIndex = 0;
        
        
        for(int i=1;i<mCount;i++)
        {
            aDiffX = mX[i] - aTrueCenterX;
            aDiffY = mY[i] - aTrueCenterY;
            
            aDist = aDiffX * aDiffX + aDiffY * aDiffY;
            mDist[i] = aDist;
            
            if(aDist < aBestDist)
            {
                aBestDist = aDist;
                aBestIndex = i;
            }
            
            //if(aDist <)
            
        }
        
        
        mCenterX = mX[aBestIndex];
        mCenterY = mY[aBestIndex];
        
    }
    else
    {
        mLeft = 0;
        mRight = 0;
        mTop = 0;
        mBottom = 0;
        
        mCenterX = 0;
        mCenterY = 0;
        
    }
}
