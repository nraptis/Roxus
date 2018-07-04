//
//  AnimationDiscoveredStar.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 9/4/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "MainApp.h"
#include "AnimationDiscoveredStar.h"
#include "core_includes.h"

AnimationDiscoveredStar::AnimationDiscoveredStar()
{
    mX = 0.0f;
    mY = 0.0f;
    
    mScale = 1.0f;
    
    mStartAffineX = gAppWidth2;
    mStartAffineY = gAppHeight2;
    mStartAffineScale = 0.5f;
    
    mTargetX = gAppWidth2;
    mTargetY = gAppHeight2;
    mTargetScale = 1.0f;
    
    mDiscoverNumber = 1;
    mDiscoverNumberTotal = 3;
    
    
    mStepper.SetTimes(60, 115, 80);
    
    mWobblerY.SetTime(50, 10);
    mWobblerY.SetInterval(-4.0f, 5.0f);
    
    mWobblerRot.SetTime(30, 4);
    mWobblerRot.SetInterval(-3.0f, 3.0f);
    
    mWobblerSkew.SetTime(18, 3);
    mWobblerSkew.SetInterval(0.0f, 1.0f);
    
    
    mWobblerSpinnerFade[0].SetTime(9, 8);
    mWobblerSpinnerFade[0].SetInterval(0.65f, 0.70f);
    
    mWobblerSpinnerFade[1].SetTime(14, 2);
    mWobblerSpinnerFade[1].SetInterval(0.50, 0.54f);
    
    
    mParticleSpawnTick[0] = 0;
    mParticleSpawnTime[0] = 3;
    
    mParticleSpawnTick[1] = 0;
    mParticleSpawnTime[1] = 6;
    
    mParticleSpawnTick[2] = 18;
    mParticleSpawnTime[2] = 22;
    
    mParticleSpawnTick[3] = 1;
    mParticleSpawnTime[3] = 9;
    
    
    mRot[0].SetRotSpeed(0.85f);
    mRot[1].SetRotSpeed(-1.5f);
}

AnimationDiscoveredStar::~AnimationDiscoveredStar()
{
    
}

void AnimationDiscoveredStar::Update()
{
    mRot[0].Update();
    mRot[1].Update();
    
    mStepper.Update();
    
    mWobblerY.Update();
    mWobblerRot.Update();
    
    mWobblerSkew.Update();
    
    mWobblerSpinnerFade[0].Update();
    mWobblerSpinnerFade[1].Update();
    
    for(int i=0;i<4;i++)
    {
        mParticleSpawnTick[i]++;
        if(mParticleSpawnTick[i] >= mParticleSpawnTime[i])
        {
            mParticleSpawnTick[i] = 0;
        }
    }
    
    if(mStepper.mFinished == false)
    {
        if(mParticleSpawnTick[0] == 0)SpawnParticle(0);
        if(mParticleSpawnTick[1] == 0)SpawnParticle(1);
        if(mParticleSpawnTick[2] == 0)SpawnParticle(2);
        if(mParticleSpawnTick[3] == 0)SpawnParticle(3);
    }

    mAnimations.Update();
    mAnimationsRelative.Update();
    
    if(mStepper.IsFinished() == false)
    {
        float aPercent = mStepper.GetValue();
        
        
        mScale = mTargetScale;
        
        mX = mTargetX;
        mY = mTargetY;
        
        if(mStepper.mStep == 0)
        {
            mScale = mStartAffineScale + (mTargetScale - mStartAffineScale) * aPercent;
            
            mX = mStartAffineX + (mTargetX - mStartAffineX) * aPercent;
            mY = mStartAffineY + (mTargetY - mStartAffineY) * aPercent;
        }
        else if(mStepper.mStep == 1)
        {
            
        }
        else
        {
            mScale = mTargetScale * aPercent;
            mX = mTargetX;//  (mTargetX - mStartAffineX) * aPercent;
            mY = mTargetY - (80.0f * (1.0f - aPercent));
        }
    }
    

    
    
    if(mStepper.mFinished && mAnimations.Empty() && mAnimationsRelative.Empty())
    {
        Kill();
    }
    
}

void AnimationDiscoveredStar::Draw()
{
    Graphics::BlendSetAdditive();
    mAnimations.Draw();
    Graphics::BlendSetAlpha();
    Graphics::SetColor();
    
    if(mStepper.IsFinished() == false)
    {
        float aPercent = mStepper.GetValue();
        
        if(mScale > 0.0f)
        {
            float aX = mX;
            float aY = mY + mWobblerY.V();
            
            float aScale = mScale;
            
            float aRot = 0.0f + mWobblerRot.V();
            
            Graphics::BlendSetAdditive();
            
            Graphics::SetColor(aPercent * mWobblerSpinnerFade[0].V());
            gApp->mEffectLightSpinnerLarge[2].Draw(aX, aY, 0.7f, mRot[1].R());
            
            
            Graphics::SetColor(aPercent * mWobblerSpinnerFade[1].V());
            gApp->mEffectLightSpinnerLarge[1].Draw(aX, aY, 0.9f, mRot[0].R());
            
            
            Graphics::BlendSetAlpha();
            Graphics::SetColor();
            
            gApp->mGameTileLevelStar.Draw(aX, aY, aScale, aRot);
        }
    }
    
    Graphics::BlendSetAdditive();
    EnumList(FParticle, aParticle, mAnimationsRelative)aParticle->DrawOffset(aParticle->mSprite, mX, mY);
    Graphics::BlendSetAlpha();
}

void AnimationDiscoveredStar::SetStartAffine(float pX, float pY, float pScale)
{
    mX = pX;
    mY = pY;
    mScale = pScale;
    
    mStartAffineX = pX;
    mStartAffineY = pY;
    mStartAffineScale = pScale;
    
    mTargetX = mStartAffineX;
    mTargetY = mStartAffineY - 160.0f;
    
    if(mTargetY < 80.0f)
    {
        mTargetY = mStartAffineY + 140.0f;
    }
    
}

void AnimationDiscoveredStar::SetStartDiscoverNumber(int pCount, int pCountTotal)
{
    mDiscoverNumber = pCount;
    mDiscoverNumberTotal = pCountTotal;
}


void AnimationDiscoveredStar::SpawnParticle(int pIndex)
{
    if(pIndex == 3)
    {
        FParticle *aTwinkle = new FParticle(gApp->mEffectTwinkle[0]);
        aTwinkle->SetPos(gRand.F(-80.0f, 80.0f), gRand.F(-80.0f, 80.0f));
        aTwinkle->SetRotation(-20.0f);
        aTwinkle->SetScale(0.05f);
        aTwinkle->mScaleSpeed = 0.20f + gRand.GetFloat(0.02f);
        aTwinkle->mScaleSpeedAdd = -0.0125f;
        aTwinkle->mRotationSpeed = gRand.GetFloat(0.5f) + 1.5f;
        mAnimationsRelative.Add(aTwinkle);
    }
    
    
    if(pIndex == 0)
    {
        FParticle *aParticle = new FParticle(gApp->mEffectParticleFlare[gRand.Get(2)][gRand.Get(4)]);
        aParticle->SetPos(mX + gRand.F(-16.0f, 16.0f), mY + gRand.F(-16.0f, 16.0f));
        aParticle->SetAlpha(0.7f + gRand.F(-0.05f, 0.2f));
        aParticle->SetAlphaSpeed(0.012f);
        aParticle->SetRotation();
        aParticle->SetRRN(gRand.F(8.0f), 0.95f);
        aParticle->SetSpeedDirectional(gRand.R(), gRand.GetFloat(6.0f, 13.5f));
        aParticle->SetAccel(0.92f);
        mAnimations.Add(aParticle);
    }
    
    if(pIndex == 1)
    {
        FParticle *aParticle = new FParticle(gApp->mEffectParticleCool[gRand.Get(4)]);
        aParticle->SetPos(mX + gRand.F(-16.0f, 16.0f), mY + gRand.F(-16.0f, 16.0f));
        aParticle->SetAlpha(0.7f + gRand.F(0.325f));
        aParticle->SetAlphaSpeed(gRand.F(0.006f, 0.0095f));
        aParticle->SetRRN(gRand.F(8.0f), 0.95f);
        aParticle->SetScaleRandom(1.0f, 0.2f);
        aParticle->mScaleSpeed = 0.01f;
        aParticle->mScaleAccel = 0.98f;
        aParticle->mGravityY = 0.01f;
        aParticle->SetAccel(0.94f);
        aParticle->SetSpeed(gRand.GetFloat() * 8.0f + 5.0f);
        mAnimations.Add(aParticle);
    }
    
    
    if(pIndex == 2)
    {
        FParticle *aParticle = new FParticle(gApp->mSequenceBurst, true);
        aParticle->mFrameSpeed = gRand.F(0.7f, 0.85f);
        aParticle->SetPos(mX, mY);
        aParticle->SetAlpha(0.72f);
        aParticle->SetAlphaSpeed(0.008f);
        aParticle->SetScale(0.8f, 0.025f, 0.90f);
        aParticle->SetRotation();
        mAnimations.Add(aParticle);
    }
}
