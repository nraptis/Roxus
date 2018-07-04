//
//  ComboTriggerOrb.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 9/7/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "core_includes.h"
#include "ComboTriggerOrb.h"
#include "MainApp.h"
#include "MainApp.h"
#include "Board.h"
#include "BoardGenericMatch.h"

ComboTriggerOrb::ComboTriggerOrb()
{
    mListener = 0;
    
    mAttachedToTile = true;
    
    mMatch = 0;
    
    mOrbitX = 0.0f;
    mOrbitY = 0.0f;
    
    mOrbitCenterX = 0.0f;
    mOrbitCenterY = 0.0f;
    
    mOrbitRadius = 23.0f;
    
    mOrbitRotationAngle = gRand.GetFloat(360.0f);
    
    mOrbitRotationAxis = 50.0f;
    mOrbitRotationSpeed = 16.0f;
    
    mMode = 0;
    mModeTimer = 0;
    
    //mBoltTargetX = 0;
    //mBoltTargetY = 0;
    
    mTargetGridX = 0;
    mTargetGridY = 0;
    
    //mBoltX = 0.0f;
    //mBoltY = 0.0f;
    
    mReadyToTrigger = false;
    
    
    mFrame = gRand.GetFloat((float)(gApp->mSequenceEffectBolt.GetMaxFrame()));
    mFrameSpeed = 0.70f;
    
    
    mTriggerTick = 0;
    mTriggerTickTotal = BOARD_TIMER_COMBO_TRIGGER_PATHING;
    
    mFade = 1.0f;
    
    mDidFizzle = false;
    
    mOrbitCenterX = 0.0f;
    mOrbitCenterY = 0.0f;
    
    mOrbitRadius = 16.0f;
    
    mOrbitRotationAngle = gRand.GetFloat(360.0f);
    
    mOrbitRotationAxis = 7.0f;
    mOrbitRotationSpeed = 3.0f;
    
    mOrbitScale = 0.475f;
    
    mOrbitTargetCenterX = 0.0f;
    mOrbitTargetCenterY = 0.0f;
    
    
    mSparkleGenerationTimer = 0;
    
    
    /*
    
    mLayerSparkles.SetSequence(&(gApp->mEffectParticleCool));
    
    mLayerSparkles.mStartX.mValue = 6.0f;
    mLayerSparkles.mStartX.mRandom = 6.0f;
    mLayerSparkles.mStartX.mSpeedRandom = 0.2f;
    mLayerSparkles.mStartX.mAccel = 0.99f;
    
    mLayerSparkles.mStartY.mValue = 6.0f;
    mLayerSparkles.mStartY.mRandom = 2.0f;
    mLayerSparkles.mStartY.mSpeedRandom = 2.5f;
    mLayerSparkles.mStartY.mAccel = 0.99f;
    
    
    mLayerSparkles.mStartAlpha.mValue = 1.45f;
    mLayerSparkles.mStartAlpha.mRandom = 0.3f;
    mLayerSparkles.mStartAlpha.mSpeed = 0.01f;
    mLayerSparkles.mStartAlpha.mSpeedRandom = 0.002f;
    
    mLayerSparkles.mAdditive = true;
    
    */
    
    
    //mLayerSparkles.SetStartPositionAttributes(StepAnimationStartAttributeCumulative(5.0f, 5.0f, 0.0f, 0.3f, 0.9825f, 0.0f, 0.0f, 0.0f), StepAnimationStartAttributeCumulative(5.0f, 5.0f, 0.0f, 0.3f, 0.9825f, 0.0f, 0.0f, 0.0f));
    
    
    //mLayerSparkles.SetStart
    
    mSpinnerRotation1 = gRand.GetFloat(360.0f);
    mSpinnerRotationSpeed1 = gRand.GetFloat(1.0f, 1.4f);
    
    mSpinnerRotation2 = gRand.GetFloat(360.0f);
    mSpinnerRotationSpeed2 = -gRand.GetFloat(2.0f, 2.25f);
    
    mScaleSin = gRand.GetFloat(360.0f);
}

ComboTriggerOrb::~ComboTriggerOrb()
{
    delete mMatch;
    mMatch = 0;
}

void ComboTriggerOrb::Update()
{
    
    mSpinnerRotation1 = LoopAngle(mSpinnerRotation1, mSpinnerRotationSpeed1);
    mSpinnerRotation2 = LoopAngle(mSpinnerRotation2, mSpinnerRotationSpeed2);
    
    mScaleSin = LoopAngle(mScaleSin, 4.0f);
    
    
    mFrame += mFrameSpeed;
    
    float aFrameMax = gApp->mSequenceEffectBolt.GetMaxFrame();
    
    mFrame = gRand.GetFloat((float)(gApp->mSequenceEffectBolt.GetMaxFrame()));
    
    if(mFrame >= aFrameMax)
    {
        mFrame -= aFrameMax;
    }
    
    
    
    if(mAttachedToTile == false)
    {
        
        mOrbitScale += 0.04f;
        if(mOrbitScale >= 1.30f)
        {
            mOrbitScale = 1.30f;
        }
        
        mOrbitRotationAxis += 3.5f;
        if(mOrbitRotationAxis >= 40.0f)
        {
            mOrbitRotationAxis = 40.0f;
        }
        
        mOrbitRadius += 5;
        if(mOrbitRadius >= 60.0f)mOrbitRadius = 60.0f;
        
        if(mMode < 3)
        {
            mFade += 0.03f;
            if(mFade >= 1.0f)
            {
                mFade = 1.0f;
            }
        }
        
        
    }
    
    if(mMode <= 1)
    {
        float aPreviousOrbitX = mOrbitX;
        float aPreviousOrbitY = mOrbitY;

        
        
        float aDiffX = mOrbitTargetCenterX - mOrbitCenterX;
        float aDiffY = mOrbitTargetCenterY - mOrbitCenterY;
        
        mOrbitCenterX += aDiffX / 10.0f;
        mOrbitCenterY += aDiffY / 10.0f;
        
        
        mOrbitRotationAngle += mOrbitRotationSpeed;
        if(mOrbitRotationAngle >= 360.0f)mOrbitRotationAngle -= 360.0f;
        if(mOrbitRotationAngle <= 0.0f)mOrbitRotationAngle += 360.0f;
        
        if(gBoard)
        {
            mOrbitX = 0.0f;
            mOrbitY = 0.0f;
            
            gBoard->mEggBorder.Get((mOrbitRotationAngle / 360.0f), mOrbitX, mOrbitY);
            
            
            mOrbitX += mOrbitCenterX;
            mOrbitY += mOrbitCenterY;
            
        }
        
        
        
        /*
         
        mOrbitX = mOrbitCenterX + Sin(mOrbitRotationAngle) * mOrbitRadius;
        mOrbitY = mOrbitCenterY + Cos(mOrbitRotationAngle) * mOrbitRadius;
        
        float aSkewY = (mOrbitCenterY - mOrbitY);
        
        if(aSkewY < 0.0f)
        {
            aSkewY *= 1.20f;
        }
        else
        {
            aSkewY *= 1.75f;
        }
        
        mOrbitY = mOrbitCenterY - aSkewY;
        */
        
        
        mOrbitSpeedX = mOrbitX - aPreviousOrbitX;
        mOrbitSpeedY = mOrbitY - aPreviousOrbitY;
        
        mOrbitRotation = FaceTarget(mOrbitSpeedX, mOrbitSpeedY);
    }
    
    if(mMode == 2)
    {
        mTriggerTick++;
        if(mTriggerTick >= mTriggerTickTotal)
        {
            mMode = 2;
        }
        
        float aPercent = ((float)mTriggerTick / ((float)mTriggerTickTotal));
        
        mSpline.Get(aPercent * mSpline.Max(), mOrbitX, mOrbitY);
        
    }
    
    if(mMode >= 3)
    {
        mFade -= 0.02f;
        
        if(mFade <= 0.0f)
        {
            mFade = 0.0f;
            
            if(mSparkles.mCount <= 0)
            {
                Kill();
            }
        }
    }
    else
    {
        mSparkleGenerationTimer++;
        
        /*
        //if(gRand.Get(5) == 2)
        if(mSparkleGenerationTimer >= 3)
        {
            mSparkleGenerationTimer = 0;
            
            StepAnimationParticle *aParticle = new StepAnimationParticle();
            
            aParticle->mSprite = gApp->mEffectParticleCoolSmall.GetRandom();
            
            aParticle->mX = mOrbitX + gRand.GetFloat(-8.0f, 8.0f);
            aParticle->mY = mOrbitY + gRand.GetFloat(-8.0f, 8.0f);
            
            aParticle->mYSpeed = 1.30f + gRand.GetFloat(0.15f);
            aParticle->mYSpeedAccel = 0.98f;
            
            aParticle->mScale = 0.4f + gRand.GetFloat(0.1f);
            aParticle->mScaleSpeed = 0.0002f;
            
            aParticle->mAlpha = 1.3f + gRand.GetFloat(0.2f);
            aParticle->mAlphaSpeed = 0.02f;
            
            mSparkles.Add(aParticle);
            
        }
        */
    }

    mSparkles.Update();
    mAnimations.Update();
    
}

void ComboTriggerOrb::Draw()
{
    Graphics::BlendSetAdditive();
    
    
    mAnimations.Draw();
    
//    EnumList(StepAnimationParticle, aParticle, mSparkles.mObjects)
//    {
//        if(aParticle->mFinished == false)
//        {
//            aParticle->Draw();//gApp->mEffectParticleCool.GetSprite(0));
//        }
//    }
    
    if(mFade > 0.0f && mOrbitScale > 0.001f)
    {
        
        
        
		Graphics::SetColor(mFade * 0.4f);
        
        //gApp->mSequenceEffectBolt.Draw(mFrame, mOrbitX, mOrbitY, mOrbitScale, mOrbitRotation);
        
        float aScale = 0.75f + Sin(mScaleSin) * 0.125f;
        
        gApp->mEffectSpecialOrbiterHaloNaked.Draw(mOrbitX, mOrbitY, aScale, mSpinnerRotation2);
        
		Graphics::SetColor(mFade * 0.8f);
        
        gApp->mEffectSpecialOrbiterHalo.Draw(mOrbitX, mOrbitY, aScale, mSpinnerRotation1);
        
        
        aScale = 0.80f + Sin(mScaleSin) * 0.05f;
        
        Graphics::BlendSetAlpha();
		Graphics::SetColor(mFade);
        
        gApp->mEffectSpecialOrbiter.Draw(mOrbitX, mOrbitY, aScale, 0.0f);
        
        
        
        //gApp->mEffectCloudPoof.Draw(mOrbitX, mOrbitY, mOrbitScale, 0.0f);
    }
    
    

    
    
    //mFrame
    
    Graphics::BlendSetAlpha();
    Graphics::SetColor();
}

void ComboTriggerOrb::StartSwirl(int pGridX, int pGridY, float pCenterX, float pCenterY)
{
    mMode = 1;
    
    mOrbitCenterX = pCenterX;
    mOrbitCenterY = pCenterY;
    
    mOrbitTargetCenterX = mOrbitCenterX;
    mOrbitTargetCenterY = mOrbitCenterY;
    
    float aPreviousOrbitX = mOrbitCenterX + Sin(mOrbitRotationAngle - mOrbitRotationSpeed) * mOrbitRadius;
    float aPreviousOrbitY = mOrbitCenterY + Cos(mOrbitRotationAngle - mOrbitRotationSpeed) * mOrbitRadius;
    
    mOrbitX = mOrbitCenterX + Sin(mOrbitRotationAngle) * mOrbitRadius;
    mOrbitY = mOrbitCenterY + Cos(mOrbitRotationAngle) * mOrbitRadius;
    
    mOrbitSpeedX = mOrbitX - aPreviousOrbitX;
    mOrbitSpeedY = mOrbitY - aPreviousOrbitY;
    
    mOrbitRotation = FaceTarget(mOrbitSpeedX, mOrbitSpeedY);
    
}

void ComboTriggerOrb::TriggerFizzle()
{
    
    mDidFizzle = true;
    mMode = 3;
    
    delete mMatch;
    mMatch = 0;
}

void ComboTriggerOrb::Trigger(BoardGenericMatch *pMatch)
{
    if(pMatch)
    {
        mMatch = pMatch;
        
        mTargetGridX = pMatch->mCenterX;
        mTargetGridY = pMatch->mCenterY;
        
        
        Trigger(mTargetGridX, mTargetGridY, gBoard->GetTileCenterX(mTargetGridX), gBoard->GetTileCenterY(mTargetGridY));
        
        
    }
}

void ComboTriggerOrb::Trigger(int pGridX, int pGridY, float pTargetX, float pTargetY)
{
    
    //printf("Triggering[%d] (%d, %d)\n", this, pGridX, pGridY);
    
    mMode = 2;
    
    //mMode =
    mTriggerTickTotal = BOARD_TIMER_COMBO_TRIGGER_PATHING;
    
    mTargetGridX = pGridX;
    mTargetGridY = pGridY;
    
    float aTryStartTanX = mOrbitSpeedX * 30.0f;
    float aTryStartTanY = mOrbitSpeedY * 30.0f;
    
    float aTryEndTanX = -mOrbitSpeedX * 5.0f;
    float aTryEndTanY = -mOrbitSpeedY * 5.0f;
    
    
    float aBestStartTanX = aTryStartTanX;
    float aBestStartTanY = aTryStartTanY;
    
    float aBestEndTanX = aTryEndTanX;
    float aBestEndTanY = aTryEndTanY;
    
    mSpline.Add(mOrbitX, mOrbitY, aBestStartTanX, aBestStartTanY);
    //mSpline.Add(aTryKinkX1, aTryKinkY1);
    //mSpline.Add(aTryKinkX2, aTryKinkY2);
    mSpline.Add(pTargetX, pTargetY, aBestEndTanX, aBestEndTanY);

    mSpline.SetTangent(0, aBestStartTanX, aBestStartTanY);
    //mSpline.SetPoint(1, aBestKinkX1, aBestKinkY1);
    //mSpline.SetPoint(2, aBestKinkX2, aBestKinkY2);
    mSpline.SetTangent(1, aBestEndTanX, aBestEndTanY);
    
    //printf("Length = [%f]\n", mSpline.LengthPredict(0.025f));
    
}


void ComboTriggerOrb::PhaseOut()
{
    //printf("Phasing Out All These Buggers[%x]", this);
    
    mMode = 3;
}
