//
//  AnimationDiscoveredTreasure.h
//  Digplex
//
//  Created by Nick Raptis on 9/23/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__AnimationDiscoveredTreasure__
#define __Digplex__AnimationDiscoveredTreasure__

//#include "StepAnimation.h"
#include "FString.h"

#include "FString.h"
#include "FObject.h"
#include "FParticle.h"

class AnimationDiscoveredTreasure : public FObject
{
public:
    
    AnimationDiscoveredTreasure();
    virtual ~AnimationDiscoveredTreasure();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    void                                SetStartAffine(float pX, float pY, float pScale);
    
    void                                SpawnParticle(int pIndex);
    
    float                               mStartAffineX;
    float                               mStartAffineY;
    float                               mStartAffineScale;
    
    float                               mTargetX;
    float                               mTargetY;
    float                               mTargetScale;
    
    FObjectList                         mAnimations;
    FObjectList                         mAnimationsAdditive;
    FObjectList                         mAnimationsRelative;
    
    FStepper3                           mStepper;
    
    FWobbler                            mWobblerY;
    FWobbler                            mWobblerRot;
    FWobbler                            mWobblerSkew;
    FWobbler                            mWobblerSpinnerFade[2];
    
    int                                 mParticleSpawnTime[4];
    int                                 mParticleSpawnTick[4];
    
    FRRotater                           mRot[2];
    int                                 mTreasureType;
    
    float                               mX;
    float                               mY;
    
    float                               mScale;
};

#endif
