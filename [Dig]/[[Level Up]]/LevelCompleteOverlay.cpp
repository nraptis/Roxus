//
//  LevelCompleteOverlay.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/26/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "LevelCompleteOverlay.h"
#include "MainMenu.h"
#include "GameMenu.h"

LevelCompleteOverlay::LevelCompleteOverlay()
{
    mConsumesTouches = false;
    
    mName = "LevelCompleteOverlay[FView]";
    
    mText = 0;
    mTextLose = 0;
    
    
    mPrizeChest = 0;
    
    
    
    
    //mText = new LevelCompleteText();
    //mText->SetUpWin();
    //mText->mX = mWidth2;
    //mText->mY = mHeight2;
    
    
    //mTextLose = new LevelCompleteText();
    //mTextLose->SetUpTimeUp();
    //mTextLose->mX = mWidth2;
    //mTextLose->mY = mHeight2;
    
    mTextAnimationMode = 0;
    mTextAnimationTime = 22;
    mTextAnimationTimer = 0;
    mTextAnimationPercent = 0.0f;
    
    
    

    mMode = 0;
    mModeTimer = 0;
    
    mFadeInTimer = 0;
    mFadeBackgroundAlpha = 0.0f;
    
    
    mWin = false;
    
    mMode = 0;
    mModeTimer = 20;

    
    SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
}

LevelCompleteOverlay::~LevelCompleteOverlay()
{
    Log("LevelCompleteOverlay Dealloc!\n");
    
}

void LevelCompleteOverlay::PositionContent()
{
    if(mText)
    {
        mText->mX = mWidth2;
        mText->mY = mHeight2 * 0.52f;
    }
    
    if(mTextLose)
    {
        mTextLose->mX = mWidth2;
        mTextLose->mY = mHeight2 + 140.0f;
    }
    
    if(mPrizeChest)
    {
        mPrizeChest->SetCenter(mWidth2, mHeight2 - mHeight2 * 0.15f);
    
    }
    
}

void LevelCompleteOverlay::SetUp(float pScale, FVec2 pCenter, bool pDidWin)
{
    mWin = pDidWin;
    
    SetTransformScale(pScale);
    
    
    
    
    SetSize(((float)gAppWidth) / pScale, ((float)gAppHeight) / pScale);

}

void LevelCompleteOverlay::Update()
{
    mModeTimer++;
    
    /*
    mButtWiggleSin1 += 4.0f;
    if(mButtWiggleSin1 >= 360.0f)mButtWiggleSin1 -= 360.0f;
    
    mButtWiggleSin2 -= 1.4f;
    if(mButtWiggleSin2 < 0)mButtWiggleSin2 += 360.0f;
    */
    
    
    if(mTextAnimationTime > 0)
    {
        mTextAnimationTimer++;
        if(mTextAnimationTimer > mTextAnimationTime)mTextAnimationTimer = mTextAnimationTime;
        mTextAnimationPercent = ((float)mTextAnimationTimer) / ((float)mTextAnimationTime);
    }
    
    if(mTextAnimationMode == 0)
    {
        if(mTextAnimationTimer == mTextAnimationTime)
        {
            mText = new LevelCompleteText();
            mText->SetUpTimeUp();
            mText->mX = mWidth2;
            mText->mY = mHeight2 * 0.52f;
            mText->EnterAnimationStart();
            
            mTextAnimationMode = 1;
            mTextAnimationTime = 158;
            mTextAnimationTimer = 0;
        }
    }
    else if(mTextAnimationMode == 1)
    {
        mText->EnterAnimationUpdate(mTextAnimationPercent);
        
        mText->mOffsetY = -100.0f * FAnimation::EaseOutElastic(mTextAnimationPercent);
        
        
        if(mTextAnimationTimer == mTextAnimationTime)
        {
            mText->EnterAnimationFinish();
            mText->LetterBounce();
            
            mTextAnimationMode = 2;
            mTextAnimationTime = 500;
            mTextAnimationTimer = 0;
        }
    }

    
    
    if(mText)mText->Update();
    if(mTextLose)mTextLose->Update();
    //if(mPrizeChest)mPrizeChest->Update();
    
    if(mMode == 0)
    {
        if(mModeTimer >= 30)
        {
            mMode = 1;
            mModeTimer = 0;
            
            
            mPrizeChest = new PrizeChestDialog();
            AddSubview(mPrizeChest);
            mPrizeChest->SetCenter(mWidth2, mHeight2 - mHeight2 * 0.15f);
        }
    }
    else if(mMode == 1)
    {
        
        if(mModeTimer >= 30)
        {
            mModeTimer = 0;
            mMode = 2;
        }
        
        mFadeBackgroundAlpha += 0.015f;
        if(mFadeBackgroundAlpha >= 0.6f)
        {
            mFadeBackgroundAlpha = 0.6f;
        }
    }
    else if(mMode == 2)
    {
        
    }
}

void LevelCompleteOverlay::Draw()
{
    Graphics::SetColor();
    
    
    if(mPrizeChest)
    {
        mPrizeChest->DrawManual();
        DrawTransform();
    }
    
    if(mText)
    {
        mText->DrawShadow();
        mText->Draw();
    }
    
    if(mTextLose)
    {
        mTextLose->DrawShadow();
        mTextLose->Draw();
    }
    
    
    
    Graphics::SetColor();
}

void LevelCompleteOverlay::TouchDown(float pX, float pY, void *pData)
{
    
}

void LevelCompleteOverlay::TouchUp(float pX, float pY, void *pData)
{
    
}

void LevelCompleteOverlay::TouchMove(float pX, float pY, void *pData)
{
    
}

void LevelCompleteOverlay::TouchFlush()
{
    
}
