//
//  Tower.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "Tower.hpp"
#include "GLApp.hpp"

Tower::Tower() {
    mFrame = 0;
    mRotation = gRand.GetFloat(0.0f, 360.0f);
    
    mRange = 256.0f;
    
    mTarget = 0;
    
    mCoolDownTime = 0;
    mCoolDownTimeMax = 40;
    
    mTestFireTimer = 0;
}

Tower::~Tower()
{
    
}

void Tower::Update()
{
    if(gRand.Get(50) == 25)mTestFireTimer = 6;
    
    if(mTestFireTimer > 0)mTestFireTimer--;
    
    if(mCoolDownTime > 0)
    {
        mCoolDownTime--;
    }
    
    mRotation += 1.0f;
    if(mRotation >= 360.0f)mRotation -= 360.0f;
    
}

void Tower::Draw()
{
    Graphics::SetColor();
    if (gApp->mDarkMode) { Graphics::SetColor(0.125f, 0.125f, 0.125f, 1.0f); }

    
    float aFrame = (mRotation / 360.0f) * ((float)TOWER_FRAMES);
    
    if (mTestFireTimer) {
        gApp->mTowerBasicOn.Draw(aFrame, mX, mY, 0.6f, 0.0f);
    } else {
        gApp->mTowerBasicOff.Draw(aFrame, mX, mY, 0.6f, 0.0f);
    }
    
    //Graphics::SetColor(1.0f, 1.0f, 0.5f, 0.6f);
    //Graphics::DrawPoint(mX, mY, 40.0f);
    
    
}



void Tower::FacePoint(float pX, float pY)
{
    mRotation = -FaceTarget(mX - pX, mY - pY);
    
    while(mRotation < 0.0f)mRotation += 360.0f;
    while(mRotation > 360.0f)mRotation -= 360.0f;
    
    float aFrame = (mRotation / 360.0f) * ((float)TOWER_FRAMES);
    
    mFrame = (int)(aFrame + 0.5f);
    if(mFrame < 0)mFrame = 0;
    if(mFrame >= TOWER_FRAMES)mFrame = (TOWER_FRAMES - 1);
}

