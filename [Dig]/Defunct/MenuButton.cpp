//
//  MenuButton.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/25/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "MenuButton.h"
#include "FButton.h"


MenuButton::MenuButton()
{
    mName = "MenuButton";
    
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

MenuButton::~MenuButton()
{
    
}

void MenuButton::Update()
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
        if(mScaleAdd < 0.030f)mScaleAdd += 0.0015f;
        if(mScaleAdd >= 0.030f)mScaleAdd = 0.030f;
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

void MenuButton::Draw()
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

/*
{
    //Graphics::SetColor(1.0f, 0.0f, 0.0f);
    //if(mIsDown)Graphics::SetColor(0.0f, 0.0f, 1.0f);
    //DrawRect(0.0f, 0.0f, mFrame.mWidth, mFrame.mHeight);
    //Graphics::SetColor();
    
    
    FSprite *aSprite = GetButtonImage();
    if(aSprite)
    {
        
        float aShiftSin = Sin(mBumpSinSpeedShift);
        
        float aDrawX = mWidth2 + mShiftDirX * aShiftSin * mBumpAmountShift;
        float aDrawY = mHeight2 + mShiftDirY * aShiftSin * mBumpAmountShift;
        
        float aDrawScale = 1.0f + mScaleAdd + mBumpAmountScale * Sin(mBumpSinScale);
        
        float aDrawRotate = mBumpAmountRotate * Sin(mBumpSinRotate);
        
        aSprite->Draw(aDrawX, aDrawY, aDrawScale, aDrawRotate);
        

        
        
        
        //aSprite->Center(mFrame.mWidth / 2.0f, mFrame.mHeight / 2.0f);
    }
}

*/

void MenuButton::ButtonActionRollOver()
{
    
}

void MenuButton::ButtonActionRollOff()
{
    
}

void MenuButton::ButtonActionDragOver()
{
    //Log("MenuButton::ButtonActionDragOver()\n");
    Bump();
}

void MenuButton::ButtonActionDragOff()
{
    //Log("MenuButton::ButtonActionDragOff()\n");
    Bump();
}

void MenuButton::ButtonActionReleaseOver()
{
    //Log("MenuButton::ButtonActionReleaseOver()\n");
    Bump();
}

void MenuButton::ButtonActionReleaseOff()
{
    
}



void MenuButton::Bump()
{
    if(mBumpAmountRotate <= 0.025f && mBumpAmountShift <= 0.025f && mBumpAmountScale <= 0.0025f)
    {
        mBumpAmountRotate = 1.25f + gRand.GetFloat(1.0f);
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
