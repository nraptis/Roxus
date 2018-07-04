//
//  GameTileMatchable.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "GameTileMatchable.h"

GameTileMatchable::GameTileMatchable()
{
    mTileType = GAME_TILE_TYPE_MATCHABLE;
 
    mComboTrigger = 0;
    
    mCanReceiveDamage = false;
    
    mSpecial = false;
    mSpecialIndex = 0;
    
    //if(gRand.Get(8) == 2)
    //{
    //    mSpecial = true;
    //    mComboTrigger = new ComboTriggerOrb();
    //}
    
    mMatchType = 0;//gRand.Get(3);
    
    mSelected = false;
    
    
    mSparkleTimer.SetTime(300, 1284);
    mSparkleTimer.SetSleep(40, 500);
    
    mSkipAnimFrame1 = 0.0f;
    mSkipAnimFrameSpeed1 = 0.0f;
    
    mSkipAnimFrameMax1 = gApp->mSequenceEffectHilight1.GetMaxFrame();
    mSkipAnimFrame2 = 0.0f;
    mSkipAnimFrameSpeed2 = 0.0f;
    mSkipAnimFrameMax2 = gApp->mSequenceEffectHilight2.GetMaxFrame();
    
    
    mSkipTimer = 0;
    mSkipTimerMode = 0;
    
    mSkipScale = 1.0f;
    
    
    mDestroyRumbleShakeX = 0.0f;
    mDestroyRumbleShakeY = 0.0f;
    mDestroyRumbleShakeAmount = 0.0f;
    
    
    mSquishShiftBounce1 = gRand.GetFloat(360.0f);
    mSquishShiftBounce2 = gRand.GetFloat(360.0f);
    
    
    mShimmerPercent = 0.0f;
    mShimmer = false;
    
    
    mLandedAnimation = false;
    
    mLandedAnimationBounces = 0;
    
    mLandedAnimationSin = 0.0f;
    mLandedAnimationSinSpeed = 0.0f;
    
    mLandedAnimationShiftX = 0.0f;
    mLandedAnimationShiftY = 0.0f;
    
    
    
}

GameTileMatchable::~GameTileMatchable()
{
    delete mComboTrigger;
    mComboTrigger = 0;
    
    mTwinkleList.Free();
}

void GameTileMatchable::Update()
{
    GameTile::Update();
    
    
    if(mShimmer)
    {
        mShimmerPercent += 0.02f;
        if(mShimmerPercent >= 1.0f)
        {
            mShimmerPercent = 1.0f;
            mShimmer = false;
        }
    }
    
    
    mSquishShiftBounce1 += 6.0f;
    if(mSquishShiftBounce1 >= 360.0f)mSquishShiftBounce1 -= 360.0f;
    
    mSquishShiftBounce2 += 4.0f;
    if(mSquishShiftBounce2 >= 360.0f)mSquishShiftBounce2 -= 360.0f;
    
    if(mLandedAnimation)
    {
        mLandedAnimationSin += mLandedAnimationSinSpeed;
        if(mLandedAnimationSin >= 360.0f)
        {
            mLandedAnimationSin = 0.0f;
            mLandedAnimationBounces++;
            
            if(mLandedAnimationBounces >= 4)
            {
                mLandedAnimationBounces = 0;
                mLandedAnimation = false;
                mLandedAnimationSin = 0.0f;
                mLandedAnimationSinSpeed = 0.0f;
                mLandedAnimationShiftX = 0.0f;
                mLandedAnimationShiftY = 0.0f;
                
            }
            else if(mLandedAnimationBounces == 3)
            {
                mLandedAnimationShiftX = 0.1f;
                mLandedAnimationShiftY = 0.25f;
                mLandedAnimationSinSpeed = 60.0f;
                
            }
            else if(mLandedAnimationBounces == 2)
            {
                mLandedAnimationShiftX = 0.25f;
                mLandedAnimationShiftY = 0.8f;
                mLandedAnimationSinSpeed = 52.0f;
            }
            else
            {
                mLandedAnimationShiftX = 1.20f;
                mLandedAnimationShiftY = 2.0f;
                mLandedAnimationSinSpeed = 40.0f;
            }
            
        }
        
        if(mLandedAnimationBounces >= 5)
        {
            
        }
        
        
    }
    
    

    
    if(mComboTrigger)
    {
        mComboTrigger->mOrbitCenterX = mCenterX;
        mComboTrigger->mOrbitCenterY = mCenterY;
        
        mComboTrigger->mOrbitTargetCenterX = mCenterX;
        mComboTrigger->mOrbitTargetCenterY = mCenterY;
        
        mComboTrigger->Update();
    }
    
    if(mSkipDraw)
    {
        mSkipAnimFrame1 += mSkipAnimFrameSpeed1;
        if(mSkipAnimFrame1 >= mSkipAnimFrameMax1)mSkipAnimFrame1 -= mSkipAnimFrameMax1;
        
        mSkipAnimFrame2 += mSkipAnimFrameSpeed2;
        if(mSkipAnimFrame2 >= mSkipAnimFrameMax2)mSkipAnimFrame2 -= mSkipAnimFrameMax2;
        
        if(mSkipTimerMode == 0)
        {
            mSkipScale += 0.0075f;
            if(mSkipScale >= 1.025f)
            {
                mSkipScale = 1.025f;
                mSkipTimerMode = 1;
            }
        }
        
        mDestroyRumbleShakeAmount += 0.25f;
        if(mDestroyRumbleShakeAmount >= 5.0f)mDestroyRumbleShakeAmount = 5.0f;
        mDestroyRumbleShakeX = gRand.GetFloat(-mDestroyRumbleShakeAmount, mDestroyRumbleShakeAmount);
        mDestroyRumbleShakeY = gRand.GetFloat(-mDestroyRumbleShakeAmount, mDestroyRumbleShakeAmount);
    }
    
    
    //if(gRand.Get(869) == 57)
    if(mSparkleTimer.T())
    {
        FParticle *aParticle = new FParticle();
        
        float aX = gRand.GetFloat(-14.0f, 14.0f);
        float aY = gRand.GetFloat(-22.0f, 22.0f);
        
        /*
         aParticle->SetPos(aX, aY);
         aParticle->SetRotation(-20.0f);
         aParticle->SetScale(0.05f);
         aParticle->mScaleSpeed = 0.36f + gRand.GetFloat(0.03f);
         aParticle->mScaleSpeedAdd = -0.03f;
         aParticle->mRotationSpeed = gRand.GetFloat(2.0f) + 5.25f;
         */
        
        aParticle->SetPos(aX, aY);
        aParticle->SetRotation(-20.0f);
        aParticle->SetScale(0.05f);
        aParticle->mScaleSpeed = 0.20f + gRand.GetFloat(0.02f);
        aParticle->mScaleSpeedAdd = -0.0125f;
        aParticle->mRotationSpeed = gRand.GetFloat(0.5f) + 1.5f;
        
        
        
        mTwinkleList.Add(aParticle);
    }
    
    mTwinkleList.Update();
    
}

void GameTileMatchable::DrawBottom()
{
    if((mSelected == true) && (mDestroyed == false))
    {
        gApp->mTileEggBack[mMatchType].Center(mCenterX, mCenterY);
    }
}

void GameTileMatchable::DrawBottomBuried()
{
    //Graphics::SetColor(0.15f);
    //gApp->mTileBubbleBack[mMatchType][0].Center(mCenterX, mCenterY);
    //Graphics::SetColor(1.0f);
}

void GameTileMatchable::Draw()
{
    
    /*
    if(mDestroyed)
    {
        Graphics::SetColor(0.85f, 0.85f, 0.85f);
        //Graphics::MonocolorEnable();
        
        gApp->mTileEggWhole[mMatchType].Center(mCenterX, mCenterY);
        gApp->mTileEggFrontSelected[mMatchType].Draw(mCenterX, mCenterY, 1.0f, 0.0f);
        
        //Graphics::MonocolorDisable();
        Graphics::SetColor();
        
    }
    else
    {
    */
        if(mSelected == false)
        {
            Graphics::SetColor();
            
            
            
            if(mLandedAnimation)
            {
                float aSin = Sin(mLandedAnimationSin);
                
                float aBounceAmountX = mLandedAnimationShiftX * aSin;
                float aBounceAmountY = mLandedAnimationShiftY * aSin;
                
                
                
                FVec2 aShiftUL = FVec2(aBounceAmountX * 0.2f, aBounceAmountY);
                FVec2 aShiftUR = FVec2(-aBounceAmountX * 0.2f, aBounceAmountY);
                
                FVec2 aShiftDL = FVec2(-aBounceAmountX, (-aBounceAmountY * 0.1f));
                FVec2 aShiftDR = FVec2(aBounceAmountX, (-aBounceAmountY * 0.1f));
                
                gApp->mTileEggBack[mMatchType].DrawShiftedCorners(mCenterX, mCenterY, 1.0f, 0.0f, aShiftUL, aShiftUR, aShiftDL, aShiftDR);
                gApp->mTileEggFront[mMatchType].Draw(mCenterX, mCenterY, 1.0f, 0.0f);
                
                
            }
            else
            {
                gApp->mTileEggWhole[mMatchType].Center(mCenterX, mCenterY);
                
                
            }
            
            Graphics::BlendSetAlpha();
            Graphics::SetColor();
        }
    
    //}
}

void GameTileMatchable::DrawBuried()
{
    Graphics::SetColor(0.85f, 0.85f, 0.85f);
    
    gApp->mTileEggFront[mMatchType].Center(mCenterX, mCenterY);
    
    Graphics::SetColor();
}

void GameTileMatchable::DrawTop()
{
    if((mSelected == true) && (mDestroyed == false))
    {
        Graphics::MonocolorEnable();
        gApp->mTileEggFrontSelected[mMatchType].Draw(mCenterX, mCenterY, 1.0f, 0.0f);
        
        Graphics::MonocolorDisable();
        gApp->mTileEggFront[mMatchType].Draw(mCenterX, mCenterY, 1.0f, 0.0f);
        
        Graphics::SetColor(1.0f);
    }
    
    if(mComboTrigger)mComboTrigger->Draw();
    
    EnumList(FParticle, aParticle, mTwinkleList)
    {
        Graphics::BlendSetAdditive();
        aParticle->DrawOffset(gApp->mEffectTwinkleYellowLarge[0], mCenterX, mCenterY);
        Graphics::BlendSetAlpha();
    }
    
    if(mShimmer)
    {
        Graphics::BlendSetAdditive();
        Graphics::SetColor();
        
        float aScale = Sin(mShimmerPercent * 360.0f) + 1.0f;
        
        gApp->mEffectLightSpinnerLarge[1].Draw(mCenterX, mCenterY, aScale * 0.2f + 0.05f, -20.0f + mShimmerPercent * 16.0f);
        
        Graphics::BlendSetAlpha();
    }
}



void GameTileMatchable::DrawTopBuried()
{
    
}


void GameTileMatchable::DrawSkipAccessoryBottom()
{
    Graphics::BlendSetAdditive();
    float aScale = 0.875f;
    
    Graphics::SetColor(1.0f, 1.0f, 1.0f);
    gApp->mSequenceEffectHilight1.Draw(mSkipAnimFrame1, mCenterX, mCenterY, aScale, 0.0f);
    //gApp->mSequenceEffectHilight2.Draw(mSkipAnimFrame1, mCenterX, mCenterY, aScale, 0.0f);
}

void GameTileMatchable::DrawSkipAccessory()
{
    Graphics::BlendSetAdditive();
    
    float aScale = 0.840f;
    
    Graphics::SetColor(1.0f, 1.0f, 1.0f);
    gApp->mSequenceEffectHilight2.Draw(mSkipAnimFrame1, mCenterX, mCenterY, aScale, 0.0f);
}

void GameTileMatchable::DrawSkipAccessoryTop()
{
    Graphics::BlendSetAlpha();
    Graphics::SetColor();
    
    
    
    /*
    
    if(mSelected == true)
    {
        Graphics::MonocolorEnable();
        gApp->mTileEggFrontSelected[mMatchType].Draw(mCenterX, mCenterY, 1.0f, 0.0f);
        
        Graphics::MonocolorDisable();
        gApp->mTileEggFront[mMatchType].Draw(mCenterX, mCenterY, 1.0f, 0.0f);
        
        Graphics::SetColor(1.0f);
    }
    
    */
    
    //mDestroyRumbleShakeX = gRand.GetFloat(-mDestroyRumbleShakeAmount, mDestroyRumbleShakeAmount);
    //mDestroyRumbleShakeY = gRand.GetFloat(-mDestroyRumbleShakeAmount, mDestroyRumbleShakeAmount);
    
    gApp->mTileEggWhole[mMatchType].Draw (mCenterX + mDestroyRumbleShakeX, mCenterY + mDestroyRumbleShakeY, mSkipScale, 0.0f);
    
    
    
    
}

void GameTileMatchable::SetUp(int pGridX, int pGridY, float pTileWidth, float pTileHeight)
{
    GameTile::SetUp(pGridX, pGridY, pTileWidth, pTileHeight);
    
    if(mComboTrigger)
    {
        mComboTrigger->StartSwirl(pGridX, pGridY, mCenterX, mCenterY);
    }
}

void GameTileMatchable::FallingComplete()
{
    
    mLandedAnimation = true;
    
    mLandedAnimationBounces = 0;
    
    mLandedAnimationSin = 0.0f;
    mLandedAnimationSinSpeed = 36.0f;
    
    mLandedAnimationShiftX = 2.25f;
    mLandedAnimationShiftY = 3.25f;
}

void GameTileMatchable::Destroy(int pDestroyType, int pDestroyTime)
{
    if(mDestroyed == false)
    {
        GameTile::Destroy(pDestroyType, pDestroyTime);
        
        
        mDestroyRumbleShakeAmount = 1.0f;
        
        
        if(pDestroyType == DESTROYED_FROM_GROUP_MATCH)
        {
            //mSkipDraw = true;
            
            
            mSkipAnimFrame1 = gRand.GetFloat(mSkipAnimFrameMax1);
            mSkipAnimFrame2 = gRand.GetFloat(mSkipAnimFrameMax2);
            
            
            mSkipAnimFrameSpeed1 = 0.68f + gRand.GetFloat(0.05f);
            mSkipAnimFrameSpeed2 = 0.68f + gRand.GetFloat(0.05f);
        }
    }
}

void GameTileMatchable::GenerateComboTrigger()
{
    mSpecial = true;
    
    if(mComboTrigger == 0)
    {
        mComboTrigger = new ComboTriggerOrb();
    }
    
}

void GameTileMatchable::SetUpFreshlySpawned()
{
    
}

void GameTileMatchable::Select()
{
    mSelected = true;
}

void GameTileMatchable::Deselect()
{
    mSelected = false;
}

void GameTileMatchable::Shimmer()
{
    mShimmerPercent = 0.0f;
    mShimmer = true;
}








