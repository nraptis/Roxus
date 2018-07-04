//
//  CollectedEssence.h
//  Digplex
//
//  Created by Nick Raptis on 10/4/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__CollectedEssence__
#define __Digplex__CollectedEssence__

#include "AnimationAffine.h"

class CollectedEssence : public AnimationAffine
{
public:
    CollectedEssence();
    virtual ~CollectedEssence();
    
    void                                ShootTowardsJar(float pX, float pY);
    
    virtual void                        Update();
    virtual void                        Draw();
    
    int                                 mTimer;
    
    float                               mSpeedX;
    float                               mSpeedY;
    
    float                               mBoltScale;
    
    float                               mSwarmTargetX;
    float                               mSwarmTargetY;
    
    float                               mSwarmFactor;
    
    float                               mSplinePos;
    float                               mSplineSpeed;
    
    bool                                mComplete;
    
    float                               mFrame;
    float                               mFrameMax;
    
    void                                *mTarget;
    
};

#endif /* defined(__Digplex__CollectedEssence__) */
