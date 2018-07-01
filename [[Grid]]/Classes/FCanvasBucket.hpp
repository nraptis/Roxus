//
//  FCanvasContainer.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 6/27/18.
//  Copyright © 2018 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_CANVAS_BUCKET_HPP
#define FRAMEWORK_CANVAS_BUCKET_HPP

#include "FList.h"

class FCanvas;
class FCanvasBucket;
class FCanvasBucketNode {
    
    friend class FCanvasBucket;

public:
    FCanvasBucketNode();
    virtual ~FCanvasBucketNode();

    FCanvas                                         *mCanvas;

    FCanvasBucketNode                               *mListPrev;
    FCanvasBucketNode                               *mListNext;

private:
    FCanvasBucketNode                               *mTableNext;

    int                                             mTableIndex;

};

class FCanvasBucket {
public:

    FCanvasBucket();
    ~FCanvasBucket();

    void                                            Add(FCanvas *pCanvas);
    void                                            Remove(FCanvas *pCanvas);
    bool                                            Exists(FCanvas *pCanvas);

    bool                                            IsEmpty();

    void                                            RemoveAll();
    bool                                            ParentExists(FCanvas *pCanvas);
    void                                            RemoveAllChildren(FCanvas *pCanvas);

    void                                            AddCanvasesToList(FList *pList);
    void                                            AddCanvasesToListAndRemoveAll(FList *pList);
    void                                            AddCanvasesAndChildrenRecursivelyToListAndRemoveAll(FList *pList);

public:
    void                                            Print();
    void                                            PrintList();
    FCanvasBucketNode                               *mListHead;
    FCanvasBucketNode                               *mListTail;

protected:
    
    void                                            ListAdd(FCanvasBucketNode *pNode);
    void                                            ListRemove(FCanvasBucketNode *pNode);

    unsigned int                                    Hash(FCanvas *pCanvas);
    void                                            SetTableSize(int pSize);

    FCanvasBucketNode                               **mTable;
    int                                             mTableCount;
    int                                             mTableSize;

    void                                            AddNodeToQueue(FCanvasBucketNode *pNode);
    FCanvasBucketNode                               *DequeueNode();

    FCanvasBucketNode                               **mQueue;
    int                                             mQueueCount;
    int                                             mQueueSize;
};

#endif
