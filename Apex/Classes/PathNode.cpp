//
//  PathNode.cpp
//  SuperTower
//
//  Created by Raptis, Nicholas on 7/19/18.
//  Copyright © 2018 Raptis, Nicholas. All rights reserved.
//

#include "PathNode.hpp"
#include "GameArena.h"

PathNodeConnection::PathNodeConnection() {
    Reset();
}

PathNodeConnection::~PathNodeConnection() { }

void PathNodeConnection::Reset() {
    mNode = 0;
    mParent = 0;
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
    PathReset();
}

PathNode::~PathNode() { }

//void PathNode::SetUp(int pGridX, int pGridY, int pGridZ) {
//    mGridX = pGridX;mGridY = pGridY;mGridZ = pGridZ;
//    mCenterX = CX(pGridX, pGridZ);mCenterY = CY(pGridY, pGridZ);
//}

void PathNode::DrawConnections() {
    for (int i=0;i<mPathConnectionCount;i++) {
        if (mPathConnection[i].mNode) {
            Graphics::DrawArrow(mCenterX, mCenterY, mPathConnection[i].mNode->mCenterX, mPathConnection[i].mNode->mCenterY);
        }
    }
}

void PathNode::ConnectTo(PathNode *pNode, int pCost) {
    if (mBlocked == false && pNode != 0) {
        if (pNode->mBlocked == false && mPathConnectionCount < NODE_CONNECTION_COUNT) {
            mPathConnection[mPathConnectionCount].mNode = pNode;
            mPathConnection[mPathConnectionCount].mCost = pCost;
            mPathConnectionCount++;
        }
    }
}

void PathNode::PathReset() {
    for (int i=0;i<NODE_CONNECTION_COUNT;i++) {
        mPathConnection[i].Reset();
    }
    mPathConnectionCount = 0;
}

