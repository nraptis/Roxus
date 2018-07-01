//
//  FViewAnimation.cpp
//  2015 Gnome Launcher
//
//  Created by Nick Raptis on 11/12/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#include "FViewAnimation.h"
#include "FView.h"

FViewAnimation::FViewAnimation()
{
    mID = VIEW_ANIMATION_NULL;
    
    mView = 0;
    
    mStartX = 0.0f;
    mTargetX = 0.0f;
    
    mStartY = 0.0f;
    mTargetY = 0.0f;
    
    mStartScale = 1.0f;
    mTargetScale = 1.0f;
    
    mStartScaleX = 1.0f;
    mTargetScaleX = 1.0f;
    
    mStartScaleY = 1.0f;
    mTargetScaleY = 1.0f;
    
    mStartRotation = 0.0f;
    mTargetRotation = 0.0f;
    
    mTimerTick = 0;
    mTime = 0;
    
    //mDelay = 0;
    
    mPercent = 0;
}
               
FViewAnimation::FViewAnimation(FView *pView)// : FViewAnimation()
{
    mID = VIEW_ANIMATION_NULL;
    
    mView = pView;
    
    mStartX = 0.0f;
    mTargetX = 0.0f;
    
    mStartY = 0.0f;
    mTargetY = 0.0f;
    
    mStartScale = 1.0f;
    mTargetScale = 1.0f;
    
    mStartScaleX = 1.0f;
    mTargetScaleX = 1.0f;
    
    mStartScaleY = 1.0f;
    mTargetScaleY = 1.0f;
    
    mStartRotation = 0.0f;
    mTargetRotation = 0.0f;
    
    mTimerTick = 0;
    mTime = 0;
    
    //mDelay = 0;
    
    mPercent = 0;
    
    SetUp(pView);
}

FViewAnimation::~FViewAnimation()
{
    delete [] mPercent;
    mPercent = 0;
}


bool FViewAnimation::Update()
{
    bool aComplete = false;
    
    
    float aAnimationPercent = 0.0f;
    
    mTimerTick++;
    if(mTime > 0)
    {
        
        aAnimationPercent = mPercent[mTimerTick];
        
        //aAnimationPercent = ((float)mTimerTick) / ((float)mTime);
        
        //aAnimationPercent = FAnimation::EaseInSine(aAnimationPercent);
        //aAnimationPercent = FAnimation::EaseOutQuint(aAnimationPercent);
        
        //aAnimationPercent = FAnimation::EaseInOutSine(aAnimationPercent);
        
        if(mTimerTick >= mTime)
        {
            aComplete = true;
        }
    }
    else
    {
        aComplete = true;
    }
    
    
    if(mView)
    {
        
        
        
        if(aComplete)
        {
            
            
            Finish();
            
            //mView->AnimationComplete(mViewAnimation, mID);
            
            
            
            //delete mViewAnimation;
            //mViewAnimation = 0;
        }
        else
        {
            mView->SetTransformX(mStartX + (mTargetX - mStartX) * aAnimationPercent);
            mView->SetTransformY(mStartY + (mTargetY - mStartY) * aAnimationPercent);
            
            
            
            mView->SetTransformScale(mStartScale + (mTargetScale - mStartScale) * aAnimationPercent);
            mView->SetTransformScaleX(mStartScaleX + (mTargetScaleX - mStartScaleX) * aAnimationPercent);
            mView->SetTransformScaleY(mStartScaleY + (mTargetScaleY - mStartScaleY) * aAnimationPercent);
            
            mView->SetTransformRotation(mStartRotation + (mTargetRotation - mStartRotation) * aAnimationPercent);
            
            //mView->SetTransformAnchorX(mStartAnchorX + (mTargetAnchorX - mStartAnchorX) * aAnimationPercent);
            //mView->SetTransformAnchorY(mStartAnchorY + (mTargetAnchorY - mStartAnchorY) * aAnimationPercent);
            
        }
    }
    
    return aComplete;
}

/*
 void FViewAnimation::Reset()
 {
 
 }
 
 void FViewAnimation::SetUp()
 {
 mStartX = 0.0f;
 mTargetX = 0.0f;
 
 mStartY = 0.0f;
 mTargetY = 0.0f;
 
 mStartScale = 1.0f;
 mTargetScale = 1.0f;
 
 mStartScaleX = 1.0f;
 mTargetScaleX = 1.0f;
 
 mStartScaleY = 1.0f;
 mTargetScaleY = 1.0f;
 
 mStartRotation = 0.0f;
 mTargetRotation = 0.0f;
 
 mTimerTick = 0;
 //mTime = 0;
 }
 */

void FViewAnimation::SetUp(FView *pView)
{
    
    mView = pView;
    
    if(pView)
    {
        mStartX = pView->GetTransformX();
        mStartY = pView->GetTransformY();
        
        mStartRotation = pView->GetTransformRotation();
        
        mStartScale = pView->GetTransformScale();
        
        mStartScaleX = pView->GetTransformScaleX();
        mStartScaleY = pView->GetTransformScaleY();
        
        //mStartAnchorX = pView->GetTransformAnchorX();
        //mStartAnchorY = pView->GetTransformAnchorY();
        
        
        mTargetX = mStartX;
        mTargetY = mStartY;
        
        mTargetRotation = mStartRotation;
        
        mTargetScale = mStartScale;
        
        mTargetScaleX = mStartScaleX;
        mTargetScaleY = mStartScaleY;
        
        //mTargetAnchorX = mStartAnchorX;
        //mTargetAnchorY = mStartAnchorY;
        
    }
}

float FViewAnimation::Percent()
{
    float aReturn = 0;
    
    if((mTimerTick >= 0) && (mTime > 0))
    {
        if(mPercent != 0)
        {
            if(mTimerTick >= mTime)
            {
                aReturn = 1.0f;
            }
            else
            {
                aReturn = mPercent[mTimerTick];
            }
            
            
        }
        else
        {
            aReturn = ((float)mTimerTick) / ((float)mTime);
            
        }
    }
    
    if(aReturn > 1.0f)aReturn = 1.0f;
    if(aReturn < 0.0f)aReturn = 0.0f;
    
    
    return aReturn;
}

void FViewAnimation::Generate(int pFunction, int pTicks)
{
    mTimerTick = 0;
    mTime = pTicks;
    //    Generate();
    //}
    
    //void FViewAnimation::Generate()
    //{
    if(mTime < 1)mTime = 1;
    
    if(mPercent)
    {
        delete [] mPercent;
        mPercent = 0;
    }
    
    mPercent = new float[mTime];
    
    float aPercent = 0.0f;
    
    for(int i=0;i<mTime;i++)
    {
        aPercent = ((float)i) / ((float)mTime);
        mPercent[i] = aPercent;
    }
    
    
    
    /*
     int aCurveType = mCurveType;
     
     
     if(aCurveType == ANIMATION_TYPE_AUTOMATIC)
     {
     if(mAnimatingIn)
     {
     aCurveType = ANIMATION_TYPE_EASE_OUT_CIRC;
     //aCurveType = ANIMATION_EASE_OUT_ELASTIC;
     //aCurveType = ANIMATION_TYPE_EASE_OUT_BACK;
     //aCurveType = ANIMATION_TYPE_OVERSHOOT;
     //aCurveType = ANIMATION_TYPE_OVERSHOOT_MORE;
     //aCurveType = ANIMATION_TYPE_BOUNCE;
     //aCurveType = ANIMATION_TYPE_BOUNCE_MORE;
     //aCurveType = ANIMATION_TYPE_EASE_OUT_QUART;
     //aCurveType = ANIMATION_TYPE_EASE_OUT_EXPO;
     
     }
     else if(mAnimatingOut)
     {
     //aCurveType = ANIMATION_TYPE_EASE_IN_CIRC;
     aCurveType = ANIMATION_TYPE_EASE_IN_OUT_CIRC;
     //aCurveType = ANIMATION_TYPE_EASE_IN_EXPO;
     //aCurveType = ANIMATION_TYPE_EASE_IN_QUART;
     
     
     
     //aCurveType = ANIMATION_TYPE_EASE_OUT_EXPO;
     aCurveType = ANIMATION_TYPE_EASE_OUT_QUART;
     
     }
     else
     {
     aCurveType = ANIMATION_TYPE_EASE_OUT_IN_SIN;
     
     }
     
     
     }
     */
    
    
    
    //
    /////////////////////////////
    
    
    
    for(int i=0;i<mTime;i++)
    {
        //mPercent[i] = FAnimation::ApplyFunction(aCurveType, mPercent[i]);
        mPercent[i] = FAnimation::ApplyFunction(pFunction, mPercent[i]);
        
        
        
        //pFunction
    }
    

    //mCurveType
}

void FViewAnimation::GenerateIn(int pTicks)
{
    Generate(ANIMATION_TYPE_EASE_OUT_CIRC, pTicks);
}

void FViewAnimation::GenerateOut(int pTicks)
{
    //Generate(ANIMATION_TYPE_EASE_OUT_QUART, pTicks);
    Generate(ANIMATION_TYPE_EASE_OUT_CIRC, pTicks);
    
}

void FViewAnimation::GenerateSmooth(int pTicks)
{
    Generate(ANIMATION_TYPE_EASE_OUT_IN_SIN, pTicks);
}

void FViewAnimation::Finish()
{
    if(mView)
    {
        mView->SetTransformX(mTargetX);
        mView->SetTransformY(mTargetY);
        mView->SetTransformScale(mTargetScale);
        mView->SetTransformScaleX(mTargetScaleX);
        mView->SetTransformScaleY(mTargetScaleY);
        mView->SetTransformRotation(mTargetRotation);
        //mView->SetTransformAnchorX(mTargetAnchorX);
        //mView->SetTransformAnchorY(mTargetAnchorY);
    }
}


