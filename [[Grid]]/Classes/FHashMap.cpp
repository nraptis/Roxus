//
//  FHashMap.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "FHashMap.hpp"
#include "core_includes.h"

FHashMapNode::FHashMapNode() {
    mObject = 0;
    mKey = 0;
    mTableNext = 0;
    mListPrev = 0;
    mListNext = 0;
    mTableIndex = -1;
}

FHashMapNode::~FHashMapNode() { }

FHashMap::FHashMap() {
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;
}

FHashMap::~FHashMap() {
    FHashMapNode *aNode = 0;
    FHashMapNode *aNext = 0;
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
    FreeList(FHashMapNode, mQueue);
    mListHead = 0;
    mListTail = 0;
}

void FHashMap::RemoveAll() {
    FHashMapNode *aNode = mListHead;
    while (aNode) {
        mQueue.Add(aNode);
        mTable[aNode->mTableIndex] = 0;
        aNode = aNode->mListNext;
    }
    mListHead = 0;
    mListTail = 0;
    mTableCount = 0;
}

void FHashMap::Add(void *pKey, void *pObject) {
    if (pObject == 0 || pKey == 0) return;
    FHashMapNode *aNode = 0;
    FHashMapNode *aHold = 0;
    unsigned int aHashBase = FHashMap::Hash(pKey);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while(aNode) {
            if(aNode->mKey == pKey) {
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

            //TODO:
            //aNewSize = 7;

            SetTableSize(aNewSize);
            aHash = (aHashBase % mTableSize);
        }
    } else {
        SetTableSize(7);
        aHash = (aHashBase % mTableSize);
    }

    FHashMapNode *aNew = (FHashMapNode *)mQueue.PopLast();
    if (aNew == 0) {
        aNew = new FHashMapNode();
    }
    aNew->mKey = pKey;
    aNew->mObject = pObject;
    aNew->mTableNext = 0;
    aNew->mTableIndex = aHash;
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
    ListAdd(aNew);
    mTableCount += 1;
}

void FHashMap::Remove(void *pKey) {
    if (mTableSize > 0) {
        unsigned int aHash = (FHashMap::Hash(pKey) % mTableSize);
        FHashMapNode *aPreviousNode = 0;
        FHashMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                if (aPreviousNode) {
                    aPreviousNode->mTableNext = aNode->mTableNext;
                } else {
                    mTable[aHash] = aNode->mTableNext;
                }
                mQueue.Add(aNode);
                ListRemove(aNode);
                mTableCount -= 1;
                return;
            }
            aPreviousNode = aNode;
            aNode = aNode->mTableNext;
        }
    }
}

void FHashMap::ListAdd(FHashMapNode *pNode) {
    pNode->mListNext = 0;
    if (mListHead == 0) {
        mListHead = pNode;
        mListTail = pNode;
        pNode->mListPrev = 0;
    } else {
        pNode->mListPrev = mListTail;
        mListTail->mListNext = pNode;
        mListTail = pNode;
    }
}

void FHashMap::ListRemove(FHashMapNode *pNode) {
    if (pNode == mListHead) {
        if (mListHead->mListNext) {
            mListHead = mListHead->mListNext;
            mListHead->mListPrev = 0;
        } else {
            mListTail = 0;
            mListHead = 0;
        }
    } else if(pNode == mListTail) {
        mListTail = mListTail->mListPrev;
        mListTail->mListNext = 0;
    } else {
        pNode->mListPrev->mListNext = pNode->mListNext;
        pNode->mListNext->mListPrev = pNode->mListPrev;
    }
    pNode->mListPrev = 0;
    pNode->mListNext = 0;
}

bool FHashMap::IsEmpty() {
    return mTableCount <= 0;
}

bool FHashMap::Exists(void *pKey) {
    return Get(pKey) != 0;
}

void *FHashMap::Get(void *pKey) {
    if(mTableSize > 0) {
        unsigned int aHash = (FHashMap::Hash(pKey) % mTableSize);
        FHashMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                return aNode->mObject;
            }
            aNode = aNode->mTableNext;
        }
    }
    return 0;
}

void FHashMap::AddObjectsToList(FList *pList) {
    FHashMapNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mObject);
        aNode = aNode->mListNext;
    }
}

void FHashMap::AddObjectsToListAndRemoveAll(FList *pList) {
    FHashMapNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mObject);
        mQueue.Add(aNode);
        mTable[aNode->mTableIndex] = 0;
        aNode = aNode->mListNext;
    }
    mListHead = 0;
    mListTail = 0;
    mTableCount = 0;
}

void FHashMap::SetTableSize(int pSize) {
    FHashMapNode *aCheck = 0;
    FHashMapNode *aNext = 0;
    FHashMapNode *aNode = 0;
    int aNewSize = pSize;
    FHashMapNode **aTableNew = new FHashMapNode*[aNewSize];
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
            aNode->mTableIndex = aHash;
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

unsigned int FHashMap::Hash(void *pObject) {
    unsigned long aResult = ((unsigned long)pObject);
    aResult = ((((aResult >> 32) * 33) + 5381) ^ (aResult));
    return (unsigned int)aResult;
}

void FHashMap::GetAllNodes(void *pKey, FList &pList) {
    if (mTableSize > 0) {
        unsigned int aHash = (FHashMap::Hash(pKey) % mTableSize);
        FHashMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mKey == pKey) {
                pList.Add(aNode);
            }
            aNode = (aNode->mTableNext);
        }
    }
}


void FHashMap::Print() {
    Log("____\n____Hash Table____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueue.mCount, mQueue.mSize);
    FHashMapNode *aNode = 0;
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
            Log("{%lx}", (unsigned long)(aNode->mObject));
            aNode = aNode->mTableNext;
        }
        Log("}\n");
    }
}

void FHashMap::PrintList() {
    Log("____\n____Hash List____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueue.mCount, mQueue.mSize);
    int aIndex = 0;
    if (mListHead == 0) {
        Log("*** EMPTY ***\n");
    } else {
        FHashMapNode *aNode = mListHead;
        while (aNode) {
            Log("[%lx], ", (unsigned long)(aNode->mObject));
            aNode = aNode->mListNext;
            aIndex += 1;
            if (aIndex >= 10) {
                aIndex -= 10;
                Log("\n");
            }
        }
    }
    Log("\n\n");
}
