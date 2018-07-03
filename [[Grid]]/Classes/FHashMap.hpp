//
//  FHashMap.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/2/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef FHashMap_hpp
#define FHashMap_hpp

#include "FList.h"

class FHashMap;
class FHashMapNode {
    friend class FHashMap;

public:
    FHashMapNode();
    virtual ~FHashMapNode();

    void                                        *mKey;
    void                                        *mObject;

private:
    FHashMapNode                                *mListPrev;
    FHashMapNode                                *mListNext;
    FHashMapNode                                *mTableNext;
    int                                         mTableIndex;
};

class FHashMap {
public:
    FHashMap();
    ~FHashMap();

    void                                        Add(void *pKey, void *pObject);
    void                                        Remove(void *pKey);
    bool                                        Exists(void *pKey);
    void                                        *Get(void *pKey);

    static unsigned int                         Hash(void *pKey);

    bool                                        IsEmpty();

    void                                        RemoveAll();

    void                                        AddObjectsToList(FList *pList);
    void                                        AddObjectsToListAndRemoveAll(FList *pList);

    void                                        GetAllNodes(void *pKey, FList &pList);

public:
    void                                        Print();
    void                                        PrintList();
    FHashMapNode                                *mListHead;
    FHashMapNode                                *mListTail;

protected:

    void                                        ListAdd(FHashMapNode *pNode);
    void                                        ListRemove(FHashMapNode *pNode);
    void                                        SetTableSize(int pSize);

    FHashMapNode                                **mTable;
    int                                         mTableCount;
    int                                         mTableSize;

    FList                                       mQueue;
};

#endif
