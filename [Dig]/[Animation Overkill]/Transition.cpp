//
//  Transition.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/25/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "Transition.h"
#include "FApp.h"
#include "MainApp.h"

Transition::Transition()
{
    mKill = 0;
    
    mTransitionState = TRANSITION_STATE_INITIAL;
    
    mEnterTime = 17;
    mSwapTime = 2;
    mExitTime = 24;
    
    
    //mEnterTime = 200;
    //mSwapTime = 40;
    //mExitTime = 150;
    
    mTimer = 0;
    
    mScale = 1.0f;
    
}

Transition::~Transition()
{
    Log("Dealloc[Transition]\n");
}

void Transition::Update()
{
    if(mTransitionState == TRANSITION_STATE_INITIAL)
    {
        mTransitionState = TRANSITION_STATE_ENTER;
        mTimer = mEnterTime;
    }
    
    if(mTimer > 0)
    {
        mTimer--;
        
        if(mTimer <= 0)
        {
            if(mTransitionState == TRANSITION_STATE_ENTER)
            {
                mTransitionState = TRANSITION_STATE_SWAP;
                mTimer = mSwapTime;
            }
            else if(mTransitionState == TRANSITION_STATE_SWAP)
            {
                if(gApp)gApp->TransitionSwapViews();
                mTransitionState = TRANSITION_STATE_EXIT;
                mTimer = mExitTime;
            }
            else
            {
                Kill();
            }
        }
    }
}

void Transition::Draw()
{
    Graphics::MatrixGoProjection();
    Graphics::MatrixLoadIdentity();
    Graphics::MatrixOrtho2D(0, gDeviceWidth, gDeviceHeight, 0); //, -4096.0f, 4096.0f);
    Graphics::MatrixGoModelView();
    Graphics::MatrixLoadIdentity();
    
    float aScale = 0.0f;
    
    //float aPercentEnter = 0.0f;
    //float aPercentSwap = 0.0f;
    //float aPercentExit = 0.0f;
    //float aFade = 0.0f;
    
    if(mTransitionState == TRANSITION_STATE_ENTER)
    {
        if(mEnterTime > 0)aScale = ((float)mTimer) / ((float)mEnterTime);
        else aScale = 0.0f;
    }
    else if(mTransitionState == TRANSITION_STATE_SWAP)
    {
        aScale = 0.0f;
    }
    else if(mTransitionState == TRANSITION_STATE_EXIT)
    {
        if(mExitTime > 0)aScale = 1.0f - ((float)mTimer) / ((float)mExitTime);
        else aScale = 0.0f;
    }
    
    aScale *= mScale;
    
    Graphics::SetColor(0.0f, 0.0f, 0.0f);
    
    if(aScale <= 0.001f)
    {
        Graphics::DrawRect(0.0f, 0.0f, gDeviceWidth, gDeviceHeight);
    }
    else
    {
        aScale *= 4.0f;
        
        float aCenterX = (gVirtualDevX + gVirtualDevWidth / 2.0f);
        float aCenterY = (gVirtualDevY + gVirtualDevHeight / 2.0f - 30.0f);
        
        gApp->mTransitionCenter.Draw(aCenterX, aCenterY, aScale, 0.0f);
        
        float aWidth = (gApp->mTransitionCenter.mWidth * aScale);
        float aHeight = (gApp->mTransitionCenter.mHeight * aScale);
        
        float aBoxLeft = (aCenterX - (aWidth / 2.0f)) + 3.0f * aScale;
        float aBoxRight = (aCenterX + (aWidth / 2.0f)) - 3.0f * aScale;
        float aBoxTop = (aCenterY - (aHeight / 2.0f)) + 3.0f * aScale;
        float aBoxBottom = (aCenterY + (aHeight / 2.0f)) - 3.0f * aScale;
        
        Graphics::SetColor(0.0f, 0.0f, 0.0f);
        Graphics::DrawRect(aBoxLeft, 0.0f, (aBoxRight - aBoxLeft), aBoxTop);
        Graphics::DrawRect(aBoxLeft, aBoxBottom, (aBoxRight - aBoxLeft), gDeviceHeight - aBoxBottom);
        Graphics::DrawRect(0.0f, 0.0f, aBoxLeft, gDeviceHeight);
        Graphics::DrawRect(aBoxRight, 0.0f, gDeviceWidth - (aBoxRight + 30), gDeviceHeight);
        
        Graphics::SetColor();
    }
}

