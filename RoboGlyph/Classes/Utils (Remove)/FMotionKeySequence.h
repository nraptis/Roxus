//
//  FMotionKeySequence.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/9/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef __DigMMMac__FMotionKeySequence__
#define __DigMMMac__FMotionKeySequence__

#include "FMotionKey.h"

class FMotionKeySequence// : public FMotionObjectNode
{
public:
    FMotionKeySequence(float *pX, float *pY);
    FMotionKeySequence();
    virtual ~FMotionKeySequence();
    
    void									Clear();
    void									Update();
    void									Refresh();
    
    
    
    void									Add(float pX, float pY, int pTime, int pFunction);
    void									Add(FMotionKeyPosition *pKey, int pTime);
    
    FMotionKeyPosition                      **mKey;
    int										*mKeyTime;
    
    
    int										mKeySize;
    int										mKeyCount;
    
    int										mTime;
    bool                                    mRefresh;
    
    void                                    SetTarget(float *pX, float *pY);
    float									*mTargetX;
    float									*mTargetY;
    
    FMotionKeyPosition                      *mInterpLHS;
    FMotionKeyPosition                      *mInterpRHS;
    float									mInterpPercent;
};


#endif /* defined(__DigMMMac__FMotionKeySequence__) */
