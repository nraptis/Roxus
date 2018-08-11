//
//  GameTile.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/15/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "GameTile.hpp"
#include "GameArena.hpp"

GameTile::GameTile() {
    mTileType = TILE_TYPE_NORMAL;
    mDisabled = false;
    ResetGrid();

    mTop = 0.0f;
    mRight = 0.0f;
    mBottom = 0.0f;
    mLeft = 0.0f;
}

GameTile::~GameTile() { }

void GameTile::ResetGrid() {
    for (int aGridX = 0;aGridX<(SUBDIVISIONS_PER_TILE + 1);aGridX++) {
        for (int aGridY = 0;aGridY<(SUBDIVISIONS_PER_TILE + 1);aGridY++) {
            mGrid[aGridX][aGridY] = 0;
        }
    }
}

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

    if (mDisabled) {
        return;
    }

    FSprite *aAccessory = 0;
    FSprite *aTile = 0;

    if (mTileType == TILE_TYPE_BLOCKED) { aAccessory = &gApp->mBlocker; }
    if (mGridZ == 0) {
        aTile = &gApp->mTileTunnel;
    }
    if (mGridZ == 1) {
        aTile = &gApp->mTileFloor;
        if(mTileType == TILE_TYPE_RAMP_U) { aAccessory = &gApp->mFloorRampU; }
        if(mTileType == TILE_TYPE_RAMP_D) { aAccessory = &gApp->mFloorRampD; }
        if(mTileType == TILE_TYPE_RAMP_L) { aAccessory = &gApp->mFloorRampL; }
        if(mTileType == TILE_TYPE_RAMP_R) { aAccessory = &gApp->mFloorRampR; }
    }
    if (mGridZ == 2) {
        aTile = &gApp->mTileBridge;
        if(mTileType == TILE_TYPE_RAMP_U) { aAccessory = &gApp->mBridgeRampU; }
        if(mTileType == TILE_TYPE_RAMP_D) { aAccessory = &gApp->mBridgeRampD; }
        if(mTileType == TILE_TYPE_RAMP_L) { aAccessory = &gApp->mBridgeRampL; }
        if(mTileType == TILE_TYPE_RAMP_R) { aAccessory = &gApp->mBridgeRampR; }
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

bool GameTile::IsBlocked() {
    bool aResult = PathNode::IsBlocked();
    if (mTileType == TILE_TYPE_BLOCKED) { aResult = true; }
    return aResult;
}

bool GameTile::IsNormal() {
    bool aResult = true;
    if (IsBlocked()) { aResult = false; }
    if (mTileType != TILE_TYPE_NORMAL) { aResult = false; }
    return aResult;
}

bool GameTile::IsRamp() {
    bool aResult = false;
    if (mTileType == TILE_TYPE_RAMP_U) { aResult = true; }
    if (mTileType == TILE_TYPE_RAMP_R) { aResult = true; }
    if (mTileType == TILE_TYPE_RAMP_D) { aResult = true; }
    if (mTileType == TILE_TYPE_RAMP_L) { aResult = true; }
    return aResult;
}

bool GameTile::PlacementAllowed() {
    bool aResult = false;
    if (mTileType == TILE_TYPE_NORMAL) {
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
    aTag->AddParam("type", FString(mTileType).c());
    return aTag;
}

void GameTile::Load(FXMLTag *pTag) {
    if (pTag) {
        mGridX = FString(pTag->GetParamValue("grid_x")).ToInt();
        mGridY = FString(pTag->GetParamValue("grid_y")).ToInt();
        mGridZ = FString(pTag->GetParamValue("grid_z")).ToInt();
        mTileType = FString(pTag->GetParamValue("type")).ToInt();
    }
    SetUp(mGridX, mGridY, mGridZ);
}
