//
//  PathNode.cpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 7/19/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "PathNode.hpp"
#include "GameArena.hpp"

PathNodeConnection::PathNodeConnection() {
    Reset();
}

PathNodeConnection::~PathNodeConnection() {

}

void PathNodeConnection::Reset() {
    mNode = NULL;
    mPathParent = NULL;
    mHashTableNext = NULL;
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
    mOccupied = false;
    PathReset();
}

PathNode::~PathNode() { }

void PathNode::HardReset() {
    mBlocked = false;
    mOccupied = false;
    mPathConnectionCount = 0;
}

bool PathNode::IsBlocked() {
    bool aResult = false;
    if (mBlocked) { aResult = true; }
    if (mOccupied) { aResult = true; }
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
    //for (int i=0;i<NODE_CONNECTION_COUNT;i++) {
    //    mPathConnection[i].Reset();
    //}
    mPathConnectionCount = 0;
    mOccupied = false;
}
