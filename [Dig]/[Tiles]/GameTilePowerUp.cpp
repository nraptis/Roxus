//
//  GameTilePowerUp.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/28/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "GameTilePowerUp.h"

GameTilePowerUp::GameTilePowerUp()
{
    mTileType = GAME_TILE_TYPE_POWERUP;
    
    mCanReceiveDamage = false;
}

GameTilePowerUp::~GameTilePowerUp()
{
    
}

void GameTilePowerUp::Update()
{
    GameTile::Update();
}

void GameTilePowerUp::Draw()
{
    gApp->mGameTilePowerupBack.Center(mCenterX, mCenterY);
    gApp->mGameTilePowerupGenericBuried.Center(mCenterX, mCenterY);
    
    if(mSpecialIndex == TREASURE_RANDOM)// || (mSpecialIndex == POWERUP_RANDOM_SMALL))
    {
        //gApp->mGameTileTreasureRandomLarge.Center(mCenterX, mCenterY);
    }
    
}

void GameTilePowerUp::DrawBuried()
{
    //gApp->mGameTilePowerupGenericBuried.Load("powerup_bomb_buried");
    
    //gApp->mGameTileTreasureBuried[0][0].Center(mCenterX, mCenterY);
    
    gApp->mGameTilePowerupGenericBuried.Center(mCenterX, mCenterY);
    
}
