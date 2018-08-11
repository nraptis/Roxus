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

    /*
    if (mCount == mSize) {
        mSize = mSize + mSize / 2 + 1;
        PathNodeConnection **aData = new PathNodeConnection*[mSize];
        for (int i=0;i<mCount;i++) { aData[i] = mData[i]; }
        delete [] mData;
        mData = aData;
    }
    mData[mCount] = pConnection;
    mCount++;
    */

    mHashMap.Add(pConnection, pConnection);
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

    mHashMap.Remove(aResult);
    return aResult;
}


