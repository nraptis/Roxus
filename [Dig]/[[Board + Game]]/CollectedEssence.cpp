//
//  CollectedEssence.cpp
//  Digplex
//
//  Created by Nick Raptis on 10/4/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "CollectedEssence.h"
#include "MainApp.h"
#include "Game.h"

CollectedEssence::CollectedEssence()
{
    mTimer = 0;
    
    mTarget = 0;
    
    mSpeedX = 0.0f;
    mSpeedY = 0.0f;
    
    mSwarmFactor = 1.0f;
    
    
    mSplinePos = 0.0f;
    //mSplineSpeed = 0.05f;
    
    mSplineSpeed = 0.03f;
    
    
    mComplete = false;
    
    mFrame = 0.0f;
    
    mBoltScale = 0.15f;
    
    mFrameMax = gApp->mSequenceGlowBall.GetMaxFrame();
    mFrame = gRand.GetFloat(mFrameMax);
}

CollectedEssence::~CollectedEssence()
{
    
}

void CollectedEssence::Update()
{
    mTimer++;
    
    mFrame += 0.65f;
    if(mFrame >= gApp->mSequenceGlowBall.GetMaxFrame())
    {
        mFrame -= gApp->mSequenceGlowBall.GetMaxFrame();
    }
    
    mSplineSpeed *= 0.988f;
    mSplinePos += 0.0080f;
    mSplinePos += mSplineSpeed;
    
    if(mSpline)
    {
        mSpline->Get(mSplinePos, mX, mY);
        mRotation = 180.0f + mSpline->Rotation(mSplinePos);
        
        if(mComplete == false)
        {
            if(mSplinePos >= mSpline->Max())
            {
                mComplete = true;
                gGame->CollectedEssenceReachedInterface(this);
            }
            
            if(mTimer >= 600)
            {
                Kill();
            }
        }
    }
    
    mBoltScale *= 1.0010f;
    mBoltScale += 0.010f;
    
    if(mBoltScale >= 1.0f)mBoltScale = 1.0f;
    
}


void CollectedEssence::Draw()
{
    
    
    
    
    
    if(mComplete == false)
    {
        Graphics::BlendSetAdditive();
        
        //Graphics::SetColor(0.45f);
        Graphics::SetColor();
        
        
        //gApp->mSequenceEffectBoltGlow.Draw(mFrame, mX, mY, mBoltScale, mRotation);
        
        //gApp->mSequenceParticleStream.Draw(mFrame, mX, mY, mBoltScale * 1.3f, mRotation);
        
        
        
        
        Graphics::SetColor();
        //Graphics::BlendSetAlpha();
        
        gApp->mSequenceGlowBall.Draw(mFrame, mX, mY, mBoltScale, mRotation);
        
        
        Graphics::SetColor(0.45f);
        Graphics::BlendSetAlpha();
        
        
        //gApp->mSequenceEffectBolt.Draw(mFrame, mX, mY, mBoltScale, mRotation);
        
        Graphics::SetColor();
        
    }
    
}


void CollectedEssence::ShootTowardsJar(float pX, float pY)
{
    mSwarmTargetX = mX;
    mSwarmTargetY = mY;
    
    mSpeedX = gRand.GetFloat(4.0f, 8.0f, true);
    mSpeedY = gRand.GetFloat(4.0f, 8.0f, true);
    
    mSwarmFactor = 1.0f;
    
    
    
    float aDiffX = pX - mX;
    
    //printf("DiffX = [%f]\n", aDiffX);
    
    
    aDiffX *= 1.75f;
    
    if(aDiffX < 450.0f)aDiffX = 450.0f;
    
    mMotionPath.AddCalibrationSpline(mX, mY, -1000.0f, 0.0f, pX, pY, aDiffX, 0.0f);
    
    mCalibrationSpline = mMotionPath.GetBest(100.0f);
    
    if(mCalibrationSpline)
    {
        mSpline = &(mCalibrationSpline->mSpline);
    }
    
    
    /*
     mTestSpline.SetPoint(1, pX, pY);
     
     float aStartX = mTestSpline.Get(0).mX;
     float aStartY = mTestSpline.Get(0).mY;
     
     
     mTestSpline.SetTangent(0, (pX - aStartX) * 1.45f, 0.0f);
     
     mTestSpline.SetTangent(1, 0.0f, (pY - aStartY) * 1.35f);
     
     
     //mTestSpline.SetTangent(0, aStartX - pX, aStartY - pY);
     
     */
    //MotionPathCalibrationSpline
    
}

