//
//  TowerDetailMenu.cpp
//  Mustache
//
//  Created by Nick Raptis on 9/6/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "TowerDetailMenu.h"

TowerDetailMenu::TowerDetailMenu() {

    mApp = GAPP;
    mTower = 0;

    mHidden = true;
    mAnimating = false;
    mAnimatingIn = false;
    
    mScale = 0.0f;
    
    mCenterX = gAppWidth2;
    mCenterY = gAppHeight2;
    
    mWidth = gAppWidth2;
    mHeight = gAppHeight2;

    mButtonClickedIndex = -1;

    for (int i=0;i<3;i++) {
        mButtonX[i] = 0.0f;
        mButtonY[i] = 0.0f;
    }
    
    mButtonWidth = mApp->mTowerDetailMenuButtonSell.mWidth;
    mButtonHeight = mApp->mTowerDetailMenuButtonSell.mHeight;
    
}

TowerDetailMenu::~TowerDetailMenu()
{
    
}

void TowerDetailMenu::Update()
{
    if(mHidden == false)
    {
        if(mAnimating)
        {
            if(mAnimatingIn)
            {
                mScale += 0.075f;
                if(mScale >= 1.0f)
                {
                    mScale = 1.0f;
                    mAnimating = false;
                }
            }
            else
            {
                mScale -= 0.075f;
                if(mScale <= 0.0f)
                {
                    mScale = 0.0f;
                    mAnimating = false;
                    mHidden = true;
                    mTower = 0;
                }
            }
        }
        
        float aWidth = mWidth * mScale;
        float aHeight = mHeight * mScale;
        
        mButtonX[0] = mCenterX - aWidth / 2.0f;
        mButtonY[0] = mCenterY;
        
        mButtonX[1] = mCenterX;
        mButtonY[1] = mCenterY - aHeight / 2.0f;
        
        mButtonX[2] = mCenterX + aWidth / 2.0f;
        mButtonY[2] = mCenterY;
        
        //float aButtonWidth = mButtonWidth * mScale;
        //float aButtonHeight = mButtonHeight * mScale;
        
        //mButtonWidth = mApp->mTowerDetailMenuButtonSell.mWidth;
        //mButtonHeight = mApp->mTowerDetailMenuButtonSell.mHeight;
    }
}

bool TowerDetailMenu::TouchHitsButton(float x, float y)
{
    bool aReturn = false;
    
    float aWidth2 = mButtonWidth * 0.5f;
    float aHeight2 = mButtonHeight * 0.5f;
    
    mButtonClickedIndex = -1;
    for(int i=0;i<3;i++)
    {
        
        float aXDiff = mButtonX[i] - x;
        float aYDiff = mButtonY[i] - y;
        
        if(aXDiff < 0)aXDiff = -aXDiff;
        if(aYDiff < 0)aYDiff = -aYDiff;
        
        if(aXDiff <= aWidth2 && aYDiff <= aHeight2)
        {
            mButtonClickedIndex = i;
            aReturn = true;
            
            
        }
    }
    
    return aReturn;
}

int TowerDetailMenu::ReleaseAction(float x, float y)
{
    int aReturn = -1;
    
    float aWidth2 = mButtonWidth * 0.5f;
    float aHeight2 = mButtonHeight * 0.5f;
    
    int aButtonClickedIndex = -1;
    for(int i=0;i<3;i++)
    {
        
        float aXDiff = mButtonX[i] - x;
        float aYDiff = mButtonY[i] - y;
        
        if(aXDiff < 0)aXDiff = -aXDiff;
        if(aYDiff < 0)aYDiff = -aYDiff;
        
        if(aXDiff <= aWidth2 && aYDiff <= aHeight2)
        {
            aButtonClickedIndex = i;
        }
    }
    
    if(aButtonClickedIndex == mButtonClickedIndex)
    {
        aReturn = aButtonClickedIndex;
    }
    else
    {
        mButtonClickedIndex = -1;
    }
    
    return aReturn;
}


void TowerDetailMenu::Draw()
{
    if(mHidden == false)
    {
        Graphics::SetColor(0.15f, 1.0f, 0.15f, 0.4f);
        
        float aWidth = mWidth * mScale;
        float aHeight = mHeight * mScale;
        
        Graphics::DrawRect(mCenterX - aWidth / 2.0f, mCenterY - aHeight / 2.0f, aWidth, aHeight);
        
        Graphics::SetColor(1.0f);
        
        if(mButtonClickedIndex == 0)Graphics::SetColor(0.75f,0.75f,0.75f);else Graphics::SetColor();
        mApp->mTowerDetailMenuButtonInfo.Draw(mButtonX[0], mButtonY[0], mScale, 0.0f);
        
        if(mButtonClickedIndex == 1)Graphics::SetColor(0.75f,0.75f,0.75f);else Graphics::SetColor();
        mApp->mTowerDetailMenuButtonSell.Draw(mButtonX[1], mButtonY[1], mScale, 0.0f);
        
        if(mButtonClickedIndex == 2)Graphics::SetColor(0.75f,0.75f,0.75f);else Graphics::SetColor();
        mApp->mTowerDetailMenuButtonUpgrade.Draw(mButtonX[2], mButtonY[2], mScale, 0.0f);
    }
}

void TowerDetailMenu::AnimateIn(float x, float y, float pZoomScale, Tower *pTower) {
    if (pTower) {
        mCenterX = x;
        mCenterY = y;
        
        mTower = pTower;
        
        mWidth = pTower->mRange * pZoomScale;
        mHeight = pTower->mRange * pZoomScale;
        
        mScale = 0.0f;
        
        mAnimatingIn = true;
        mAnimating = true;
        mHidden = false;

        mButtonClickedIndex = -1;
    }
}

void TowerDetailMenu::AnimateOut() {
    if (mAnimating == false) {
        mAnimatingIn = false;
        mAnimating = true;
        mButtonClickedIndex = -1;
    }
}
