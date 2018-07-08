//
//  ModelDataOptimizer.h
//  DoomKnights
//
//  Created by Nick Raptis on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef MODEL_DATA_OPTIMIZER_H
#define MODEL_DATA_OPTIMIZER_H

class ModelDataIndexed;
class ModelData;
class List;

class ModelDataOptimizerNode
{
public:
    
    float                       mX, mY, mZ;
    float                       mU, mV, mW;
    float                       mNormX, mNormY, mNormZ;
    
    int                         mCount;
    
    int                         mIndex;
    int                         mMapIndex;
    
    ModelDataOptimizerNode      *mNextNode;
};

class ModelDataOptimizer
{
public:
    
    ModelDataOptimizer();
    ~ModelDataOptimizer();
    
    bool                        mIgnoreXYZ;
    bool                        mIgnoreUVW;
    bool                        mIgnoreNormal;
    
    unsigned int                *mIndex;
    int                         mIndexCount;
    int                         mIndexSize;
    
    unsigned int                *mCypher;
    int                         mCypherCount;
    
    float                       *mUVW;
    
    unsigned int                HashFloat(unsigned int pRunningSum, float pFloat);
    
    int                         Hash(float pX, float pY, float pZ,
                                     float pU, float pV, float pW,
                                     float pNormX, float pNormY, float pNormZ);
    
    int                         PushNode(int pMapToIndex, float pX, float pY, float pZ,
                                         float pU, float pV, float pW,
                                         float pNormX, float pNormY, float pNormZ, List *pList);
    
    void                        Push(ModelData *pData, List *pList);
    
    void                        Generate(ModelData *pData);
    void                        Convert(ModelData *pData, ModelDataIndexed *pTarget);
    ModelDataIndexed            *Convert(ModelData *pData);
    
    
    void                        SolveXYZ(ModelData *pReference, ModelData *pTarget);
    void                        SolveUVW(ModelData *pData, ModelData *pTarget);
    void                        SolveNormal(ModelData *pData, ModelData *pTarget);
    
    void                        Print();
    void                        PrintOverview();
    
    void                        SizeHashTable(int pSize, List *pList);
    int                         mHashTableSize;
    
    ModelDataOptimizerNode      **mHashTable;
};

#endif
