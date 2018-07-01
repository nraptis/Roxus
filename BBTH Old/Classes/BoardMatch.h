//
//  BoardMatch.h
//  Digplex
//
//  Created by Nick Raptis on 9/20/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__BoardMatch__
#define __Digplex__BoardMatch__

#include "FObject.h"

class BoardMatch : public FObject
{
public:
    BoardMatch();
    virtual ~BoardMatch();
    
    void                        Add(int pGridX, int pGridY);
    void                        AddKnot(int pGridX, int pGridY);
    
    void                        Reset();
    virtual void                Compute(int pGridStartX, int pGridStartY, int pGridEndX, int pGridEndY);
    
    BoardMatch                  *Clone();
    void                        Clone(BoardMatch *pMatch);
    
    int                         mProcScore;
    float                       mProcProbability;
    
    int                         mCenterX;
    int                         mCenterY;
    
    bool                        mTagged;
    
    bool                        mHorizontal;
    bool                        mVertical;
    
    int                         mMatchDir;
    
    int                         mLeft;
    int                         mRight;
    int                         mTop;
    int                         mBottom;
    
    int                         *mX;
    int                         *mY;
    int                         mCount;
    int                         mListSize;
    
    int                         *mKnotX;
    int                         *mKnotY;
    int                         mKnotCount;
    int                         mKnotListSize;
    
    int                         mMatchType;
    
    float                       *mDist;
};

#endif /* defined(__Digplex__BoardMatch__) */
