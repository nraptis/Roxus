//
//  Tower.h
//  Mustache
//
//  Created by Nick Raptis on 6/16/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_Tower_h
#define Mustache_Tower_h

#include "GLApp.h"
#include "Unit.h"

class Tower
{
public:
    
    Tower();
    virtual ~Tower();
    
    GLApp                               *mApp;
    
    void                                SetUp(int pGridX, int pGridY);
    
    virtual void                        Update();
    virtual void                        Draw();
    
    void                                FacePoint(float pX, float pY);
    
    int                                 mGridX;
    int                                 mGridY;
    
    float                               mCenterX;
    float                               mCenterY;
    
    float                               mRotation;
    
    int                                 mFrame;
    
    
    Unit                                *mTarget;
    
    
    int                                 mCoolDownTime;
    int                                 mCoolDownTimeMax;
    
};

#endif
