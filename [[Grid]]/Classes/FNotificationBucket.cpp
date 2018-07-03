//
//  FNotificationBucket.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "FNotificationBucket.hpp"
#include "core_includes.h"

FNotificationBucketNode::FNotificationBucketNode() {
    mKey = 0;
    mTableNext = 0;
}

FNotificationBucketNode::~FNotificationBucketNode() { }

void FNotificationBucketNode::Clear() {
    mNodeList.RemoveAll();
}

FNotificationBucket::FNotificationBucket() {
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;
}

FNotificationBucket::~FNotificationBucket() {
    FNotificationBucketNode *aNode = 0;
    FNotificationBucketNode *aNext = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            delete aNode;
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;
    FreeList(FNotificationBucketNode, mQueue);
}

void FNotificationBucket::Add(FCanvas *pKey, FHashTableNode *pNode) {
    FNotificationBucketNode *aNode = 0;
    FNotificationBucketNode *aHold = 0;
    unsigned int aHashBase = FHashMap::Hash(pKey);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while(aNode) {
            if(aNode->mKey == pKey) {
                aNode->mNodeList.Add(pNode);
                return;
            }
            aNode = aNode->mTableNext;
        }
        if (mTableCount >= (mTableSize / 2)) {
            int aNewSize = mTableCount + 1;
            if(mTableCount < ((13 / 2) - 1))aNewSize = 13;
            else if(mTableCount < ((29 / 2) - 1))aNewSize = 29;
            else if(mTableCount < ((41 / 2) - 1))aNewSize = 41;
            else if(mTableCount < ((53 / 2) - 1))aNewSize = 53;
            else if(mTableCount < ((97 / 2) - 1))aNewSize = 97;
            else if(mTableCount < ((149 / 2) - 5))aNewSize = 149;
            else if(mTableCount < ((193 / 2) - 5))aNewSize = 193;
            else if(mTableCount < ((269 / 2) - 5))aNewSize = 269;
            else if(mTableCount < ((389 / 2) - 5))aNewSize = 389;
            else if(mTableCount < ((439 / 2) - 5))aNewSize = 439;
            else if(mTableCount < ((631 / 2) - 5))aNewSize = 631;
            else if(mTableCount < ((769 / 2) - 5))aNewSize = 769;
            else if(mTableCount < ((907 / 2) - 7))aNewSize = 907;
            else if(mTableCount < ((1213 / 2) - 7))aNewSize = 1213;
            else if(mTableCount < ((1543 / 2) - 7))aNewSize = 1543;
            else if(mTableCount < ((2089 / 2) - 7))aNewSize = 2089;
            else if(mTableCount < ((2557 / 2) - 9))aNewSize = 2557;
            else if(mTableCount < ((3079 / 2) - 13))aNewSize = 3079;
            else if(mTableCount < ((3613 / 2) - 13))aNewSize = 3613;
            else if(mTableCount < ((4013 / 2) - 13))aNewSize = 4013;
            else if(mTableCount < ((5119 / 2) - 13))aNewSize = 5119;
            else if(mTableCount < ((6151 / 2) - 13))aNewSize = 6151;
            else if(mTableCount < ((7151 / 2) - 13))aNewSize = 7151;
            else if(mTableCount < ((12289 / 2) - 17))aNewSize = 12289;
            else { aNewSize = (mTableCount + (mTableCount * 2) / 3 + 7); }

            SetTableSize(aNewSize);
            aHash = (aHashBase % mTableSize);
        }
    } else {
        SetTableSize(7);
        aHash = (aHashBase % mTableSize);
    }

    FNotificationBucketNode *aNew = (FNotificationBucketNode *)mQueue.PopLast();
    if (aNew == 0) {
        aNew = new FNotificationBucketNode();
    }

    aNew->Clear();
    aNew->mKey = pKey;
    aNew->mTableNext = 0;
    aNew->mNodeList.Add(pNode);

    if (mTable[aHash]) {
        aNode = mTable[aHash];
        while (aNode) {
            aHold = aNode;
            aNode = aNode->mTableNext;
        }
        aHold->mTableNext = aNew;
    } else {
        mTable[aHash] = aNew;
    }
    mTableCount += 1;
}

void FNotificationBucket::Remove(FCanvas *pKey, FHashTableNode *pNode) {
    if (mTableSize > 0) {
        unsigned int aHash = (FHashMap::Hash(pKey) % mTableSize);
        FNotificationBucketNode *aPreviousNode = 0;
        FNotificationBucketNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                aNode->mNodeList.Remove(pNode);
                if (aNode->mNodeList.mCount <= 0) {
                    if (aPreviousNode) {
                        aPreviousNode->mTableNext = aNode->mTableNext;
                    } else {
                        mTable[aHash] = aNode->mTableNext;
                    }
                    aNode->Clear();
                    mQueue.Add(aNode);
                    mTableCount -= 1;
                }
                return;
            }
            aPreviousNode = aNode;
            aNode = aNode->mTableNext;
        }
    }
}

void FNotificationBucket::Remove(FCanvas *pKey) {
    if (mTableSize > 0) {
        unsigned int aHash = (FHashMap::Hash(pKey) % mTableSize);
        FNotificationBucketNode *aPreviousNode = 0;
        FNotificationBucketNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                if (aPreviousNode) {
                    aPreviousNode->mTableNext = aNode->mTableNext;
                } else {
                    mTable[aHash] = aNode->mTableNext;
                }
                aNode->Clear();
                mQueue.Add(aNode);
                mTableCount -= 1;
                return;
            }
            aPreviousNode = aNode;
            aNode = aNode->mTableNext;
        }
    }
}

void FNotificationBucket::RemoveAll() {
    FNotificationBucketNode *aNode = 0;
    FNotificationBucketNode *aNext = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            aNode->Clear();
            mQueue.Add(aNode);
            aNode = aNext;
        }
        mTable[i] = 0;
    }
    mTableCount = 0;
    mTableSize = 0;
}


FNotificationBucketNode *FNotificationBucket::Get(FCanvas *pKey) {
    if(mTableSize > 0) {
        unsigned int aHash = (FHashMap::Hash(pKey) % mTableSize);
        FNotificationBucketNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                return aNode;
            }
            aNode = aNode->mTableNext;
        }
    }
    return 0;
}

void FNotificationBucket::SetTableSize(int pSize) {
    FNotificationBucketNode *aCheck = 0;
    FNotificationBucketNode *aNext = 0;
    FNotificationBucketNode *aNode = 0;
    int aNewSize = pSize;
    FNotificationBucketNode **aTableNew = new FNotificationBucketNode*[aNewSize];
    for(int i=0;i<aNewSize;i++) {
        aTableNew[i] = 0;
    }
    unsigned int aHash = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            aNode->mTableNext = 0;
            aHash = FHashMap::Hash(aNode->mKey) % aNewSize;
            if(aTableNew[aHash] == 0) {
                aTableNew[aHash] = aNode;
            } else {
                aCheck = aTableNew[aHash];
                while (aCheck->mTableNext) {
                    aCheck = aCheck->mTableNext;
                }
                aCheck->mTableNext = aNode;
            }
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = aTableNew;
    mTableSize = aNewSize;
}

void FNotificationBucket::Print() {
    Log("____\n____Hash Table____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueue.mCount, mQueue.mSize);
    FNotificationBucketNode *aNode = 0;
    for (int i=0;i<mTableSize;i++) {
        int aCount = 0;
        aNode = mTable[i];
        while (aNode) {
            aCount++;
            aNode = aNode->mTableNext;
        }
        Log("Row[%d] (%d)\t{", i, aCount);
        aNode = mTable[i];
        while(aNode) {
            Log("{%s}", aNode->mKey->mName.c());
            aNode = aNode->mTableNext;
        }
        Log("}\n");
    }
}
