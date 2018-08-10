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
    return mHashMap.Exists(pConnection);
}

void TilePathFinderHeap::Add(PathNodeConnection *pConnection) {
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

}

PathNodeConnection *TilePathFinderHeap::Pop() {
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
}

/*
bool TilePathFinderHeap::Contains(PathNodeConnection *pConnection) {
    return mHashMap.Exists(pConnection);
}

void TilePathFinderHeap::Add(PathNodeConnection *pConnection) {
    mHashMap.Add(pConnection, pConnection);

    if (mCount == mSize) {
        mSize = mSize + mSize / 2 + 1;
        PathNodeConnection **aData = new PathNodeConnection*[mSize];
        for (int i=0;i<mCount;i++) { aData[i] = mData[i]; }
        delete [] mData;
        mData = aData;
    }
    
    mData[mCount] = pConnection;
    mCount += 1;
    HeapSiftUp(mCount - 1);
}



PathNodeConnection *TilePathFinderHeap::Pop() {
    PathNodeConnection *aResult = mData[0];
    mData[0] = mData[mCount - 1];
    mCount -= 1;

    HeapSiftDown(0);

    mHashMap.Remove(aResult);
    return aResult;
}
*/

/*
void TilePathFinderHeap::HeapSiftUp(int pIndex) {
    int aIndex = pIndex;
    int aParentIndex = GetParentIndex(pIndex);
    PathNodeConnection *aHold = NULL;

    while (pIndex > 0 && mData[aParentIndex]->mCostTotal > mData[aIndex]->mCostTotal) {
        aHold = mData[aIndex];
        mData[aIndex] = mData[aParentIndex];
        mData[aParentIndex] = aHold;
        aIndex = aParentIndex;
        aParentIndex = (aIndex - 1) / 2;
    }
}

// 0  1  2    3 4   5 6
void TilePathFinderHeap::HeapSiftDown(int pIndex) {

    PathNodeConnection *aHold = NULL;

    int aIndex = pIndex;
    int leftChildIndex, rightChildIndex, minIndex;

    leftChildIndex = GetLeftChildIndex(pIndex);
    rightChildIndex = GetRightChildIndex(pIndex);

    if (rightChildIndex >= mCount) {
        if (leftChildIndex >= mCount) {
            return;
        } else {
            minIndex = leftChildIndex;
        }
    } else {
        if (mData[leftChildIndex]->mCostTotal <= mData[rightChildIndex]->mCostTotal)
            minIndex = leftChildIndex;
        else
            minIndex = rightChildIndex;

    }

    if (mData[aIndex] > mData[minIndex]) {
        aHold = mData[minIndex];
        mData[minIndex] = mData[aIndex];
        mData[aIndex] = aHold;
        HeapSiftDown(minIndex);
    }
}
*/

