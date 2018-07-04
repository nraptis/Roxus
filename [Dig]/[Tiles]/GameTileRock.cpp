//
//  GameTileRock.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "GameTileRock.h"

GameTileRock::GameTileRock()
{
    mTileType = GAME_TILE_TYPE_ROCK;
    
    mCanReceiveDamage = true;
    mHP = 3;
}

GameTileRock::~GameTileRock()
{
    
}

void GameTileRock::Update()
{
    GameTile::Update();
    
    if(mDamageFlash.mActive)
    {
        mDamageFlash.Update();
    }
}

void GameTileRock::Draw()
{
    Graphics::SetColor();
    
    gApp->mGameTileRockBuried.Center(mCenterX, mCenterY);
    
    if(mHP <= 1)
    {
        gApp->mGameTileRockCracked[1].Center(mCenterX, mCenterY);
    }
    else if(mHP <= 2)
    {
        gApp->mGameTileRockCracked[0].Center(mCenterX, mCenterY);
    }
    else
    {
        gApp->mGameTileRock.Center(mCenterX, mCenterY);
    }
    
    if(mDamageFlash.mActive)
    {
        mDamageFlash.Draw(&(gApp->mGameTileRock), mCenterX, mCenterY);
        
    }
}

void GameTileRock::DrawBuried()
{
    gApp->mGameTileRockBuried.Center(mCenterX, mCenterY);
    
}


