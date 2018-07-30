//
//  TilePathFinderHeap.h
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef TILE_PATH_FINDER_HEAP_HPP
#define TILE_PATH_FINDER_HEAP_HPP

#include "GameTile.hpp"

class TilePathFinderHeap {
public:
    TilePathFinderHeap();
    ~TilePathFinderHeap();
    
    void                            Reset();
    void                            Add(PathNodeConnection *pConnection);
    bool                            Contains(PathNodeConnection *pConnection);
    
    PathNodeConnection              *Pop();
    
    int                             mSize;
    int                             mCount;
    PathNodeConnection              **mData;
    
};

#endif
