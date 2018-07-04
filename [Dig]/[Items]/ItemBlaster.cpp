//
//  ItemBlaster.cpp
//  Digplex
//
//  Created by Nick Raptis on 12/5/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "ItemBlaster.h"
#include "MainApp.h"
#include "CollectedEssence.h"
#include "Game.h"

ItemBlaster::ItemBlaster()
{
    mName = "Blaster!";
    
    
    SetSize(gApp->mGIItemBack);
    
    /*
    mCollectEssenceEnqueued = false;
    mCollectedEssenceCount = 0;
    mCollectedEssenceMax = 64;
    mCollectedEssenceOverflow = 0;
    mCollectedEssenceBounceAmount = 0.0f;
    */
    
    mCollectEssenceEnqueued = false;
    mCollectedEssenceCount = 32;
    mCollectedEssenceMax = 36;
    mCollectedEssenceOverflow = 0;
    mCollectedEssenceBounceAmount = 0.0f;
    
    
    
    
    mKnotCount = 0;
    
    int aKnotSize = 32;
    
    mKnotControlX = new float[aKnotSize * 8];
    mKnotControlY = &(mKnotControlX[aKnotSize]);
    
    mKnotSin = &(mKnotControlY[aKnotSize]);
    mKnotSinSpeed = &(mKnotSin[aKnotSize]);
    
    
    mKnotShiftDirX = &(mKnotSin[aKnotSize]);
    mKnotShiftDirY = &(mKnotShiftDirX[aKnotSize]);
    
    
    mKnotShiftMagnitude = &(mKnotShiftDirY[aKnotSize]);
    
    
    
    
    mCoolDownFadeIsHappening = false;
    mCoolDownFadeTimer.mTime = 32;
    
    mChargerGemSpinner1 = gRand.F(360.0f);
    mChargerGemSpinner2 = gRand.F(360.0f);
    
    mChargePercent = ((float)mCollectedEssenceCount) / ((float)mCollectedEssenceMax);
    mChargePercentTarget = mChargePercent;
    mChargePercentDraw = true;
    
    
    
    mTwinkleFrame[0] = gApp->mSequenceTwinkleSphere.GetMaxFrame() / 2.0f;
    mTwinkleFrame[1] = 0.0f;
    
    mGlowBallFrame[0] = gApp->mSequenceGlowBall.GetMaxFrame() / 2.0f;
    mGlowBallFrame[1] = 2.0f;
    
    mStartX = 0;
    mStartY = 0;
    
    mEndX = 0;
    mEndY = 0;
    
    mBeamWidth = 0.0f;
    
    mBeamWidth = 0.0f;
    
    mBeamWidthSin = gRand.GetFloat(360.0f);
    
    mContactNodeRot[0] = gRand.GetFloat(360.0f);
    mContactNodeRot[1] = gRand.GetFloat(360.0f);
    
    mContactNodeScale[0] = 0.0f;
    mContactNodeScale[1] = 0.0f;
    
    mContactNodeScaleSin[0] = gRand.GetFloat(360.0f);
    mContactNodeScaleSin[1] = gRand.GetFloat(360.0f);
    
    mQuadSnake.AddPoint(mStartX, mStartY);
    
    mLaserFrameMax = gApp->mSequenceLaserLoop.GetMaxFrame();
    mLaserFrame = gRand.GetFloat(mLaserFrameMax);
    mQuadSnake.SetSprite(gApp->mSequenceLaserLoop.Get());
    
    mQuadSnake.mWidthFactor = 0.5f;
    mQuadSnake.mNodeList.mEnabledColor = false;
    
    mFrameSpinner = 0.0f;
    
    
    mWobblerCollectRotationShake.SetTime(60, 10);
    mWobblerCollectShiftShake.SetTime(60, 10);
    
    mHitWobbleAmount = 0.0f;
    
    mWobblerAlwaysRotate.SetTime(70, 25);
    
    
    mWobblerCollectRotationShake.SetTime(60, 20);
    
    
    mWobblerCollectShiftShake.SetTime(70, 20);
    
    
    mHitWobbleAmount = 0.0f;
    
    mChargePercentDraw = true;
    
    mDelayWaitTimer.Halt();
    mDelayReadyTimer.Halt();
}

ItemBlaster::~ItemBlaster()
{
    
}

void ItemBlaster::Update()
{
    ActionProcItem::Update();
    
    mChargerGemSpinner1 -= 6.0f;
    if(mChargerGemSpinner1 <= 0.0f)mChargerGemSpinner1 += 360.0f;
    
    mChargerGemSpinner2 += 6.0f;
    if(mChargerGemSpinner2 >= 360.0f)mChargerGemSpinner2 += 360.0f;
    
    if(mCollectedEssenceBounceAmount > 0.0f)
    {
        mCollectedEssenceBounceAmount *= 0.99f;
        mCollectedEssenceBounceAmount -= 0.015f;
        
        if(mCollectedEssenceBounceAmount <= 0.0f)mCollectedEssenceBounceAmount = 0.0f;
        
        mShakeX = gRand.F(-mCollectedEssenceBounceAmount, mCollectedEssenceBounceAmount);
        mShakeY = gRand.F(-mCollectedEssenceBounceAmount, mCollectedEssenceBounceAmount);
    }
    else
    {
        mShakeX = 0.0f;
        mShakeY = 0.0f;
    }
    
    if(mCoolDownFadeIsHappening)
    {
        
        mChargePercent = (1.0f - mCoolDownFadeTimer.P());
        
        if(mCoolDownFadeTimer.T())
        {
            mCoolDownFadeTimer.Reset();
            mCoolDownFadeIsHappening = false;
            
            mChargePercent = 0.0f;
            mChargePercentTarget = 0.0f;
            
            int aCollectedEssencesCount = gGame->CollectedEssencesCount(this);
            
            if(aCollectedEssencesCount <= 0)
            {
                if(mCollectedEssenceCount >= mCollectedEssenceMax)mChargePercentTarget = 1.0f;
                else mChargePercentTarget = ((float)mCollectedEssenceCount) / ((float)mCollectedEssenceMax);
            }
        }
    }
    
    if(mCoolDownFadeIsHappening == false)
    {
        if(mCoolingDown)
        {
            mChargePercent = 0.0f;
        }
        else
        {
            if(mChargePercent < mChargePercentTarget)
            {
                mChargePercent += (mChargePercentTarget - mChargePercent) * 0.02f + 0.002f;
                //mChargePercent += (mChargePercentTarget - mChargePercent) * 0.04f + 0.033f;
                
                if(mChargePercent >= mChargePercentTarget)mChargePercent = mChargePercentTarget;
            }
        }
    }
    
    
    mHitWobbleAmount *= 0.99f;
    mHitWobbleAmount -= 0.02f;
    if(mHitWobbleAmount < 0)mHitWobbleAmount = 0.0f;
    
    mWobblerCollectRotationShake.Update();
    mWobblerCollectShiftShake.Update();
    mWobblerAlwaysRotate.Update();
    
    mDelayWait = false;
    mDelayReady = false;
    
    for(int i=0;i<2;i++)
    {
        mTwinkleFrame[i] = gApp->mSequenceTwinkleSphere.LoopFrame(mTwinkleFrame[i], 0.725f);
        mGlowBallFrame[i] += gApp->mSequenceGlowBall.LoopFrame(mGlowBallFrame[i], 0.8f);
    }
    
    mLaserFrame += 0.70f;
    if(mLaserFrame >= mLaserFrameMax)mLaserFrame -= mLaserFrameMax;
    mQuadSnake.SetSprite(gApp->mSequenceLaserLoop.Get(mLaserFrame));
    
    float aX = 0.0f;
    float aY = 0.0f;
    
    for(int i=0;i<mKnotCount;i++)
    {
        mKnotSin[i] = LoopAngle(mKnotSin[i], mKnotSinSpeed[i]);
        
        
        aX = mKnotControlX[i];
        aY = mKnotControlY[i];
        
        float aSin = Sin(mKnotSin[i]);
        
        float aDirX = mKnotShiftDirX[i];
        float aDirY = mKnotShiftDirY[i];
        
        float aMag = mKnotShiftMagnitude[i];
        
        aX += aDirX * aSin * aMag;
        aY += aDirY * aSin * aMag;
    }
    
    mQuadSnake.Reset();
    
    for(float aPos=0.0f;aPos<mSpline.Max();aPos+=0.1f)
    {
        mSpline.Get(aPos, aX, aY);
        mQuadSnake.AddPoint(aX, aY);
    }
    
    mContactNodeRot[0] += 3.0f;
    if(mContactNodeRot[0] >= 360.0f)mContactNodeRot[0] -= 360.0f;
    
    mContactNodeRot[1] += 4.0f;
    if(mContactNodeRot[1] >= 360.0f)mContactNodeRot[1] -= 360.0f;
    
    mFrameSpinner += 0.8f;
    if(mFrameSpinner >= gApp->mSequenceEffectSpiralLoop.GetMaxFrame())mFrameSpinner -= gApp->mSequenceEffectSpiralLoop.GetMaxFrame();
}


void ItemBlaster::Draw()
{
    ActionProcItem::Draw();
    
    DrawCircle();
    
    float aX = mWidth2;
    float aY = mHeight2;
    
    aX += mShakeX;
    aY += mShakeY * 0.5f;
    
    float aRotationShift = (mWobblerCollectRotationShake.V() * mHitWobbleAmount * 3.5f);
    float aRotationShiftExtra = mWobblerAlwaysRotate.V() * 2.0f;
    
    float aEggScale = 0.76f;
    float aEggRotation = aRotationShift + aRotationShiftExtra;
    
    
    gApp->mGIRockHammerBack.Draw(aX, aY, aEggScale, aEggRotation);
    
    //if(mCollectedEssenceCount >= mCollectedEssenceMax)gApp->mGIChaosEggBack[1].Draw(aX, aY, aEggScale, aEggRotation);
    //else gApp->mGIChaosEggBack[2].Draw(aX, aY, aEggScale, aEggRotation);
    
    
    Graphics::BlendSetAlpha();
    Graphics::SetColor();
    
    //gApp->mGIChaosEggDiamondSlot.Draw(aX, aY, aEggScale, aEggRotation);
    //gApp->mGIChaosEggDiamond.Draw(aX, aY, aEggScale, aEggRotation);
    
    DrawEffects();
}

void ItemBlaster::DrawEffects()
{
    ActionProcItem::DrawEffects();
}

void ItemBlaster::DrawFocus(float pX, float pY)
{
    float aPercent = mTriggerStepper.V();
    
    Graphics::BlendSetAdditive();
    Graphics::SetColor(aPercent * 0.85f);
    
    mQuadSnake.Draw();
    
    Graphics::BlendSetAdditive();
    Graphics::SetColor(1.0f * aPercent);
    gApp->mEffectTwinkleAdditivePinwheel[1].Draw(mStartX, mStartY, 1.0f, mContactNodeRot[1]);
    gApp->mEffectTwinkleAdditivePinwheel[1].Draw(mEndX, mEndY, 1.0f, mContactNodeRot[1]);
    
    Graphics::SetColor();
    
    gApp->mSequenceGlowBall.Draw(mGlowBallFrame[0], mStartX, mStartY, aPercent + 0.05f, -mContactNodeRot[0]);
    gApp->mSequenceGlowBall.Draw(mGlowBallFrame[1], mEndX, mEndY, aPercent + 0.05f, -mContactNodeRot[1]);
    
    Graphics::SetColor(0.85f * aPercent);
    Graphics::BlendSetGhost1();
    
    gApp->mSequenceTwinkleSphere.Draw(mTwinkleFrame[0], mStartX, mStartY, 1.0f, 0.0f);
    gApp->mSequenceTwinkleSphere.Draw(mGlowBallFrame[1], mEndX, mEndY, 1.0f, 0.0f);
    
    
    Graphics::SetColor();
    Graphics::BlendSetAlpha();
}

void ItemBlaster::StartTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus)
{
    pFocus->mMatch[1] = false;
    pFocus->mMatch[2] = false;
    
    gApp->mSoundBlasterChargeUp.Play();
    
    ActionProcItem::StartTrigger(pFromX, pFromY, pFocus);
    
    mStartX = pFromX;
    mStartY = pFromY;
    
    mEndX = pFocus->mMatchCenterX[0];
    mEndY = pFocus->mMatchCenterY[0];
    
    float aSpanX = mEndX - mStartX;
    float aSpanY = mEndY - mStartY;
    
    mDirX = aSpanX;
    mDirY = aSpanY;
    
    float aDist = mDirX * mDirX + mDirY * mDirY;
    
    if(aDist > 0.1f)
    {
        aDist = (float)sqrtf(aDist);
        
        mDirX /= aDist;
        mDirY /= aDist;
    }
    else
    {
        mDirX = 0.0f;
        mDirY = 1.0f;
    }
    
    if(aDist < 5.0f)aDist = 5.0f;
    
    float aTargetDistPerHop = 110.0f;
    
    mKnotCount = (int)((aDist / aTargetDistPerHop) + 0.5f);
    
    if(mKnotCount < 4)mKnotCount = 4;
    if(mKnotCount > 9)mKnotCount = 9;
    
    mNormX = ( mDirY);
    mNormY = (-mDirX);
    
    mSpline.Clear();
    
    for(int i=0;i<mKnotCount;i++)
    {
        float aPercent = ((float)i) / ((float)(mKnotCount - 1));
        float aPercentAlt = (1.0f - aPercent);
        
        float aPercentFactor = aPercent;
        if(aPercentAlt < aPercentFactor)aPercentFactor = aPercentAlt;
        
        mKnotControlX[i] = mStartX + aSpanX * aPercent;
        mKnotControlY[i] = mStartY + aSpanY * aPercent;
        
        mKnotSin[i] = gRand.GetFloat(((float)i) * 360.0f);
        mKnotSinSpeed[i] = 30.0f + gRand.GetFloat(3.25f);
        
        mKnotShiftMagnitude[i] = (30.0f + gRand.GetFloat(10.0f)) * aPercentFactor;
        
        mKnotShiftDirX[i] = mNormX;
        mKnotShiftDirY[i] = mNormY;
        
        mSpline.Add(mKnotControlX[i], mKnotControlY[i]);
    }
}

void ItemBlaster::UpdateTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus)
{
    int aTriggerStep = mTriggerStepper.mStep;
    
    ActionProcItem::UpdateTrigger(pFromX, pFromY, pFocus);
    
    if(aTriggerStep != mTriggerStepper.mStep)
    {
        if(mTriggerStepper.mStep == 1)
        {
            gApp->mSoundBlasterTrigger.Play();
        }
        if(mTriggerStepper.mStep == 2)
        {
            gApp->mSoundBlasterEnd.Play();
        }
    }
    
    mStartX = pFromX;
    mStartY = pFromY;
    
    mEndX = pFocus->mMatchCenterX[0];
    mEndY = pFocus->mMatchCenterY[0];
    
    float aSpanX = mEndX - mStartX;
    float aSpanY = mEndY - mStartY;
    
    mDirX = aSpanX;
    mDirY = aSpanY;
    
    float aDist = mDirX * mDirX + mDirY * mDirY;
    
    if(aDist > 0.1f)
    {
        aDist = (float)sqrtf(aDist);
        
        mDirX /= aDist;
        mDirY /= aDist;
    }
    else
    {
        mDirX = 0.0f;
        mDirY = 1.0f;
    }
    
    mNormX = ( mDirY);
    mNormY = (-mDirX);
    
    for(int i=0;i<mKnotCount;i++)
    {
        float aPercent = ((float)i) / ((float)(mKnotCount - 1));
        float aPercentAlt = (1.0f - aPercent);
        
        float aPercentFactor = aPercent;
        if(aPercentAlt < aPercentFactor)aPercentFactor = aPercentAlt;
        
        mKnotControlX[i] = mStartX + aSpanX * aPercent;
        mKnotControlY[i] = mStartY + aSpanY * aPercent;
        
        mKnotShiftDirX[i] = mNormX;
        mKnotShiftDirY[i] = mNormY;
    }
}

void ItemBlaster::EndTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus)
{
    ActionProcItem::EndTrigger(pFromX, pFromY, pFocus);
    
    mCollectedEssenceCount = mCollectedEssenceOverflow;
    mCollectedEssenceOverflow = 0;
    
    mChargePercent = 0.0f;
    
    if(mCollectedEssenceCount >= mCollectedEssenceMax)mChargePercentTarget = 1.0f;
    else mChargePercentTarget = ((float)mCollectedEssenceCount) / ((float)mCollectedEssenceMax);
    
    mCoolDownFadeIsHappening = true;
    mCoolDownFadeTimer.Reset();
}



void ItemBlaster::WillCollectItem(void *pItem)
{
    CollectedEssence *aEssence = (CollectedEssence *)pItem;
    
    if(aEssence)
    {
        int aValue = 3 + gRand.Get(4);
        
        if(mCollectedEssenceCount < mCollectedEssenceMax)
        {
            mCollectedEssenceCount += aValue;
            if(mCollectedEssenceCount >= mCollectedEssenceMax)
            {
                int aOverflow = (mCollectedEssenceCount - mCollectedEssenceMax);
                mCollectedEssenceCount = mCollectedEssenceMax;
                mCollectedEssenceOverflow = aOverflow;
            }
        }
        else
        {
            mCollectedEssenceOverflow += aValue;
        }
    }
    
    //mCollectedEssencePercent = ((float)mCollectedEssenceCount) / ((float)mCollectedEssenceMax);
    //mCollectedEssencePercentTarget = mCollectedEssencePercent;
    mCollectedEssenceOverflow = 0;
}

void ItemBlaster::CollectItem(void *pItem)
{
    CollectedEssence *aEssence = (CollectedEssence *)pItem;
    
    if(aEssence)
    {
        if(mCollectedEssenceCount >= mCollectedEssenceMax)mChargePercentTarget = 1.0f;
        else mChargePercentTarget = ((float)mCollectedEssenceCount) / ((float)mCollectedEssenceMax);
    }
    
    mCollectedEssenceBounceAmount = 3.0f;
}

bool ItemBlaster::IsReady()
{
    bool aReturn = false;
    if(WillBeReady())
    {
        if(mChargePercent >= 0.9999f)aReturn = true;
    }
    return aReturn;
}

bool ItemBlaster::WillBeReady()
{
    bool aReturn = false;
    if((mTriggering == false) && (mCoolingDown == false) && (mCollectedEssenceCount >= mCollectedEssenceMax))aReturn = true;
    return aReturn;
}



