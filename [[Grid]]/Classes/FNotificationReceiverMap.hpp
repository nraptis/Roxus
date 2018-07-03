//
//  FNotificationReceiverMap.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef FNotificationReceiverMap_hpp
#define FNotificationReceiverMap_hpp

#include "FList.h"
#include "FNotificationTable.hpp"

class FCanvas;
class FNotificationReceiverMap;
class FNotificationReceiverMapNode {
    friend class FNotificationReceiverMap;

public:
    FNotificationReceiverMapNode();
    virtual ~FNotificationReceiverMapNode();

    void                                        Reset();

    FCanvas                                     *mMenu;

    //FCanvas                                     *mButton;

    FList                                       mNotificationNodeList;

private:

    FNotificationReceiverMapNode                *mTableNext;

};


class FNotificationReceiverMap {
public:
    FNotificationReceiverMap();
    ~FNotificationReceiverMap();
    
    FNotificationReceiverMapNode                *Add(FCanvas *pMenu, FNotificationTableNode *pNode);
    FNotificationReceiverMapNode                *GetNode(FCanvas *pMenu);

    bool                                        RemoveNode(FNotificationReceiverMapNode *pNode);
    
public:
    void                                        Print();

protected:

    void                                        SetTableSize(int pSize);
    
    FNotificationReceiverMapNode                **mTable;
    int                                         mTableCount;
    int                                         mTableSize;

    FList                                       mQueue;
};

#endif

