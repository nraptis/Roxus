//
//  TilePathFinder.h
//  Mustache
//
//  Created by Nick Raptis on 7/5/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#ifndef Mustache_TilePathFinder_h
#define Mustache_TilePathFinder_h

#include "PathNode.hpp"
#include "TilePathFinderHeap.hpp"

class TilePathFinder {
public:
    
    TilePathFinder();
    ~TilePathFinder();

    //Performs a layered A* path finding algorithm, assuming the nodes are
    //set up already.
    bool                                FindPath(PathNode *pStart, PathNode *pEnd);
    
    PathNodeConnection                  *mPathEnd;
    PathNodeConnection                  *mPathStart;
    
    TilePathFinderHeap                  mOpenList;
    TilePathFinderHeap                  mClosedList;
};

#endif
