//
//  LevelCompleteText.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/13/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "LevelCompleteText.h"
#include "MainApp.h"
#include "core_includes.h"
#include "FAnimation.h"

LevelCompleteText::LevelCompleteText()
{
    mX = 0.0f;
    mY = 0.0f;
    
    mOffsetX = 0.0f;
    mOffsetY = 0.0f;
    
    mScale = 1.0f;
    mRotation = 0.0f;
    
    
    mWidth = 500.0f;
    mHeight = 240.0f;
    
    mLetterBounce = false;
    mLetterBounceIndex = 0;
    mLetterBounceTimer = 0;
    mLetterBounceScale = 1.0f;
    


    mEnterAnimation = false;
    mEnterAnimationPercent = 0.0f;
    
    
    
    
    mSwaySin = 0.0f;
    
    
}



LevelCompleteText::~LevelCompleteText()
{
    FreeList(LevelCompleteTextLetter, mLetters);
    
}

void LevelCompleteText::Update()
{
    
    //mExtraRotation
    
    /*
    if(mEnterAnimationMode == 0)
    {
        mEnterAnimationScale += mEnterAnimationScaleSpeed;
        
        //;
        
        mEnterAnimationScaleSpeed -= 0.004f;
        
        if(mEnterAnimationScaleSpeed <= 0.0f)
        {
            if(mEnterAnimationScale <= 1.0f)
            {
                mEnterAnimationScale = 1.0f;
            mEnterAnimationScaleSpeed = 0.0f;
            mEnterAnimationMode = 1;
            
            mEnterAnimationTimer = 130;
            }
        }
    }
    
    if(mEnterAnimationMode == 1)
    {
        mEnterAnimationTimer--;
        if(mEnterAnimationTimer <= 0)
        {
            mEnterAnimationTimer = 0;
            
            mEnterAnimationMode = 0;
            mEnterAnimationTimer = 0;
            
            mEnterAnimationScale = 0.15f;
            mEnterAnimationScaleSpeed = 0.086f;
            
        }
    }
     
    

    
    
    
    */
    
    
    
    
    if(mEnterAnimation)
    {
        
    }
    
    
    
    if(mLetterBounce)
    {
        mLetterBounceTimer--;
        if(mLetterBounceTimer <= 0)
        {
            mLetterBounceTimer = 0;
            LevelCompleteTextLetter *aLetter = (LevelCompleteTextLetter *)(mLetters.Fetch(mLetterBounceIndex));
            
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
    
    
    /*
    float aArc = (Sin(mSwaySin) + 1.0f) / 2.0f;
    EnumList(LevelCompleteTextLetter, aLetter, mLetters)
    {
        
        aLetter->mArc = aArc;
        
        //aLetter->mExtraY = aAmount * 50.0f * aLetter->mSkewFactor;
    }
    
    //mArc
    */
    
    
    EnumList(LevelCompleteTextLetter, aLetter, mLetters)aLetter->Update();
}

void LevelCompleteText::Draw(bool pShadow)
{
    //float aShiftSin = Sin(mBumpSinSpeedShift);
    
    float aX = mX + mOffsetX;
    float aY = mY + mOffsetY;
    
    float aRotation = 0.0f;
    float aScale = 1.0f;
    
    
    //aScale *= mEnterAnimationScale;
    
    //aX += mShiftDirX * aShiftSin * mBumpAmountShift;
    //aY += mShiftDirY * aShiftSin * mBumpAmountShift;
    
    
    Graphics::SetColor();
    Graphics::BlendSetAlpha();
    if(pShadow)
    {
        //EnumList(LevelCompleteTextLetter, aLetter, mLetters)aLetter->DrawStroke(aX, aY, aScale);
        EnumList(LevelCompleteTextLetter, aLetter, mLetters)aLetter->DrawShadow(aX, aY, aScale);
    }
    else
    {
        EnumList(LevelCompleteTextLetter, aLetter, mLetters)aLetter->Draw(aX, aY, aScale);
    }
    
    
}

void LevelCompleteText::Draw()
{
    Draw(false);
    
    Graphics::OutlineRect(mX - (mWidth / 2.0f), mY - (mHeight / 2.0f), mWidth, mHeight, 4);
}

void LevelCompleteText::DrawShadow()
{
    Draw(true);
}

void LevelCompleteText::SetUpTimeUp()
{
    
    int aIndex0 = 0;
    int aIndex1 = 1;
    
    AddLetter(&(gApp->mMILevelUpTextNoMovesN[aIndex0]), &(gApp->mMILevelUpTextNoMovesN[aIndex1]), -256.5f, 0.0f);
    AddLetter(&(gApp->mMILevelUpTextNoMovesO[aIndex0]), &(gApp->mMILevelUpTextNoMovesO[aIndex1]), -215.5f, 0.0f);
    
    AddLetter(&(gApp->mMILevelUpTextNoMovesM[aIndex0]), &(gApp->mMILevelUpTextNoMovesM[aIndex1]), -143.5f, 1.0f);
    AddLetter(&(gApp->mMILevelUpTextNoMovesO[aIndex0]), &(gApp->mMILevelUpTextNoMovesO[aIndex1]), -102.5f, -1.0f);
    AddLetter(&(gApp->mMILevelUpTextNoMovesV[aIndex0]), &(gApp->mMILevelUpTextNoMovesV[aIndex1]), -60.5f, 0.0f);
    AddLetter(&(gApp->mMILevelUpTextNoMovesE[aIndex0]), &(gApp->mMILevelUpTextNoMovesE[aIndex1]), -22.5f, 0.0f);
    AddLetter(&(gApp->mMILevelUpTextNoMovesS[aIndex0]), &(gApp->mMILevelUpTextNoMovesS[aIndex1]), 20.5f, 0.0f);
    
    AddLetter(&(gApp->mMILevelUpTextNoMovesL[aIndex0]), &(gApp->mMILevelUpTextNoMovesL[aIndex1]), 92.5f, 0.0f);
    AddLetter(&(gApp->mMILevelUpTextNoMovesE[aIndex0]), &(gApp->mMILevelUpTextNoMovesE[aIndex1]), 132.5f, 0.0f);
    AddLetter(&(gApp->mMILevelUpTextNoMovesF[aIndex0]), &(gApp->mMILevelUpTextNoMovesF[aIndex1]), 174.5f, 0.0f);
    AddLetter(&(gApp->mMILevelUpTextNoMovesT[aIndex0]), &(gApp->mMILevelUpTextNoMovesT[aIndex1]), 214.5f, 0.0f);
    
    AddLetter(&(gApp->mMILevelUpTextNoMovesDot[aIndex0]), &(gApp->mMILevelUpTextNoMovesDot[aIndex1]), 242.5f, 0.0f);
    AddLetter(&(gApp->mMILevelUpTextNoMovesDot[aIndex0]), &(gApp->mMILevelUpTextNoMovesDot[aIndex1]), 261.5f, 0.0f);
    AddLetter(&(gApp->mMILevelUpTextNoMovesDot[aIndex0]), &(gApp->mMILevelUpTextNoMovesDot[aIndex1]), 282.5f, 0.0f);

    mWidth = 560.0f;
    mHeight = 100.0f;
    
    SetUpLetters();
}

void LevelCompleteText::SetUpWin()
{
    int aIndex0 = 0;
    int aIndex1 = 1;
    
    AddLetter(&(gApp->mMILevelUpTextWinY[aIndex0]), &(gApp->mMILevelUpTextWinY[aIndex1]), -243.0f, 2.0f);
    AddLetter(&(gApp->mMILevelUpTextWinO[aIndex0]), &(gApp->mMILevelUpTextWinO[aIndex1]), -164.0f, 1.0f);
    AddLetter(&(gApp->mMILevelUpTextWinU[aIndex0]), &(gApp->mMILevelUpTextWinU[aIndex1]), -84.0f, 1.0f);
    
    AddLetter(&(gApp->mMILevelUpTextWinW[aIndex0]), &(gApp->mMILevelUpTextWinW[aIndex1]), 56.0f, 2.0f);
    AddLetter(&(gApp->mMILevelUpTextWinI[aIndex0]), &(gApp->mMILevelUpTextWinI[aIndex1]), 104.0f, 2.0f);
    AddLetter(&(gApp->mMILevelUpTextWinN[aIndex0]), &(gApp->mMILevelUpTextWinN[aIndex1]), 159.0f, 0.0f);
    
    AddLetter(&(gApp->mMILevelUpTextWinExc[aIndex0]), &(gApp->mMILevelUpTextWinExc[aIndex1]), 212.0f, 0.0f);
    AddLetter(&(gApp->mMILevelUpTextWinExc[aIndex0]), &(gApp->mMILevelUpTextWinExc[aIndex1]), 241.0f, 2.0f);
    AddLetter(&(gApp->mMILevelUpTextWinExc[aIndex0]), &(gApp->mMILevelUpTextWinExc[aIndex1]), 267.0f, 1.0f);
    
    mWidth = 560.0f;
    mHeight = 140.0f;
    
    SetUpLetters();
}

void LevelCompleteText::SetUpLetters()
{
    
    float aWidthFactor = mWidth / 2.0f;
    if(aWidthFactor < 2.0f)aWidthFactor = 2.0f;
    
    EnumList(LevelCompleteTextLetter, aLetter, mLetters)
    {
        aLetter->mSkewFactor = (aLetter->mBaseX / aWidthFactor);
        if(aLetter->mSkewFactor < 0.0f)
        {
            aLetter->mSkewFactor = -(aLetter->mSkewFactor);
            aLetter->mSkewDir = -1;
            aLetter->mSkewFactor = FAnimation::EaseOutSine(aLetter->mSkewFactor);
            
        }
        else
        {
            aLetter->mSkewDir = 1;
            aLetter->mSkewFactor = FAnimation::EaseInSine(aLetter->mSkewFactor);
        }
    }
}


void LevelCompleteText::AddLetter(FSprite *pSpriteShadow, FSprite *pSprite, float pX, float pY)
{
    LevelCompleteTextLetter *aLetter = new LevelCompleteTextLetter();
    aLetter->mSpriteShadow = pSpriteShadow;
    aLetter->mSprite = pSprite;
    
    aLetter->mBaseX = pX;
    aLetter->mBaseY = pY;
    
    aLetter->mX = pX;
    aLetter->mY = pY;
    
    mLetters += aLetter;
}

//mEnterAnimation = false;
//mEnterAnimationPercent = 0.0f;


void LevelCompleteText::EnterAnimationStart()
{
    mEnterAnimation = true;
    mEnterAnimationPercent = 0.0f;
    EnterAnimationUpdate(0.0f);
}

void LevelCompleteText::EnterAnimationUpdate(float pPercent)
{
    mEnterAnimationPercent = pPercent;
    int aIndex = 0;
    
    EnumList(LevelCompleteTextLetter, aLetter, mLetters)
    {
        float aIndexPer = ((float)aIndex) / ((float)(mLetters.mCount));
        aIndexPer = (1.0f - aIndexPer);
        
        float aFactor = mEnterAnimationPercent;
        
        aFactor += aIndexPer * 0.2f;
        if(aFactor >= 1.0f)aFactor = 1.0f;
        
        //aFactor = FAnimation::EaseOutBounce(aFactor, 0.4f);
        aFactor = FAnimation::EaseOutBack(aFactor, 1.4f);
        
        float aFactorX = aLetter->mSkewFactor;//FAnimation::EaseInSine(aLetter->mSkewFactor);
        float aPercent = (1.0f - aFactor);
        
        aFactorX = aPercent * aFactorX;
        
        
        aLetter->mCurrentOffsetX = (1.0f - aFactor) * (gAppWidth2 * 1.6f * aFactorX);
        aLetter->mCurrentOffsetY = (1.0f - aFactor) * (-(gAppHeight2 * 1.1f - aFactorX * gAppHeight2 * 0.60f));
        
        aLetter->mCurrentOffsetRotation = (1.0f - aFactor) * 34.0f;
        aLetter->mArc = (1.0f - mEnterAnimationPercent) * 0.3f;
        
        if(aLetter->mSkewDir < 0)
        {
            aLetter->mCurrentOffsetRotation = (-(aLetter->mCurrentOffsetRotation));
            aLetter->mCurrentOffsetX = -(aLetter->mCurrentOffsetX);
        }
        aIndex++;
    }
    
    
}

void LevelCompleteText::EnterAnimationFinish()
{
    mEnterAnimation = false;
    mEnterAnimationPercent = 1.0f;
    EnterAnimationUpdate(1.0f);
}

void LevelCompleteText::LetterBounce()
{
    if(mLetterBounce == false)
    {
        mLetterBounce = true;
        mLetterBounceTimer = 1;
        
        mLetterBounceIndex = 0;
    }
}