//
//  GameTile.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "GameTile.h"
#include "GameArena.h"
#include "Game.h"

GameTileConnection::GameTileConnection()
{
    Reset();
}

GameTileConnection::~GameTileConnection()
{
    
}


void GameTileConnection::Reset()
{
    mTile = 0;
    mParent = 0;
    
    mCost = 0;
    
    mCostG = 0;
    mCostH = 0;
    mCostTotal = 0;
}




GameTile::GameTile()
{
    mApp = GAPP;
    
    mGridX = -1;
    mGridY = -1;
    mGridZ = -1;
    
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    
    mType = TILE_TYPE_NORMAL;
    
    mPathConnectionCount = 0;
    
    mBlocked = false;
    mOccupied = false;
    
    PathReset();
}

GameTile::~GameTile()
{
    
}

void GameTile::SetUp(int pGridX, int pGridY, int pGridZ)
{
    mGridX = pGridX;
    mGridY = pGridY;
    mGridZ = pGridZ;
    
    mCenterX = CX(pGridX, pGridZ);// (float)pGridX * gTileWidth + (gTileWidth / 2.0f);
    mCenterY = CY(pGridY, pGridZ);//(float)pGridY * gTileHeight + (gTileHeight / 2.0f);
    
    
}

void GameTile::Update()
{
    
}

void GameTile::Draw()
{
    FSprite *aAccessory = 0;
    FSprite *aTile = 0;
    
    
    
    if(mType == TILE_TYPE_BLOCKED)aAccessory = &mApp->mBlocker;
    
    if(mGridZ == 0)
    {
        aTile = &mApp->mTileTunnel;
    }
    if(mGridZ == 1)
    {
        aTile = &mApp->mTileFloor;
        
        if(mType == TILE_TYPE_RAMP_U)aAccessory = &mApp->mFloorRampU;
        if(mType == TILE_TYPE_RAMP_D)aAccessory = &mApp->mFloorRampD;
        if(mType == TILE_TYPE_RAMP_L)aAccessory = &mApp->mFloorRampL;
        if(mType == TILE_TYPE_RAMP_R)aAccessory = &mApp->mFloorRampR;
    }
    if(mGridZ == 2)
    {
        aTile = &mApp->mTileBridge;

        if(mType == TILE_TYPE_RAMP_U)aAccessory = &mApp->mBridgeRampU;
        if(mType == TILE_TYPE_RAMP_D)aAccessory = &mApp->mBridgeRampD;
        if(mType == TILE_TYPE_RAMP_L)aAccessory = &mApp->mBridgeRampL;
        if(mType == TILE_TYPE_RAMP_R)aAccessory = &mApp->mBridgeRampR;
    }
    
    float aDrawX = CX(mGridX);
    float aDrawY = CY(mGridY);
    
    if(aAccessory)
    {
        aAccessory->Center(aDrawX, aDrawY);
    }
    else
    {
        if(aTile)
        {
            aTile->Center(aDrawX, aDrawY);
        }
    }
    
    
    
    
    
    float aBoxSize = 2.0f;
    
    //DrawRect(mCenterX - gTileWidth / 2.0f, mCenterY - gTileHeight / 2.0f, aBoxSize, gTileHeight);
    //DrawRect(mCenterX + gTileWidth / 2.0f - aBoxSize, mCenterY - gTileHeight / 2.0f, aBoxSize, gTileHeight);
    //DrawRect(mCenterX - gTileWidth / 2.0f, mCenterY - gTileHeight / 2.0f, gTileWidth, aBoxSize);
    //DrawRect(mCenterX - gTileWidth / 2.0f, mCenterY + gTileHeight / 2.0f - aBoxSize, gTileWidth, aBoxSize);
    
}

void GameTile::DrawConnections()
{
    for(int i=0;i<mPathConnectionCount;i++)
    {
        if(mPathConnection[i].mTile)
        {
            Graphics::DrawArrow(mCenterX, mCenterY, mPathConnection[i].mTile->mCenterX, mPathConnection[i].mTile->mCenterY);
        }
    }
}

bool GameTile::IsBlocked()
{
    bool aReturn = false;
    
    if(mBlocked)aReturn = true;
    if(mOccupied)aReturn = true;
    
    if(mType == TILE_TYPE_BLOCKED)aReturn = true;
    
    return aReturn;
}

bool GameTile::IsNormal()
{
    bool aReturn = true;
    
    if(IsBlocked())aReturn = false;
    if(mType != TILE_TYPE_NORMAL)aReturn = false;
    
    return aReturn;
}

void GameTile::ConnectTo(GameTile *pTile, int pCost)
{
    if(IsBlocked() == false)
    {
        if(pTile)
        {
            if(pTile->IsBlocked() == false)
            {
                if(mPathConnectionCount < TILE_CONNECTION_COUNT)
                {
                    mPathConnection[mPathConnectionCount].mTile = pTile;
                    mPathConnection[mPathConnectionCount].mCost = pCost;
                    
                    mPathConnectionCount++;
                }
            }
        }
    }
}

void GameTile::PathReset()
{
    mOccupied = false;
    
    for(int i=0;i<TILE_CONNECTION_COUNT;i++)
    {
        mPathConnection[i].Reset();
        mPathConnection[i].mTile = this;
    }
    
    mPathConnectionCount = 0;
}

bool GameTile::PlacementAllowed()
{
    bool aReturn = false;
    
    if(mType == TILE_TYPE_NORMAL)
    {
        if(mBlocked == false)
        {
            aReturn = true;
        }
    }
    
    return aReturn;
}

FXMLTag *GameTile::Save()
{
    
    FXMLTag *aTag = new FXMLTag("tile");
    
    aTag->AddParam("grid_x", FString(mGridX).c());
    aTag->AddParam("grid_y", FString(mGridY).c());
    aTag->AddParam("grid_z", FString(mGridZ).c());
    
    aTag->AddParam("type", FString(mType).c());
    
    return aTag;
}

void GameTile::Load(FXMLTag *pTag)
{
    if(pTag)
    {
        mGridX = FString(pTag->GetParamValue("grid_x")).ToInt();
        mGridY = FString(pTag->GetParamValue("grid_y")).ToInt();
        mGridZ = FString(pTag->GetParamValue("grid_z")).ToInt();
        
        mType = FString(pTag->GetParamValue("type")).ToInt();
    }
    
    SetUp(mGridX, mGridY, mGridZ);
}
