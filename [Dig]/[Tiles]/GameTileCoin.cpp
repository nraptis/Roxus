//
//  GameTileCoin.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "GameTileCoin.h"

GameTileCoin::GameTileCoin()
{
    mTileType = GAME_TILE_TYPE_COIN;
    mValue = 25;
    
    mSpecialIndex = gRand.Get(3);
    
    mCanReceiveDamage = false;
    
    mDirt = true;
    
    mRotation = gRand.Rot();
}

GameTileCoin::~GameTileCoin()
{
    
}

void GameTileCoin::Update()
{
    GameTile::Update();
    
    //mRotation += 2.0f;
    //if(mRotation >= 360.0f)mRotation -= 360.0f;
}

void GameTileCoin::Draw()
{
    Graphics::SetColor(0.5f, 0.5f, 0.75f, 0.15f);
    Graphics::DrawRect((mCenterX - gTileWidth2) + 6.0f, (mCenterY - gTileHeight2) + 6.0f, gTileWidth - 12.0f, gTileHeight - 12.0f);
    
    Graphics::SetColor();
    gApp->mSequenceCoinSpin[0].Draw(0, mCenterX, mCenterY, 1.25f, mRotation);
}

void GameTileCoin::DrawTop()
{
    
}






