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
    mData = 0;
}

TilePathFinderHeap::~TilePathFinderHeap() {
    delete [] mData;
    mData = 0;
    mSize = 0;
    mCount = 0;
}

void TilePathFinderHeap::Reset() {
    mCount = 0;
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
}

bool TilePathFinderHeap::Contains(PathNodeConnection *pConnection) {
    bool aResult = false;
    for (int i=0;i<mCount;i++) {
        if(mData[i] == pConnection)aResult = true;
    }
    return aResult;
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
}

