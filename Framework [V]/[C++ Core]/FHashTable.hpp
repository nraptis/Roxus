//
//  FHashTable.h
//  RaptisGame
//
//  Created by Nick Raptis on 2/25/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_HASH_TABLE_H
#define FRAMEWORK_HASH_TABLE_H

#include "FString.h"
#include "FList.h"

class FHashTableNode {
public:
    FHashTableNode();
    virtual ~FHashTableNode();
    
    void                                        *mObject;
    
    FString                                     mKey;
    FString                                     mKeyFull;

    FHashTableNode                              *mNext;
};

class FHashTable {
public:
    FHashTable();
    virtual ~FHashTable();
    
    FHashTableNode                              *Add(const char *pKey, const char *pKeyFull, void *pObject);
    FHashTableNode                              *Add(char *pKey, char *pKeyFull, void *pObject) { return Add((const char *)(pKey), (const char *)(pKeyFull), pObject); }
    FHashTableNode                              *Add(FString pKey, FString pKeyFull, void *pObject) { return Add((const char *)(pKey.c()), (const char *)(pKeyFull.c()), pObject); }
    FHashTableNode                              *Add(const char *pKey, void *pObject) { return Add(pKey, 0, pObject); }
    FHashTableNode                              *Add(char *pKey, void *pObject) { return Add((const char *)(pKey), pObject); }
    FHashTableNode                              *Add(FString pKey, void *pObject) { return Add((const char *)(pKey.c()), pObject); }

    bool                                        Remove(const char *pKey);
    bool                                        RemoveNode(FHashTableNode *pNode);
    
    //void                                        *Get(void *pKey); //, void *pObject
    void                                        *Get(const char *pKey);
    void                                        *Get(char *pKey){return Get((const char *)(pKey));}
    void                                        *Get(FString pKey){return Get((const char *)(pKey.c()));}
    
    FHashTableNode                              *GetNode(const char *pKey);
    FHashTableNode                              *GetNode(char *pKey){return GetNode((const char *)(pKey));}
    FHashTableNode                              *GetNode(FString pKey){return GetNode((const char *)(pKey.c()));}
    
    void                                        GetAllNodes(const char *pKey, FList &pList);

    static unsigned int                         Hash(const char *pString);
    
    void                                        SetTableSize(int pSize);
    
    bool                                        mAllowDuplicateKeys;
    bool                                        mAllowDuplicateFullKeys;
    
    void                                        Print();
    
    FHashTableNode                              **mTable;
    int                                         mTableCount;
    int                                         mTableSize;

    FList                                       mQueue;
};



#endif 
