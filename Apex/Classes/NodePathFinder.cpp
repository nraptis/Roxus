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
    mOpenListTableSize = 15149;
    mClosedListTableSize = 15149;
    mOpenListTableData = &(mOpenListData[mOpenListSize]);
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

bool NodePathFinder::FindPath(PathNode *pStart, PathNode *pEnd) {
    bool aResult = false;
    bool aFound = false;
    bool aOpenListContains = false;
    bool aClosedListContains = false;
    
    //printf("Pathing From [%d %d %d] => [%d %d %d]\n", pStart->mGridX, pStart->mGridY, pStart->mGridZ, pEnd->mGridX, pEnd->mGridY, pEnd->mGridZ);

    PathNodeConnection *aPreviousConnection = NULL;
    PathNodeConnection *aHold = NULL;
    PathNodeConnection *aSearch = NULL;

    unsigned int aBubbleIndex = 0;
    unsigned int aHash = 0;
    unsigned int aParentIndex = 0;
    unsigned int aLeftChild = 0;
    unsigned int aRightChild = 0;
    unsigned int aMinChild = 0;
    unsigned int aCostG = 0;
    unsigned int aConnectionIndex = 0;

    //Flush the lists...

    //Seems to go much faster by flushing whole hash table to 0
    //and not using linked list style pointers.
    for (int i=0;i<mOpenListTableSize;i++) {
        mOpenListTableData[i] = NULL;
    }

    for (int i=0;i<mOpenListTableSize;i++) {
        mClosedListTableData[i] = NULL;
    }

    //Reset the open list
    mOpenListCount = 0;
    mPathEnd = 0;

    if (pStart != 0 && pEnd != 0) {

        //Here is our target grid position.
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
        //H cost = (Manhattan distance) * 100
        aCurrent->mCostH = (aDiffX + aDiffY) * 100;
        aCurrent->mCostG = 0;
        //Total cost = (g cost + h cost)
        aCurrent->mCostTotal = aCurrent->mCostH + aCurrent->mCostG;

        //Add aCurrent to the open list (min heap + hash table)
        aHash = (FHashMap::Hash(aCurrent) % mOpenListTableSize);
        aCurrent->mOpenHashTableNext = NULL;
        if (mOpenListTableData[aHash]) {
            aSearch = mOpenListTableData[aHash];
            while (aSearch != NULL) {
                aHold = aSearch;
                aSearch = aSearch->mOpenHashTableNext;
            }
            aHold->mOpenHashTableNext = aCurrent;
        } else {
            mOpenListTableData[aHash] = aCurrent;
        }

        //We should never overflow.
        if (mOpenListCount == mOpenListSize) {
            printf("Fatal Error: OpenList Overflow...");
            return false;
        }

        //Add to end of heap and bubble up (still adding to open list)
        mOpenListData[mOpenListCount] = aCurrent;
        aBubbleIndex = mOpenListCount;
        mOpenListCount += 1;
        aParentIndex = (aBubbleIndex - 1) >> 1;
        while (aBubbleIndex > 0 && mOpenListData[aBubbleIndex]->mCostTotal < mOpenListData[aParentIndex]->mCostTotal) {
            aHold = mOpenListData[aBubbleIndex];
            mOpenListData[aBubbleIndex] = mOpenListData[aParentIndex];
            mOpenListData[aParentIndex] = aHold;
            aBubbleIndex = aParentIndex;
            aParentIndex = (aBubbleIndex - 1) >> 1;
        }

        //While open list is not empty...
        while (mOpenListCount > 0) {

            //Pop the minimum cost node from the open list.
            aCurrent = mOpenListData[0];
            mOpenListCount -= 1;
            //First item from min heap
            mOpenListData[0] = mOpenListData[mOpenListCount];
            aBubbleIndex = 0;
            aLeftChild = (aBubbleIndex << 1) + 1;
            aRightChild = aLeftChild + 1;
            aMinChild = aLeftChild;
            //Bubble down the heap.
            while (aLeftChild < mOpenListCount) {
                if (aRightChild < mOpenListCount && mOpenListData[aRightChild]->mCostTotal < mOpenListData[aLeftChild]->mCostTotal) {
                    aMinChild = aRightChild;
                }
                if (mOpenListData[aMinChild]->mCostTotal < mOpenListData[aBubbleIndex]->mCostTotal) {
                    aHold = mOpenListData[aMinChild];
                    mOpenListData[aMinChild] = mOpenListData[aBubbleIndex];
                    mOpenListData[aBubbleIndex] = aHold;
                    aBubbleIndex = aMinChild;
                    aLeftChild = (aBubbleIndex << 1) + 1;
                    aRightChild = aLeftChild + 1;
                    aMinChild = aLeftChild;
                } else {
                    aLeftChild = mOpenListCount;
                }
            }

            //Remove aCurrent from open list hash table.
            aHash = (FHashMap::Hash(aCurrent) % mOpenListTableSize);
            aPreviousConnection = NULL;
            aHold = mOpenListTableData[aHash];
            aFound = false;
            while (aHold != NULL && aFound == false) {
                if (aHold == aCurrent) {
                    if (aPreviousConnection) {
                        aPreviousConnection->mOpenHashTableNext = aHold->mOpenHashTableNext;
                    } else {
                        mOpenListTableData[aHash] = aHold->mOpenHashTableNext;
                    }
                    aFound = true;
                }
                aPreviousConnection = aHold;
                aHold = aHold->mOpenHashTableNext;
            }

            //Check if aCurrent is on the closed list (just a hash table)
            aHash = (FHashMap::Hash(aCurrent) % mClosedListTableSize);
            aHold = mClosedListTableData[aHash];
            aClosedListContains = false;
            while (aHold != NULL && aClosedListContains == false) {
                aClosedListContains = (aHold == aCurrent);
                aHold = aHold->mClosedHashTableNext;
            }

            if (aClosedListContains == false) {

                //Insert aCurrent into the closed list (optimized to just hash table)
                aHash = (FHashMap::Hash(aCurrent) % mClosedListTableSize);
                aCurrent->mClosedHashTableNext = NULL;
                if (mClosedListTableData[aHash]) {
                    aSearch = mClosedListTableData[aHash];
                    while (aSearch != NULL) {
                        aHold = aSearch;
                        aSearch = aSearch->mClosedHashTableNext;
                    }
                    aHold->mClosedHashTableNext = aCurrent;
                } else {
                    mClosedListTableData[aHash] = aCurrent;
                }
                //return false;
            }

            //If we are at the end, we have our shortest path...
            aNode = aCurrent->mNode;
            if(aNode->mGridX == aEndX && aNode->mGridY == aEndY && aNode->mGridZ == aEndZ) {
                mPathEnd = aCurrent;
                break;
            } else {
                //For all of our node's connections...
                for (aConnectionIndex=0;aConnectionIndex<aNode->mPathConnectionCount;aConnectionIndex++) {
                    aConnection = &(aNode->mPathConnection[aConnectionIndex]);

                    //Disabled?
                    //if (aConnection->mDisabled != 0) { continue; }

                    //Adjust G cost by adding this connections cost.
                    aCostG = aCurrent->mCostG + aConnection->mCost;

                    //Find if this connection is in the closed list.
                    aHash = (FHashMap::Hash(aConnection) % mClosedListTableSize);
                    aHold = mClosedListTableData[aHash];
                    aClosedListContains = false;
                    while (aHold != NULL && aClosedListContains == false) {
                        aClosedListContains = (aHold == aConnection);
                        aHold = aHold->mClosedHashTableNext;
                    }

                    //If we're on the list with a lower g cost, ignore...
                    if (aCostG >= aConnection->mCostG && aClosedListContains == true) { continue; }

                    //Find if this connection is in the open list.
                    aHash = (FHashMap::Hash(aConnection) % mOpenListTableSize);
                    aHold = mOpenListTableData[aHash];
                    aOpenListContains = false;
                    while (aHold != NULL && aOpenListContains == false) {
                        aOpenListContains = (aHold == aConnection);
                        aHold = aHold->mOpenHashTableNext;
                    }

                    //If this connection is not in the open list and
                    //we have a lower g cost than previously...
                    if ((aOpenListContains == false) || (aCostG < aConnection->mCostG)) {

                        //This is part of our final solution, link to parent.
                        aConnection->mPathParent = aCurrent;

                        //Adjust the connection's g cost to the new lowest g cost.
                        aConnection->mCostG = aCostG;
                        aDiffX = aConnection->mNode->mGridX - aEndX;
                        if (aDiffX < 0) { aDiffX = -aDiffX; }
                        aDiffY = aConnection->mNode->mGridY - aEndY;
                        if (aDiffY < 0) { aDiffY = -aDiffY; }
                        //H cost = (Manhattan distance) * 100
                        aConnection->mCostH = (aDiffX + aDiffY) * 100;
                        //Total cost = (g cost + h cost)
                        aConnection->mCostTotal = aConnection->mCostH + aConnection->mCostG;

                        //If we are not in the open list, add to the open list.
                        if (aOpenListContains == false) {

                            //Open list hash table step.
                            aHash = (FHashMap::Hash(aConnection) % mOpenListTableSize);
                            aConnection->mOpenHashTableNext = NULL;
                            if (mOpenListTableData[aHash]) {
                                aSearch = mOpenListTableData[aHash];
                                while (aSearch != NULL) {
                                    aHold = aSearch;
                                    aSearch = aSearch->mOpenHashTableNext;
                                }
                                aHold->mOpenHashTableNext = aConnection;
                            } else {
                                mOpenListTableData[aHash] = aConnection;
                            }

                            if (mOpenListCount >= mOpenListSize) {
                                printf("Fatal Error: OpenList Overflow...");
                                return false;
                            }

                            //Open list min heap step.
                            mOpenListData[mOpenListCount] = aConnection;
                            aBubbleIndex = mOpenListCount;
                            mOpenListCount += 1;

                            //Bubble up.
                            aParentIndex = (aBubbleIndex - 1) >> 1;
                            while (aBubbleIndex > 0 && mOpenListData[aBubbleIndex]->mCostTotal < mOpenListData[aParentIndex]->mCostTotal) {
                                aHold = mOpenListData[aBubbleIndex];
                                mOpenListData[aBubbleIndex] = mOpenListData[aParentIndex];
                                mOpenListData[aParentIndex] = aHold;
                                aBubbleIndex = aParentIndex;
                                aParentIndex = (aBubbleIndex - 1) >> 1;
                            }
                        }
                    }
                }
            }
        }
    }

    //$1,000,000.
    return aResult;
}


