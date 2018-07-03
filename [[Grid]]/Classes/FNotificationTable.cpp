//
//  FNotificationTable.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "FNotificationTable.hpp"
#include "FCanvas.hpp"
#include "FHashTable.hpp"
#include "core_includes.h"

FNotificationTableNode::FNotificationTableNode() {
    mButton = 0;
    mNextNode = 0;
}

FNotificationTableNode::~FNotificationTableNode() {

}

void FNotificationTableNode::Reset() {
    mMenuList.RemoveAll();
    mButton = 0;
    mNextNode = 0;
}

FNotificationTable::FNotificationTable() {
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;
}

FNotificationTable::~FNotificationTable() {
    FNotificationTableNode *aNode = 0;
    FNotificationTableNode *aNext = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mNextNode;
            delete aNode;
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = 0;
    mTableCount = 0;
    mTableSize = 0;
    FreeList(FNotificationTableNode, mQueue);

    //mTable = 0;
    //mTableCount = 0;
    //mTableSize = 0;

}

FNotificationTableNode *FNotificationTable::Add(const char *pNotification, FCanvas *pMenu, FCanvas *pButton) {
    FNotificationTableNode *aNode = 0;
    FNotificationTableNode *aHold = 0;
    unsigned int aHashBase = Hash(pNotification, pButton);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mNotification == pNotification && aNode->mButton == pButton) {
                if (!aNode->mMenuList.Exists(pMenu)) {
                    aNode->mMenuList.Add(pMenu);
                }
                return aNode;
            }
            aNode = aNode->mNextNode;
        }

        if (mTableCount >= (mTableSize / 2)) {
            int aNewSize = mTableCount + 1;
            if(mTableCount < ((7 / 2) - 1))aNewSize = 7;
            else if(mTableCount < ((13 / 2) - 1))aNewSize = 13;
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

    FNotificationTableNode *aNew = (FNotificationTableNode *)mQueue.PopLast();
    if (!aNew) { aNew = new FNotificationTableNode(); }
    aNew->mNotification = pNotification;
    aNew->mButton = pButton;
    aNew->mMenuList.Add(pMenu);
    aNew->mNextNode = 0;
    if (mTable[aHash]) {
        aNode = mTable[aHash];
        while (aNode) {
            aHold = aNode;
            aNode = aNode->mNextNode;
        }
        aHold->mNextNode = aNew;
    } else {
        mTable[aHash] = aNew;
    }
    mTableCount++;
    return aNew;
}

bool FNotificationTable::RemoveNode(FNotificationTableNode *pNode) {
    if (mTableSize > 0 && pNode != 0) {
        unsigned int aHash = (Hash(pNode->mNotification.c(), pNode->mButton) % mTableSize);
        FNotificationTableNode *aPreviousNode = 0;
        FNotificationTableNode *aNode = mTable[aHash];
        while (aNode) {
            if(aNode == pNode) {
                if (aPreviousNode) {
                    aPreviousNode->mNextNode = aNode->mNextNode;
                } else {
                    mTable[aHash] = aNode->mNextNode;
                }
                aNode->Reset();
                mQueue.Add(aNode);
                mTableCount -= 1;
                return true;
            }
            aPreviousNode = aNode;
            aNode = aNode->mNextNode;
        }
    }
    return false;
}

FNotificationTableNode *FNotificationTable::GetNode(const char *pNotification, FCanvas *pButton) {
    FNotificationTableNode *aResult = 0;
    if (mTableSize > 0) {
        unsigned int aHash = (Hash(pNotification, pButton) % mTableSize);
        FNotificationTableNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mNotification == pNotification && pButton == aNode->mButton) {
                return aNode;
            }
            aNode = aNode->mNextNode;
        }
    }
    return aResult;
}

void FNotificationTable::SetTableSize(int pSize) {
    FNotificationTableNode *aCheck = 0;
    FNotificationTableNode *aNext = 0;
    FNotificationTableNode *aNode = 0;
    int aNewSize = pSize;
    FNotificationTableNode **aTableNew = new FNotificationTableNode*[aNewSize];
    for (int i=0;i<aNewSize;i++) {
        aTableNew[i] = 0;
    }
    unsigned int aHash = 0;
    for (int i=0;i<mTableSize;i++) {
        aNode = mTable[i];
        while (aNode) {
            aNext = aNode->mNextNode;
            aNode->mNextNode = 0;
            aHash = (Hash(aNode->mNotification.c(), aNode->mButton) % aNewSize);
            if (aTableNew[aHash] == 0) {
                aTableNew[aHash] = aNode;
            } else {
                aCheck = aTableNew[aHash];
                while (aCheck->mNextNode) {
                    aCheck = aCheck->mNextNode;
                }
                aCheck->mNextNode = aNode;
            }
            aNode = aNext;
        }
    }
    delete [] mTable;
    mTable = aTableNew;
    mTableSize = aNewSize;
}

unsigned int FNotificationTable::Hash(const char *pNotification, FCanvas *pButton) {
    unsigned int aHash1 = FHashMap::Hash(pButton);
    unsigned int aHash2 = FHashTable::Hash(pNotification);
    return aHash1 ^ aHash2;
}

void FNotificationTable::Print() {
    Log("____\n____Hash Table____\n_Count = %d  Size = %d\n\n", mTableCount, mTableSize);

    FNotificationTableNode *aNode = 0;
    for (int i=0;i<mTableSize;i++) {
        int aCount = 0;
        aNode = mTable[i];
        while (aNode) {
            aCount++;
            aNode = aNode->mNextNode;
        }

        Log("Row[%d] (%d)\t{", i, aCount);

        aNode = mTable[i];
        while (aNode) {

            Log(" ((%s", aNode->mNotification.c());
            Log("|%s) {", aNode->mButton->mName.c());
            int aIndex = 0;
            EnumList(FCanvas, aCanvas, aNode->mMenuList) {
                printf("%s", aCanvas->mName.c());
                if (aIndex != aNode->mMenuList.mCount - 1) {
                    printf(", ");
                }
                aIndex += 1;
            }
            Log("}) ");
            aNode = aNode->mNextNode;
        }
        Log("}\n");
    }
}
