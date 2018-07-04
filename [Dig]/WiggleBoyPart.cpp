//
//  WiggleBoyPart.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "WiggleBoyPart.h"
#include "core_includes.h"


WiggleBoyPart::WiggleBoyPart(FSprite *pSprite, WiggleBoyPart *pParent, float pParentOffsetX, float pParentOffsetY, bool pFront) : WiggleBoyPart(pSprite)
{
    if(pParent)
    {
        SetParentOffset(pParentOffsetX, pParentOffsetY);
        pParent->AddPart(this, pFront);
    }
}

WiggleBoyPart::WiggleBoyPart(FSprite *pSprite, float pOffsetX, float pOffsetY) : WiggleBoyPart(pSprite)
{
    SetOffset(pOffsetX, pOffsetY);
}

WiggleBoyPart::WiggleBoyPart(FSprite *pSprite) : WiggleBoyPart()
{
    SetSprite(pSprite);
}

WiggleBoyPart::WiggleBoyPart()
{
    mParent = 0;
    mSprite = 0;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mWidth = 0.0f;
    mHeight = 0.0f;
    
    mOffsetX = 0.0f;
    mOffsetY = 0.0f;
    
    mRotation = 0.0f;
    mScale = 1.0f;
    
    mPivotOffsetX = 0.0f;
    mPivotOffsetY = 0.0f;
    
    mParentOffsetX = 0.0f;
    mParentOffsetY = 0.0f;
    
    for(int i=0;i<4;i++)
    {
        mCornerOffsetX[i] = 0.0f;
        mCornerOffsetY[i] = 0.0f;
    }
    
    mOffsetRotation = 0.0f;
    mOffsetScale = 1.0f;
    
    mDrawRotation = 0.0f;
    mDrawScale = 1.0f;
}

WiggleBoyPart::~WiggleBoyPart()
{
    FreeList(WiggleBoyAnim, mAnimationList);
    
}

void WiggleBoyPart::Update(float pX, float pY, float pScale, float pRotation)
{
    
    
    
    
    
    
    float aCenterX = pX;
    float aCenterY = pY;
    
    float aOffsetX = mOffsetX;
    float aOffsetY = mOffsetY;
    
    
    //mParentOffsetX
    
    float aParentOffsetX = 0.0f;
    float aParentOffsetY = 0.0f;
    
    
    if(mParent)
    {
        aParentOffsetX = mParentOffsetX;
        aParentOffsetY = mParentOffsetY;
        
        if(pRotation != 0.0f)
        {
            if((aParentOffsetX != 0.0f) || (aParentOffsetY != 0.0f))
            {
                
                float aRot = pRotation * 0.01745329251994329576923690768488;
                float aDist = 0.0f;
                float aPivot = 0.0f;
                
                aDist = aParentOffsetX * aParentOffsetX + aParentOffsetY * aParentOffsetY;
                if(aDist > SQRT_EPSILON)
                {
                    aDist = sqrtf(aDist);
                    aParentOffsetX /= aDist;
                    aParentOffsetY /= aDist;
                }
                
                aDist *= pScale;
                
                //aPivot = (aRot - atan2f(-aParentOffsetX, -aParentOffsetY));
                aPivot = (aRot - atan2f(-aParentOffsetX, -aParentOffsetY));
                
                aParentOffsetX = (sin(aPivot)) * aDist;
                aParentOffsetY = (-cos(aPivot)) * aDist;
            }
        }
        else if(pScale != 1.0f)
        {
            aParentOffsetX *= pScale;
            aParentOffsetY *= pScale;
        }
        
        aCenterX = mParent->mQuadDraw.CenterX() + aParentOffsetX;
        aCenterY = mParent->mQuadDraw.CenterY() + aParentOffsetY;
    }
    
    
    EnumList(WiggleBoyAnim, aAnim, mAnimationList)
    {
        aAnim->Update(this);
    }
    
    
    mDrawRotation = pRotation + mRotation + mOffsetRotation;
    mDrawScale = pScale * mScale * mOffsetScale;
    
    
    
    
    if(mDrawRotation != 0.0f)
    {
        if((aOffsetX != 0.0f) || (aOffsetY != 0.0f))
        {
            float aRot = mDrawRotation * 0.01745329251994329576923690768488;
            float aDist = 0.0f;
            float aPivot = 0.0f;
            aDist = aOffsetX * aOffsetX + aOffsetY * aOffsetY;
            if(aDist > SQRT_EPSILON)
            {
                aDist = sqrtf(aDist);
                aOffsetX /= aDist;
                aOffsetY /= aDist;
            }
            aDist *= mDrawScale;
            aPivot = (aRot - atan2f(-aOffsetX, -aOffsetY));
            aOffsetX = (sin(aPivot)) * aDist;
            aOffsetY = (-cos(aPivot)) * aDist;
        }
    }
    else if(mDrawScale != 1.0f)
    {
        aOffsetX *= mDrawScale;
        aOffsetY *= mDrawScale;
    }

    
    
    mQuadDraw.SetRect(-(mWidth / 2.0f), -(mHeight / 2.0f), mWidth, mHeight);
    
    
    //mQuadDraw.Translate(-mPivotOffsetX, -mPivotOffsetY);
    
    
    
    aCenterX += aOffsetX;
    aCenterY += aOffsetY;
    
    mQuadDraw.Rotate(mDrawRotation, mPivotOffsetX, mPivotOffsetY);
    mQuadDraw.Scale(mDrawScale);
    
    mQuadDraw.Translate(aCenterX, aCenterY);
    mQuadDraw.Add(mCornerOffsetX[0], mCornerOffsetY[0], mCornerOffsetX[1], mCornerOffsetY[1], mCornerOffsetX[2], mCornerOffsetY[2], mCornerOffsetX[3], mCornerOffsetY[3]);
    
    EnumList(WiggleBoyPart, aPart, mPartListBack)aPart->Update(aCenterX, aCenterY, mDrawScale, mDrawRotation);
    EnumList(WiggleBoyPart, aPart, mPartListFront)aPart->Update(aCenterX, aCenterY, mDrawScale, mDrawRotation);
}

void WiggleBoyPart::Draw()
{
    if(mSprite)
    {
        mQuadDraw.Draw(mSprite);
    }
}

void WiggleBoyPart::SetSprite(FSprite *pSprite)
{
    mSprite = pSprite;
    
    if(mSprite)
    {
        if((mWidth <= 1.0f) || (mHeight <= 1.0f))
        {
            mWidth = mSprite->mWidth;
            mHeight = mSprite->mHeight;
        }
        
        //
    }
}


void WiggleBoyPart::SetParentOffset(float pX, float pY)
{
    mParentOffsetX = pX;
    mParentOffsetY = pY;
}

void WiggleBoyPart::SetPivotOffset(float pX, float pY)
{
    mPivotOffsetX = pX;
    mPivotOffsetY = pY;
}

void WiggleBoyPart::SetOffset(float pX, float pY)
{
    mOffsetX = pX;
    mOffsetY = pY;
    
}

//


void WiggleBoyPart::AddPart(WiggleBoyPart *pPart, bool pFront)
{
    if(pFront)mPartListFront.Add(pPart);
    else mPartListBack.Add(pPart);
    
    pPart->mParent = this;
}

void WiggleBoyPart::AddAnim(WiggleBoyAnim *pAnim)
{
    mAnimationList.Add(pAnim);
}

WiggleBoyAnim::WiggleBoyAnim()
{
    mBlockSimul = false;
    
    mTimeSleep = 0;
    mTimeSleepRandom = 0;
    
    mTimeCooldown = 0;
    mTimeCooldownRandom = 0;
    
    mTimeDuration = 0;
    mTimeDurationRandom = 0;
    
    mProcRandom = 0;
    
    mActive = false;
    
    
    mCycleTimerSleep = 0;
    mCycleTimerCoolDown = 0;
    mCycleTimerDuration = 0;
    
    mCycleTimeSleep = 0;
    mCycleTimeCoolDown = 0;
    mCycleTimeDuration = 0;
}

WiggleBoyAnim::~WiggleBoyAnim()
{
    
}

void WiggleBoyAnim::Update(WiggleBoyPart *pPart)
{
    if(mActive == true)
    {
        if((mTimeDuration > 0) || (mTimeDurationRandom > 0))
        {
            mCycleTimerDuration--;
            if(mCycleTimerDuration <= 0)
            {
                mCycleTimerDuration = 0;
                
                
                WillFinish();
                Finish(pPart);
            }
        }
    }
    else
    {
        if(IsReady(pPart))
        {
            WillActivate();
            Activate(pPart);
        }
        else
        {
            
            if(mCycleTimerCoolDown > 0)mCycleTimerCoolDown--;
            if(mCycleTimerSleep > 0)mCycleTimerSleep--;
            
            
            
        }
    }
    
}

void WiggleBoyAnim::Activate(WiggleBoyPart *pPart)
{
    
}

void WiggleBoyAnim::Finish(WiggleBoyPart *pPart)
{
    if((mTimeCooldown > 0) || (mTimeCooldownRandom > 0))
    {
        mCycleTimeCoolDown = mTimeCooldown;
        if(mTimeCooldownRandom > 0)mCycleTimeCoolDown += gRand.Get(mTimeCooldownRandom);
        mCycleTimerCoolDown = mCycleTimeCoolDown;
    }
    
    if((mTimeSleep > 0) || (mTimeSleepRandom > 0))
    {
        mCycleTimeSleep = mTimeSleep;
        if(mTimeSleepRandom > 0)mCycleTimeSleep += gRand.Get(mTimeSleepRandom);
        mCycleTimerSleep = mCycleTimeSleep;
    }
    
    
}

void WiggleBoyAnim::WillActivate()
{
    if((mTimeDuration > 0) || (mTimeDurationRandom > 0))
    {
        mCycleTimeDuration = mTimeDuration;
        if(mTimeDurationRandom > 0)mCycleTimeDuration += gRand.Get(mTimeDurationRandom);
        mCycleTimerDuration = mCycleTimeDuration;
    }
    
    mActive = true;
}

void WiggleBoyAnim::WillFinish()
{
    mActive = false;
    
}

bool WiggleBoyAnim::IsReady(WiggleBoyPart *pPart)
{
    bool aReturn = true;
    
    if(pPart)
    {
        if(mBlockSimul)
        {
            EnumList(WiggleBoyAnim, aAnim, pPart->mAnimationList)
            {
                if((aAnim->mActive == true) && (aAnim != this))
                {
                    aReturn = false;
                }
            }
            
            
            
        
        }
        
        if((aReturn == true) && (mActive == false))
        {
            if((mCycleTimerCoolDown > 0) && (mCycleTimeCoolDown > 0))
            {
                aReturn = false;
            }
            
            if((mCycleTimerSleep > 0) && (mCycleTimeSleep > 0))
            {
                aReturn = false;
            }
        }
        
        if((aReturn == true) && (mProcRandom > 0))
        {
            if(gRand.Get(mProcRandom + 1) != mProcRandom)
            {
                aReturn = false;
            }
        }
    }
    
    
    return aReturn;
}


WiggleBoyAnimTest::WiggleBoyAnimTest()
{
    mTestMode = -1;
    
    mTestActionType = -1;
    
    mTestValueStart1 = 0;
    mTestValueEnd1 = 0;
    
    mTestValueStart2 = 0;
    mTestValueEnd2 = 0;
    
    mTestCornerIndex = 0;
    
    mTimeCooldown = 10;
    mTimeCooldownRandom = 60;
    
    mTimeDuration = 24;
    mTimeDurationRandom = 60;
    
    mTimeSleep = 8;
    mTimeSleepRandom = 8;
    
    
    float aRot = gRand.Rot();
    mTestDirX = Sin(aRot);
    mTestDirY = -Cos(aRot);
    
    
    
    
    
}

WiggleBoyAnimTest::~WiggleBoyAnimTest()
{
    
}

void WiggleBoyAnimTest::Update(WiggleBoyPart *pPart)
{
    WiggleBoyAnim::Update(pPart);
    
    
    if(mActive)
    {
        
        float aPercent = 1.0f;
        
        if(mCycleTimeDuration > 0)
        {
            aPercent = ((float)mCycleTimerDuration) / ((float)mCycleTimeDuration);
            
        }
        
        aPercent = (1.0f - aPercent);
        
        float aValue1 = mTestValueStart1 + (mTestValueEnd1 - mTestValueStart1) * aPercent;
        float aValue2 = mTestValueStart2 + (mTestValueEnd2 - mTestValueStart2) * aPercent;
        
        if(mTestMode == 0)
        {
            pPart->mRotation = aValue1;
        }
        
        if(mTestMode == 1)
        {
            pPart->mScale = aValue1;
            
            //Log("Animator Forcing SCALE To [%f]\n", pPart->mScale);
            
        }

        
        if(mTestMode == 2)
        {
            
            pPart->mCornerOffsetX[mTestCornerIndex] = aValue1;
            pPart->mCornerOffsetY[mTestCornerIndex] = aValue2;
            
            
            //Log("Animator Forcing SCALE To [%f]\n", pPart->mScale);
            
        }

    }
    
    
}


void WiggleBoyAnimTest::Activate(WiggleBoyPart *pPart)
{
    mTestMode = gRand.Get(3);
    
    
    float aRot = gRand.Rot();
    mTestDirX = Sin(aRot);
    mTestDirY = -Cos(aRot);
    
    mTestCornerIndex = gRand.Get(4);
    
    //Rotation
    if(mTestMode == 0)
    {
        mTestValueStart1 = pPart->mRotation;
        mTestValueEnd1 = pPart->mRotation + gRand.GetFloat(8.0f);
        
        if(mTestValueEnd1 >= 20.0f)mTestValueEnd1 -= 14.0f;
        if(mTestValueEnd1 <= -20.0f)mTestValueEnd1 += 9.0f;
    }
    
    if(mTestMode == 1)
    {
        mTestValueStart1 = pPart->mScale;
        mTestValueEnd1 = pPart->mScale + gRand.GetFloat(-0.03f, 0.03f);
        
        if(mTestValueEnd1 >= 1.75f)mTestValueEnd1 -= 0.6f;
        if(mTestValueEnd1 <= 0.36f)mTestValueEnd1 += 0.42f;
    }
    
    if(mTestMode == 2)
    {
        mTestValueStart1 = pPart->mCornerOffsetX[mTestCornerIndex];
        mTestValueStart2 = pPart->mCornerOffsetY[mTestCornerIndex];
        
        mTestValueEnd1 = gRand.GetFloat(-4.0f, 4.0f);
        mTestValueEnd2 = gRand.GetFloat(-4.0f, 4.0f);
        
    }
}


