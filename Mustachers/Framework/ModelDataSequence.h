//
//  ModelDataSequence.h
//  DoomKnights
//
//  Created by Nick Raptis on 1/20/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "stdafx.h"

#ifndef MODEL_DATA_SEQUENCE_H
#define MODEL_DATA_SEQUENCE_H

class ModelDataIndexed;
class ModelDataOptimizer;
class ModelData;

class ModelDataSequence
{
public:
    
    ModelDataSequence();
    virtual ~ModelDataSequence();
    
    void                            Free();
    
    ModelDataIndexed                *mParent;
    
    int                             mSize;
    int                             mCount;
    ModelDataIndexed                **mData;
    
    void                            Add(ModelDataIndexed *pData);
    
    void                            SetSprite(Sprite *pSprite, bool pFixUVW=true);
    
    bool                            mDisableNormal;
    bool                            mDisableUVW;
    bool                            mDisableIndeces;
    
    bool                            mUsesBaseXYZ;
    bool                            mUsesBaseUVW;
    bool                            mUsesBaseNormal;
    int                             mBindIndex;
    
    virtual void                    GetCentroid(int pFrame, float &pCentroidX, float &pCentroidY, float &pCentroidZ);
    
    void                            FlipXY();
    void                            FlipYZ();
    void                            FlipZX();
    
    
    void                            NegateX();
    void                            NegateY();
    void                            NegateZ();
    
    float                           *mUVWShifted;
    void                            DrawShifted(float pFrame, float pUShift, float pVShift);
    
    void                            Draw(float pFrame);
    
    void                            Load(const char *pFileBase, int pStartIndex, int pEndIndex=-1, const char *pFileReferenceName=0);
    
    void                            Save(const char *pFile);
    void                            Load(const char *pFile);
};

#endif
