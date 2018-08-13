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
    
    void                                OpenListAdd(PathNodeConnection *pConnection);
    PathNodeConnection                  *OpenListPop();
    bool                                OpenListExists(PathNodeConnection *pConnection);


    void                                ClosedListAdd(PathNodeConnection *pConnection);
    PathNodeConnection                  *ClosedListPop();
    bool                                ClosedListExists(PathNodeConnection *pConnection);



    //MAX_UNIT_GRID_WIDTH * GRID_DEPTH * MAX_UNIT_GRID_HEIGHT
    PathNodeConnection                  *mOpenListData[((MAX_UNIT_GRID_WIDTH * MAX_UNIT_GRID_HEIGHT * GRID_DEPTH) * 2) + (15149 * 2)];
    //MAX_UNIT_GRID_WIDTH * GRID_DEPTH * MAX_UNIT_GRID_HEIGHT
    PathNodeConnection                  **mClosedListData;
    //15149
    PathNodeConnection                  **mOpenListTableData;
    //15149
    PathNodeConnection                  **mClosedListTableData;

    int                                 mOpenListCount;
    int                                 mOpenListSize;
    int                                 mOpenListTableSize;

    int                                 mClosedListCount;
    int                                 mClosedListSize;
    int                                 mClosedListTableSize;
};

#endif
