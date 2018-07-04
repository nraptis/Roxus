//
//  MainMenuButton.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/26/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "MainMenuButton.h"
#include "MainApp.h"
#include "core_includes.h"

MainMenuButton::MainMenuButton()
{
    mName = "MainMenuButton";
    
    mScaleAdd = 0.0f;
    
    mBumpSinRotate = 0.0f;
    mBumpSinSpeedRotate = 0.0f;
    
    mBumpSinShift = 0.0f;
    mBumpSinSpeedShift = 0.0f;
    
    mBumpSinScale = 0.0f;
    mBumpSinSpeedScale = 0.0f;
    
    
    mBumpAmountRotate = 0.0f;
    mBumpAmountShift = 0.0f;
    mBumpAmountScale = 0.0f;
    
    mShiftDirX = 0.0f;
    mShiftDirY = 0.0f;
    
    mGem = 0;
    
    mButtonSprite = 0;
    mButtonSpriteShadow = 0;
    
    
    mLetterBounce = false;
    mLetterBounceIndex = 0;
    mLetterBounceTimer = 0;
    mLetterBounceScale = 1.0f;
    
    
    mLeavesRuffle = false;
    mLeavesRuffleAmount = 0.0f;
    mLeavesRuffleFadeIn = 0.0f;
    mLeavesRuffleSin = 0.0f;
    mLeavesRuffleTimer = 0;
}

MainMenuButton::~MainMenuButton()
{
    if(mGem)
    {
        delete mGem;
        mGem = 0;
    }
    
    FreeList(MainMenuButtonLeaf, mLeavesLeft);
    FreeList(MainMenuButtonLeaf, mLeavesRight);
    
    FreeList(MainMenuButtonLetter, mLetters);
    
}

void MainMenuButton::Update()
{
    
    if(gRand.Get(80) == 6)LetterBounce();
    
    if(gRand.Get(60) == 6)LeavesRuffle();
    
    mBumpSinRotate += mBumpSinSpeedRotate;
    if(mBumpSinRotate >= 360.0f)mBumpSinRotate -= 360.0f;
    if(mBumpSinRotate < 0.0f   )mBumpSinRotate += 360.0f;
    
    mBumpSinShift += mBumpSinSpeedShift;
    if(mBumpSinShift >= 360.0f)mBumpSinShift -= 360.0f;
    if(mBumpSinShift < 0.0f   )mBumpSinShift += 360.0f;
    
    mBumpSinScale += mBumpSinSpeedScale;
    if(mBumpSinScale >= 360.0f)mBumpSinScale -= 360.0f;
    if(mBumpSinScale < 0.0f   )mBumpSinScale += 360.0f;
    
    if(mBumpAmountRotate > 0)
    {
        mBumpAmountRotate *= 0.975f;
        mBumpAmountRotate -= 0.025f;
        if(mBumpAmountRotate < 0)
        {
            mBumpAmountRotate = 0.0f;
        }
    }
    
    if(mBumpAmountShift > 0)
    {
        mBumpAmountShift *= 0.975f;
        mBumpAmountShift -= 0.025f;
        if(mBumpAmountShift < 0)
        {
            mBumpAmountShift = 0.0f;
        }
    }
    
    if(mBumpAmountScale > 0)
    {
        mBumpAmountScale *= 0.975f;
        mBumpAmountScale -= 0.00025f;
        if(mBumpAmountScale < 0)
        {
            mBumpAmountScale = 0.0f;
        }
    }
    
    
    if(mTouchDownInside)
    {
        if(mScaleAdd < 0.175f)mScaleAdd += 0.0125f;
        if(mScaleAdd >= 0.175f)mScaleAdd = 0.175f;
    }
    else
    {
        if(mScaleAdd > 0.0f)
        {
            mScaleAdd -= 0.01f;
            if(mScaleAdd <= 0.0f)mScaleAdd = 0.0f;
        }
    }
    
    
    if(mLeavesRuffle)
    {
        mLeavesRuffleSin -= 6.0f;
        if(mLeavesRuffleSin <= 0.0f)mLeavesRuffleSin += 360.0f;
        
        
        mLeavesRuffleTimer++;
        
        if(mLeavesRuffleTimer > 32)
        {
            mLeavesRuffleAmount *= 0.98f;
            
            mLeavesRuffleAmount -= 0.02f;
            if(mLeavesRuffleAmount <= 0.0f)
            {
                mLeavesRuffle = false;
                mLeavesRuffleAmount = 0.0f;
                mLeavesRuffleTimer = 0;
                mLeavesRuffleSin = 0.0f;
            }
        }
        
        mLeavesRuffleFadeIn += 0.05f;
        if(mLeavesRuffleFadeIn >= 1.0f)mLeavesRuffleFadeIn = 1.0f;
        
    }
    
    float aRuffleAmount = mLeavesRuffleFadeIn * mLeavesRuffleAmount;
    
    EnumList(MainMenuButtonLeaf, aLeaf, mLeavesRight)
    {
        float aSin = mLeavesRuffleSin + aLeaf->mRuffleOffset;
        aLeaf->mRuffleRot = Sin(aSin) * aRuffleAmount;
    }
    
    EnumList(MainMenuButtonLeaf, aLeaf, mLeavesLeft)
    {
        float aSin = mLeavesRuffleSin + aLeaf->mRuffleOffset;
        aLeaf->mRuffleRot = Sin(aSin) * aRuffleAmount;
    }
    
    if(mLetterBounce)
    {
        mLetterBounceTimer--;
        if(mLetterBounceTimer <= 0)
        {
            mLetterBounceTimer = 0;
            MainMenuButtonLetter *aLetter = (MainMenuButtonLetter *)(mLetters.Fetch(mLetterBounceIndex));
            
            if(aLetter)
            {
                aLetter->Bounce();
                aLetter->mBounceScale = mLetterBounceScale;
                
                mLetterBounceIndex++;
                mLetterBounceTimer = 6;
            }
            else
            {
                mLetterBounce = false;
                mLetterBounceTimer = 0;
            }
        }
    }
    
    EnumList(MainMenuButtonLeaf, aLeaf, mLeavesLeft)aLeaf->Update();
    EnumList(MainMenuButtonLeaf, aLeaf, mLeavesRight)aLeaf->Update();
    
    EnumList(MainMenuButtonLetter, aLetter, mLetters)aLetter->Update();
    
    if(mGem)mGem->Update(mX, mY, mTransform.mScale);
    
}

void MainMenuButton::Draw()
{
    
    
    
    
    float aShiftSin = Sin(mBumpSinSpeedShift);
    
    float aX = mWidth2;
    float aY = mHeight2;
    
    float aRotation = mBumpAmountRotate * Sin(mBumpSinRotate);
    float aScale = 1.0f + mScaleAdd + mBumpAmountScale * Sin(mBumpSinScale);
    
    
    aX += mShiftDirX * aShiftSin * mBumpAmountShift;
    aY += mShiftDirY * aShiftSin * mBumpAmountShift;
    
    if(mButtonSpriteShadow)mButtonSpriteShadow->Draw(aX, aY + 13.0f * aScale, aScale, aRotation);
    
    
    EnumList(MainMenuButtonLeaf, aLeaf, mLeavesLeft)aLeaf->DrawShadow(aX - 3.0f, aY + 10.0f, aScale);
    EnumList(MainMenuButtonLeaf, aLeaf, mLeavesRight)aLeaf->DrawShadow(aX + 3.0f, aY + 10.0f, aScale);
    
    EnumList(MainMenuButtonLeaf, aLeaf, mLeavesLeft)aLeaf->DrawLeaf(aX, aY, aScale);
    EnumList(MainMenuButtonLeaf, aLeaf, mLeavesRight)aLeaf->DrawLeaf(aX, aY, aScale);
    
    if(mButtonSprite)mButtonSprite->Draw(aX, aY, aScale, aRotation);
    
    aX = mWidth2;
    aY = mHeight2;
    
    EnumList(MainMenuButtonLetter, aLetter, mLetters)aLetter->Draw(mWidth2, mHeight2, aScale);
    
    Graphics::SetColor();
    
    if(mGem)mGem->Draw(aX, aY, aScale);
    
}

void MainMenuButton::ButtonActionRollOver()
{
    
}

void MainMenuButton::ButtonActionRollOff()
{
    
}

void MainMenuButton::ButtonActionDragOver()
{
    Bump();
}

void MainMenuButton::ButtonActionDragOff()
{
    Bump();
}

void MainMenuButton::ButtonActionReleaseOver()
{
    Bump();
}

void MainMenuButton::ButtonActionReleaseOff()
{
    
}

void MainMenuButton::Bump()
{
    if(mBumpAmountRotate <= 0.025f && mBumpAmountShift <= 0.025f && mBumpAmountScale <= 0.0025f)
    {
        mBumpAmountRotate = 4.0f + gRand.GetFloat(2.5f);
        mBumpAmountShift = 4.0f + gRand.GetFloat(2.5f);
        mBumpAmountScale = 0.04f + gRand.GetFloat(0.02f);
        
        
        mShiftDirX = gRand.GetFloat(-1.0f, 1.0f);
        mShiftDirY = gRand.GetFloat(-1.0f, 1.0f);
        
        
        mBumpSinRotate = 0.0f;
        mBumpSinSpeedRotate = 5.0f + gRand.GetFloat(3.0f);
        
        mBumpSinShift = 0.0f;
        mBumpSinSpeedShift = 12.0f + gRand.GetFloat(10.0f);
        
        mBumpSinScale = 0.0f;
        mBumpSinSpeedScale = 8.0f + gRand.GetFloat(4.0f);
        
        if(gRand.GetBool())mBumpSinSpeedRotate = -mBumpSinSpeedRotate;
        if(gRand.GetBool())mBumpSinSpeedShift  = -mBumpSinShift;
        if(gRand.GetBool())mBumpSinSpeedScale  = -mBumpSinSpeedScale;
    }
}

void MainMenuButton::SetSprites(FSprite *pSprite, FSprite *pSpriteShadow)
{
    mButtonSprite = pSprite;
    mButtonSpriteShadow = pSpriteShadow;
    
    if(pSprite)
    {
        if(pSprite->mWidth > mWidth)SetWidth(pSprite->mWidth);
        if(pSprite->mHeight > mHeight)SetHeight(pSprite->mHeight);
    }
}




void MainMenuButton::AddLetter(FSprite *pSprite, float pX, float pY)
{
    MainMenuButtonLetter *aLetter = new MainMenuButtonLetter();
    aLetter->mSprite = pSprite;
    
    aLetter->mX = pX;
    aLetter->mY = pY;
    
    mLetters += aLetter;
}

void MainMenuButton::AddLeavesRight(float pOffset)
{
    
    int aCount = 5;
    
    
    for(int i=0;i<aCount;i++)
    {
        MainMenuButtonLeaf *aLeaf = new MainMenuButtonLeaf();
        
        float aScale = 0.67f;
        if(i == 1)aScale = 0.84f;
        if(i == 3)aScale = 1.08f;
        if(i == 5)aScale = 0.76f;
        
        aLeaf->mLeft = false;
        aLeaf->mButtonOffset = pOffset;
        aLeaf->mBaseScale = aScale;
        aLeaf->mBaseArmRot = 32.0f + ((float)i) * 24.0f;
        aLeaf->mBaseArmLength = 40.0f;
        aLeaf->mRuffleOffset = ((float)i) * (8.0f);
        
        mLeavesRight += aLeaf;
    }
}

void MainMenuButton::AddLeavesLeft(float pOffset)
{
    
    int aCount = 5;
    
    for(int i=0;i<aCount;i++)
    {
        MainMenuButtonLeaf *aLeaf = new MainMenuButtonLeaf();
        
        
        float aScale = 0.66f;
        
        if(i == 1)aScale = 0.82f;
        if(i == 3)aScale = 1.08f;
        if(i == 5)aScale = 0.76f;
        
        aLeaf->mLeft = true;
        aLeaf->mButtonOffset = pOffset;
        aLeaf->mBaseScale = aScale;
        
        aLeaf->mBaseArmRot = -32.0f - ((float)i) * 24.0f;
        aLeaf->mBaseArmLength = 40.0f;
        
        aLeaf->mRuffleOffset = ((float)i) * (8.0f);
        
        mLeavesLeft += aLeaf;
    }
}





void MainMenuButton::LetterBounce()
{
    if(mLetterBounce == false)
    {
        mLetterBounce = true;
        mLetterBounceTimer = 1;
        
        mLetterBounceIndex = 0;
    }
}


void MainMenuButton::LeavesRuffle()
{
    if(mLeavesRuffle == false)
    {
        mLeavesRuffle = true;
        
        mLeavesRuffleAmount = 9.0f;
        mLeavesRuffleSin = 0.0f;
        
        mLeavesRuffleTimer = 0;
        
        mLeavesRuffleFadeIn = 0.0f;
    }
}






MainMenuButtonLetter::MainMenuButtonLetter()
{
    mSprite = 0;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mBounceAmount = 0.0f;
    mBounceTimer = 0;
    
    mBounceSin = 0.0f;
    mBounceSinSpeed = 0.0f;
}

MainMenuButtonLetter::~MainMenuButtonLetter()
{
    
}

void MainMenuButtonLetter::Update()
{
    if(mBounceAmount > 0.0f)
    {
        mBounceSin += mBounceSinSpeed;
        if(mBounceSin >= 360.0f)mBounceSin -= 360.0f;
        mBounceSinSpeed *= 0.997f;
        
        mBounceTimer++;
        if(mBounceTimer > 18)
        {
            mBounceTimer = 18;
            mBounceAmount *= 0.96f;
            mBounceAmount -= 0.03f;
        }
        
        if(mBounceAmount <= 0.0f)
        {
            mBounceAmount = 0.0f;
            mBounceTimer = 0;
        }
    }
}

void MainMenuButtonLetter::Draw(float pX, float pY, float pScale)
{
    float aX = mX * pScale + pX;
    float aY = mY * pScale + pY;
    float aScaleX = pScale;
    float aScaleY = pScale;
    float aRot = 0.0f;
    
    if(mBounceAmount > 0.0f)
    {
        float aBounceSin = Sin(mBounceSin);
        aScaleY += aBounceSin * 0.033f;
        aScaleX -= aBounceSin * 0.025f;
        aY -= aBounceSin * mBounceAmount * 0.5f * mBounceScale;
        aRot += aBounceSin * (-3.0f);
    }
    if(mSprite)
    {
        mSprite->DrawScaled(aX, aY, aScaleX, aScaleY, aRot);
    }
}


void MainMenuButtonLetter::Bounce()
{
    mBounceAmount = 12.0f;
    
    mBounceTimer = 0;
    
    mBounceSin = 0.0f;
    
    mBounceSinSpeed = 9.0f + gRand.F();

    
}

MainMenuButtonLeaf::MainMenuButtonLeaf()
{
    mX = 0.0f;
    mY = 0.0f;
    
    mBaseArmRot = 0.0f;
    mBaseArmLength = 0.0f;
    mBaseScale = 1.0f;
    
    mLeft = false;
    
    mRuffleOffset = 0.0f;
    mRuffleRot = 0.0f;
    
    mWobblerRot.SetTime(120, 40);
    mWobblerRot.SetInterval(-2.0f, 2.0f);
    
    mWobblerExtend.SetTime(60, 20);
    mWobblerExtend.SetInterval(-1.5f, 1.5f);
    
    mRuffleOffset = 0.0f;
    mRuffleRot = 0.0f;
}

MainMenuButtonLeaf::~MainMenuButtonLeaf()
{
    
}

void MainMenuButtonLeaf::Update()
{
    mWobblerRot.Update();
    mWobblerExtend.Update();
}

void MainMenuButtonLeaf::DrawShadow(float pX, float pY, float pScale)
{
    Draw(&(gApp->mTitleButtonLeaf[1]), pX, pY, pScale);
}

void MainMenuButtonLeaf::DrawLeaf(float pX, float pY, float pScale)
{
    Draw(&(gApp->mTitleButtonLeaf[0]), pX, pY, pScale);
}

void MainMenuButtonLeaf::Draw(FSprite *pSprite, float pX, float pY, float pScale)
{
    float aX = pX;
    float aY = pY;
    
    if(mLeft)aX -= mButtonOffset * pScale;
    else aX += mButtonOffset * pScale;
    
    float aArmRot = mBaseArmRot;
    float aArmLength = (mBaseArmLength + mWobblerExtend.V()) * pScale;
    
    float aRot = aArmRot;
    
    if(mLeft == false)aRot = (180.0f - (aRot + 90.0f));
    else aRot += 98.0f;
    
    
    float aOffsetRotation = mWobblerRot.V() + mRuffleRot;
    
    aOffsetRotation += mRuffleRot;
    
    //if(mLeft)aArmRot = 180.0f - (aArmRot + 45.0f);
    //else aArmRot += 90.0f;
    
    float aArmX = Sin(aArmRot) * aArmLength;
    float aArmY = -Cos(aArmRot) * aArmLength;
    
    float aScaleX = mBaseScale * pScale;
    float aScaleY = mBaseScale * pScale;
    
    if(mLeft == false)aScaleX = -aScaleX;
    
    aX += aArmX;
    aY += aArmY;
    
    aRot += aOffsetRotation;
    
    
    if(pSprite)pSprite->DrawScaled(aX, aY, aScaleX, aScaleY, aRot);
}


MainMenuButtonGem::MainMenuButtonGem()
{
    mWobbleRotSin = 0.0f;
    
    mX = 0.0f;
    mY = 0.0f;
}

MainMenuButtonGem::~MainMenuButtonGem()
{
    
}

void MainMenuButtonGem::Update(float pX, float pY, float pScale)
{
    mWobbleRotSin += 5.0f;
    if(mWobbleRotSin >= 360.0f)
    {
        mWobbleRotSin -= 360.0f;
    }
    
    //mTwinkle.mOffsetX = 120.0f;
    //mTwinkle.mOffsetY = 40.0f;
    
    mTwinkle.Update(mX + 120.0f * pScale, mY + 18.0f * pScale, pScale, 0.0f);
    
}

void MainMenuButtonGem::Draw(float pX, float pY, float pScale)
{
    float aX = mX * pScale + pX;
    float aY = mY * pScale + pY;
    
    float aWobbleRot = Sin(mWobbleRotSin) * 3.0f;
    
    gApp->mTitleButtonStoreGem.Draw(aX, aY, 1.0f, aWobbleRot, 0);
    
    mTwinkle.Draw();
}


