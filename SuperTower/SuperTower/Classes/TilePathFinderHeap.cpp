//
//  TilePathFinderHeap.cpp
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "TilePathFinderHeap.h"

TilePathFinderHeap::TilePathFinderHeap() {
    mSize = 0;
    mCount = 0;
    mData = NULL;
}

TilePathFinderHeap::~TilePathFinderHeap() {
    delete [] mData;
    mData = NULL;
    mSize = 0;
    mCount = 0;
}

void TilePathFinderHeap::Reset() {
    mHashMap.RemoveAll();
    mCount = 0;
}

bool TilePathFinderHeap::Contains(PathNodeConnection *pConnection) {

    bool aResult = false;
    for (int i=0;i<mCount;i++) {
        if( mData[i] == pConnection) {
            aResult = true;
        }
    }
    return aResult;
    //return mHashMap.Exists(pConnection);
}

void TilePathFinderHeap::Add(PathNodeConnection *pConnection) {

    if (mCount == mSize) {
        mSize = mSize + mSize / 2 + 1;
        PathNodeConnection **aData = new PathNodeConnection*[mSize];
        for (int i=0;i<mCount;i++) { aData[i] = mData[i]; }
        delete [] mData;
        mData = aData;
    }
    mData[mCount] = pConnection;
    mCount++;

    /*


    mHashMap.Add(pConnection, pConnection);
    if (mCount == mSize) {
        mSize = mSize + mSize / 2 + 1;
        PathNodeConnection **aData = new PathNodeConnection*[mSize];
        for (int i=0;i<mCount;i++) { aData[i] = mData[i]; }
        delete [] mData;
        mData = aData;
    }
    mData[mCount] = pConnection;

    int aBubbleIndex = mCount;
    mCount++;


    PathNodeConnection *aSwapHold = NULL;
    int aParentIndex = (aBubbleIndex - 1) >> 1;
    while (aBubbleIndex > 0 && mData[aBubbleIndex]->mCostTotal < mData[aParentIndex]->mCostTotal) {
        aSwapHold = mData[aBubbleIndex];
        mData[aBubbleIndex] = mData[aParentIndex];
        mData[aParentIndex] = aSwapHold;

        aBubbleIndex = aParentIndex;
        aParentIndex = (aBubbleIndex - 1) >> 1;
    }

    */

}

PathNodeConnection *TilePathFinderHeap::Pop() {

    PathNodeConnection *aResult = 0;
    int aMinCost = 2147483647;
    int aMinIndex = -1;
    for (int i=0;i<mCount;i++) {
        PathNodeConnection *aCheck = mData[i];
        if (aCheck->mCostTotal < aMinCost) {
            aMinCost = aCheck->mCostTotal;
            aResult = aCheck;
            aMinIndex = i;
        }
    }
    if (aResult) {
        for (int i=(aMinIndex + 1);i<mCount;i++) {
            mData[i - 1] = mData[i];
        }
        mCount--;
    }
    return aResult;

    /*
    PathNodeConnection *aResult = mData[0];
    mCount -= 1;
    mData[0] = mData[mCount];

    int aBubbleIndex = 0;
    PathNodeConnection *aSwapHold = NULL;
    
    int aLeftChild = 2 * aBubbleIndex + 1;
    int aRightChild = aLeftChild + 1;
    int aMinChild = 0;
    while (aLeftChild < mCount) {
        if (aRightChild < mCount && mData[aRightChild]->mCostTotal < mData[aLeftChild]->mCostTotal) {
            aMinChild = aRightChild;
        }
        if (mData[aMinChild]->mCostTotal < mData[aBubbleIndex]->mCostTotal) {
            aSwapHold = mData[aMinChild];
            mData[aMinChild] = mData[aBubbleIndex];
            mData[aBubbleIndex] = aSwapHold;
            aBubbleIndex = aMinChild;
            aLeftChild = (aBubbleIndex << 1) + 1;
            aRightChild = aLeftChild + 1;
        } else {
            aLeftChild = mCount;
        }
    }

    mHashMap.Remove(aResult);
    return aResult;
    */
}


