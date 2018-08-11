//
//  TilePathFinder.cpp
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "TilePathFinder.h"

TilePathFinder::TilePathFinder() {
    mPathStart = new PathNodeConnection();
    mPathEnd = 0;
}

TilePathFinder::~TilePathFinder() {
    delete mPathStart;
    mPathStart = 0;
    mPathEnd = 0;
}


bool TilePathFinder::FindPath(PathNode *pStart, PathNode *pEnd) {
    bool aResult = false;

    printf("Pathing From [%d %d %d] => [%d %d %d]\n", pStart->mGridX, pStart->mGridY, pStart->mGridZ, pEnd->mGridX, pEnd->mGridY, pEnd->mGridZ);

    mOpenList.Reset();
    mClosedList.Reset();
    
    mPathEnd = 0;
    int aPathLoops = 0;


    if (pStart != 0 && pEnd != 0) {
        int aEndX = pEnd->mGridX;
        int aEndY = pEnd->mGridY;
        int aEndZ = pEnd->mGridZ;

        PathNode *aNode = 0;
        PathNodeConnection *aConnection = 0;
        PathNodeConnection *aCurrent = mPathStart;

        aCurrent->mNode = pStart;
        aCurrent->mPathParent = 0;
        
        int aDiffX = pStart->mGridX - aEndX;
        if(aDiffX < 0)aDiffX = -aDiffX;
        
        int aDiffY = pStart->mGridX - aEndY;
        if(aDiffY < 0)aDiffY = -aDiffY;
        
        aCurrent->mPathParent = 0;
        
        aCurrent->mCostH = (aDiffX + aDiffY) * 100;
        aCurrent->mCostG = 0;
        aCurrent->mCostTotal = aCurrent->mCostH + aCurrent->mCostG;
        
        mOpenList.Add(aCurrent);
        
        while (mOpenList.mCount > 0) {
            aCurrent = mOpenList.Pop();

            if (mClosedList.Contains(aCurrent)) {
                return false;
            } else {
                mClosedList.Add(aCurrent);
            }
            
            aNode = aCurrent->mNode;
            if(aNode->mGridX == aEndX && aNode->mGridY == aEndY && aNode->mGridZ == aEndZ) {
                mPathEnd = aCurrent;
                break;
            } else {
                for (int k=0;k<aNode->mPathConnectionCount;k++) {
                    aPathLoops++;
                    aConnection = &(aNode->mPathConnection[k]);
                    int aCostG = aCurrent->mCostG + aConnection->mCost;
                    //TODO: Speed-up this lookup.
                    if (mClosedList.Contains(aConnection) && aCostG >= aConnection->mCostG) { continue; }
                    bool aOpenListContains = mOpenList.Contains(aConnection);
                    if ((aOpenListContains == false) || (aCostG < aConnection->mCostG)) {
                        aConnection->mPathParent = aCurrent;
                        aConnection->mCostG = aCostG;
                        aDiffX = aConnection->mNode->mGridX - aEndX;
                        if (aDiffX < 0) { aDiffX = -aDiffX; }
                        aDiffY = aConnection->mNode->mGridY - aEndY;
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
    printf("Total Path Loops: %d Open[%d] Closed[%d]\n", aPathLoops, mOpenList.mLoops, mClosedList.mLoops);
    return aResult;
}
