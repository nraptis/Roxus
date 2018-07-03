//
//  FNotificationCenter.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#include "FNotificationCenter.hpp"

FNotificationCenter::FNotificationCenter() {

}

FNotificationCenter::~FNotificationCenter() {

}

void FNotificationCenter::Register(FCanvas *pReciever, const char *pNotification) {
    FHashTableNode *aNode = mSendMap.Add(pNotification, "", pReciever);
    mNotifyBucket.Add(pReciever, aNode);
}

void FNotificationCenter::Unregister(FCanvas *pReciever, const char *pNotification) {
    FHashTableNode *aTableNode = mSendMap.GetNode(pNotification);
    if (aTableNode) {
        mNotifyBucket.Remove(pReciever, aTableNode);
        mSendMap.RemoveNode(aTableNode);
    }
}

void FNotificationCenter::Unregister(FCanvas *pReciever) {
    FNotificationBucketNode *aBucketNode = mNotifyBucket.Get(pReciever);
    if (aBucketNode) {
        EnumList(FHashTableNode, aTableNode, aBucketNode->mNodeList) {
            mSendMap.RemoveNode(aTableNode);
        }
        mNotifyBucket.Remove(pReciever);
    }
}

void FNotificationCenter::Post(FCanvas *pSender, const char *pNotification) {
    mNodeList.RemoveAll();
    mSendMap.GetAllNodes(pNotification, mNodeList);
    EnumList(FHashTableNode, aNode, mNodeList) {
        FCanvas *aCanvas = (FCanvas *)aNode->mObject;
        aCanvas->BaseNotify(pSender, pNotification);
    }
}

void FNotificationCenter::Post(const char *pNotification) {
    Post(0, pNotification);
}

void FNotificationCenter::Print() {

    mNotifyBucket.Print();
    mSendMap.Print();

}




