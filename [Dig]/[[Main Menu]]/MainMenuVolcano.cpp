//
//  MainMenuVolcano.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "MainMenuVolcano.h"
#include "MainApp.h"

MainMenuVolcano::MainMenuVolcano(FSprite *pSprite) : MainMenuSceneItem(pSprite)
{
    mBaseMouthX = -10.0f;
    mBaseMouthY = -10.0f;
    
    mBaseMouthDir = 80.0f;
    mBaseMouthWidth = 60.0f;
    
    mCornerWobbleSin1 = 180.0f;
    mCornerWobbleSin2 = 360.0f;
    
    mSmokeBaseDriftSin = gRand.GetFloat(360.0f);
    mSmokeBaseDriftSinSpeed = 4.0f;
    
    
    mPuffCount = 5;
    mPuffTimer = 0;
    mPuffMode = 0;
    mPuffBlastCount = 0;
    mPuffBlastDelay = 0;
    mWaitTimer = gRand.Get(100);
    mMode = 0;
    
    mPuffBounce = 0.0f;
    mPuffBounceSpeed = 0.0f;
    
    mBounceFactor = 1.0f;
    
}

MainMenuVolcano::~MainMenuVolcano()
{
    mSmokeList.Free();
}

void MainMenuVolcano::Update()
{
    MainMenuSceneItem::Update();
    
    mCornerWobbleSin1 += 6.0f;
    mCornerWobbleSin2 += 4.0f;
    
    if(mCornerWobbleSin1 >= 360.0f)mCornerWobbleSin1 -= 360.0f;
    if(mCornerWobbleSin2 >= 360.0f)mCornerWobbleSin2 -= 360.0f;
    
    mSmokeBaseDriftSin += mSmokeBaseDriftSinSpeed;
    if(mSmokeBaseDriftSin >= 360.0f)mSmokeBaseDriftSin -= 360.0f;
    
    if(mMode == 0)
    {
        mWaitTimer--;
        if(mWaitTimer <= 0)
        {
            mPuffTimer = 0;
            mWaitTimer = 0;
            mMode = 1;
            mPuffMode = 0;
            mPuffCount = gRand.Get(2) + 1;
            if(gRand.Get(5) == 1)mPuffCount += 2;
            mPuffBlastCount = gRand.Get(4) + 6;
            
            mPuffBlastDelay = 2;
        }
        mPuffBounce *= 0.96f;
    }
    else
    {
        if(mPuffMode == 0)
        {
            mPuffMode = 1;
            mPuffBounceSpeed = -5.10f;
        }
        
        else
        {
            mPuffBounce += mPuffBounceSpeed;
            
            if(mPuffMode == 1)
            {
                mPuffBounceSpeed += 0.625f;
                
                if(mPuffBounce >= 0.0f)
                {
                    mPuffMode = 2;
                }
                
                mPuffBlastDelay--;
                if(mPuffBlastDelay <= 0)
                {
                    mPuffBlastDelay = 2 + gRand.Get(1);
                    
                int aCount = 1 + gRand.Get(1);
                while((mPuffBlastCount > 0) && (aCount > 0))
                {
                    MainMenuVolcanoSmoke *aSmoke = new MainMenuVolcanoSmoke();
                    
                    aSmoke->mDriftSin += mSmokeBaseDriftSin;
                    aSmoke->SetPos(mBaseMouthX, mBaseMouthY);
                    
                    float aConeAngle = gRand.F(-16.0f, 16.0f) + mBaseMouthDir;
                    float aConePush = gRand.F(3.0f, 30.0f);
                    
                    aSmoke->mX += Sin(aConeAngle) * aConePush;
                    aSmoke->mY -= Cos(aConeAngle) * aConePush;
                    
                    mSmokeList.Add(aSmoke);
                    
                    mPuffBlastCount--;
                    aCount--;
                }
                }
            }
            
            if(mPuffMode == 2)
            {
                mPuffBounceSpeed -= 0.85f;
                if(mPuffBounce <= 0.0f)
                {
                    mPuffCount--;
                    mPuffMode = 0;
                    
                    if(mPuffCount <= 0)
                    {
                        mPuffCount = 0;
                        mMode = 0;
                        mWaitTimer = 60 + gRand.Get(160);
                    }
                    else
                    {
                        mPuffBlastCount = gRand.Get(4) + 6;
                    }
                }
            }

        }
    }
    
    mSmokeList.Update();
}

void MainMenuVolcano::Draw()
{
    //FVec2 aMouthDir = AngleToVector(mBaseMouthDir);
    //float aMouthDirX = aMouthDir.mX;
    //float aMouthDirY = aMouthDir.mY;
    
    if(mSprite)
    {
        float aAng1 = mBaseMouthDir + 20.0f;
        float aAng2 = mBaseMouthDir - 6.0f;
        
        float aBounce = mPuffBounce * mScale * 0.5f * mBounceFactor;
        
        mQuadOffset.mX[0] = Sin(aAng1) * (aBounce);
        mQuadOffset.mY[0] = -Cos(aAng1) * (aBounce);
        
        mQuadOffset.mX[1] = Sin(aAng2) * (aBounce);
        mQuadOffset.mY[1] = -Cos(aAng2) * (aBounce);
        
        mQuadDraw.Set(mQuadBase);
        mQuadDraw.Add(mQuadOffset);
        
        Graphics::SetColor();
        mSprite->DrawQuad(mQuadDraw.X1(), mQuadDraw.Y1(), mQuadDraw.X2(), mQuadDraw.Y2(), mQuadDraw.X3(), mQuadDraw.Y3(), mQuadDraw.X4(), mQuadDraw.Y4());

    }
    
    

    
    
    //float aOriAngle1 = FaceTarget(mQuadDraw.mX[0], mQuadDraw.mY[0], mQuadDraw.mX[2], mQuadDraw.mY[2]);
    //float aOriAngle2 = FaceTarget(mQuadDraw.mX[1], mQuadDraw.mY[1], mQuadDraw.mX[3], mQuadDraw.mY[3]);
    
    //float aAngleDiff = DistanceBetweenAngles(aOriAngle1, aOriAngle2);
    
    

    
    
    //float aMouthRot = mBaseMouthDir + aAngleDiff;
    //aMouthDirX = Sin(aMouthRot);
    //aMouthDirY = -Cos(aMouthRot);
    
    Graphics::BlendSetAlpha();
    
    EnumList(MainMenuVolcanoSmoke, aSmoke, mSmokeList)
    {
        if(aSmoke->mKill == 0)
        {
            //aSmoke->DrawShadow(mX, mY, mScale);
        }
    }
    
    Graphics::BlendSetAdditive();
    EnumList(MainMenuVolcanoSmoke, aSmoke, mSmokeList)
    {
        if(aSmoke->mKill == 0)
        {
            aSmoke->Draw(mX, mY, mScale);
        }
    }
    
    Graphics::BlendSetAlpha();
    Graphics::SetColor();
}

void MainMenuVolcano::SetRelativePos(float pX, float pY)
{
    MainMenuSceneItem::SetRelativePos(pX, pY);
}

void MainMenuVolcano::Place(float pCenterX, float pCenterY, float pScale)
{
    MainMenuSceneItem::Place(pCenterX, pCenterY, pScale);
    
    mScale = pScale;
    
    mX = pCenterX + mRelativeX * mScale;
    mY = pCenterY + mRelativeY * mScale;
    
    float aWidth = 128.0f;
    float aHeight = 128.0f;
    
    if(mSprite)
    {
        aWidth = mSprite->mWidth * mScale;
        aHeight = mSprite->mHeight * mScale;
    }
    
    
    mQuadBase.SetRect(mX - aWidth / 2.0f, mY - aHeight / 2.0f, aWidth, aHeight);
    
    
    
}

void MainMenuVolcano::SetMouthPos(float pX, float pY)
{
    mBaseMouthX = pX;
    mBaseMouthY = pY;
}

void MainMenuVolcano::SetMouthDir(float pDegrees)
{
    
}

void MainMenuVolcano::SetMouthWidth(float pWidth)
{
    
}



MainMenuVolcanoSmoke::MainMenuVolcanoSmoke()
{
    mSmokeIndex = gRand.Get(3);
    
    mDriftSin = gRand.GetFloat(-8.0f, 8.0f);
    mDriftSinSpeed = gRand.GetFloat(4.0f, 4.05f);
    
    
    mXSpeed = gRand.GetFloat(-0.45f, 0.60f);
    mYSpeed = gRand.GetFloat(-4.2f, -2.2f);
    
    
    mSpeedAccel = 0.987f;
    
    mScale = 0.8f;
    mScaleSpeed = 0.0023f;
    mScaleAccel = 0.994f;
    
    int aColorIndex = gRand.Get(2);
    
    if(aColorIndex == 0)SetColor(1.0f, 1.0f, 1.0f, gRand.F(1.35f, 1.5f));
    else SetColor(1.0f, 1.0f, 1.0f, gRand.F(1.35f, 1.5f));
    
    
    SetColorSpeed(0.003f, 0.003f, 0.003f, 0.0f);
    
    
    if(gRand.GetBool())
    {
        mGravityY = gRand.F(0.001f, 0.006f);
    }
    
    float aRot = gRand.Rot();
    
    mScatterDirX = Sin(aRot);
    mScatterDirY = -Cos(aRot);
    
    
    mScatterMagnitude = gRand.F(0.4f, 2.0f);
    mScatterTimer = 130 + gRand.Get(40);
    mScatterRotSpeed = gRand.F(-0.15f, -0.6f);
    mScatterFade = 0.0f;
    
    
    
    mDriftOffsetX = 0.0f;
    mDriftOffsetY = 0.0f;
    
    mBirthFade = 0.0f;
    
    mDrawShadow = gRand.GetBool();
}

MainMenuVolcanoSmoke::~MainMenuVolcanoSmoke()
{
    
}

void MainMenuVolcanoSmoke::Update()
{
    
    if(mTimerAlive >= 120)
    {
        mScale -= 0.004f;
        mAlpha -= 0.01f;
    }
    
    if(mTimerAlive >= 70)
    {
        mXSpeed += 0.0125f;
        mYSpeed *= 0.98f;
    }
    
    mYSpeed *= 0.996f;
    
    
    
    mScatterTimer--;
    if(mScatterTimer <= 0)
    {
        mScatterFade += 0.00525f;
        if(mScatterFade >= 1.0f)mScatterFade = 1.0f;
        
        float aScatterMag = (mScatterMagnitude * mScatterFade);
        
        mX += mScatterDirX * aScatterMag;
        mY += mScatterDirY * aScatterMag;
        
        mRotation += mScatterRotSpeed * mScatterFade;
    }
    
    mDriftSin += mDriftSinSpeed;
    if(mDriftSin >= 360.0f)mDriftSin -= 360.0f;
    
    mDriftOffsetX = -Cos(mDriftSin) * 0.5f;
    mDriftOffsetY = Sin(mDriftSin) * 7.25f;
    
    mDriftOffsetX *= mBirthFade;
    mDriftOffsetY *= mBirthFade;
    
    mBirthFade += 0.04f;
    if(mBirthFade >= 1.0f)mBirthFade = 1.0f;
    
    FParticle::Update();
}



void MainMenuVolcanoSmoke::Draw(float pX, float pY, float pScale)
{
    if(mDrawShadow)Draw(&(gApp->mTitleVolcanoSmokeShadow[mSmokeIndex]), pX, pY, pScale, true);
    Draw(&(gApp->mTitleVolcanoSmoke[mSmokeIndex]), pX, pY, pScale, false);
}

void MainMenuVolcanoSmoke::DrawShadow(float pX, float pY, float pScale)
{
    
}

void MainMenuVolcanoSmoke::Draw(FSprite *pSprite, float pX, float pY, float pScale, bool pShadow)
{
    float aX = pX + (mX + mDriftOffsetX) * pScale;
    float aY = pY + (mY + mDriftOffsetY) * pScale;
    
    float aScale = ((mScale * mBirthFade * 0.6f) + (mScale * 0.4f)) * pScale;
    
    float aRed = mRed;
    if(aRed > 1.0f)aRed = 1.0f;
    if(aRed < 0.0f)aRed = 0.0f;
    
    float aGreen = mGreen;
    if(aGreen > 1.0f)aGreen = 1.0f;
    if(aGreen < 0.0f)aGreen = 0.0f;
    
    float aBlue = mBlue;
    if(aBlue > 1.0f)aBlue = 1.0f;
    if(aBlue < 0.0f)aBlue = 0.0f;
    
    float aAlpha = mAlpha;
    if(aAlpha > 1.0f)aAlpha = 1.0f;
    if(aAlpha < 0.0f)aAlpha = 0.0f;
    
    if((mAlpha > 0.0f) && (aScale > 0.0f) && (mTimerDelay <= 0))
    {

            Graphics::SetColor(aRed, aGreen, aBlue, aAlpha);
            pSprite->Draw(aX, aY, aScale, mRotation + Sin(mDriftSin) * 1.8f);
    }
}




