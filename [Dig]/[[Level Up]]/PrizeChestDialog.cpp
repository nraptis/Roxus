//
//  PrizeChestDialog.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/15/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "PrizeChestDialog.h"
#include "MainApp.h"
#include "FAnimation.h"

PrizeChestDialog::PrizeChestDialog()
{
    mX = 0.0f;
    mY = 0.0f;
    
    mDrawManual = true;
    
    //mWidth = gApp->mMIDialogBackSmall.mWidth;
    //mHeight = gApp->mMIDialogBackSmall.mHeight;
    
    
    SetFrame(0.0f, 0.0f, gApp->mMIDialogBackSmall.mWidth, gApp->mMIDialogBackSmall.mHeight);
    //PrizeChestDialog
    
    mChestX = 0.0f;
    mChestY = -50.0f;
    
    
    
    
    mChest = false;
    mChestOpen = false;
    
    
    mChestScale = 0.0f;
    mChestScaleX = 1.0f;
    mChestScaleY = 1.0f;
    mChestRotation = 0.0f;
    
    mAnimationEnter = true;
    mAnimationEnterPercent = 0.0f;
    mAnimationEnterMode = 0;
    mAnimationEnterTimer = 0;
    mAnimationEnterTime = 130;
    
    
    mBackScale = 0.0f;
    mBackScaleX = 1.0f;
    mBackScaleY = 1.0f;
    
}

PrizeChestDialog::~PrizeChestDialog()
{
    
}


void PrizeChestDialog::Update()
{
    
    
    if(mAnimationEnter)
    {
        
        if(mAnimationEnterTime > 0)
        {
            mAnimationEnterTimer++;
            if(mAnimationEnterTimer > mAnimationEnterTime)mAnimationEnterTimer = mAnimationEnterTime;
            mAnimationEnterPercent = ((float)mAnimationEnterTimer) / ((float)mAnimationEnterTime);
        }
        
        if(mAnimationEnterMode == 0)
        {
            
            if(mAnimationEnterTimer >= mAnimationEnterTime)
            {
                mBackScale = 1.0f;
                
                mAnimationEnterTimer = 0;
                mAnimationEnterTime = 90;
                mAnimationEnterMode = 1;
                
            }
            else
            {
                mBackScale = FAnimation::EaseOutBack(mAnimationEnterPercent, 1.7f);
            }
        }
        else if(mAnimationEnterMode == 1)
        {
            
            if(mAnimationEnterTimer >= mAnimationEnterTime)
            {
                mChestScale = 1.0f;
                
                mAnimationEnterTimer = 0;
                mAnimationEnterTime = 90;
                mAnimationEnterMode = 2;
                
            }
            else
            {
                mChestScale = FAnimation::EaseOutBack(mAnimationEnterPercent, 1.7f);
            }
        }
        
    }
    

    
}

void PrizeChestDialog::Draw()
{
    
    
    float aX = mWidth2;
    float aY = mHeight2;
    
    float aChestX = aX + mChestX;
    float aChestY = aY + mChestY;
    
    if(mBackScale > 0.0f)
    {
        gApp->mMIDialogBackSmall.DrawScaled(aX, aY, mBackScale * mBackScaleX, mBackScale * mBackScaleY, 0.0f);
    }
    
    if(mChestScale > 0.0f)
    {
        gApp->mMIPrizeChestClosed.DrawScaled(aChestX, aChestY, mChestScale * mChestScaleX, mChestScale * mChestScaleY, 0.0f);
    }
    
    mChestSpinner1.Transform(100, 30, 1, 1, 60);
    mChestSpinner1.Draw();
    
}

void PrizeChestDialog::Notify(void *pSender)
{
    
}






