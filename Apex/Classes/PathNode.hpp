//
//  PathNode.hpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 7/19/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#ifndef PATH_NODE_HPP
#define PATH_NODE_HPP

#include <stdio.h>

#define NODE_CONNECTION_COUNT 8

class PathNode;
class PathNodeConnection {
public:
    PathNodeConnection();
    ~PathNodeConnection();

    void                        Reset();

    PathNode                    *mNode;

    PathNodeConnection          *mParent;

    //This is the cost to hop to this node from its parent..
    int                         mCost;

    //A* Costs, these are updated / replaced on each search..
    int                         mCostG;
    int                         mCostH;
    int                         mCostTotal;
};

class PathNode {
public:
    PathNode();
    virtual ~PathNode();

    //virtual void                        SetUp(int pGridX, int pGridY, int pGridZ);
    
    void                                DrawConnections();
    
    //For generic nodes, we have no special "will be blocked" the controller
    //is responsible for either blocking or unblocking a node...
    bool                                mBlocked;

    int                                 mGridX;
    int                                 mGridY;
    int                                 mGridZ;

    float                               mCenterX;
    float                               mCenterY;

    PathNodeConnection                  mPathConnection[NODE_CONNECTION_COUNT];
    int                                 mPathConnectionCount;

    void                                PathReset();
    void                                ConnectTo(PathNode *pNode, int pCost);
};

#endif

