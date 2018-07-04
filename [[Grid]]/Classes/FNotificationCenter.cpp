//
//  FNotificationCenter.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "core_includes.h"
#include "FNotificationCenter.hpp"
#include "FCanvas.hpp"
#include "FHashMap.hpp"
#include "FHashTable.hpp"


FNotificationCenter::FNotificationCenter() { }

FNotificationCenter::~FNotificationCenter() { }

void FNotificationCenter::Register(FCanvas *pListener, FCanvas *pSender, const char *pNotification) {

    if (pListener == 0 || pNotification == 0 || pSender == 0) { return; }
    //FNotificationTableNode *aNotificationNode = mSendTable.Add(pNotification, pListener, pSender);
    //mSendTable.GetNode(pNotification, pSender);
    mRegisterTable.Add(pListener, mSendTable.Add(pNotification, pListener, pSender));
}


void FNotificationCenter::Unregister(FCanvas *pListener, FCanvas *pSender, const char *pNotification) {
    FNotificationReceiverMapNode *aRegistrationNode = mRegisterTable.GetNode(pListener);
    if (aRegistrationNode != 0) {
        mNodeList.RemoveAll();
        EnumList(FNotificationTableNode, aNotificationNode, aRegistrationNode->mNotificationNodeList) {
            //Assuming global removal...
            if (pSender == 0 && pNotification == 0) {
                mNodeList.Add(aNotificationNode);
            } else {
                if(aNotificationNode->mSender == pSender && aNotificationNode->mNotification == pNotification) {
                    mNodeList.Add(aNotificationNode);
                }
            }
        }
        EnumList(FNotificationTableNode, aNotificationNode, mNodeList) {
            if (aRegistrationNode->mNotificationNodeList.mCount > 0) {
                aRegistrationNode->mNotificationNodeList.Remove(aNotificationNode);
                if (aRegistrationNode->mNotificationNodeList.mCount <= 0) {
                    mRegisterTable.RemoveNode(aRegistrationNode);
                }
            }
        }
        EnumList(FNotificationTableNode, aNotificationNode, mNodeList) {
            if (aNotificationNode->mListenerList.mCount > 0) {
                aNotificationNode->mListenerList.Remove(pListener);
                if (aNotificationNode->mListenerList.mCount <= 0) {
                    mSendTable.RemoveNode(aNotificationNode);
                }
            }
        }
    }
}

void FNotificationCenter::Unregister(FCanvas *pListener) {
    Unregister(pListener, 0, 0);
}

void FNotificationCenter::Post(FCanvas *pSender, const char *pNotification) {

    FNotificationTableNode *aNotificationNode = mSendTable.GetNode(pNotification, pSender);
    bool aDidPost = false;
    if (aNotificationNode != 0) {
        mPostList.RemoveAll();
        mPostList.Add(aNotificationNode->mListenerList);
        EnumList(FCanvas, aCanvas, mPostList) {
            aCanvas->BaseNotify(pSender, pNotification);
            aDidPost = true;
            printf("NTF Success Post [%s] Sender: {%X} Receiver: {%X}\n", pNotification, pSender, aCanvas);
        }
    }
    
    if (aDidPost == false) {
        printf("NTF Fail Post [%s] Sender: {%X}\n", pNotification, pSender);
    }
}

FNotificationReceiverMapNode::FNotificationReceiverMapNode() {
    mListener = 0;
    mTableNext = 0;
}

FNotificationReceiverMapNode::~FNotificationReceiverMapNode() { }

void FNotificationReceiverMapNode::Reset() {
    mNotificationNodeList.RemoveAll();
    mListener = 0;
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

FNotificationReceiverMapNode *FNotificationReceiverMap::Add(FCanvas *pListener, FNotificationTableNode *pNode) {
    FNotificationReceiverMapNode *aNode = 0;
    FNotificationReceiverMapNode *aHold = 0;
    unsigned int aHashBase = FHashMap::Hash(pListener);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while(aNode) {
            if(aNode->mListener == pListener) {
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

    aNew->mListener = pListener;
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

FNotificationReceiverMapNode *FNotificationReceiverMap::GetNode(FCanvas *pListener) {
    FNotificationReceiverMapNode *aResult = 0;
    if (mTableSize > 0) {
        unsigned int aHash = FHashMap::Hash(pListener) % mTableSize;
        FNotificationReceiverMapNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mListener == pListener) {
                return aNode;
            }
            aNode = aNode->mTableNext;
        }
    }
    return aResult;
}

bool FNotificationReceiverMap::RemoveNode(FNotificationReceiverMapNode *pNode) {
    if (mTableSize > 0) {
        unsigned int aHash = FHashMap::Hash(pNode->mListener) % mTableSize;
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
            aHash = FHashMap::Hash(aNode->mListener) % aNewSize;
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

FNotificationTableNode::FNotificationTableNode() {
    mSender = 0;
    mNextNode = 0;
}

FNotificationTableNode::~FNotificationTableNode() { }

void FNotificationTableNode::Reset() {
    mListenerList.RemoveAll();
    mSender = 0;
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
}

FNotificationTableNode *FNotificationTable::Add(const char *pNotification, FCanvas *pListener, FCanvas *pSender) {
    FNotificationTableNode *aNode = 0;
    FNotificationTableNode *aHold = 0;
    unsigned int aHashBase = Hash(pNotification, pSender);
    unsigned int aHash = 0;
    if (mTableSize > 0) {
        aHash = (aHashBase % mTableSize);
        aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mNotification == pNotification && aNode->mSender == pSender) {
                if (!aNode->mListenerList.Exists(pListener)) {
                    aNode->mListenerList.Add(pListener);
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
    aNew->mSender = pSender;
    aNew->mListenerList.Add(pListener);
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
        unsigned int aHash = (Hash(pNode->mNotification.c(), pNode->mSender) % mTableSize);
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

FNotificationTableNode *FNotificationTable::GetNode(const char *pNotification, FCanvas *pSender) {
    FNotificationTableNode *aResult = 0;
    if (mTableSize > 0) {
        unsigned int aHash = (Hash(pNotification, pSender) % mTableSize);
        FNotificationTableNode *aNode = mTable[aHash];
        while (aNode) {
            if (aNode->mNotification == pNotification && pSender == aNode->mSender) {
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
            aHash = (Hash(aNode->mNotification.c(), aNode->mSender) % aNewSize);
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

unsigned int FNotificationTable::Hash(const char *pNotification, FCanvas *pSender) {
    unsigned int aHash1 = FHashMap::Hash(pSender);
    unsigned int aHash2 = FHashTable::Hash(pNotification);
    return aHash1 ^ aHash2;
}

