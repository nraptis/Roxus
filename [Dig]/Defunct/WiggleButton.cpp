//
//  WiggleButton.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/25/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "WiggleButton.h"
#include "FButton.h"


WiggleButton::WiggleButton()
{
    mName = "WiggleButton";
    
    mScaleAdd = 0.0f;
    
    mBumpSinRotate = 0.0f;
    mBumpSinSpeedRotate = 0.0f;
    
    mBumpSinShift = 0.0f;
    mBumpSinSpeedShift = 0.0f;
    
    mBumpSinScale = 0.0f;
    mBumpSinSpeedScale = 0.0f;
    
    
    mBumpAmountRotate = 0.0f;
    mBumpAmountShift = 0.0f;
    mBumpAmountScale = 0.0f;
    
    mShiftDirX = 0.0f;
    mShiftDirY = 0.0f;
    
}

WiggleButton::~WiggleButton()
{
    
}

void WiggleButton::Update()
{
    
    mBumpSinRotate += mBumpSinSpeedRotate;
    if(mBumpSinRotate >= 360.0f)mBumpSinRotate -= 360.0f;
    if(mBumpSinRotate < 0.0f   )mBumpSinRotate += 360.0f;
    
    mBumpSinShift += mBumpSinSpeedShift;
    if(mBumpSinShift >= 360.0f)mBumpSinShift -= 360.0f;
    if(mBumpSinShift < 0.0f   )mBumpSinShift += 360.0f;
    
    mBumpSinScale += mBumpSinSpeedScale;
    if(mBumpSinScale >= 360.0f)mBumpSinScale -= 360.0f;
    if(mBumpSinScale < 0.0f   )mBumpSinScale += 360.0f;
    
    if(mBumpAmountRotate > 0)
    {
        mBumpAmountRotate *= 0.975f;
        mBumpAmountRotate -= 0.025f;
        if(mBumpAmountRotate < 0)
        {
            mBumpAmountRotate = 0.0f;
        }
    }
    
    if(mBumpAmountShift > 0)
    {
        mBumpAmountShift *= 0.975f;
        mBumpAmountShift -= 0.025f;
        if(mBumpAmountShift < 0)
        {
            mBumpAmountShift = 0.0f;
        }
    }
    
    if(mBumpAmountScale > 0)
    {
        mBumpAmountScale *= 0.975f;
        mBumpAmountScale -= 0.00025f;
        if(mBumpAmountScale < 0)
        {
            mBumpAmountScale = 0.0f;
        }
    }
    
    
    if(mTouchDownInside)
    {
        if(mScaleAdd < 0.175f)mScaleAdd += 0.0125f;
        if(mScaleAdd >= 0.175f)mScaleAdd = 0.175f;
    }
    else
    {
        if(mScaleAdd > 0.0f)
        {
            mScaleAdd -= 0.01f;
            if(mScaleAdd <= 0.0f)mScaleAdd = 0.0f;
        }
    }
    
}

void WiggleButton::Draw()
{
    float aShiftSin = Sin(mBumpSinSpeedShift);
    
    EnumList(FButtonLayer, aSubLayer, mButtonLayersUnder)
    {
        aSubLayer->mOffsetX = mShiftDirX * aShiftSin * mBumpAmountShift;
        aSubLayer->mOffsetY = mShiftDirY * aShiftSin * mBumpAmountShift;
        aSubLayer->mScale = 1.0f + mScaleAdd + mBumpAmountScale * Sin(mBumpSinScale);
        aSubLayer->mRotation = mBumpAmountRotate * Sin(mBumpSinRotate);
        aSubLayer->Draw(this, true, false, mTouchDownInside);
    }
    
    FButtonLayer *aLayer = mButtonLayer;
    aLayer->mOffsetX = mShiftDirX * aShiftSin * mBumpAmountShift;
    aLayer->mOffsetY = mShiftDirY * aShiftSin * mBumpAmountShift;
    aLayer->mScale = 1.0f + mScaleAdd + mBumpAmountScale * Sin(mBumpSinScale);
    aLayer->mRotation = mBumpAmountRotate * Sin(mBumpSinRotate);
    aLayer->Draw(this, true, false, mTouchDownInside);
    
    EnumList(FButtonLayer, aSubLayer, mButtonLayersOver)
    {
        aSubLayer->mOffsetX = mShiftDirX * aShiftSin * mBumpAmountShift;
        aSubLayer->mOffsetY = mShiftDirY * aShiftSin * mBumpAmountShift;
        aSubLayer->mScale = 1.0f + mScaleAdd + mBumpAmountScale * Sin(mBumpSinScale);
        aSubLayer->mRotation = mBumpAmountRotate * Sin(mBumpSinRotate);
        aSubLayer->Draw(this, true, false, mTouchDownInside);
    }
}

void WiggleButton::ButtonActionRollOver()
{

}

void WiggleButton::ButtonActionRollOff()
{
    
}

void WiggleButton::ButtonActionDragOver()
{
    //Log("WiggleButton::ButtonActionDragOver()\n");
    Bump();
}

void WiggleButton::ButtonActionDragOff()
{
    //Log("WiggleButton::ButtonActionDragOff()\n");
    Bump();
}

void WiggleButton::ButtonActionReleaseOver()
{
    //Log("WiggleButton::ButtonActionReleaseOver()\n");
    Bump();
}

void WiggleButton::ButtonActionReleaseOff()
{
    
}

void WiggleButton::Bump()
{
    if(mBumpAmountRotate <= 0.025f && mBumpAmountShift <= 0.025f && mBumpAmountScale <= 0.0025f)
    {
        mBumpAmountRotate = 4.0f + gRand.GetFloat(2.5f);
        mBumpAmountShift = 4.0f + gRand.GetFloat(2.5f);
        mBumpAmountScale = 0.04f + gRand.GetFloat(0.02f);
        
        
        mShiftDirX = gRand.GetFloat(-1.0f, 1.0f);
        mShiftDirY = gRand.GetFloat(-1.0f, 1.0f);
        
        
        mBumpSinRotate = 0.0f;
        mBumpSinSpeedRotate = 5.0f + gRand.GetFloat(3.0f);
        
        mBumpSinShift = 0.0f;
        mBumpSinSpeedShift = 12.0f + gRand.GetFloat(10.0f);
        
        mBumpSinScale = 0.0f;
        mBumpSinSpeedScale = 8.0f + gRand.GetFloat(4.0f);
        
        if(gRand.GetBool())mBumpSinSpeedRotate = -mBumpSinSpeedRotate;
        if(gRand.GetBool())mBumpSinSpeedShift  = -mBumpSinShift;
        if(gRand.GetBool())mBumpSinSpeedScale  = -mBumpSinSpeedScale;
    }
    else
    {
        //Log("Blocked Bump [R:%f SH:%f SC:%f]\n", mBumpAmountRotate, mBumpAmountShift, mBumpAmountScale);
    }
}
