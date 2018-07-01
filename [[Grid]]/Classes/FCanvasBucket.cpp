//
//  FCanvasContainer.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/27/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#include "FCanvasBucket.hpp"
#include "FCanvas.hpp"
#include "core_includes.h"

FCanvasBucketNode::FCanvasBucketNode() {
    mCanvas = 0;
    mTableNext = 0;
    mListPrev = 0;
    mListNext = 0;
    mTableIndex = -1;
}

FCanvasBucketNode::~FCanvasBucketNode() { }

FCanvasBucket::FCanvasBucket() {
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;
    mQueue = 0;
    mQueueCount = 0;
    mQueueSize = 0;
}

FCanvasBucket::~FCanvasBucket() {
    FCanvasBucketNode *aNode = 0;
    FCanvasBucketNode *aNext = 0;
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

    for (int i=0;i<mQueueCount;i++) {
        delete mQueue[i];
    }
    delete [] mQueue;
    mQueue = 0;
    mQueueCount = 0;
    mQueueSize = 0;

    mListHead = 0;
    mListTail = 0;
}

void FCanvasBucket::RemoveAll() {
    FCanvasBucketNode *aNode = mListHead;
    while (aNode) {
        AddNodeToQueue(aNode);
        mTable[aNode->mTableIndex] = 0;
        aNode = aNode->mListNext;
    }
    mListHead = 0;
    mListTail = 0;
    mTableCount = 0;
}

void FCanvasBucket::Add(FCanvas *pCanvas) {
    if (pCanvas == 0) return;
    FCanvasBucketNode *aNode = 0;
    FCanvasBucketNode *aHold = 0;
    unsigned int aHashBase = Hash(pCanvas);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while(aNode) {
            if(aNode->mCanvas == pCanvas) {
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

    FCanvasBucketNode *aNew = DequeueNode();
    if (aNew == 0) {
        aNew = new FCanvasBucketNode();
    }
    aNew->mCanvas = pCanvas;
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

void FCanvasBucket::Remove(FCanvas *pCanvas) {
    if (mTableSize > 0) {
        unsigned int aHash = (Hash(pCanvas) % mTableSize);
        FCanvasBucketNode *aPreviousNode = 0;
        FCanvasBucketNode *aNode = mTable[aHash];
        while (aNode) {
            if(aNode->mCanvas == pCanvas) {
                if (aPreviousNode) {
                    aPreviousNode->mTableNext = aNode->mTableNext;
                } else {
                    mTable[aHash] = aNode->mTableNext;
                }
                AddNodeToQueue(aNode);
                ListRemove(aNode);
                mTableCount -= 1;
                return;
            }
            aPreviousNode = aNode;
            aNode = aNode->mTableNext;
        }
    }
}

void FCanvasBucket::ListAdd(FCanvasBucketNode *pNode) {
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

void FCanvasBucket::ListRemove(FCanvasBucketNode *pNode) {
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

bool FCanvasBucket::IsEmpty() {
    return mTableCount <= 0;
}

bool FCanvasBucket::Exists(FCanvas *pCanvas) {
    if(mTableSize > 0) {
        unsigned int aHash = (Hash(pCanvas) % mTableSize);
        FCanvasBucketNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mCanvas == pCanvas) {
                return true;
            }
            aNode = aNode->mTableNext;
        }
    }
    return false;
}

bool FCanvasBucket::ParentExists(FCanvas *pCanvas) {
    FCanvas *aCanvas = pCanvas->mParent;
    while (aCanvas != 0) {
        if (Exists(aCanvas)) {
            return true;
        }
        aCanvas = aCanvas->mParent;
    }
    return false;
}

void FCanvasBucket::RemoveAllChildren(FCanvas *pCanvas){
    EnumList(FCanvas, aChild, pCanvas->mChildren) {
        Remove(aChild);
        RemoveAllChildren(aChild);
    }
}

void FCanvasBucket::AddCanvasesToList(FList *pList) {
    FCanvasBucketNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mCanvas);
        aNode = aNode->mListNext;
    }
}

void FCanvasBucket::AddCanvasesToListAndRemoveAll(FList *pList) {
    FCanvasBucketNode *aNode = mListHead;
    while (aNode) {
        pList->Add(aNode->mCanvas);
        AddNodeToQueue(aNode);
        mTable[aNode->mTableIndex] = 0;
        aNode = aNode->mListNext;
    }
    mListHead = 0;
    mListTail = 0;
    mTableCount = 0;
}

void FCanvasBucket::AddCanvasesAndChildrenRecursivelyToListAndRemoveAll(FList *pList) {
    AddCanvasesToListAndRemoveAll(pList);
    int aIndex = 0;
    while (aIndex < pList->mCount) {
        FCanvas *aCanvas = (FCanvas *)(pList->mData[aIndex]);
        for (int aChildIndex = 0;aChildIndex<aCanvas->mChildren.mCount;aChildIndex++) {
            pList->Add(aCanvas->mChildren.mData[aChildIndex]);
        }
        aIndex += 1;
    }
}

void FCanvasBucket::SetTableSize(int pSize) {
    FCanvasBucketNode *aCheck = 0;
    FCanvasBucketNode *aNext = 0;
    FCanvasBucketNode *aNode = 0;
    int aNewSize = pSize;
    FCanvasBucketNode **aTableNew = new FCanvasBucketNode*[aNewSize];
    for(int i=0;i<aNewSize;i++) {
        aTableNew[i] = 0;
    }
    unsigned int aHash = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            aNode->mTableNext = 0;
            aHash = Hash(aNode->mCanvas) % aNewSize;

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

unsigned int FCanvasBucket::Hash(FCanvas *pCanvas) {
    unsigned long aResult = ((unsigned long)pCanvas);
    aResult = ((((aResult >> 32) * 33) + 5381) ^ (aResult));
    return (unsigned int)aResult;
}

void FCanvasBucket::AddNodeToQueue(FCanvasBucketNode *pNode) {
    if(mQueueCount >= mQueueSize) {
        int aNewSize = mQueueCount + mQueueCount / 2 + 1;
        FCanvasBucketNode **aNew = new FCanvasBucketNode*[aNewSize];
        for(int i = 0; i<mQueueCount; i++)aNew[i] = mQueue[i];
        delete[] mQueue;
        mQueue = aNew;
        mQueueSize = aNewSize;
    }
    mQueue[mQueueCount] = pNode;
    mQueueCount += 1;
}

FCanvasBucketNode *FCanvasBucket::DequeueNode() {
    if (mQueueCount > 0) {
        mQueueCount -= 1;
        return mQueue[mQueueCount];
    }
    return 0;
}

void FCanvasBucket::Print() {
    Log("____\n____Hash Table____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueueCount, mQueueSize);
    FCanvasBucketNode *aNode = 0;
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
            Log("{%s}", aNode->mCanvas->mName.c());
            aNode = aNode->mTableNext;
        }
        Log("}\n");
    }
}

void FCanvasBucket::PrintList() {
    Log("____\n____Hash List____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueueCount, mQueueSize);

    int aIndex = 0;
    if (mListHead == 0) {
        Log("*** EMPTY ***\n");
    } else {
        FCanvasBucketNode *aNode = mListHead;

        while (aNode) {
            Log("[%s], ", aNode->mCanvas->mName.c());
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



