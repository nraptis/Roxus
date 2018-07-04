//
//  WiggleBoy.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__WiggleBoy__
#define __DigMMMac__WiggleBoy__

#include "WiggleBoyPart.h"
#include "FMotionObject.h"

//The Rules of Wiggle Boy..

//Wiggle boy lets you pin 2 corners to the parent node now..

class WiggleBoy : public FMotionObject
{
public:
    WiggleBoy();
    virtual ~WiggleBoy();
    
    virtual void                    Update();
    virtual void                    Draw();
    
    void                            SetSize(FSprite *pSprite);
    void                            SetSize(float pWidth, float pHeight);
    
    //GeoQuad                         mQuadBase;
    
    
    //float                           mX;
    //float                           mY;
    
    //float                           mWidth;
    //float                           mHeight;
    
    //float                           mScale;
    
    
    //float                           mRotation;
    
    FList                           mPartList;
    
    
    float                           mTestSin1;
    float                           mTestSin2;
    float                           mTestSin3;
    
    bool                            mTestRotMode;
    float                           mTestRotTarget;
    
};

#endif
