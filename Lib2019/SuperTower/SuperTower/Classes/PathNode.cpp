//
//  PathNode.cpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 7/19/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "PathNode.hpp"
#include "MapArena.hpp"

PathNodeConnection::PathNodeConnection() {
    Reset();
}

PathNodeConnection::~PathNodeConnection() {

}

void PathNodeConnection::Reset() {
    mNode = NULL;
    mPathParent = NULL;
    //mHashTableNext = NULL;
    
    mOpenHashTableNext = NULL;
    mClosedHashTableNext = NULL;

    mCost = 0;
    mCostG = 0;
    mCostH = 0;
    mCostTotal = 0;
}

PathNode::PathNode() {
    mGridX = -1;
    mGridY = -1;
    mGridZ = -1;
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    mPathConnectionCount = 0;
    mBlocked = false;

    mOccupiedByTower = false;
    mOccupiedByUnit = false;
    mOccupiedByItem = false;
}

PathNode::~PathNode() { }

void PathNode::Unblock() {
    mBlocked = false;

    //mOccupied = false;

    mOccupiedByTower = false;
    mOccupiedByUnit = false;
    mOccupiedByItem = false;
}

void PathNode::HardReset() {
    mBlocked = false;
    mOccupiedByTower = false;
    mOccupiedByUnit = false;
    mOccupiedByItem = false;
    mPathConnectionCount = 0;
}

bool PathNode::IsBlocked() {
    bool aResult = false;
    if (mBlocked) { aResult = true; }

    if (mOccupiedByTower) { aResult = true; }
    if (mOccupiedByUnit) { aResult = true; }
    if (mOccupiedByItem) { aResult = true; }

    return aResult;
}

void PathNode::DrawConnections() {
    for (int i=0;i<mPathConnectionCount;i++) {
        if (mPathConnection[i].mNode) {
            Graphics::DrawArrow(mCenterX, mCenterY, mPathConnection[i].mNode->mCenterX, mPathConnection[i].mNode->mCenterY);
        }
    }
}

void PathNode::ConnectTo(PathNode *pNode, int pCost) {
    if (pNode != 0) {
        //TODO: If we are crashing here, there is an outside logical error.
        //Note: It's possible to arrive at an illegal configuration in editor mode...
        if (mPathConnectionCount < NODE_CONNECTION_COUNT) {
            mPathConnection[mPathConnectionCount].Reset();
            mPathConnection[mPathConnectionCount].mNode = pNode;
            mPathConnection[mPathConnectionCount].mCost = pCost;
            mPathConnectionCount++;
        }
    }
}

void PathNode::PathReset() {
    mPathConnectionCount = 0;

    mOccupiedByTower = false;
    mOccupiedByUnit = false;
    mOccupiedByItem = false;

}
