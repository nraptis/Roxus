//
//  GameTileTreasure.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "GameTileTreasure.h"

GameTileTreasure::GameTileTreasure()
{
    mTileType = GAME_TILE_TYPE_TREASURE;
    
    mSpecialIndex = gRand.Get(3);
    
    mCanReceiveDamage = false;
}

GameTileTreasure::~GameTileTreasure()
{
    
}

void GameTileTreasure::Update()
{
    GameTile::Update();
}

void GameTileTreasure::Draw()
{
    //gApp->mEffectBurstStar7[0].Center(mCenterX, mCenterY);
    
    //mGameTileTreasureBuried[0][0].Center(mCenterX, mCenterY);
    
    if(mSpecialIndex == TREASURE_RANDOM)
    {
        gApp->mGameTilePowerupRandomSmall.Center(mCenterX, mCenterY);
    }
    else
    {
        gApp->mGameTileTreasureBuried[mSpecialIndex][mBackgroundIndex].Center(mCenterX, mCenterY);
    }
    
    
    
}

void GameTileTreasure::DrawTop()
{
    //gApp->mGameTileTreasureBuried[0][0].Center(mCenterX, mCenterY);
    
}








