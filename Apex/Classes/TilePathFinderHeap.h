//
//  TilePathFinderHeap.h
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_TilePathFinderHeap_h
#define Mustache_TilePathFinderHeap_h

#include "GameTile.h"

class TilePathFinderHeap
{
public:
    
    TilePathFinderHeap();
    ~TilePathFinderHeap();
    
    void                            Reset();
    void                            Add(GameTileConnection *pConnection);
    bool                            Contains(GameTileConnection *pConnection);
    
    GameTileConnection              *Pop();
    
    int                             mSize;
    int                             mCount;
    
    GameTileConnection              **mData;
    
};

#endif
