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

void FNotificationCenter::Register(FCanvas *pMenu, FCanvas *pButton, const char *pNotification) {

    if (pMenu == 0 || pNotification == 0 || pButton == 0) { return; }

    printf("Adding...\n");
    printf("ADDING M[%s] B[%s] N[%s]\n", pMenu->mName.c(), pButton->mName.c(), pNotification);

    mSendTable.Add(pNotification, pMenu, pButton);
    FNotificationTableNode *aNotificationNode = mSendTable.GetNode(pNotification, pButton);


    //Set up the registration map...
    mRegisterTable.Add(pMenu, aNotificationNode);
    /*
    FNotificationReceiverMapNode *aRegistrationNode = mRegisterTable.Add(pMenu, aNotificationNode);
    if (!aRegistrationNode->mNotificationNodeList.Exists(aNotificationNode)) {
        printf("NotificaButtn{%s}\n", aNotificationNode->mButton->mName.c());
        aRegistrationNode->mNotificationNodeList.Add(aNotificationNode);
    }
    */

}


void FNotificationCenter::Unregister(FCanvas *pMenu, FCanvas *pButton, const char *pNotification) {
    
    if (pMenu && pButton && pNotification) {
        printf("Removing M[%s] B[{GONE}] N[%s]\n", pMenu->mName.c(), pNotification);
    } else {
        printf("Removing M[%s] {ALL}\n", pMenu->mName.c());
    }

    FNotificationReceiverMapNode *aRegistrationNode = mRegisterTable.GetNode(pMenu);
    if (aRegistrationNode != 0) {
        mNodeList.RemoveAll();
        EnumList(FNotificationTableNode, aNotificationNode, aRegistrationNode->mNotificationNodeList) {
            if (pButton == 0 && pNotification == 0) {
                mNodeList.Add(aNotificationNode);
            } else {
                if(aNotificationNode->mButton == pButton && aNotificationNode->mNotification == pNotification) {
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
            if (aNotificationNode->mMenuList.mCount > 0) {
                aNotificationNode->mMenuList.Remove(pMenu);
                if (aNotificationNode->mMenuList.mCount <= 0) {
                    mSendTable.RemoveNode(aNotificationNode);
                }
            }
        }
    }
}

void FNotificationCenter::Unregister(FCanvas *pMenu) {
    Unregister(pMenu, 0, 0);
}

void FNotificationCenter::Post(FCanvas *pButton, const char *pNotification) {

    FNotificationTableNode *aNotificationNode = mSendTable.GetNode(pNotification, pButton);
    bool aDidPost = false;
    if (aNotificationNode != 0) {

        //printf("Posting From Node[%s] {", aNotificationNode->mNotification.c());
        //EnumList(FCanvas, aCanvas, aNotificationNode->mMenuList) {
        //    printf("%s, ", aCanvas->mName.c());
        //}
        //printf("}\n");


        mPostList.RemoveAll();
        EnumList(FCanvas, aCanvas, aNotificationNode->mMenuList) {
            mPostList.Add(aCanvas);
        }
        EnumList(FCanvas, aCanvas, mPostList) {
            aCanvas->BaseNotify(pButton, pNotification);
            aDidPost = true;
            printf("NTF Success Post [%s] Sender: {%s} Receiver: {%s}\n", pNotification, pButton->mName.c(), aCanvas->mName.c());
        }
    }
    
    if (aDidPost == false) {
        printf("NTF Fail Post [%s] Sender: {%s}\n", pNotification, pButton->mName.c());
    }
}

void FNotificationCenter::Print() {
    mSendTable.Print();
    mRegisterTable.Print();
}




