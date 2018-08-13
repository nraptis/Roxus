//
//  NodePathFinder.cpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 8/13/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "NodePathFinder.hpp"

NodePathFinder::NodePathFinder() {
    mPathStart = new PathNodeConnection();
    mPathEnd = 0;


    mOpenListCount = 0;
    mOpenListSize = MAX_UNIT_GRID_WIDTH * MAX_UNIT_GRID_HEIGHT * GRID_DEPTH;
    mClosedListCount = 0;
    mClosedListSize = MAX_UNIT_GRID_WIDTH * MAX_UNIT_GRID_HEIGHT * GRID_DEPTH;
    mOpenListTableSize = 15149;
    mClosedListTableSize = 15149;

    mClosedListData = &(mOpenListData[mOpenListSize]);
    mOpenListTableData = &(mClosedListData[mClosedListSize]);
    mClosedListTableData = &(mOpenListTableData[mOpenListTableSize]);

    for (int i=0;i<mOpenListTableSize;i++) {
        mOpenListTableData[i] = NULL;
    }
    for (int i=0;i<mOpenListTableSize;i++) {
        mClosedListTableData[i] = NULL;
    }



}

NodePathFinder::~NodePathFinder() {
    delete mPathStart;
    mPathStart = 0;
    mPathEnd = 0;
}

void NodePathFinder::OpenListAdd(PathNodeConnection *pConnection) {
    PathNodeConnection *aConnection = 0;
    PathNodeConnection *aHold = 0;
    unsigned int aBubbleIndex = 0;
    unsigned int aHash = 0;
    unsigned int aParentIndex = 0;

    aHash = (FHashMap::Hash(pConnection) % mOpenListTableSize);
    pConnection->mHashTableNext = NULL;
    if (mOpenListTableData[aHash]) {
        aConnection = mOpenListTableData[aHash];
        while (aConnection) {
            aHold = aConnection;
            aConnection = aConnection->mHashTableNext;
        }
        aHold->mHashTableNext = pConnection;
    } else {
        mOpenListTableData[aHash] = pConnection;
    }

    if (mOpenListCount >= mOpenListSize) {
        printf("Fatal Error: OpenList Overflow...");
        return;
    }

    mOpenListData[mOpenListCount] = pConnection;
    aBubbleIndex = mOpenListCount;
    mOpenListCount += 1;

    aParentIndex = (aBubbleIndex - 1) / 2;
    while (aBubbleIndex > 0 && mOpenListData[aBubbleIndex]->mCostTotal < mOpenListData[aParentIndex]->mCostTotal) {
        aHold = mOpenListData[aBubbleIndex];
        mOpenListData[aBubbleIndex] = mOpenListData[aParentIndex];
        mOpenListData[aParentIndex] = aHold;
        aBubbleIndex = aParentIndex;
        aParentIndex = (aBubbleIndex - 1) / 2;
    }
}

PathNodeConnection *NodePathFinder::OpenListPop() {
    unsigned int aBubbleIndex = 0;
    unsigned int aLeftChild = 0;
    unsigned int aRightChild = 0;
    unsigned int aMinChild = 0;
    unsigned int aHash = 0;
    PathNodeConnection *aPopResult = NULL;
    PathNodeConnection *aHold = NULL;
    bool aFound = false;
    PathNodeConnection *aPreviousConnection = NULL;
    PathNodeConnection *aConnection = NULL;
    aPopResult = mOpenListData[0];
    mOpenListCount -= 1;
    mOpenListData[0] = mOpenListData[mOpenListCount];

    aBubbleIndex = 0;
    aLeftChild = 2 * aBubbleIndex + 1;
    aRightChild = aLeftChild + 1;
    aMinChild = aLeftChild;
    while (aLeftChild < mOpenListCount) {
        if (aRightChild < mOpenListCount && mOpenListData[aRightChild]->mCostTotal < mOpenListData[aLeftChild]->mCostTotal) {
            aMinChild = aRightChild;
        }
        if (mOpenListData[aMinChild]->mCostTotal < mOpenListData[aBubbleIndex]->mCostTotal) {
            aHold = mOpenListData[aMinChild];
            mOpenListData[aMinChild] = mOpenListData[aBubbleIndex];
            mOpenListData[aBubbleIndex] = aHold;
            aBubbleIndex = aMinChild;
            aLeftChild = (aBubbleIndex * 2) + 1;
            aRightChild = aLeftChild + 1;
            aMinChild = aLeftChild;
        } else {
            aLeftChild = mOpenListCount;
        }
    }

    aHash = (FHashMap::Hash(aPopResult) % mOpenListTableSize);
    aPreviousConnection = NULL;
    aConnection = mOpenListTableData[aHash];
    aFound = false;
    while (aConnection != NULL && aFound == false) {
        if (aConnection == aPopResult) {
            if (aPreviousConnection) {
                aPreviousConnection->mHashTableNext = aConnection->mHashTableNext;
            } else {
                mOpenListTableData[aHash] = aConnection->mHashTableNext;
            }
            aFound = true;
        }
        aPreviousConnection = aConnection;
        aConnection = aConnection->mHashTableNext;
    }

    return aPopResult;
}

bool NodePathFinder::OpenListExists(PathNodeConnection *pConnection) {
    unsigned int aHash = 0;
    PathNodeConnection *aConnection = NULL;
    bool aExistsResult = false;


    aHash = (FHashMap::Hash(pConnection) % mOpenListTableSize);
    aConnection = mOpenListTableData[aHash];
    aExistsResult = false;
    while (aConnection != NULL && aExistsResult == false) {
        aExistsResult = (aConnection == pConnection);
        aConnection = aConnection->mHashTableNext;
    }
    return aExistsResult;
}

void NodePathFinder::ClosedListAdd(PathNodeConnection *pConnection) {

    PathNodeConnection *aConnection = 0;
    PathNodeConnection *aHold = 0;
    unsigned int aBubbleIndex = 0;
    unsigned int aHash = 0;
    unsigned int aParentIndex = 0;

    aHash = (FHashMap::Hash(pConnection) % mClosedListTableSize);
    pConnection->mHashTableNext = NULL;
    if (mClosedListTableData[aHash]) {
        aConnection = mClosedListTableData[aHash];
        while (aConnection) {
            aHold = aConnection;
            aConnection = aConnection->mHashTableNext;
        }
        aHold->mHashTableNext = pConnection;
    } else {
        mClosedListTableData[aHash] = pConnection;
    }

    if (mClosedListCount >= mClosedListSize) {
        printf("Fatal Error: ClosedList Overflow...");
        return;
    }

    mClosedListData[mClosedListCount] = pConnection;
    aBubbleIndex = mClosedListCount;
    mClosedListCount += 1;

    aParentIndex = (aBubbleIndex - 1) / 2;
    while (aBubbleIndex > 0 && mClosedListData[aBubbleIndex]->mCostTotal < mClosedListData[aParentIndex]->mCostTotal) {
        aHold = mClosedListData[aBubbleIndex];
        mClosedListData[aBubbleIndex] = mClosedListData[aParentIndex];
        mClosedListData[aParentIndex] = aHold;
        aBubbleIndex = aParentIndex;
        aParentIndex = (aBubbleIndex - 1) / 2;
    }

}

PathNodeConnection *NodePathFinder::ClosedListPop() {
    unsigned int aBubbleIndex = 0;
    unsigned int aLeftChild = 0;
    unsigned int aRightChild = 0;
    unsigned int aMinChild = 0;
    unsigned int aHash = 0;
    PathNodeConnection *aPopResult = NULL;
    PathNodeConnection *aHold = NULL;
    bool aFound = false;
    PathNodeConnection *aPreviousConnection = NULL;
    PathNodeConnection *aConnection = NULL;

    aPopResult = mClosedListData[0];
    mClosedListCount -= 1;
    mClosedListData[0] = mClosedListData[mClosedListCount];

    aBubbleIndex = 0;
    aLeftChild = 2 * aBubbleIndex + 1;
    aRightChild = aLeftChild + 1;
    aMinChild = aLeftChild;
    while (aLeftChild < mClosedListCount) {
        if (aRightChild < mClosedListCount && mClosedListData[aRightChild]->mCostTotal < mClosedListData[aLeftChild]->mCostTotal) {
            aMinChild = aRightChild;
        }
        if (mClosedListData[aMinChild]->mCostTotal < mClosedListData[aBubbleIndex]->mCostTotal) {
            aHold = mClosedListData[aMinChild];
            mClosedListData[aMinChild] = mClosedListData[aBubbleIndex];
            mClosedListData[aBubbleIndex] = aHold;
            aBubbleIndex = aMinChild;
            aLeftChild = (aBubbleIndex * 2) + 1;
            aRightChild = aLeftChild + 1;
            aMinChild = aLeftChild;
        } else {
            aLeftChild = mClosedListCount;
        }
    }

    aHash = (FHashMap::Hash(aPopResult) % mClosedListTableSize);
    aPreviousConnection = NULL;
    aConnection = mClosedListTableData[aHash];
    aFound = false;
    while (aConnection != NULL && aFound == false) {
        if (aConnection == aPopResult) {
            if (aPreviousConnection) {
                aPreviousConnection->mHashTableNext = aConnection->mHashTableNext;
            } else {
                mClosedListTableData[aHash] = aConnection->mHashTableNext;
            }
            aFound = true;
        }
        aPreviousConnection = aConnection;
        aConnection = aConnection->mHashTableNext;
    }

    return aPopResult;
}

bool NodePathFinder::ClosedListExists(PathNodeConnection *pConnection) {
    unsigned int aHash = 0;
    PathNodeConnection *aConnection = NULL;
    bool aExistsResult = false;

    aHash = (FHashMap::Hash(pConnection) % mClosedListTableSize);
    aConnection = mClosedListTableData[aHash];
    aExistsResult = false;
    while (aConnection != NULL && aExistsResult == false) {
        aExistsResult = (aConnection == pConnection);
        aConnection = aConnection->mHashTableNext;
    }
    return aExistsResult;
}

bool NodePathFinder::FindPath(PathNode *pStart, PathNode *pEnd) {
    bool aResult = false;

    printf("Pathing From [%d %d %d] => [%d %d %d]\n", pStart->mGridX, pStart->mGridY, pStart->mGridZ, pEnd->mGridX, pEnd->mGridY, pEnd->mGridZ);


    PathNodeConnection *aConnection = NULL;
    PathNodeConnection *aPreviousConnection = NULL;
    PathNodeConnection *aHold = NULL;
    PathNodeConnection *aPopResult = NULL;
    unsigned int aBubbleIndex = 0;
    unsigned int aHash = 0;
    unsigned int aParentIndex = 0;
    unsigned int aLeftChild = 0;
    unsigned int aRightChild = 0;
    unsigned int aMinChild = 0;
    bool aFound = false;

    int aCostG = 0;
    bool aOpenListContains = false;
    bool aClosedListContains = false;

    int k = 0;


    //mClosedList.Reset();


    //Flush the lists...
    for (int i=0;i<mOpenListTableSize;i++) {
        mOpenListTableData[i] = NULL;
    }
    for (int i=0;i<mOpenListTableSize;i++) {
        mClosedListTableData[i] = NULL;
    }

    mOpenListCount = 0;
    mClosedListCount = 0;

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

        OpenListAdd(aCurrent);
        //mOpenList.Add(aCurrent);

        while (mOpenListCount > 0) {
            aCurrent = OpenListPop();

            if (ClosedListExists(aCurrent)) {
                return false;
            }

            ClosedListAdd(aCurrent);

            aNode = aCurrent->mNode;
            if(aNode->mGridX == aEndX && aNode->mGridY == aEndY && aNode->mGridZ == aEndZ) {
                mPathEnd = aCurrent;
                break;
            } else {
                for (k=0;k<aNode->mPathConnectionCount;k++) {
                    aPathLoops++;
                    aConnection = &(aNode->mPathConnection[k]);
                    aCostG = aCurrent->mCostG + aConnection->mCost;
                    //TODO: Speed-up this lookup.

                    //if (mClosedList.Contains(aConnection) && aCostG >= aConnection->mCostG) { continue; }
                    //bool aOpenListContains = mOpenList.Contains(aConnection);
                    //if ((aOpenListContains == false) || (aCostG < aConnection->mCostG)) {

                    aClosedListContains = ClosedListExists(aConnection);
                    if (aCostG >= aConnection->mCostG && aClosedListContains == true) { continue; }

                    aOpenListContains = OpenListExists(aConnection);
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
                            OpenListAdd(aConnection);
                        }
                    }
                }
            }
        }
    }

    return aResult;
}


