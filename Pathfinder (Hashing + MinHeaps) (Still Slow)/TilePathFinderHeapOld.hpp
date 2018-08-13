//
//  TilePathFinderHeapOldOld.hpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 8/10/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef TilePathFinderHeapOldOld_hpp
#define TilePathFinderHeapOldOld_hpp

#include "GameTile.hpp"
#include "PriorityQueue.hpp"
#include "FHashTable.hpp"

class TilePathFinderHeapOld {
public:
    TilePathFinderHeapOld();
    ~TilePathFinderHeapOld();

    void                            Reset();
    void                            Add(PathNodeConnection *pConnection);
    bool                            Contains(PathNodeConnection *pConnection);

    PathNodeConnection              *Pop();

    int                             mSize;
    int                             mCount;
    PathNodeConnection              **mData;

    FHashMap                        mHashMap;

};

#endif /* TilePathFinderHeapOldOld_hpp */
