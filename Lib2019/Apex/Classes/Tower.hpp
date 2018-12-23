//
//  Tower.h
//  Mustache
//
//  Created by Nick Raptis on 6/16/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef Mustache_Tower_h
#define Mustache_Tower_h

#include "GLApp.hpp"
#include "LargeGameObject.hpp"
#include "Unit.hpp"

class Tower : public LargeGameObject {
public:

    Tower();
    virtual ~Tower();

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
