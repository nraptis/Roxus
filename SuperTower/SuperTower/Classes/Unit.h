//
//  Unit.h
//  Mustache
//
//  Created by Nick Raptis on 6/17/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef Mustache_Unit_h
#define Mustache_Unit_h

#include "GLApp.h"
#include "GamePath.h"
#include "GameObject.h"

class GameArena;

class Unit : public GameObject
{
public:
    
    Unit();
    virtual ~Unit();
    
    GLApp                               *mApp;
    GameArena                           *mArena;
    
    GamePath                            mPath;
    
    virtual void                        Update();
    virtual void                        Draw();
    
    void                                ComputePath();
    
    void                                SetUp(GamePath *pPath);
    
    //This is this unit's final grid destination... Huzzah!
    int                                 mFinalGridX;
    int                                 mFinalGridY;
    int                                 mFinalGridZ;
    
    int                                 mHPMax;
    int                                 mHP;
    
    
    
    float                               mTargetX;
    float                               mTargetY;
    float                               mTargetZ;
    
    int                                 mPathIndex;
    
    float                               mWalkSpeed;
    bool                                mWalking;
    
    float                               mRotation;
    float                               mRotationSpeed;
    
    float                               mFrame;
    
};

#endif
