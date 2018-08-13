//
//  TilePathFinderHeapOldOld.cpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 8/10/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "TilePathFinderHeapOld.hpp"

TilePathFinderHeapOld::TilePathFinderHeapOld() {
    mSize = 0;
    mCount = 0;
    mData = NULL;
}

TilePathFinderHeapOld::~TilePathFinderHeapOld() {
    delete [] mData;
    mData = NULL;
    mSize = 0;
    mCount = 0;
}

void TilePathFinderHeapOld::Reset() {
    mHashMap.RemoveAll();
    mCount = 0;
}

bool TilePathFinderHeapOld::Contains(PathNodeConnection *pConnection) {
    bool aResult = false;
    for (int i=0;i<mCount;i++) {
        if( mData[i] == pConnection) {
            aResult = true;
        }
    }
    return aResult;
}

void TilePathFinderHeapOld::Add(PathNodeConnection *pConnection) {

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

PathNodeConnection *TilePathFinderHeapOld::Pop() {

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


