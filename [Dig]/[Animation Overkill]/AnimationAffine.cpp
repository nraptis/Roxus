//
//  AnimationAffine.cpp
//  Digplex
//
//  Created by Nick Raptis on 10/4/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "AnimationAffine.h"
#include "Game.h"
#include "core_includes.h"

AnimationAffine::AnimationAffine()
{
    mAffineStartX = 0.0f;
    mAffineStartY = 0.0f;
    
    mAffineStartScale = 1.0f;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mScale = 1.0f;
    
    mRotation = 0.0f;
    
    mCalibrationSpline = 0;
    mSpline = 0;
    
}

AnimationAffine::~AnimationAffine()
{
    
}

void AnimationAffine::SetStartAffine(float pX, float pY, float pScale)
{
    if(gGame)
    {
        mAffineStartX = gGame->UntransformX(pX);
        mAffineStartY = gGame->UntransformY(pY);
        
        mAffineStartScale = gGame->UntransformScale() * pScale;
        
        mX = mAffineStartX;
        mY = mAffineStartY;
        
        mScale = mAffineStartScale;
    }
}


