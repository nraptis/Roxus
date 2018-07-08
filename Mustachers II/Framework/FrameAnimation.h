//
//  FrameAnimation.h
//  Wrangler
//
//  Created by Nick Raptis on 10/31/11.
//  Copyright (c) 2011 __MyCompanyName__. All rights reserved.
//

#ifndef FRAMEANIMATION_H
#define FRAMEANIMATION_H

#include "Sprite.h"
#include "FString.h"
#include "List.h"

class FrameAnimation
{
public:
    
    FrameAnimation();
    ~FrameAnimation();
    
    Sprite              *GetSprite(float pFrame);
    
    void                Clear();
    
    void                Load(const char *pFilePrefix, int pStartIndex, int pEndIndex, int pLeadingZeros=4);
    void                Load(const char *pFilePrefix, int pStartIndex=0);
    
    
    float               mOffsetX;
    float               mOffsetY;
    
    List                mSpriteList;
};

class FrameRef
{
public:
    FrameRef(FrameAnimation *pFrameAnimation);
    ~FrameRef();
    
    FrameAnimation      *mFrameAnimation;
    
    virtual void        Update();
    
    virtual void        Draw(float x, float y, float pScale, float pRotationDegrees, int pFacing=1);
    
    void                PlayOnce();
    void                Start();
    
    bool                mPlayOnce;
    bool                mCompleted;
    
    //int                 mLoopCount;
    //bool                mLooping;
    
    float               mFrame;
    
    float               mSpeed;
    
    int                 mCount;
    
    float               mMax;
};

#endif
