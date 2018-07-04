//
//  MainMenuTwinkle.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/8/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "MainMenuTwinkle.h"
#include "MainApp.h"

MainMenuTwinkle::MainMenuTwinkle() : WiggleBoyPart(&(gApp->mEffectTwinkleAdditive[0]))
{
    mTimer.SetTime(40, 80);
    
    mTwinkleOn = false;
    
    mTwinkleScale = 1.0f;
    mTwinkleRotation = 0.0f;
    mTwinkleScaleSpeed = 0.0f;
}

MainMenuTwinkle::~MainMenuTwinkle()
{
    
}

void MainMenuTwinkle::Update(float pX, float pY, float pScale, float pRotation)
{
    
    
    
    
    if(mTwinkleOn == true)
    {
        mTwinkleScale += mTwinkleScaleSpeed;
        
        mTwinkleScaleSpeed -= 0.015f;
        
        mTwinkleRotation += mTwinkleScaleSpeed * 12.0f;
        
        if(mTwinkleScale <= 0.0f)
        {
            mTwinkleScale = 0.0f;
            mTwinkleOn = false;
            mTimer.Reset();
        }
        
    }
    else
    {
        if(mTimer.Tick())
        {
            mTwinkleOn = true;
            
            mTwinkleScale = 0.05f;
            mTwinkleScaleSpeed = 0.2f;
            
            mTwinkleRotation = -12.0f;
            
        }
    }
    
    mOffsetScale = mTwinkleScale;
    mOffsetRotation = mTwinkleRotation;
    
    
    WiggleBoyPart::Update(pX, pY, pScale, pRotation);
    
    //mDrawScale *= mTwinkleScale;
    //mDrawRotation *= mTwinkleRotation;
    
}

void MainMenuTwinkle::Draw()
{
    
    if(mTwinkleOn == true)
    {
        Graphics::BlendSetAdditive();
    
        WiggleBoyPart::Draw();
    
        Graphics::BlendSetAlpha();
    }
}
