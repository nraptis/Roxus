//
//  FNotificationTable.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef FNotificationTable_hpp
#define FNotificationTable_hpp

#include "FString.h"
#include "FList.h"

class FCanvas;
class FNotificationTableNode {
public:
    FNotificationTableNode();
    virtual ~FNotificationTableNode();
    void                                                Reset();
    FString                                             mNotification;
    FCanvas                                             *mButton;
    FList                                               mMenuList;
    FNotificationTableNode                              *mNextNode;
};

class FNotificationTable {
public:
    FNotificationTable();
    virtual ~FNotificationTable();
    FNotificationTableNode                              *Add(const char *pNotification, FCanvas *pMenu, FCanvas *pButton);
    bool                                                RemoveNode(FNotificationTableNode *pNode);
    FNotificationTableNode                              *GetNode(const char *pNotification, FCanvas *pButton);
    void                                                SetTableSize(int pSize);
    unsigned int                                        Hash(const char *pNotification, FCanvas *pButton);
    void                                                Print();
    FNotificationTableNode                              **mTable;
    int                                                 mTableCount;
    int                                                 mTableSize;
    FList                                               mQueue;
};

#endif /* FNotificationTable_hpp */
