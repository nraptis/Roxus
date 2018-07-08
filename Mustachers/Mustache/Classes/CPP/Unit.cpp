//
//  Unit.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "Unit.h"
#include "Game.h"

Unit::Unit()
{
    
    mApp = GAPP;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mTargetX = 0.0f;
    mTargetY = 0.0f;
    
    mGridX = -1;
    mGridY = -1;
    
    mTargetGridX = -1;
    mTargetGridY = -1;
    
    mWalkSpeed = gRand.GetFloat(2.5f, 4.0f);
    
    mHPMax = 200;
    mHP = mHPMax;
    
    mWalking = false;
}

Unit::~Unit()
{
    
}

void Unit::Update()
{
    
    if(mWalking)
    {
        float aDiffX = mTargetX - mX;
        float aDiffY = mTargetY - mY;
        
        float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
        
        if(aDist > 0.2f)
        {
            aDist = sqrtf(aDist);
            
            aDiffX /= aDist;
            aDiffY /= aDist;
        }
        
        if(aDist < mWalkSpeed)
        {
            mX = mTargetX;
            mY = mTargetY;
            mWalking = false;
        }
        else
        {
            mX += aDiffX * mWalkSpeed;
            mY += aDiffY * mWalkSpeed;
        }
    }
    
}

void Unit::Draw()
{
    SetColor();
    
    mApp->mUnit.Center(mX, mY);
}

void Unit::WalkTo(int pGridX, int pGridY)
{
    mWalking = true;
    
    mTargetGridX = pGridX;
    mTargetGridY = pGridY;
    
    mTargetX = CX(mTargetGridX);
    mTargetY = CY(mTargetGridY);
    
}

void Unit::SetUp(int pGridX, int pGridY)
{
    mX = CX(pGridX);
    mY = CY(pGridY);
    
    mGridX = pGridX;
    mGridY = pGridY;
}
