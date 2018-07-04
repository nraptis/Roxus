//
//  AnimationDiscoveredStar.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 9/4/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef ___015_Jeep_Arcon__AnimationDiscoveredStar__
#define ___015_Jeep_Arcon__AnimationDiscoveredStar__

#include "FString.h"
#include "FObject.h"
#include "FParticle.h"

class AnimationDiscoveredStar : public FObject
{
public:
    
    AnimationDiscoveredStar();
    virtual ~AnimationDiscoveredStar();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    void                                SetStartAffine(float pX, float pY, float pScale);
    void                                SetStartDiscoverNumber(int pCount, int pCountTotal);
    
    void                                SpawnParticle(int pIndex);
    
    float                               mStartAffineX;
    float                               mStartAffineY;
    float                               mStartAffineScale;
    
    float                               mTargetX;
    float                               mTargetY;
    float                               mTargetScale;
    
    
    int                                 mDiscoverNumber;
    int                                 mDiscoverNumberTotal;
    
    FObjectList                         mAnimations;
    FObjectList                         mAnimationsRelative;
    
    FStepper3                           mStepper;
    
    FWobbler                            mWobblerY;
    FWobbler                            mWobblerRot;
    FWobbler                            mWobblerSkew;
    FWobbler                            mWobblerSpinnerFade[2];
    
    int                                 mParticleSpawnTime[4];
    int                                 mParticleSpawnTick[4];
    
    
    FRRotater                           mRot[2];
    
    
    
    
    float                               mX;
    float                               mY;
    
    float                               mScale;
};

#endif /* defined(___015_Jeep_Arcon__AnimationDiscoveredStar__) */
