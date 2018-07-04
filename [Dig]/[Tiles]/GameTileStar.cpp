//
//  GameTileStar.cpp
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "GameTileStar.h"
#include "core_includes.h"

GameTileStar::GameTileStar()
{
    mTileType = GAME_TILE_TYPE_STAR;
    
    AddPart(0,1);
    AddPart(1,0);
    AddPart(1,1);
    
    mStarIndex = gRand.Get(3);
    
    mOffsetX = gTileWidth2;
    mOffsetY = gTileHeight2;
}

GameTileStar::~GameTileStar()
{
    
}

void GameTileStar::Update()
{
    GameTile::Update();
}

void GameTileStar::Draw()
{

    gApp->mGameTileLevelStarBuried[mStarIndex].Draw(mCenterX + mOffsetX, mCenterY + mOffsetY, 1.0f, 0.0f);
    

    //gApp->mFontMovesRemaining.Center(FString(mStarIndex).c(), mCenterX, mCenterY);
}

void GameTileStar::Save(FXMLTag *pTag)
{
    if(pTag)
    {
        GameTile::Save(pTag);
        
        pTag->AddParamInt("star_index", mStarIndex);
    }
}

void GameTileStar::Load(FXMLTag *pTag)
{
    if(pTag)
    {
        GameTile::Load(pTag);
        
        mStarIndex = pTag->GetParamInt("star_index");
    }
    
}

