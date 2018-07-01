//
//  Tile.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/12/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#include "Tile.h"
#include "GLApp.h"

Tile::Tile()
{
    mType = TILE_TYPE_UNKNOWN;
    
    mGridX = -1;
    mGridY = -1;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mKill = 0;
    
    
    mSelected = false;
    mMatched = false;
    
    mNew = true;
    
    mFallTargetY = 0.0f;
    mFallSpeed = 0.0f;
    
    mFalling = false;
    
    mMultiTile = false;
    mMultiTilePart = false;
    
    mFlag1 = false;
    mFlag2 = false;
    
    mFlagU = false;
    mFlagR = false;
    mFlagD = false;
    mFlagL = false;
}

Tile::~Tile()
{
    
}

void Tile::Update()
{
    if(mFalling)
    {
        mFallSpeed += 2.85f;
        mFallSpeed *= 0.975f;
        
        //mFallSpeed += 1.0f;
        //mFallSpeed *= 0.965f;
        
        mY += mFallSpeed;
        
        if(mY >= mFallTargetY)
        {
            mY = mFallTargetY;
            mFalling = false;
        }
    }
}

void Tile::Draw(){
    
}

void Tile::DrawBuried(){
    
    //gApp->mTileGem.Draw(mX, mY, 0.5f, 0.0f);
    
    
}

void Tile::DrawEffectsUnder(int pDepth)
{
    
}

void Tile::DrawEffectsOver(int pDepth)
{
    
    if(pDepth == 0){
        if(mFlag1){
            gApp->mGIItemBack.Draw(mX, mY, 0.25, 40.0f);
        }
        if(mFlag2){
            gApp->mGIItemLock.Draw(mX, mY, 1.0f, 180.0f);
        }
        
        Graphics::SetColor(0.88f, 0.75f, 0.15f, 1.0f);
        
        if(mFlagU)Graphics::DrawArrow(mX, mY, mX, mY - 40);
        if(mFlagR)Graphics::DrawArrow(mX, mY, mX + 40, mY);
        if(mFlagD)Graphics::DrawArrow(mX, mY, mX, mY + 40);
        if(mFlagL)Graphics::DrawArrow(mX, mY, mX - 40, mY);
        
        Graphics::SetColor();
        
    }
}

void Tile::SetUp(int pGridX, int pGridY)
{
    mGridX = pGridX;
    mGridY = pGridY;
    
    mX = ((float)mGridX) * gTileWidth + gTileWidth / 2.0f;
    mY = ((float)mGridY) * gTileHeight + gTileHeight / 2.0f;
}

void Tile::FallTo(int pGridY)
{
    mGridY = pGridY;
    mFallTargetY = (float)pGridY * gTileHeight + (gTileHeight / 2.0f);
    
    //eturn (float)pGridY * mTileHeight + (mTileHeight / 2.0f);
    
    if(mFalling == false)
    {
        mFallSpeed = 3.0f;
        mFalling = true;
    }
}




