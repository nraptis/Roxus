//
//  BoardGenericTile.cpp
//  Bone
//
//  Created by Nick Raptis on 8/6/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#include "BoardGenericTile.h"
#include "core_includes.h"

BoardGenericTile::BoardGenericTile()
{
    mInitialized = false;
    
    mTimerDelete = 15;
    
    mGridX = -1;
    mGridY = -1;
    
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    
    mWidth = 80.0f;
    mHeight = 80.0f;
    
    mOffsetX = 0.0;
    mOffsetY = 0.0;
    
    mMulti = false;
    
    mTileType = -1;
    mMatchType = -1;
    
    
    mDestroyTimer = 0;
    mDestroyTypeIndex = 0;
    
    //mCanReceiveDamage = true;
    mCanReceiveDamage = false;
    
    mDestroyed = false;
    mDestroyRealized = false;
    
    mHP = 1;
    
    mMultiPart = false;
    mMultiPartParent = 0;
    
    mMultiPartGridOffsetX = 0;
    mMultiPartGridOffsetY = 0;
    
    
    mMulti = false;
    
    mMultiPartCount = 0;
    mMultiPartList = 0;
}

BoardGenericTile::~BoardGenericTile()
{
    
}

void BoardGenericTile::Update()
{
    
}


void BoardGenericTile::Draw()
{
    Graphics::SetColorSwatch(mMatchType);
    Graphics::DrawRect(mCenterX - mWidth / 2.0f + mOffsetX, mCenterY - mHeight / 2.0f + mOffsetX, mWidth, mHeight);
    
    Graphics::SetColor();
    
    
}


void BoardGenericTile::SetUp(int pGridX, int pGridY, float pTileWidth, float pTileHeight)
{
    mGridX = pGridX;
    mGridY = pGridY;
    
    mCenterX = ((float)mGridX) * pTileWidth + pTileWidth / 2.0f;
    mCenterY = ((float)mGridY) * pTileHeight + pTileHeight / 2.0f;
}

BoardGenericTile *BoardGenericTile::SpawnPart()
{
    return new BoardGenericTile();
}

void BoardGenericTile::AddPart(int pOffsetX, int pOffsetY)
{
    BoardGenericTile *aPart = SpawnPart();
    
    if(aPart)
    {
        aPart->mMultiPartGridOffsetX = pOffsetX;
        aPart->mMultiPartGridOffsetY = pOffsetY;
        
        aPart->mMultiPart = true;
        aPart->mMultiPartParent = this;
        
    
        BoardGenericTile **aMultiPartList = new BoardGenericTile*[mMultiPartCount + 1];
    
        for(int i=0;i<mMultiPartCount;i++)
        {
            aMultiPartList[i] = mMultiPartList[i];
        }
    
        delete [] mMultiPartList;
        mMultiPartList = aMultiPartList;
    
        mMultiPartList[mMultiPartCount] = aPart;
    
        mMultiPartCount++;
        mMulti = true;
        
    }
}

void BoardGenericTile::Destroy(int pDestroyType, int pDestroyTime)
{
    mDestroyTypeIndex = pDestroyType;
    mDestroyTimer = pDestroyTime;
    mDestroyed = true;
}

bool BoardGenericTile::CanReceiveDamage(int pDamageType)
{
    return mCanReceiveDamage;
}

bool BoardGenericTile::Damage(int pDamage)
{
    bool aReturn = false;
    
    if(mDestroyed == false)
    {
        mHP -= pDamage;
        
        if(mHP <= 0)
        {
            mHP = 0;
            
            aReturn = true;
            
            mDestroyed = true;
        }
    }
    
    return aReturn;
}
