//
//  NodePathFinder.hpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 8/13/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef NODE_PATH_FIND_HPP
#define NODE_PATH_FIND_HPP

#include "PathNode.hpp"
#include "GameTile.hpp"
#include "TilePathFinderHeap.hpp"

class NodePathFinder {
public:
    NodePathFinder();
    ~NodePathFinder();

    //Performs a layered A* path finding algorithm, assuming the nodes are
    //set up already.
    bool                                FindPath(PathNode *pStart, PathNode *pEnd);

    PathNodeConnection                  *mPathEnd;
    PathNodeConnection                  *mPathStart;
    
    //MAX_UNIT_GRID_WIDTH * GRID_DEPTH * MAX_UNIT_GRID_HEIGHT
    PathNodeConnection                  *mOpenListData[(MAX_UNIT_GRID_WIDTH * MAX_UNIT_GRID_HEIGHT * GRID_DEPTH) + (15149 * 2)];
    PathNodeConnection                  **mOpenListTableData;
    PathNodeConnection                  **mClosedListTableData;

    int                                 mOpenListCount;
    int                                 mOpenListSize;
    int                                 mOpenListTableSize;
    int                                 mClosedListTableSize;
};

#endif
