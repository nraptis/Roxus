//
//  FMotionKey.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/9/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef __DigMMMac__FMotionKey__
#define __DigMMMac__FMotionKey__

#include <stdio.h>


class FMotionKey
{
public:
    FMotionKey();
    
    //int                             mTime;
    float                           mValue;
};

class FMotionKeyPosition
{
public:
    FMotionKeyPosition();
    
    //int                             mTime;
    int                             mFunction;
    
    float                           mX;
    float                           mY;
    
    
    //bool                            mTrackScreen;
    //int                             mTrackSideX;
    //int                             mTrackSideY;
    //float                           mTrackOffsetX;
    //float                           mTrackOffsetY;
    
};

#endif /* defined(__DigMMMac__FMotionKey__) */
