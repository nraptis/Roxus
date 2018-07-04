//
//  FNotificationBucket.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

//
//  FNotificationBucket.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef FNotificationBucket_hpp
#define FNotificationBucket_hpp

#include "FList.h"
#include "FHashTable.hpp"

class FCanvas;
class FNotificationBucket;
class FNotificationBucketNode {
    friend class FNotificationBucket;

public:
    FNotificationBucketNode();
    virtual ~FNotificationBucketNode();

    void                                        Clear();

    FCanvas                                     *mKey;
    FList                                       mNodeList;

    FNotificationBucketNode                     *mTableNext;
};

class FNotificationBucket {
public:
    FNotificationBucket();
    ~FNotificationBucket();

    void                                        Add(FCanvas *pKey, FHashTableNode *pNode);
    void                                        Remove(FCanvas *pKey, FHashTableNode *pNode);
    void                                        Remove(FCanvas *pKey);
    FNotificationBucketNode                     *Get(FCanvas *pKey);

    void                                        RemoveAll();

public:
    void                                        Print();

protected:

    void                                        SetTableSize(int pSize);
    
    FNotificationBucketNode                     **mTable;
    int                                         mTableCount;
    int                                         mTableSize;

    FList                                       mQueue;
};

#endif

