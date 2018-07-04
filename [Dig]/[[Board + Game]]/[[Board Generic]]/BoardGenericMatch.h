//
//  BoardGenericMatch.h
//  Digplex
//
//  Created by Nick Raptis on 9/20/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__BoardGenericMatch__
#define __Digplex__BoardGenericMatch__

#include "FObject.h"

class BoardGenericMatch : public FObject
{
public:
    BoardGenericMatch();
    virtual ~BoardGenericMatch();
    
    void                        Add(int pGridX, int pGridY);
    void                        Reset();
    virtual void                Compute(int pGridStartX, int pGridStartY, int pGridEndX, int pGridEndY);
    
    BoardGenericMatch           *Clone();
    void                        Clone(BoardGenericMatch *pMatch);
    
    int                         mProcScore;
    float                       mProcProbability;
    
    int                         mCenterX;
    int                         mCenterY;
    
    bool                        mTagged;
    
    int                         mLeft;
    int                         mRight;
    int                         mTop;
    int                         mBottom;
    
    int                         mCount;
    int                         mListSize;
    
    int                         *mX;
    int                         *mY;
    
    float                       *mDist;
};

#endif /* defined(__Digplex__BoardGenericMatch__) */
