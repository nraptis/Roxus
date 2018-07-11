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

    //Performs a layered A* path finding algorithm, assuming the nodes are
    //set up already.
    bool                                FindPath(GameTile *pStart, GameTile *pEnd);
    
    GameTileConnection                  *mPathEnd;
    GameTileConnection                  *mPathStart;
    
    TilePathFinderHeap                  mOpenList;
    TilePathFinderHeap                  mClosedList;
};

#endif
