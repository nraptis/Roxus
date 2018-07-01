//
//  BoardMatch.cpp
//  Digplex
//
//  Created by Nick Raptis on 9/20/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "BoardMatch.h"
#include "core_includes.h"

BoardMatch::BoardMatch()
{
    mLeft = 0;
    mRight = 0;
    mTop = 0;
    mBottom = 0;
    
    mMatchDir = 0;
    
    mCenterX = 0;
    mCenterY = 0;
    
    mTagged = false;
    
    mHorizontal = false;
    mVertical = false;
    
    mProcScore = 0;
    mProcProbability = 0.0f;
    
    mX = 0;
    mY = 0;
    mDist = 0;
    
    mCount = 0;
    mListSize = 0;
    
    mMatchType = -1;
    
    mKnotX = 0;
    mKnotY = 0;
    mKnotCount = 0;
    mKnotListSize = 0;
}

BoardMatch::~BoardMatch()
{
    delete [] mX;
    delete [] mY;
    delete [] mDist;
    
    mX = 0;
    mY = 0;
    mDist = 0;
    mListSize = 0;
    mCount = 0;
    
    delete [] mKnotX;
    delete [] mKnotY;
    mKnotX = 0;
    mKnotY = 0;
    mKnotCount = 0;
    mKnotListSize = 0;
}

BoardMatch *BoardMatch::Clone()
{
    BoardMatch *aClone = new BoardMatch();
    
    Clone(aClone);
    
    return aClone;
}

void BoardMatch::Clone(BoardMatch *pMatch)
{
    if(pMatch)
    {
        pMatch->mCount = mCount;
        pMatch->mKnotCount = mKnotCount;
        
        pMatch->mLeft = mLeft;
        pMatch->mRight = mRight;
        pMatch->mTop = mTop;
        pMatch->mBottom = mBottom;
        
        pMatch->mTagged = true;
        
        pMatch->mHorizontal = mHorizontal;
        pMatch->mVertical = mVertical;
       
        pMatch->mCenterX = mCenterX;
        pMatch->mCenterY = mCenterY;
        
        pMatch->mProcProbability = mProcProbability;
        pMatch->mProcScore = mProcScore;
        
        pMatch->mMatchType = mMatchType;
        
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
        
        if(mKnotListSize > 0)
        {
            pMatch->mKnotX = new int[mKnotListSize];
            pMatch->mKnotY = new int[mKnotListSize];
            
            pMatch->mKnotListSize = mKnotListSize;
            
            for(int i=0;i<mKnotCount;i++)
            {
                pMatch->mKnotX[i] = mKnotX[i];
                pMatch->mKnotY[i] = mKnotY[i];
            }
        }
    }
}

void BoardMatch::Add(int pGridX, int pGridY)
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

void BoardMatch::AddKnot(int pGridX, int pGridY)
{
    if(mKnotCount == mKnotListSize)
    {
        mKnotListSize = mKnotCount + mKnotCount / 2 + 1;
        
        int *aKnotX = new int[mKnotListSize];
        for(int i=0;i<mKnotCount;i++)aKnotX[i] = mKnotX[i];
        delete [] mKnotX;
        mKnotX = aKnotX;
        
        int *aKnotY = new int[mKnotListSize];
        for(int i=0;i<mKnotCount;i++)aKnotY[i] = mKnotY[i];
        delete [] mKnotY;
        mKnotY = aKnotY;
    }
    
    mKnotX[mCount] = pGridX;
    mKnotY[mCount] = pGridY;
    
    mKnotCount++;
}

void BoardMatch::Reset()
{
    mCount = 0;
    mKnotCount = 0;
    mTagged = false;
    
    mMatchType = -1;
    
    mHorizontal = false;
    mVertical = false;
    
    mProcScore = 0;
    mProcProbability = 0.0f;
}


void BoardMatch::Compute(int pGridStartX, int pGridStartY, int pGridEndX, int pGridEndY)
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
            if(mX[i] < mLeft)
            {
                mLeft = mX[i];
                mHorizontal = true;
                
            }
            if(mX[i] > mRight)
            {
                mRight = mX[i];
                mHorizontal = true;
            }
            
            if(mY[i] < mTop)
            {
                mTop = mY[i];
                mVertical = true;
            }
            if(mY[i] > mBottom)
            {
                mBottom = mY[i];
                mVertical = true;
            }
            
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
        
        mHorizontal = false;
        mVertical = false;
    }
}
