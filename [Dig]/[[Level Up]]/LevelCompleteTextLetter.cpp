//
//  LevelCompleteTextLetter.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/13/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "LevelCompleteTextLetter.h"
#include "core_includes.h"



LevelCompleteTextLetter::LevelCompleteTextLetter()
{
    mSprite = 0;
    mSpriteShadow = 0;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mFade = 0.0f;
    mExtraFade = 1.0f;
    
    mBaseX = 0.0f;
    mBaseY = 0.0f;
    
    mBounceAmount = 0.0f;
    mBounceTimer = 0;
    mBounceSin = 0.0f;
    mBounceSinSpeed = 0.0f;

    
    mCurrentOffsetX = 0.0f;
    mCurrentOffsetY = 0.0f;
    mCurrentOffsetRotation = 0.0f;

    mSkewFactor = 0.0f;
    mSkewDir = 1;
    
    mExtraRotation = 0.0f;
    mExtraScale = 1.0f;
    mExtraShadowScale = 1.0f;
    mExtraX = 0.0f;
    mExtraY = 0.0f;
    
    mArc = 0.0f;
}

LevelCompleteTextLetter::~LevelCompleteTextLetter()
{
    
}

void LevelCompleteTextLetter::Update()
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
    
    mFade += 0.025f;
    if(mFade >= 1.0f)
    {
        mFade = 1.0f;
    }
}

void LevelCompleteTextLetter::Draw(FSprite *pSprite, float pX, float pY, float pScale)
{
    
    
    float aX = (mX + mExtraX + mCurrentOffsetX) * pScale + pX;
    float aY = (mY + mExtraY + mCurrentOffsetY) * pScale + pY;
    
    float aScale = mExtraScale * pScale;
    
    float aScaleX = aScale;
    float aScaleY = aScale;
    float aRot = mExtraRotation + mCurrentOffsetRotation;
    
    if(mBounceAmount > 0.0f)
    {
        float aBounceSin = Sin(mBounceSin);
        aScaleY += aBounceSin * 0.033f;
        aScaleX -= aBounceSin * 0.025f;
        aY -= aBounceSin * mBounceAmount * 0.5f * mBounceScale;
        //aRot += aBounceSin * (-3.0f);
    }
    
    
    if(mArc != 0.0f)
    {
        float aArc = fabsf(mArc) * mSkewFactor;
        float aArcRot = aArc;
        
        aArc = FAnimation::EaseOutSine(aArc);
        aArcRot = FAnimation::EaseOutSine(aArcRot);
        aArcRot *= 30.0f;
        
        
        if(mSkewDir < 0)aArcRot = (-aArcRot);
        
        aRot += aArcRot;

        if(mSkewDir < 0)
        {
            
            aX -= (aArc * mBaseX * 0.28f);
            aY -= (aArc * (mBaseX * 0.23f));
            aX += ((aArc * 0.6f) * mBaseX * 0.3f);
        }
        else
        {
            aX -= (aArc * mBaseX * 0.28f);
            aY += (aArc * (mBaseX * 0.23f));
            aX += ((aArc * 0.6f) * mBaseX * 0.3f);
        }
    }
    
    if(pSprite == mSpriteShadow)
    {
        aScaleX *= mExtraShadowScale;
        aScaleY *= mExtraShadowScale;
    }
    
    Graphics::SetColor(mFade * mExtraFade);
    
    if(pSprite)
    {
        pSprite->DrawScaled(aX, aY, aScaleX, aScaleY, aRot);
    }
    
    Graphics::SetColor();
}

void LevelCompleteTextLetter::Draw(float pX, float pY, float pScale)
{
    Draw(mSprite, pX, pY, pScale);
}

void LevelCompleteTextLetter::DrawShadow(float pX, float pY, float pScale)
{
    Draw(mSpriteShadow, pX, pY, pScale);
}

void LevelCompleteTextLetter::DrawStroke(float pX, float pY, float pScale)
{
    Graphics::MonocolorEnable();
    Graphics::SetColor(0.2f, 0.2f, 0.12f, 0.4f);
    
    mExtraShadowScale = 1.18f;
    
    Draw(mSpriteShadow, pX - 8.0f * pScale, pY + 12.0f * pScale, pScale);
    
    mExtraShadowScale = 1.0f;
    
    Graphics::SetColor();
    Graphics::MonocolorDisable();
}

void LevelCompleteTextLetter::Bounce()
{
    mBounceAmount = 12.0f;
    
    mBounceTimer = 0;
    
    mBounceSin = 0.0f;
    
    mBounceSinSpeed = 9.0f + gRand.F();
}
