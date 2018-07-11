//
//  TilePathFinder.cpp
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "TilePathFinder.h"



TilePathFinder::TilePathFinder()
{
    mPathStart = new GameTileConnection();
    mPathEnd = 0;
}

TilePathFinder::~TilePathFinder()
{
    delete mPathStart;
    mPathStart = 0;
    mPathEnd = 0;
}

bool TilePathFinder::FindPath(GameTile *pStart, GameTile *pEnd)
{
    bool aReturn = false;
    
    mOpenList.Reset();
    mClosedList.Reset();
    
    mPathEnd = 0;
    
    if(pStart != 0 && pEnd != 0)
    {
        int aEndX = pEnd->mGridX;
        int aEndY = pEnd->mGridY;
        int aEndZ = pEnd->mGridZ;
        
        GameTile *aTile = 0;
        GameTileConnection *aConnection = 0;
        
        GameTileConnection *aCurrent = mPathStart;
        
        aCurrent->mTile = pStart;
        aCurrent->mParent = 0;
        
        int aDiffX = pStart->mGridX - aEndX;
        if(aDiffX < 0)aDiffX = -aDiffX;
        
        int aDiffY = pStart->mGridX - aEndY;
        if(aDiffY < 0)aDiffY = -aDiffY;
        
        aCurrent->mParent = 0;
        
        aCurrent->mCostH = (aDiffX + aDiffY) * 100;
        aCurrent->mCostG = 0;
        aCurrent->mCostTotal = aCurrent->mCostH + aCurrent->mCostG;
        
        mOpenList.Add(aCurrent);
        
        while (mOpenList.mCount > 0) {
            aCurrent = mOpenList.Pop();
            mClosedList.Add(aCurrent);
            aTile = aCurrent->mTile;
            if(aTile->mGridX == aEndX && aTile->mGridY == aEndY && aTile->mGridZ == aEndZ) {
                mPathEnd = aCurrent;
                break;
            } else {
                for (int k=0;k<aTile->mPathConnectionCount;k++) {
                    aConnection = &(aTile->mPathConnection[k]);
                    int aCostG = aCurrent->mCostG + aConnection->mCost;
                    //TODO: Speed-up this lookup.
                    if (mClosedList.Contains(aConnection) && aCostG >= aConnection->mCostG) { continue; }
                    bool aOpenListContains = mOpenList.Contains(aConnection);
                    if ((aOpenListContains == false) || (aCostG < aConnection->mCostG)) {
                        aConnection->mParent = aCurrent;
                        aConnection->mCostG = aCostG;
                        aDiffX = aConnection->mTile->mGridX - aEndX;
                        if (aDiffX < 0) { aDiffX = -aDiffX; }
                        aDiffY = aConnection->mTile->mGridY - aEndY;
                        if (aDiffY < 0) { aDiffY = -aDiffY; }
                        aConnection->mCostH = (aDiffX + aDiffY) * 100;
                        aConnection->mCostTotal = aConnection->mCostH + aConnection->mCostG;
                        if (aOpenListContains == false) {
                            mOpenList.Add(aConnection);
                        }
                    }
                }
            }
        }
    }
    return aReturn;
}


