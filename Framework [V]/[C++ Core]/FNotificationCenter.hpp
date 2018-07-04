//
//  FNotificationCenter.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef FNotificationCenter_hpp
#define FNotificationCenter_hpp

#include "FList.h"
#include "FString.h"

class FNotificationCenter;
class FCanvas;
class FNotificationTableNode {
    friend class FNotificationCenter;
    friend class FNotificationTable;
    
private:
    FNotificationTableNode();
    virtual ~FNotificationTableNode();
    void                                                Reset();
    FString                                             mNotification;
    FCanvas                                             *mSender;
    FList                                               mListenerList;
    FNotificationTableNode                              *mNextNode;
};

class FNotificationTable {
    friend class FNotificationCenter;

private:
    FNotificationTable();
    virtual ~FNotificationTable();
    FNotificationTableNode                              *Add(const char *pNotification, FCanvas *pListener, FCanvas *pSender);
    bool                                                RemoveNode(FNotificationTableNode *pNode);
    FNotificationTableNode                              *GetNode(const char *pNotification, FCanvas *pSender);
    void                                                SetTableSize(int pSize);
    unsigned int                                        Hash(const char *pNotification, FCanvas *pSender);

    FNotificationTableNode                              **mTable;
    int                                                 mTableCount;
    int                                                 mTableSize;
    FList                                               mQueue;
};

class FNotificationReceiverMapNode {
    friend class FNotificationReceiverMap;
    friend class FNotificationCenter;

private:
    FNotificationReceiverMapNode();
    virtual ~FNotificationReceiverMapNode();
    void                                        Reset();
    FCanvas                                     *mListener;
    FList                                       mNotificationNodeList;
    FNotificationReceiverMapNode                *mTableNext;
};

class FNotificationReceiverMap {
    friend class FNotificationCenter;

private:
    FNotificationReceiverMap();
    ~FNotificationReceiverMap();
    FNotificationReceiverMapNode                *Add(FCanvas *pListener, FNotificationTableNode *pNode);
    FNotificationReceiverMapNode                *GetNode(FCanvas *pListener);
    bool                                        RemoveNode(FNotificationReceiverMapNode *pNode);
    void                                        SetTableSize(int pSize);
    FNotificationReceiverMapNode                **mTable;
    int                                         mTableCount;
    int                                         mTableSize;
    FList                                       mQueue;
};

class FNotificationCenter {
public:
    FNotificationCenter();
    ~FNotificationCenter();

    void                            Register(FCanvas *pListener, FCanvas *pSender, const char *pNotification);
    void                            Unregister(FCanvas *pListener, FCanvas *pSender, const char *pNotification);
    void                            Unregister(FCanvas *pListener);
    void                            Post(FCanvas *pSender, const char *pNotification);


protected:

    //"Forward" map...
    FNotificationTable              mSendTable;

    //"Backward" map...
    FNotificationReceiverMap        mRegisterTable;

    FList                           mNodeList;
    FList                           mPostList;
};

#endif

