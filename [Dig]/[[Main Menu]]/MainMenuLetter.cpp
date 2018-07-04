//
//  MainMenuLetter.cpp
//  Gnomes
//
//  Created by Nick Raptis on 3/28/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#include "MainMenuLetter.h"


MainMenuLetter::MainMenuLetter(FSprite *pSprite)
{
    mSprite = pSprite;

    mX = 0.0f;
    mY = 0.0f;
    
    
    mSound = &(gApp->mSoundTitleLetterBonk);
    mSoundPitch = 1.0f;
    
    mRotSin = gRand.GetFloat(360.0f);
    mRotSinSpeed = 4.0f + gRand.GetFloat(2.0f);
    mRotAmount = 3.0f;
    
    mBounceSin = 0.0f;
    mBounceAmount = 0.0f;
    
    
    
}

MainMenuLetter::~MainMenuLetter()
{
    
}

void MainMenuLetter::Update()
{
    if(mBounceAmount > 0)
    {
        mBounceAmount *= 0.96f;
        mBounceAmount -= 0.01f;
        if(mBounceAmount < 0)mBounceAmount = 0.0f;
    }
    
    mRotSin += mRotSinSpeed;
    if(mRotSin >= 360.0f)mRotSin -= 360.0f;
    
    
    mBounceSin += 8.0f;
    if(mBounceSin >= 360.0f)mBounceSin -= 360.0f;
    
}

void MainMenuLetter::Draw()
{
    float aBounceX = 0.0f;
    float aBounceY = Sin(mBounceSin) * mBounceAmount;
    
    float aRotation = Sin(mRotSin) * mRotAmount;
    //aRotation = 0.0f;
    
    mSprite->Draw(mX + aBounceX, mY + aBounceY, 1.0f, aRotation);
    
}

void MainMenuLetter::Bounce()
{
    mBounceSin = 0.0f;
    mBounceAmount = 24.0f;
    
    mSound->PlayPitched(mSoundPitch);
}

MainMenuLetterRow2::MainMenuLetterRow2(FSprite *pSprite) : MainMenuLetter(pSprite)
{
    
}

MainMenuLetterRow2::~MainMenuLetterRow2()
{
    
}

void MainMenuLetterRow2::Bounce()
{
    mBounceSin = 0.0f;
    mBounceAmount = 18.0f;
    
    mSound->PlayPitched(mSoundPitch);
}

