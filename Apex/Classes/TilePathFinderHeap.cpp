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

void TilePathFinderHeap::Add(PathNodeConnection *pConnection) {
    
    mHashMap.Add(pConnection, pConnection);
    
    //printf("Add (C=%d) [%d %d %d]\n", mCount, pConnection->mNode->mGridX, pConnection->mNode->mGridY, pConnection->mNode->mGridZ);
    
    
    if (mCount == mSize) {
        mSize = mSize + mSize / 2 + 1;
        PathNodeConnection **aData = new PathNodeConnection*[mSize];
        for (int i=0;i<mCount;i++) { aData[i] = mData[i]; }
        delete [] mData;
        mData = aData;
    }
    
    mData[mCount] = pConnection;
    HeapSiftUp(mCount);
    mCount++;
}

bool TilePathFinderHeap::Contains(PathNodeConnection *pConnection) {
    return mHashMap.Exists(pConnection);
}

PathNodeConnection *TilePathFinderHeap::Pop() {
    PathNodeConnection *aResult = mData[0];
    mData[0] = mData[mCount - 1];
    mCount -= 1;
    
    HeapSiftDown(0);
    
    mHashMap.Remove(aResult);
    return aResult;
    
}

void TilePathFinderHeap::HeapSiftUp(int pIndex) {
    
    PathNodeConnection *aHold = 0;
    
    int aIndex = pIndex;
    int maxIndex = pIndex;
    
    while (true) {
        
        int leftChild = aIndex * 2 + 1;
        int rightChild = aIndex * 2 + 2;
        
        if (leftChild < mCount) {
            if (mData[leftChild] < mData[maxIndex]) {
                maxIndex = leftChild;
            }
        }
        if (rightChild < mCount) {
            if(mData[rightChild] > mData[maxIndex]) {
                maxIndex = rightChild;
            }
        }
        
        if (maxIndex == aIndex) {
            break;
        } else {
            
            aHold = mData[maxIndex];
            mData[maxIndex] = mData[aIndex];
            mData[aIndex] = aHold;
            
            aIndex = maxIndex;
        }
    }
    
    
    /*
    
    //       20
    //   21     32
    //36   35  40
    
    int aIndex = pIndex;
    int aLeftIndex = aIndex * 2 + 1;
    int aRightIndex = aLeftIndex + 1;
    int aChild = aIndex;
    
    
    
    while (aLeftIndex < mCount) {
        
        aChild = aLeftIndex;
        if (aRightIndex < mCount) {
            if (mData[aRightIndex]->mCostTotal < mData[aLeftIndex]->mCostTotal) {
                aChild = aRightIndex;
            }
        }
        
        if (mData[aChild]->mCostTotal > mData[aIndex]->mCostTotal) {
            aHold = mData[aChild];
            mData[aChild] = mData[aIndex];
            mData[aIndex] = aHold;
        }
        
        aIndex = aChild;
        aLeftIndex = aIndex * 2 + 1;
        aRightIndex = aLeftIndex + 1;
    }
    */
}

// 0  1  2    3 4   5 6
void TilePathFinderHeap::HeapSiftDown(int pIndex) {
    
    int aIndex = pIndex;
    int aParentIndex = (aIndex - 1) / 2;
    
    PathNodeConnection *aHold = 0;
    while (pIndex > 0 && mData[aParentIndex]->mCostTotal > mData[aIndex]->mCostTotal) {
        
        aHold = mData[aIndex];
        mData[aIndex] = mData[aParentIndex];
        mData[aParentIndex] = aHold;
        
        aIndex = aParentIndex;
        aParentIndex = (aIndex - 1) / 2;
    }
}
