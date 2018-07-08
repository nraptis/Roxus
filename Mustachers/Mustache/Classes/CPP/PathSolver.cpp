//
//  PathSolver.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/22/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "PathSolver.h"
#include "GLApp.h"


PathSolverNode::PathSolverNode(int pGridX, int pGridY, int pGridZ)
{
    mNeighbor = 0;
    
    mNeighborCount = 0;
    mNeighborSize = 0;
    
    mGridX = pGridX;
    mGridY = pGridY;
    mGridZ = pGridZ;
    
    mCenterX = CX(mGridX);
    mCenterY = CY(mGridY);
    
}

PathSolverNode::~PathSolverNode()
{
    for(int i=0;i<mNeighborCount;i++)delete mNeighbor[i];
    
    delete [] mNeighbor;
    mNeighbor = 0;
    
    mNeighborCount = 0;
    mNeighborSize = 0;
}

void PathSolverNode::AddNode(PathSolverNode *pNode, int pCost)
{
    if(mNeighborCount == mNeighborSize)
    {
        mNeighborSize = mNeighborCount + mNeighborCount / 2 + 1;
        
        PathSolverNeighbor **aNeightbor = new PathSolverNeighbor*[mNeighborSize];
        
        for(int i=0;i<mNeighborCount;i++)aNeightbor[i] = mNeighbor[i];
        for(int i=mNeighborCount;i<mNeighborSize;i++)aNeightbor[i] = 0;
        
        delete [] mNeighbor;
        
        mNeighbor = aNeightbor;
    }
    
    PathSolverNeighbor *aNew = new PathSolverNeighbor();
    aNew->mNode = pNode;
    aNew->mCost = pCost;
    
    mNeighbor[mNeighborCount] = aNew;
    mNeighborCount++;
}

PathSolver::PathSolver()
{
    mNode = 0;
    mNodeCount = 0;
    mNodeSize = 0;
}

PathSolver::~PathSolver()
{
    Clear();
}

void PathSolver::Draw()
{
    
    for(int i=0;i<mNodeCount;i++)
    {
        PathSolverNode *aNode = mNode[i];
        
        SetColor(0.0f, 0.0f, 0.0f);
        
        DrawRect(aNode->mCenterX - 7, aNode->mCenterY - 2, 15, 15);
        
        SetColor(1.0f, 0.0f, 0.0f);
        
        DrawRect(aNode->mCenterX - 4, aNode->mCenterY - 4, 9, 9);
    }
    
    
    for(int i=0;i<mNodeCount;i++)
    {
        PathSolverNode *aNode = mNode[i];
        
        for(int k=0;k<aNode->mNeighborCount;k++)
        {
            PathSolverNeighbor *aNeighbor = aNode->mNeighbor[k];
            
            PathSolverNode *aChild = aNeighbor->mNode;
            
            SetColor(0.0f, 1.0f, 0.0f);
            
            if(aNode->mGridZ == 0 && aChild->mGridZ == 0)SetColor(0.0f, 1.0f, 0.0f);
            else if(aNode->mGridZ == 1 && aChild->mGridZ == 1)SetColor(0.0f, 0.0f, 1.0f);
            else SetColor(1.0f, 0.0f, 0.0f);
            
            DrawArrow(aNode->mCenterX, aNode->mCenterY, aChild->mCenterX, aChild->mCenterY);
            
            //DrawLine(aNode->mCenterX, aNode->mCenterY, aChild->mCenterX, aChild->mCenterY);
            
        }
    }
    
    
}

void PathSolver::Connect(int pStartX, int pStartY, int pStartZ, int pEndX, int pEndY, int pEndZ, int pCost)
{
    PathSolverNode *aStartNode = 0;
    PathSolverNode *aEndNode = 0;
    
    for(int i=0;i<mNodeCount;i++)
    {
        PathSolverNode *aNode = mNode[i];
        
        if(aNode->mGridX == pStartX && aNode->mGridY == pStartY && aNode->mGridZ == pStartZ)aStartNode = aNode;
        if(aNode->mGridX == pEndX && aNode->mGridY == pEndY && aNode->mGridZ == pEndZ)aEndNode = aNode;
    }
    
    if(aStartNode != 0 && aEndNode != 0)
    {
        if(aStartNode != aEndNode)
        {
            aStartNode->AddNode(aEndNode, pCost);
        }
    }
}

void PathSolver::Clear()
{
    for(int i=0;i<mNodeCount;i++)delete mNode[i];
    
    delete [] mNode;
    mNode = 0;
    
    mNodeCount = 0;
    mNodeSize = 0;
    
}

void PathSolver::AddNode(PathSolverNode *pNode)
{
    if(mNodeCount == mNodeSize)
    {
        mNodeSize = mNodeCount + mNodeCount / 2 + 1;
        
        PathSolverNode **aNode = new PathSolverNode*[mNodeSize];
        
        for(int i=0;i<mNodeCount;i++)aNode[i] = mNode[i];
        for(int i=mNodeCount;i<mNodeSize;i++)aNode[i] = 0;
        
        delete[]mNode;
        
        mNode = aNode;
    }
    
    mNode[mNodeCount] = pNode;
    mNodeCount++;
}
