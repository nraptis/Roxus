//
//  Tower.h
//  Mustache
//
//  Created by Nick Raptis on 6/16/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef Mustache_Tower_h
#define Mustache_Tower_h

#include "GLApp.h"
#include "GameObject.h"
#include "Unit.h"

class Tower : public GameObject
{
public:
    
    Tower();
    virtual ~Tower();
    
    GLApp                               *mApp;
    
    virtual void                        Update();
    virtual void                        Draw();
    
    void                                FacePoint(float pX, float pY);
    
    float                               mRange;
    
    float                               mRotation;
    
    int                                 mFrame;
    
    Unit                                *mTarget;
    
    int                                 mCoolDownTime;
    int                                 mCoolDownTimeMax;
    
    int                                 mTestFireTimer;
};

#endif
