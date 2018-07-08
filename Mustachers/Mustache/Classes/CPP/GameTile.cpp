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

GameTile::GameTile()
{
    mApp = GAPP;
    
    mGridX = -1;
    mGridY = -1;
    
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    
    mType = 0;
    
    mBlocked = false;
    
    mTunnelU = true;
    mTunnelD = true;
    mTunnelL = true;
    mTunnelR = true;
    
    mBridgeU = false;
    mBridgeD = false;
    mBridgeL = false;
    mBridgeR = false;
    
}

GameTile::~GameTile()
{
    
}

void GameTile::SetUp(int pType, int pGridX, int pGridY)
{
    mType = pType;
    
    SetUp(pGridX, pGridY);
}

void GameTile::SetUp(int pGridX, int pGridY)
{
    mCenterX = CX(pGridX);// (float)pGridX * gTileWidth + (gTileWidth / 2.0f);
    mCenterY = CY(pGridY);//(float)pGridY * gTileHeight + (gTileHeight / 2.0f);
    
    mGridX = pGridX;
    mGridY = pGridY;
}

void GameTile::Update()
{
    
}

void GameTile::Draw()
{
    mApp->mTile.Draw(mCenterX, mCenterY, 1.0f, 0.0f);
}

XMLTag *GameTile::Save()
{
    
    XMLTag *aTag = new XMLTag("game_tile");
    
    aTag->AddParam("grid_x", FString(mGridX).c());
    aTag->AddParam("grid_y", FString(mGridY).c());
    
    aTag->AddParam("blocked", mBlocked ? "true" : "false");
    
    aTag->AddParam("tunnel_u", mTunnelU ? "true" : "false");
    aTag->AddParam("tunnel_d", mTunnelD ? "true" : "false");
    aTag->AddParam("tunnel_l", mTunnelL ? "true" : "false");
    aTag->AddParam("tunnel_r", mTunnelR ? "true" : "false");
    
    aTag->AddParam("bridge_u", mBridgeU ? "true" : "false");
    aTag->AddParam("bridge_d", mBridgeD ? "true" : "false");
    aTag->AddParam("bridge_l", mBridgeL ? "true" : "false");
    aTag->AddParam("bridge_r", mBridgeR ? "true" : "false");
    
    return aTag;
}

void GameTile::Load(XMLTag *pTag)
{
    if(pTag)
    {
        mGridX = FString(pTag->GetParamValue("grid_x")).ToInt();
        mGridY = FString(pTag->GetParamValue("grid_y")).ToInt();
        
        mBlocked = FString (pTag->GetParamValue("blocked")).ToBool();
        
        mTunnelU = FString (pTag->GetParamValue("tunnel_u")).ToBool();
        mTunnelD = FString (pTag->GetParamValue("tunnel_d")).ToBool();
        mTunnelL = FString (pTag->GetParamValue("tunnel_l")).ToBool();
        mTunnelR = FString (pTag->GetParamValue("tunnel_r")).ToBool();
        
        mBridgeU = FString (pTag->GetParamValue("bridge_u")).ToBool();
        mBridgeD = FString (pTag->GetParamValue("bridge_d")).ToBool();
        mBridgeL = FString (pTag->GetParamValue("bridge_l")).ToBool();
        mBridgeR = FString (pTag->GetParamValue("bridge_r")).ToBool();
                            
    }
    
    SetUp(mGridX, mGridY);
    
}
