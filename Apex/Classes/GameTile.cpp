//
//  GameTile.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "GameTile.h"
#include "GameArena.h"

GameTileConnection::GameTileConnection() {
    Reset();
}

GameTileConnection::~GameTileConnection() { }

void GameTileConnection::Reset() {
    mTile = 0;
    mParent = 0;
    mCost = 0;
    mCostG = 0;
    mCostH = 0;
    mCostTotal = 0;
}




GameTile::GameTile() {
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

GameTile::~GameTile() { }

void GameTile::SetUp(int pGridX, int pGridY, int pGridZ) {
    mGridX = pGridX;
    mGridY = pGridY;
    mGridZ = pGridZ;
    mCenterX = CX(pGridX, pGridZ);// (float)pGridX * gTileSize + (gTileSize / 2.0f);
    mCenterY = CY(pGridY, pGridZ);//(float)pGridY * gTileSize + (gTileSize / 2.0f);
}

void GameTile::Update() {
    
}

void GameTile::Draw() {

    FSprite *aAccessory = 0;
    FSprite *aTile = 0;

    if (mType == TILE_TYPE_BLOCKED) { aAccessory = &gApp->mBlocker; }
    if (mGridZ == 0) {
        aTile = &gApp->mTileTunnel;
    }
    if (mGridZ == 1) {
        aTile = &gApp->mTileFloor;
        if(mType == TILE_TYPE_RAMP_U) { aAccessory = &gApp->mFloorRampU; }
        if(mType == TILE_TYPE_RAMP_D) { aAccessory = &gApp->mFloorRampD; }
        if(mType == TILE_TYPE_RAMP_L) { aAccessory = &gApp->mFloorRampL; }
        if(mType == TILE_TYPE_RAMP_R) { aAccessory = &gApp->mFloorRampR; }
    }
    if (mGridZ == 2) {
        aTile = &gApp->mTileBridge;
        if(mType == TILE_TYPE_RAMP_U) { aAccessory = &gApp->mBridgeRampU; }
        if(mType == TILE_TYPE_RAMP_D) { aAccessory = &gApp->mBridgeRampD; }
        if(mType == TILE_TYPE_RAMP_L) { aAccessory = &gApp->mBridgeRampL; }
        if(mType == TILE_TYPE_RAMP_R) { aAccessory = &gApp->mBridgeRampR; }
    }

    float aDrawX = CX(mGridX, mGridZ);
    if (IsRamp()) {
        if (aAccessory) {
            aAccessory->Center(aDrawX, CY(mGridY, 1));
        }
    } else {
        if (aTile) {
            aTile->Center(aDrawX, CY(mGridY, 1));
        }
        if (aAccessory) {
            aAccessory->Center(aDrawX, CY(mGridY, mGridZ));
        }
    }



    /*
    float aBoxSize = 2.0f;
    Graphics::DrawRect(mCenterX - gTileSize / 2.0f, mCenterY - gTileSize / 2.0f, aBoxSize, gTileSize);
    Graphics::DrawRect(mCenterX + gTileSize / 2.0f - aBoxSize, mCenterY - gTileSize / 2.0f, aBoxSize, gTileSize);
    Graphics::DrawRect(mCenterX - gTileSize / 2.0f, mCenterY - gTileSize / 2.0f, gTileSize, aBoxSize);
    Graphics::DrawRect(mCenterX - gTileSize / 2.0f, mCenterY + gTileSize / 2.0f - aBoxSize, gTileSize, aBoxSize);
    */
}

void GameTile::DrawConnections() {
    for (int i=0;i<mPathConnectionCount;i++) {
        if (mPathConnection[i].mTile) {
            Graphics::DrawArrow(mCenterX, mCenterY, mPathConnection[i].mTile->mCenterX, mPathConnection[i].mTile->mCenterY);
        }
    }
}

bool GameTile::IsBlocked() {
    bool aResult = false;
    if(mBlocked)aResult = true;
    if(mOccupied)aResult = true;
    if(mType == TILE_TYPE_BLOCKED)aResult = true;
    return aResult;
}

bool GameTile::IsNormal() {
    bool aResult = true;
    if(IsBlocked())aResult = false;
    if(mType != TILE_TYPE_NORMAL)aResult = false;
    return aResult;
}

bool GameTile::IsRamp() {
    bool aResult = false;
    if (mType == TILE_TYPE_RAMP_U) aResult = true;
    if (mType == TILE_TYPE_RAMP_R) aResult = true;
    if (mType == TILE_TYPE_RAMP_D) aResult = true;
    if (mType == TILE_TYPE_RAMP_L) aResult = true;
    return aResult;
}

void GameTile::ConnectTo(GameTile *pTile, int pCost) {
    if (IsBlocked() == false && pTile != 0) {
        if (pTile->IsBlocked() == false && mPathConnectionCount < TILE_CONNECTION_COUNT) {
            mPathConnection[mPathConnectionCount].mTile = pTile;
            mPathConnection[mPathConnectionCount].mCost = pCost;
            mPathConnectionCount++;
        }
    }
}

void GameTile::PathReset() {
    mOccupied = false;
    for (int i=0;i<TILE_CONNECTION_COUNT;i++) {
        mPathConnection[i].Reset();
        mPathConnection[i].mTile = this;
    }
    mPathConnectionCount = 0;
}

bool GameTile::PlacementAllowed() {
    bool aResult = false;
    if (mType == TILE_TYPE_NORMAL) {
        if (mBlocked == false) {
            aResult = true;
        }
    }
    return aResult;
}

FXMLTag *GameTile::Save() {
    FXMLTag *aTag = new FXMLTag("tile");
    aTag->AddParam("grid_x", FString(mGridX).c());
    aTag->AddParam("grid_y", FString(mGridY).c());
    aTag->AddParam("grid_z", FString(mGridZ).c());
    aTag->AddParam("type", FString(mType).c());
    return aTag;
}

void GameTile::Load(FXMLTag *pTag) {
    if (pTag) {
        mGridX = FString(pTag->GetParamValue("grid_x")).ToInt();
        mGridY = FString(pTag->GetParamValue("grid_y")).ToInt();
        mGridZ = FString(pTag->GetParamValue("grid_z")).ToInt();
        mType = FString(pTag->GetParamValue("type")).ToInt();
    }
    SetUp(mGridX, mGridY, mGridZ);
}
