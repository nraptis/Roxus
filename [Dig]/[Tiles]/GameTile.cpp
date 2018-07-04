//
//  GameTile.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "GameTile.h"

GameTile::GameTile()
{
    mBackgroundIndex = -1;
    mSpecialIndex = -1;
    mBuriedIndex = 0;
    
    mDirt = false;
    
    mToppleEnabled = true;
    
    mTargetCenterX = 0.0f;
    mTargetCenterY = 0.0f;
    mFallSpeed = 0.0f;
    
    mDestroyPoints = 25;
    mDestroyPointsDisplay = false;
    
    mSkipDraw = false;
    
    mRecentlyGenerated = false;
    
    mFalling = false;
    mWasFalling = false;
 
    mDestroyHalt = false;
}

GameTile::~GameTile()
{
    
}

void GameTile::Update()
{
    if(mFalling)
    {
        mFallSpeed += 2.85f;
        mFallSpeed *= 0.975f;
        
        mCenterY += mFallSpeed;
        
        if(mCenterY >= mTargetCenterY)
        {
            mCenterY = mTargetCenterY;
            mFalling = false;
            FallingComplete();
        }
    }
}



void GameTile::DrawBottom()
{
    
}

void GameTile::Draw()
{
    
}

void GameTile::DrawSkipAccessoryBottom()
{
    
}

void GameTile::DrawSkipAccessory()
{
    
}

void GameTile::DrawSkipAccessoryTop()
{
    
}


void GameTile::DrawTop()
{
    
}

void GameTile::FallTo(int pGridY)
{
    mGridY = pGridY;
    mTargetCenterY = (float)pGridY * gTileHeight + (gTileHeight / 2.0f);
    
    //eturn (float)pGridY * mTileHeight + (mTileHeight / 2.0f);
    
    if(mFalling == false)
    {
        mFallSpeed = 3.0f;
        mFalling = true;
        mWasFalling = true;
    }
}

void GameTile::FallingComplete()
{
    
}

BoardGenericTile *GameTile::SpawnPart()
{
    //printf("GameTile::SpawnPart()\n");
    return new GameTile();
}


void GameTile::Save(FXMLTag *pTag)
{
    if(pTag)
    {
        pTag->AddParamInt("grid_x", mGridX);
        pTag->AddParamInt("grid_y", mGridY);
        
        if(mSpecialIndex != -1)pTag->AddParamInt("special_index", mSpecialIndex);
        if(mBackgroundIndex != -1)pTag->AddParamInt("background_index", mBackgroundIndex);
    }
    
}

void GameTile::Load(FXMLTag *pTag)
{
    if(pTag)
    {
        mGridX = pTag->GetParamInt("grid_x");
        mGridY = pTag->GetParamInt("grid_y");
        
        mSpecialIndex = pTag->GetParamInt("special_index");
        mBackgroundIndex = pTag->GetParamInt("background_index");
    }
}


DamageFlashOscillator::DamageFlashOscillator()
{
    
    mDamageSin = 0.0f;
    mDamageSinSpeed = 24.10f;
    
    mDamageFade = 1.0f;
    
    mSinLoopIndex = 0;
    mSinLoopCount = 3;
    
    mActive = false;
    
}

DamageFlashOscillator::~DamageFlashOscillator()
{
    
}

void DamageFlashOscillator::Hit()
{
    mActive = true;
    
    mDamageFade = 1.0f;
    
    mSinLoopIndex = 0;
    mDamageSin = 0.0f;
    
    //DamageFlashOscillator
}

void DamageFlashOscillator::Update()
{
    mDamageSin += mDamageSinSpeed;
    
    if(mDamageSin >= 360.0f)
    {
        mDamageSin -= 360.0f;
        
        mSinLoopIndex++;
        
        if(mSinLoopIndex >= mSinLoopCount)
        {
            //mSinLoopIndex
            
        }
    }
    
    if(mSinLoopIndex >= mSinLoopCount)
    {
        mDamageFade -= 0.15f;
        
        if(mDamageFade <= 0.0f)
        {
            mActive = false;
            mDamageFade = 0.0f;
        }
    }
    
    //mSinLoopCount = 10;
    
}

void DamageFlashOscillator::Draw(FSprite *pSprite, float pCenterX, float pCenterY)
{
    
    if(pSprite)
    {
        //gApp->mTileEggWhole[mMatchType].Center(mCenterX, mCenterY);
    
        //Graphics::MonocolorEnable();
        
        Graphics::BlendSetAdditive();
        
        float aRed = 1.0f;
        float aGreen = 0.0f;//0.3f;
        float aBlue = 0.0f;//0.28f;
        
        float aAlpha = (0.7f + Sin(mDamageSin) * 0.3f) * mDamageFade;
        
        if(aAlpha <= 0.0f)aAlpha = 0.0f;
        if(aAlpha >= 1.0f)aAlpha = 1.0f;
        
        Graphics::SetColor(aRed, aGreen, aBlue, aAlpha);
        
        pSprite->Center(pCenterX, pCenterY);
    
        //Graphics::MonocolorDisable();
        
        Graphics::BlendSetAlpha();
        Graphics::SetColor();
        
    }
}







