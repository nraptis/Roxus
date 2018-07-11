//
//  Tower.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "Tower.h"
#include "Game.h"

Tower::Tower()
{
    mApp = GAPP;
    
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
    
    float aFrame = (mRotation / 360.0f) * ((float)TOWER_FRAMES);
    
    if(mTestFireTimer)
    {
        mApp->mTowerBasicOn.Draw(mX, mY, aFrame, 0.6f, 0.0f);
    }
    else
    {
        mApp->mTowerBasicOff.Draw(mX, mY, aFrame, 0.6f, 0.0f);
    }
    
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

