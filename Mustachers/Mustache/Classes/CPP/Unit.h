//
//  Unit.h
//  Mustache
//
//  Created by Nick Raptis on 6/17/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_Unit_h
#define Mustache_Unit_h

#include "GLApp.h"

class Unit
{
public:
    
    Unit();
    virtual ~Unit();
    
    GLApp                               *mApp;
    
    virtual void                        Update();
    virtual void                        Draw();
    
    void                                SetUp(int pGridX, int pGridY);
    
    void                                WalkTo(int pGridX, int pGridY);
    
    int                                 mHPMax;
    int                                 mHP;
    
    float                               mX;
    float                               mY;
    
    float                               mTargetX;
    float                               mTargetY;
    
    int                                 mGridX;
    int                                 mGridY;
    
    int                                 mTargetGridX;
    int                                 mTargetGridY;
    
    float                               mWalkSpeed;
    
    bool                                mWalking;
    
    
};

#endif
