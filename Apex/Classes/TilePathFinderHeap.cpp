//
//  TilePathFinderHeap.cpp
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "TilePathFinderHeap.h"


TilePathFinderHeap::TilePathFinderHeap()
{
    mSize = 0;
    mCount = 0;
    mData = 0;
}

TilePathFinderHeap::~TilePathFinderHeap()
{
    delete [] mData;
    mData = 0;
    mSize = 0;
    mCount = 0;
}

void TilePathFinderHeap::Reset()
{
    mCount = 0;
}



void TilePathFinderHeap::Add(GameTileConnection *pConnection)
{
    
    if(mCount == mSize)
    {
        mSize = mSize + mSize / 2 + 1;
        
        GameTileConnection **aData = new GameTileConnection*[mSize];
        
        for(int i=0;i<mCount;i++)aData[i] = mData[i];
        
        delete [] mData;
        mData = aData;
    }
    
    mData[mCount] = pConnection;
    mCount++;
    
}

bool TilePathFinderHeap::Contains(GameTileConnection *pConnection)
{
    bool aReturn = false;
    
    for(int i=0;i<mCount;i++)
    {
        if(mData[i] == pConnection)aReturn = true;
    }
    
    return aReturn;
}

GameTileConnection *TilePathFinderHeap::Pop()
{
    GameTileConnection *aReturn = 0;
    
    int aMinCost = 521849300;
    int aMinIndex = -1;
    
    for(int i=0;i<mCount;i++)
    {
        GameTileConnection *aCheck = mData[i];
        
        if(aCheck->mCostTotal < aMinCost)
        {
            aMinCost = aCheck->mCostTotal;
            aReturn = aCheck;
            aMinIndex = i;
        }
    }
    
    if(aReturn)
    {
        for(int i=(aMinIndex + 1);i<mCount;i++)
        {
            mData[i - 1] = mData[i];
        }
        mCount--;
    }
    
    return aReturn;
    
}










