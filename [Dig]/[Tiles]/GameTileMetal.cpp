//
//  GameTileMetal.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "GameTileMetal.h"

GameTileMetal::GameTileMetal()
{
    mTileType = GAME_TILE_TYPE_METAL;
    
    mCanReceiveDamage = true;
    mHP = 8;
    
    mBuriedIndex = gRand.Get(2);
}

GameTileMetal::~GameTileMetal()
{
    
}

void GameTileMetal::Update()
{
    GameTile::Update();
    
    if(mDamageFlash.mActive)
    {
        mDamageFlash.Update();
    }
}

void GameTileMetal::Draw()
{
    Graphics::SetColor();
    gApp->mGameTileMetal[8 - mHP].Center(mCenterX, mCenterY);
}

void GameTileMetal::DrawBuried()
{
    //gApp->mGameTileMetalBuried[8 - mHP][mBuriedIndex].Center(mCenterX, mCenterY);
    gApp->mGameTileMetalBuried[8 - mHP][mBuriedIndex].Center(mCenterX, mCenterY);
}


