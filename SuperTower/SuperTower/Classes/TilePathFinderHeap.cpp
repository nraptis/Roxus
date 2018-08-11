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

    mHashListHead = NULL;
    mHashListTail = NULL;
    mTableSize = 31033;
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
}

void TilePathFinderHeap::Reset() {
    HashRemoveAll();
    mCount = 0;
}

bool TilePathFinderHeap::Contains(PathNodeConnection *pConnection) {
    return HashExists(pConnection);
}

void TilePathFinderHeap::Add(PathNodeConnection *pConnection) {

    HashAdd(pConnection);
    
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

    HashRemove(aResult);

    return aResult;
}

void TilePathFinderHeap::HashAdd(PathNodeConnection *pConnection) {
    //mHashMap.Add(pConnection, pConnection);


    pConnection->mHashListNext = NULL;
    pConnection->mHashListPrev = NULL;
    pConnection->mHashTableNext = NULL;

    PathNodeConnection *aConnection = 0;
    PathNodeConnection *aHold = 0;

    unsigned int aHash = (FHashMap::Hash(pConnection) % mTableSize);

    pConnection->mHashTableNext = NULL;
    pConnection->mHashTableIndex = aHash;
    if (mTable[aHash]) {
        aConnection = mTable[aHash];
        while (aConnection) {
            aHold = aConnection;
            aConnection = aConnection->mHashTableNext;
        }
        aHold->mHashTableNext = pConnection;
    } else {
        mTable[aHash] = pConnection;
    }

    pConnection->mHashListNext = 0;
    if (mHashListHead == 0) {
        mHashListHead = pConnection;
        mHashListTail = pConnection;
        pConnection->mHashListPrev = 0;
    } else {
        pConnection->mHashListPrev = mHashListTail;
        mHashListTail->mHashListNext = pConnection;
        mHashListTail = pConnection;
    }
}

void TilePathFinderHeap::HashRemove(PathNodeConnection *pConnection) {
    //mHashMap.Remove(pConnection);


    unsigned int aHash = (FHashMap::Hash(pConnection) % mTableSize);
    PathNodeConnection *aPreviousConnection = NULL;
    PathNodeConnection *aConnection = mTable[aHash];
    while (aConnection) {
        if (aConnection == pConnection) {

            if (aPreviousConnection) {
                aPreviousConnection->mHashTableNext = aConnection->mHashTableNext;
            } else {
                mTable[aHash] = aConnection->mHashTableNext;
            }

            if (pConnection == mHashListHead) {
                if (mHashListHead->mHashListNext) {
                    mHashListHead = mHashListHead->mHashListNext;
                    mHashListHead->mHashListPrev = NULL;
                } else {
                    mHashListTail = NULL;
                    mHashListHead = NULL;
                }
            } else if(pConnection == mHashListTail) {
                mHashListTail = mHashListTail->mHashListPrev;
                mHashListTail->mHashListNext = NULL;
            } else {
                pConnection->mHashListPrev->mHashListNext = pConnection->mHashListNext;
                pConnection->mHashListNext->mHashListPrev = pConnection->mHashListPrev;
            }

            pConnection->mHashListPrev = NULL;
            pConnection->mHashListNext = NULL;

            /*
            if (pConnection == mHashListHead) {
                if (mHashListHead->mHashListNext != NULL) {
                    mHashListHead = mHashListHead->mHashListNext;
                    mHashListHead->mHashListPrev = NULL;
                } else {
                    mHashListTail = NULL;
                    mHashListHead = NULL;
                }
            } else if(pConnection == mHashListTail) {
                mHashListTail = mHashListTail->mHashListPrev;
                mHashListTail->mHashListNext = NULL;
            } else {
                pConnection->mHashListPrev->mHashListNext = pConnection->mHashListNext;
                pConnection->mHashListNext->mHashListPrev = pConnection->mHashListPrev;
            }
            pConnection->mHashListPrev = NULL;
            pConnection->mHashListNext = NULL;
            */

            return;
        }
        aPreviousConnection = aConnection;
        aConnection = aConnection->mHashTableNext;
    }


}

bool TilePathFinderHeap::HashExists(PathNodeConnection *pConnection) {

    //return mHashMap.Exists(pConnection);

    unsigned int aHash = (FHashMap::Hash(pConnection) % mTableSize);

    //Fast lookup?
    //if (mTable[aHash] == pConnection) { return true; }

    PathNodeConnection *aConnection = mTable[aHash];
    bool aResult = false;
    while (aConnection != NULL && aResult == false) {
        aResult = (aConnection == pConnection);
        aConnection = aConnection->mHashTableNext;
    }
    return aResult;

}

void TilePathFinderHeap::HashRemoveAll() {
    //mHashMap.RemoveAll();

    //
    //
    //for (int i=0;i<mTableSize;i++) { mTable[i] = NULL; }
    //
    //

    int aLoops = 0;
    PathNodeConnection *aConnection = mHashListHead;
    while (aConnection) {
        printf(" (%d) (C=%d) Setting Table[%d] to NULL\n", aLoops, mCount, aConnection->mHashTableIndex);
        mTable[aConnection->mHashTableIndex] = NULL;
        aConnection = aConnection->mHashListNext;
               aLoops++;
    }

    aLoops = 0;

    for (int i=0;i<mTableSize;i++) {
        if (mTable[i] != NULL) {
            printf("Failed To Remove [%d] @ (%d) ...\n", aLoops, FHashMap::Hash(mTable[i]) % mTableSize);
            aLoops++;
        }

    }

    mHashListHead = NULL;
    mHashListTail = NULL;
}


