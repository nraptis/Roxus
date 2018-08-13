//
//  TilePathFinderHeap.cpp
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "TilePathFinderHeap.hpp"

TilePathFinderHeap::TilePathFinderHeap() {
    mSize = 0;
    mCount = 0;
    mData = NULL;

    mLoops = 0;

    mTableSize = 15149;
    mTable = new PathNodeConnection*[mTableSize];
    for (int i=0;i<mTableSize;i++) {
        mTable[i] = NULL;
    }
}

TilePathFinderHeap::~TilePathFinderHeap() {
    delete [] mData;
    mData = NULL;
    mSize = 0;
    mCount = 0;

    delete [] mTable;
    mTable = 0;
    mTableSize = 0;
}

void TilePathFinderHeap::Reset() {
    for (int i=0;i<mTableSize;i++) { mTable[i] = NULL; }
    mCount = 0;
    mLoops = 0;
}

bool TilePathFinderHeap::Contains(PathNodeConnection *pConnection) {
    unsigned int aHash = (FHashMap::Hash(pConnection) % mTableSize);
    PathNodeConnection *aConnection = mTable[aHash];
    bool aResult = false;
    while (aConnection != NULL && aResult == false) {
        mLoops += 1;
        aResult = (aConnection == pConnection);
        aConnection = aConnection->mOpenHashTableNext;
    }
    return aResult;
}

void TilePathFinderHeap::Add(PathNodeConnection *pConnection) {

    if (Contains(pConnection)) {
        printf("Fatal Error: Contains Conn...\n\n");
    }

    PathNodeConnection *aConnection = 0;
    PathNodeConnection *aHold = 0;
    unsigned int aHash = (FHashMap::Hash(pConnection) % mTableSize);
    pConnection->mOpenHashTableNext = NULL;
    if (mTable[aHash]) {
        aConnection = mTable[aHash];
        while (aConnection) {
            mLoops += 1;
            aHold = aConnection;
            aConnection = aConnection->mOpenHashTableNext;
        }
        mLoops += 1;
        aHold->mOpenHashTableNext = pConnection;
    } else {
        mLoops += 1;
        mTable[aHash] = pConnection;
    }

    //...

    if (mCount == mSize) {
        mSize = mSize + mSize / 2 + 1;
        PathNodeConnection **aData = new PathNodeConnection*[mSize];
        for (int i=0;i<mCount;i++) { aData[i] = mData[i]; }
        delete [] mData;
        mData = aData;
    }
    mData[mCount] = pConnection;
    unsigned int aBubbleIndex = mCount;
    mCount++;
    PathNodeConnection *aSwapHold = NULL;
    unsigned int aParentIndex = (aBubbleIndex - 1) / 2;
    while (aBubbleIndex > 0 && mData[aBubbleIndex]->mCostTotal < mData[aParentIndex]->mCostTotal) {
        mLoops += 1;
        aSwapHold = mData[aBubbleIndex];
        mData[aBubbleIndex] = mData[aParentIndex];
        mData[aParentIndex] = aSwapHold;
        aBubbleIndex = aParentIndex;
        aParentIndex = (aBubbleIndex - 1) / 2;
    }
}

PathNodeConnection *TilePathFinderHeap::Pop() {

    PathNodeConnection *aResult = mData[0];
    mCount -= 1;
    mData[0] = mData[mCount];

    PathNodeConnection *aSwapHold = NULL;
    unsigned int aBubbleIndex = 0;
    unsigned int aLeftChild = 2 * aBubbleIndex + 1;
    unsigned int aRightChild = aLeftChild + 1;
    unsigned int aMinChild = aLeftChild;
    while (aLeftChild < mCount) {
        mLoops += 1;
        if (aRightChild < mCount && mData[aRightChild]->mCostTotal < mData[aLeftChild]->mCostTotal) {
            aMinChild = aRightChild;
        }
        if (mData[aMinChild]->mCostTotal < mData[aBubbleIndex]->mCostTotal) {
            aSwapHold = mData[aMinChild];
            mData[aMinChild] = mData[aBubbleIndex];
            mData[aBubbleIndex] = aSwapHold;
            aBubbleIndex = aMinChild;
            aLeftChild = (aBubbleIndex * 2) + 1;
            aRightChild = aLeftChild + 1;
            aMinChild = aLeftChild;
        } else {
            aLeftChild = mCount;
        }
    }
    
    unsigned int aHash = (FHashMap::Hash(aResult) % mTableSize);
    PathNodeConnection *aPreviousConnection = NULL;
    PathNodeConnection *aConnection = mTable[aHash];
    bool aFound = false;
    while (aConnection != NULL && aFound == false) {
        mLoops += 1;
        if (aConnection == aResult) {
            if (aPreviousConnection) {
                aPreviousConnection->mOpenHashTableNext = aConnection->mOpenHashTableNext;
            } else {
                mTable[aHash] = aConnection->mOpenHashTableNext;
            }
            aFound = true;
        }
        aPreviousConnection = aConnection;
        aConnection = aConnection->mOpenHashTableNext;
    }


    return aResult;
}
