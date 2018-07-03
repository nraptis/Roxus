//
//  FNotificationReceiverMap.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "FNotificationReceiverMap.hpp"
#include "FHashMap.hpp"
#include "core_includes.h"

FNotificationReceiverMapNode::FNotificationReceiverMapNode() {
    mMenu = 0;
    mTableNext = 0;
}

FNotificationReceiverMapNode::~FNotificationReceiverMapNode() { }


void FNotificationReceiverMapNode::Reset() {
    mNotificationNodeList.RemoveAll();
    mMenu = 0;
    mTableNext = 0;
}

FNotificationReceiverMap::FNotificationReceiverMap() {
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;
}

FNotificationReceiverMap::~FNotificationReceiverMap() {
    FNotificationReceiverMapNode *aNode = 0;
    FNotificationReceiverMapNode *aNext = 0;
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
    FreeList(FNotificationReceiverMapNode, mQueue);
}

FNotificationReceiverMapNode *FNotificationReceiverMap::Add(FCanvas *pMenu, FNotificationTableNode *pNode) {
    FNotificationReceiverMapNode *aNode = 0;
    FNotificationReceiverMapNode *aHold = 0;
    unsigned int aHashBase = FHashMap::Hash(pMenu);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while(aNode) {
            if(aNode->mMenu == pMenu) {
                if (!aNode->mNotificationNodeList.Exists(pNode)) {
                    aNode->mNotificationNodeList.Add(pNode);
                }
                return aNode;
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

    FNotificationReceiverMapNode *aNew = (FNotificationReceiverMapNode *)mQueue.PopLast();
    if (aNew == 0) {
        aNew = new FNotificationReceiverMapNode();
    }

    aNew->mMenu = pMenu;
    aNew->mNotificationNodeList.Add(pNode);
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
    return aNew;
}

FNotificationReceiverMapNode *FNotificationReceiverMap::GetNode(FCanvas *pMenu) {
    FNotificationReceiverMapNode *aResult = 0;
    if (mTableSize > 0) {
        unsigned int aHash = FHashMap::Hash(pMenu) % mTableSize;
        FNotificationReceiverMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mMenu == pMenu) {
                return aNode;
            }
            aNode = aNode->mTableNext;
        }
    }
    return aResult;
}

bool FNotificationReceiverMap::RemoveNode(FNotificationReceiverMapNode *pNode) {
    if (mTableSize > 0) {
        unsigned int aHash = FHashMap::Hash(pNode->mMenu) % mTableSize;
        FNotificationReceiverMapNode *aPreviousNode = 0;
        FNotificationReceiverMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode == pNode) {
                if (aPreviousNode) {
                    aPreviousNode->mTableNext = aNode->mTableNext;
                } else {
                    mTable[aHash] = aNode->mTableNext;
                }
                aNode->Reset();
                mQueue.Add(aNode);
                mTableCount -= 1;
                return true;
            }
            aPreviousNode = aNode;
            aNode = aNode->mTableNext;
        }
    }
    return false;
}

void FNotificationReceiverMap::SetTableSize(int pSize) {
    FNotificationReceiverMapNode *aCheck = 0;
    FNotificationReceiverMapNode *aNext = 0;
    FNotificationReceiverMapNode *aNode = 0;
    int aNewSize = pSize;
    FNotificationReceiverMapNode **aTableNew = new FNotificationReceiverMapNode*[aNewSize];
    for(int i=0;i<aNewSize;i++) {
        aTableNew[i] = 0;
    }
    unsigned int aHash = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mTableNext;
            aNode->mTableNext = 0;
            aHash = FHashMap::Hash(aNode->mMenu) % aNewSize;
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


//FNotificationReceiverMapNode                *Add(FCanvas *pButton, FCanvas *pMenu);
//bool                                        RemoveNode(FNotificationReceiverMapNode *pNode);

//FCanvas *pButton, FCanvas *pMenu

void FNotificationReceiverMap::Print() {

    Log("____\n____ReceiverMap____\n_Count = %d  Size = %d QueueCount = %d QueueSize = %d\n\n", mTableCount, mTableSize, mQueue.mCount, mQueue.mSize);
    FNotificationReceiverMapNode *aNode = 0;
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
            Log("{%s [%d]}", aNode->mMenu->mName.c(), aNode->mNotificationNodeList.mCount);
            aNode = aNode->mTableNext;
        }
        Log("}\n");
    }
}

