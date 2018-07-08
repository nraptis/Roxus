//
//  PathSolver.h
//  Mustache
//
//  Created by Nick Raptis on 6/22/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_PathSolver_h
#define Mustache_PathSolver_h

class PathSolverNode;
class PathSolverNeighbor
{
public:
    PathSolverNode              *mNode;
    
    int                         mCost;
};

class PathSolverNode
{
public:
    
    PathSolverNode(int pGridX, int pGridY, int pGridZ);
    ~PathSolverNode();
    
    PathSolverNeighbor              **mNeighbor;
    
    int                             mNeighborCount;
    int                             mNeighborSize;
    
    int                             mGridX;
    int                             mGridY;
    int                             mGridZ;
    
    float                           mCenterX;
    float                           mCenterY;
    
    void                            AddNode(PathSolverNode *pNode, int pCost);
    
};



class PathSolver
{
public:
    
    PathSolver();
    ~PathSolver();
    
    PathSolverNode                  **mNode;
    
    int                             mNodeCount;
    int                             mNodeSize;
    
    void                            Draw();
    void                            Clear();
    
    void                            AddNode(PathSolverNode *pNode);
    
    void                            Connect(int pStartX, int pStartY, int pStartZ, int pEndX, int pEndY, int pEndZ, int pCost);

};


#endif
