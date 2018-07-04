//
//  ActionProcItem.cpp
//  Digplex
//
//  Created by Nick Raptis on 11/30/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "ActionProcItem.h"
#include "MainApp.h"
#include "Game.h"
#include "Board.h"

ActionProcItem::ActionProcItem()
{
    mItemID = 0;
    mCharging = false;
    
    mShakeX = 0.0f;
    mShakeY = 0.0f;
    
    mChargePercent = 0.0f;
    mChargePercentTarget = 0.0f;
    mChargePercentDraw = false;
    mChargePercentDrawBlinkSin = 0.0f;
    
    
    mIsClickable = false;
    mIsClicked = false;
    
    
    mDragable = false;
    
    
    mTriggering = false;
    //mTriggerTime = 160;
    
    //mTriggeringTimerTick = 0;
    //mTriggerStepper.SetTimes(36, 70, 40);
    //mTriggerStepper.SetTimes(32, 46, 22);
    mTriggerStepper.SetTimes(26, 22, 10);
    
    
    //mTriggerStepper.SetTimes(60, 70, 35);
    
    mTriggerStepper.SetValues(0.0f, 1.0f, 1.0f, 0.0f);
    mTriggerFocus = 0;
    //mTriggerChargeTime = 36;
    
    mCoolingDown = false;
    mCoolDownTimer.mTime = 36;
    
    
    mDelayReady = false;
    mDelayReadyTimer.SetTime(10, 0);
    
    
    mDelayWait = true;
    mDelayWaitTimer.SetTime(40, 0);
    mDelayWaitTimer.R();
    
    
    mSelectionHaloRotation1 = gRand.GetFloat(360.0f);
    mSelectionHaloRotation2 = gRand.GetFloat(360.0f);
    
    mSelectionHaloWobbler.SetInterval(0.95f, 1.05f);
    mSelectionHaloWobbler.SetTime(160, 20);
    
    
    
    mTimerSpawnParticle1.SetTime(8);
    mTimerSpawnParticle1.SetSleep(3);
    
    mTimerSpawnParticle2.SetTime(16);
    mTimerSpawnParticle2.SetSleep(0);
    
    mTimerSpawnParticle3.SetTime(4);
    mTimerSpawnParticle3.SetSleep(12);
    
    mTimerSpawnParticle4.SetTime(7);
    mTimerSpawnParticle4.SetSleep(19);
    
}

ActionProcItem::~ActionProcItem()
{
    
}

void ActionProcItem::Update()
{
    mAnimations.Update();
    mAnimationsAdditive.Update();
    mAnimationsRelative.Update();
    
    if(mTimerSpawnParticle1.T())SpawnParticle(0);
    if(mTimerSpawnParticle2.T())SpawnParticle(1);
    if(mTimerSpawnParticle3.T())SpawnParticle(2);
    if(mTimerSpawnParticle4.T())SpawnParticle(3);

    mSelectionHaloRotation1 += 2.5f;
    if(mSelectionHaloRotation1 >= 360.0f)mSelectionHaloRotation1 -= 360.0f;
    
    mSelectionHaloRotation2 -= 2.0f;
    if(mSelectionHaloRotation2 <= 0.0f)mSelectionHaloRotation2 += 360.0f;
    
    mSelectionHaloWobbler.Update();
    
    
    if((mChargePercent != mChargePercentTarget) && (mChargePercentDraw == true))
    {
        mChargePercentDrawBlinkSin += 9.0f;
        if(mChargePercentDrawBlinkSin >= 360.0f)mChargePercentDrawBlinkSin -= 360.0f;
    }
    
    
    if(mCoolingDown)
    {
        
        //mCoolDownTimerTick--;
        if(mCoolDownTimer.T())
        {
            mCoolDownTimer.Reset();
            //mCoolDownTimerTick = 0;
            mCoolingDown = false;
        }
    }
    else if(mDelayReady)
    {
        
        /*
        if(mDelayReadyTimer.T())
        {
            mDelayReady = false;
            
            mDelayWaitTimer.Reset();
        }
        */
        
    }
    else if(mDelayWait)
    {
        /*
        if(mDelayWaitTimer.T())
        {
            Log("ActionProcItem:: DELAY FINISHED, READY TO TRIGGER");
            mDelayWait = false;
            
            
            if(gGame)
            {
                gGame->ActionProcItemWillBeReady();
            }
            
            mDelayReady = true;
            mDelayReadyTimer.Reset();
        }
        */
    }
    
    //mDelayWait = true;
    //mDelayWaitTimer.SetTime(500, 100);
    //mDelayWaitTimer.R();
    
    
}

void ActionProcItem::Draw()
{
    DrawEffects();
    //Graphics::SetColor(0.8f, 0.2f, 0.2f, 0.8f);
    //Graphics::OutlineRect(0.0f, 0.0f, mWidth, mHeight, 4.0f);
    Graphics::SetColor();
}

void ActionProcItem::DrawEffects()
{
    
    
    mAnimations.Draw();
    
    Graphics::BlendSetAdditive();
    
    mAnimationsAdditive.Draw();
    
    Graphics::BlendSetAlpha();
    
    Graphics::BlendSetAdditive();
    EnumList(FParticle, aParticle, mAnimationsRelative)aParticle->DrawOffset(aParticle->mSprite, mX, mY);
    
    Graphics::BlendSetAlpha();
    Graphics::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    
}

void ActionProcItem::DrawCircle()
{
    float aX = mWidth2;
    float aY = mHeight2;
    float aScale = 1.0f;
    float aRot = 0.0f;
    
    aX += mShakeX;
    aY += mShakeY;
    
    gApp->mGIItemBack.Draw(aX, aY, aScale, aRot);
    //gApp->mGIItemBackInset.Draw(aX, aY, aScale, aRot);
    
    
    gApp->mGIItemBackInactive.DrawAngleRange(aX, aY, 1.0f, 0.0f, mChargePercent * 360.0f, 360.0f);
    if(mChargePercentTarget != mChargePercent)
    {
        Graphics::MonocolorEnable();
        Graphics::SetColor(1.0f, 1.0f, 1.0f, Sin(mChargePercentDrawBlinkSin) * 0.2f + 0.8f);
        
        gApp->mGIItemBackInactive.DrawAngleRange(aX, aY, 1.0f, 0.0f, 0.0f, mChargePercentTarget * 360.0f);
        
        Graphics::SetColor();
        Graphics::MonocolorDisable();
    }
    
    //Graphics::SetColor();
    //gApp->mGIItemBackInsetActive.DrawAngleRange(aX, aY, 1.0f, 0.0f, 0.0f, mChargePercent * 360.0f);
    
    Graphics::BlendSetAdditive();
    
    Graphics::SetColor(0.6f);
    gApp->mEffectLightSpinner[1].Draw(aX, aY, mSelectionHaloWobbler.V(), mSelectionHaloRotation1);
    gApp->mEffectLightSpinner[1].Draw(aX, aY, mSelectionHaloWobbler.V(), mSelectionHaloRotation2);
    
    Graphics::SetColor();
    
    
    
    Graphics::BlendSetAlpha();
    Graphics::SetColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void ActionProcItem::DrawFocus(float pX, float pY)
{
    Graphics::SetColor(0.25f);
    
    gApp->mMILevelUpDisplayStar.Draw(pX, pY, 0.25f, 50.0f);
    
    Graphics::SetColor();
    if((mTriggering != 0) && (mTriggerFocus != 0))
    {
        Graphics::SetColor(0.25f, 0.95f, 0.45f, 0.65f);
        
        for(int i=0;i<3;i++)
        {
            if(mTriggerFocus->mMatch[i])
            {
                Graphics::DrawLine(pX, pY, mTriggerFocus->mMatchCenterX[i], mTriggerFocus->mMatchCenterY[i], mTriggerBeamWidth[i]);
            }
        }
        
        Graphics::SetColor(0.85f, 0.35f, 0.65f, 0.65f);
        
        for(int i=0;i<3;i++)
        {
            if(mTriggerFocus->mObstacle[i])
            {
                Graphics::DrawLine(pX, pY, mTriggerFocus->mObstacleCenterX[i], mTriggerFocus->mObstacleCenterY[i], mTriggerObstacleBeamWidth[i]);
            }
        }
    }
    
    Graphics::SetColor();
}

void ActionProcItem::DrawProgressBars()
{
    if(mDelayWait)
    {
        Graphics::SetColor(0.4f, 0.375f, 0.415f);
        Graphics::DrawRect(10.0f, 10.0f, mWidth - 20.0f, 24.0f);
        
        Graphics::SetColor(1.0f, 0.15f, 0.15f);
        Graphics::DrawRect(14.0f, 12.0f, (mWidth - 24.0f) * mDelayWaitTimer.P(), 20.0f);
        
    }
    else if(mDelayReady)
    {
        Graphics::SetColor(0.4f, 0.375f, 0.415f);
        Graphics::DrawRect(10.0f, 10.0f, 30.0f, 150.0f);
        
        Graphics::SetColor(0.0f, 0.65f, 0.15f);
        Graphics::DrawRect(14.0f, 12.0f, 26.0f, 142.0f * mDelayReadyTimer.P());
    }
    else if(mCoolingDown)
    {
        Graphics::SetColor(0.4f, 0.375f, 0.415f);
        Graphics::DrawRect(10.0f, 50, 30.0f, 150.0f);
        
        Graphics::SetColor(0.15f, 0.33f, 0.95f);
        Graphics::DrawRect(14.0f, 52.0f, 26.0f, 142.0f * mCoolDownTimer.P());
    }
    
    Graphics::SetColor();
    
}


void ActionProcItem::TouchDown(float pX, float pY, void *pData)
{
    if(mIsClickable)
    {
        
        if(gBoard->DragItemCanStart())
        {
            gBoard->DragItemStart(this);
        }
        
        mIsClicked = true;
    }
    
}

void ActionProcItem::TouchUp(float pX, float pY, void *pData)
{
    TouchFlush();
    
    
    
    //mIsClicked = false;
}

void ActionProcItem::TouchMove(float pX, float pY, void *pData)
{
    
}

void ActionProcItem::TouchFlush()
{
    if(mIsClickable)
    {
        if(gBoard->mDragItem == this)
        {
            gBoard->DragItemEnd(this);
        }
        
        mIsClicked = false;
    }
    
    
}

bool ActionProcItem::IsReady()
{
    bool aReturn = false;
    
    
    if((mCoolingDown == false) && (mTriggering == false) && (mDelayWait == false) && (mDelayReady == false))
    {
        aReturn = true;
    }
    
    return aReturn;
}

bool ActionProcItem::WillBeReady()
{
    bool aReturn = false;
    
    if((mCoolingDown == false) && (mTriggering == false) && (mDelayWait == false))// && (mDelayReady == false))
    {
        Log("ActionProcItem::WillBeReady()\n");
        aReturn = true;
    }
    
    return aReturn;
}

void ActionProcItem::SetClickable()
{
    mIsClickable = true;
 
    /*
    if(mButton == 0)
    {
        mButton = new FButton();
        AddSubview(mButton);
        
    }
    else
    {
        BringSubviewToFront(mButton);
    }
    
    mButton->mDrawRectIfSpriteIsNull = false;
    mButton->SetFrame(0.0f, 0.0f, mWidth, mHeight);
    */
}

void ActionProcItem::SetDragable()
{
    mDragable = true;
}

void ActionProcItem::Notify(void *pSender)
{
    /*
    if(pSender == mButton)
    {
        mButtonClicked = true;
        
        if((mDragable == true) && (gBoard != 0))
        {
            if(gBoard->DragItemCanStart())
            {
                //gBoard->DragItemStart(this);
            }
        }
    }
    */
}


void ActionProcItem::SpawnParticle(int pIndex)
{
    
    /*
    
    if(pIndex == 0)
    {
        //FParticle *aTwinkle = new FParticle(gApp->mMILevelUpDisplayStar);
        FParticle *aTwinkle = new FParticle(gApp->mEffectTwinkleWhite[gRand.Get(2)]);
        aTwinkle->SetPos(gRand.F(-80.0f, 80.0f), gRand.F(-80.0f, 80.0f));
        aTwinkle->SetRotation(-20.0f);
        aTwinkle->SetScale(0.05f);
        aTwinkle->mScaleSpeed = 0.20f + gRand.GetFloat(0.02f);
        aTwinkle->mScaleSpeedAdd = -0.0125f;
        aTwinkle->mRotationSpeed = gRand.GetFloat(0.5f) + 1.5f;
        mAnimationsRelative.Add(aTwinkle);
    }
    
    if(pIndex == 1)
    {
        FParticle *aParticle = new FParticle(gApp->mEffectParticleFlare[gRand.Get(2)][gRand.Get(4)]);
        aParticle->SetPos(mX + gRand.F(-16.0f, 16.0f), mY + gRand.F(-16.0f, 16.0f));
        aParticle->SetAlpha(0.7f + gRand.F(-0.05f, 0.2f));
        aParticle->SetAlphaSpeed(0.012f);
        aParticle->SetSpeedDirectional(gRand.R(), gRand.GetFloat(6.0f, 13.5f));
        aParticle->SetAccel(0.95f, 0.95f);
        mAnimationsAdditive.Add(aParticle);
    }
    
    if(pIndex == 2)
    {
        FParticle *aParticle = new FParticle(gApp->mEffectParticleFlare[gRand.Get(2)][gRand.Get(4)]);
        aParticle->SetPos(gRand.F(-16.0f, 16.0f), gRand.F(-16.0f, 16.0f));
        aParticle->SetAlpha(0.7f + gRand.F(-0.05f, 0.2f));
        aParticle->SetAlphaSpeed(0.012f);
        aParticle->SetSpeedDirectional(gRand.R(), gRand.GetFloat(6.0f, 13.5f));
        aParticle->SetAccel(0.95f, 0.95f);
        mAnimationsAdditive.Add(aParticle);
    }
    
    if(pIndex == 3)
    {
        FParticle *aParticle = new FParticle(gApp->mEffectParticleFlare[gRand.Get(2)][gRand.Get(4)]);
        aParticle->SetPos(gRand.F(-16.0f, 16.0f), gRand.F(-16.0f, 16.0f));
        aParticle->SetAlpha(0.7f + gRand.F(-0.05f, 0.2f));
        aParticle->SetAlphaSpeed(0.012f);
        aParticle->SetSpeedDirectional(gRand.R(), gRand.GetFloat(6.0f, 13.5f));
        aParticle->SetAccel(0.95f, 0.95f);
        mAnimationsAdditive.Add(aParticle);
    }
    
    */
    
}

int ActionProcItem::GetTriggerChargeTime()
{
    return mTriggerStepper.mTime[0];
}

void ActionProcItem::StartTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus)
{
    mTriggerStepper.Reset();
    
    for(int i=0;i<3;i++)
    {
        mTriggerBeamWidth[i] = 0.0f;
        mTriggerObstacleBeamWidth[i] = 0.0f;
    }
    
    mTriggerFocus = pFocus;
    mTriggering = true;
}

void ActionProcItem::UpdateTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus)
{
    
    mTriggerStepper.Update();
    
    if(mTriggerStepper.mStep == 0)
    {
        
    }
    
    for(int i=0;i<3;i++)
    {
        mTriggerBeamWidth[i] = 24.0f * mTriggerStepper.V();
        mTriggerObstacleBeamWidth[i] = 28 * mTriggerStepper.V();
    }
    
    if(mTriggerStepper.mStep >= 3)
    {
        EndTrigger(pFromX, pFromY, pFocus);
        
        mTriggering = false;
        
        mCoolingDown = true;
        mCoolDownTimer.Reset();
        
        mDelayWait = true;
        mDelayWaitTimer.Reset();
        
        mDelayReadyTimer.Reset();
        gGame->ActionProcItemTriggerStop();
    }
}

void ActionProcItem::EndTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus)
{
    
}


ActionProcItemFocus::ActionProcItemFocus()
{
    
    for(int i=0;i<3;i++)
    {
        
        mMatch[i] = false;
        mObstacle[i] = false;
        
        
        mMatchGridX[i] = -1;
        mMatchGridY[i] = -1;
        
        mMatchCenterX[i] = 0.0f;
        mMatchCenterY[i] = 0.0f;
        
        mObstacleGridX[i] = -1;
        mObstacleGridY[i] = -1;
        
        mObstacleCenterX[i] = 0.0f;
        mObstacleCenterY[i] = 0.0f;
    }
}

ActionProcItemFocus::~ActionProcItemFocus()
{
    
}


