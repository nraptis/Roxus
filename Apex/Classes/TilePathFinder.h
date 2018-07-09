//
//  TilePathFinder.h
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef Mustache_TilePathFinder_h
#define Mustache_TilePathFinder_h

#include "GameTile.h"
#include "TilePathFinderHeap.h"

class TilePathFinder
{
public:
    
    TilePathFinder();
    ~TilePathFinder();
    
    bool                                FindPath(GameTile *pStart, GameTile *pEnd);
    
    GameTileConnection                  *mPathEnd;
    GameTileConnection                  *mPathStart;
    
    TilePathFinderHeap                  mOpenList;
    TilePathFinderHeap                  mClosedList;
};

#endif
