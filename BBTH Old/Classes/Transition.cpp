//
//  Transition.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/25/13.
//  Completed by Nick Raptis on 03/31/15 at 1:40 AM after a 34 hour shred fest.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "Transition.h"
#include "FApp.h"
#include "GLApp.h"

#define TRANSITION_STATE_INITIAL 0
#define TRANSITION_STATE_ENTER 1
#define TRANSITION_STATE_SWAP 2
#define TRANSITION_STATE_EXIT 3

Transition::Transition()
{
    Log("Transition::Transition()\n\n");
    
    mKill = 0;
    
    mFade = 0.0f;
    mBlur = 0.0f;
    
    mTransitionState = TRANSITION_STATE_INITIAL;
    
    mEnterTime = 28;
    mSwapTime = 1;
    mExitTime = 30;
    
    mTimer = 0;
    
    mGlobalScale = 1.0f;
    mScale = 1.0f;
    
    float aMaxWidth = gApp->mTransitionCenter.mWidth * 4.0f;
    float aMaxHeight = gApp->mTransitionCenter.mHeight * 4.0f;
    
    float aScreenWidth = gAppWidth * 1.6f;
    float aScreenHeight = gAppHeight * 1.6f;
    
    int aFudge = 20;
    
    while (((aMaxWidth < aScreenWidth) || (aMaxHeight < aScreenHeight)) && (aFudge > 0))
    {
        mGlobalScale += 0.1f;
        
        aMaxWidth = gApp->mTransitionCenter.mWidth * 4.0f * mGlobalScale;
        aMaxHeight = gApp->mTransitionCenter.mHeight * 4.0f * mGlobalScale;
        
        aFudge--;
    }
}

Transition::~Transition()
{
    Log("Transition::~Transition()\n\n");
    
    //gApp->mTransition = 0;
    
}

void Transition::Update()
{
    /*
    if(mTransitionState == TRANSITION_STATE_INITIAL)
    {
        mTransitionState = TRANSITION_STATE_ENTER;
        mTimer = mEnterTime;
    }
    
    if(mTimer > 0)
    {
        mTimer--;
        
        if(mTransitionState == TRANSITION_STATE_EXIT)
        {
            mBlur -= 0.10f;
            if(mBlur < 0.0f)mBlur = 0.0f;
            
            if(mTimer < 8)
            {
                mFade = (mTimer / 8.0f);
            }
        }
        else
        {
            mFade += 0.18f;
            if(mFade > 1.0f)mFade = 1.0f;
            
            mBlur += 0.10f;
            if(mBlur > 1.0f)mBlur = 1.0f;
        }
        
        
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
                mKill = 5;
                //Kill();
            }
        }
    }
    */
}

void Transition::Draw()
{
    gApp->mViewController.mRoot.DrawTransform();
    
    float aScale = 0.0f;
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
    
    aScale *= (mScale * mGlobalScale);

    if(aScale <= 0.001f)
    {
        Graphics::SetColor(0.0f, 0.0f, 0.0f);
        Graphics::DrawRect(-2.0f, -2.0f, gAppWidth + 4.0f, gAppHeight + 4.0f);
    }
    else
    {
        Graphics::SetColor(1.0f, 0.95f, 0.8f, mFade * mBlur * 0.40f);
        Graphics::DrawRect(0.0f, 0.0f, gAppWidth, gAppHeight);
        
        aScale *= 4.0f;
        
        float aCenterX = gAppWidth2;
        float aCenterY = gAppHeight2 - gAppHeight2 * 0.15f;
        
        Graphics::SetColor(mFade);
        
        gApp->mTransitionCenter.Draw(aCenterX, aCenterY, aScale, 0.0f);
        
        float aWidth = (gApp->mTransitionCenter.mWidth * aScale);
        float aHeight = (gApp->mTransitionCenter.mHeight * aScale);
        
        float aBoxLeft = (aCenterX - (aWidth / 2.0f)) + 3.0f * aScale;
        float aBoxRight = (aCenterX + (aWidth / 2.0f)) - 3.0f * aScale;
        float aBoxTop = (aCenterY - (aHeight / 2.0f)) + 3.0f * aScale;
        float aBoxBottom = (aCenterY + (aHeight / 2.0f)) - 3.0f * aScale;
        
        Graphics::SetColor(0.0f, 0.0f, 0.0f);
        Graphics::DrawRect(aBoxLeft, 0.0f, (aBoxRight - aBoxLeft), aBoxTop);
        Graphics::DrawRect(aBoxLeft, aBoxBottom, (aBoxRight - aBoxLeft), (gAppHeight - aBoxBottom) + 4.0f);
        Graphics::DrawRect(0.0f, 0.0f, aBoxLeft, gAppHeight);
        Graphics::DrawRect(aBoxRight, 0.0f, gAppWidth - (aBoxRight - 6.0f), gAppHeight);
        Graphics::SetColor();
    }
}

