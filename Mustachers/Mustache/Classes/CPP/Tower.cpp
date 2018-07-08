//
//  Tower.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "Tower.h"
#include "Game.h"

Tower::Tower()
{
    mApp = GAPP;
    
    mFrame = 0;
    mRotation = 0.0f;
    
    mGridX = -1;
    mGridY = -1;
    
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    
    mTarget = 0;
    
    mCoolDownTime = 0;
    mCoolDownTimeMax = 40;
    
}

Tower::~Tower()
{
    
}

void Tower::Update()
{
    if(mCoolDownTime > 0)
    {
        mCoolDownTime--;
    }
}

void Tower::Draw()
{
    //mFrame++;
    //if(mFrame >= TOWER_FRAMES)mFrame=0;
    
    SetColor();
    mApp->mTower[mFrame].Center(mCenterX, mCenterY - 20.0f);
    
    
    SetColor(0.0f, 0.66f, 0.88f);
    
    float aDirX = Sin(mRotation);
    float aDirY = Cos(mRotation);
    
    float aEndX = mCenterX + aDirX * 30.0f;
    float aEndY = mCenterY + aDirY * 30.0f;
    
    
    DrawLine(mCenterX, mCenterY, aEndX, aEndY);
    
    DrawRect(aEndX - 3, aEndY - 3, 7, 7);
    
}

void Tower::SetUp(int pGridX, int pGridY)
{
    mCenterX = (float)pGridX * gTileWidth + (gTileWidth / 2.0f);
    mCenterY = (float)pGridY * gTileHeight + (gTileHeight / 2.0f);
    
    mGridX = pGridX;
    mGridY = pGridY;
}

void Tower::FacePoint(float pX, float pY)
{
    
    mRotation = -FaceTarget(mCenterX - pX, mCenterY - pY);
    
    while(mRotation < 0.0f)mRotation += 360.0f;
    while(mRotation > 360.0f)mRotation -= 360.0f;
    
    float aFrame = (mRotation / 360.0f) * ((float)TOWER_FRAMES);
    
    mFrame = (int)(aFrame + 0.5f);
    if(mFrame < 0)mFrame = 0;
    if(mFrame >= TOWER_FRAMES)mFrame = (TOWER_FRAMES - 1);
    
}

