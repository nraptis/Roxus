//
//  FPointList.h
//  LizDash
//
//  Created by Nick Raptis on 3/24/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef FPOINT_LIST_H
#define FPOINT_LIST_H

#include "ModelDataSequence.h"

class FPointList
{
public:
    
    FPointList();
    virtual ~FPointList();
    
    
    float                   *mX;
    float                   *mY;
    float                   *mZ;
    
    void                    Clear();
    
    void                    Add(float pX, float pY, float pZ);
    void                    Size(int pSize);
    
    float                   GetX(float pFrame);
    float                   GetY(float pFrame);
    float                   GetZ(float pFrame);
    
    int                     mCount;
    int                     mSize;
    
    void                    Load(ModelDataSequence *pSequence, int pStartIndex=-1, int pEndIndex=-1);
    void                    Save(const char *pFile);
    void                    Load(const char *pFile);
    
    
};

#endif
