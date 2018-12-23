//
//  FIndexList.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/14/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef __DigMMMac__FIndexList__
#define __DigMMMac__FIndexList__

#define GFX_MODEL_INDEX_TYPE unsigned short
//#define GFX_MODEL_INDEX_TYPE unsigned int

#include "FSprite.h"
#include "FString.h"
#include "FFile.hpp"

class FIndexList {
public:
    
    FIndexList();
    virtual ~FIndexList();
    
    void                    Clear();
    void                    Reset();
    
    
    GFX_MODEL_INDEX_TYPE	*mIndex;
    int                     mCount;
    int                     mSize;
    
    void                    Add(FIndexList *pList);
    void                    Add(GFX_MODEL_INDEX_TYPE pIndex);
    void                    Set(int pSlot, GFX_MODEL_INDEX_TYPE pIndex);
    
    GFX_MODEL_INDEX_TYPE	Get(int pIndex);
    
    void                    Reverse();
    
    void                    AddIndeces(int pCount, GFX_MODEL_INDEX_TYPE pIndex1 = -1, GFX_MODEL_INDEX_TYPE pIndex2 = -1, GFX_MODEL_INDEX_TYPE pIndex3 = -1, GFX_MODEL_INDEX_TYPE pIndex4 = -1, GFX_MODEL_INDEX_TYPE pIndex5 = -1, GFX_MODEL_INDEX_TYPE pIndex6 = -1, GFX_MODEL_INDEX_TYPE pIndex7 = -1, GFX_MODEL_INDEX_TYPE pIndex8 = -1, GFX_MODEL_INDEX_TYPE pIndex9 = -1, GFX_MODEL_INDEX_TYPE pIndex10 = -1, GFX_MODEL_INDEX_TYPE pIndex11 = -1, GFX_MODEL_INDEX_TYPE pIndex12 = -1, GFX_MODEL_INDEX_TYPE pIndex13 = -1, GFX_MODEL_INDEX_TYPE pIndex14 = -1, GFX_MODEL_INDEX_TYPE pIndex15 = -1);
    void                    AddIndecesReset(int pCount, GFX_MODEL_INDEX_TYPE pIndex1 = -1, GFX_MODEL_INDEX_TYPE pIndex2 = -1, GFX_MODEL_INDEX_TYPE pIndex3 = -1, GFX_MODEL_INDEX_TYPE pIndex4 = -1, GFX_MODEL_INDEX_TYPE pIndex5 = -1, GFX_MODEL_INDEX_TYPE pIndex6 = -1, GFX_MODEL_INDEX_TYPE pIndex7 = -1, GFX_MODEL_INDEX_TYPE pIndex8 = -1, GFX_MODEL_INDEX_TYPE pIndex9 = -1, GFX_MODEL_INDEX_TYPE pIndex10 = -1, GFX_MODEL_INDEX_TYPE pIndex11 = -1, GFX_MODEL_INDEX_TYPE pIndex12 = -1, GFX_MODEL_INDEX_TYPE pIndex13 = -1, GFX_MODEL_INDEX_TYPE pIndex14 = -1, GFX_MODEL_INDEX_TYPE pIndex15 = -1);
    
    void                    Size(int pSize);
    inline void             SetSize(int pSize){ Size(pSize); }
    
    void                    Clone(FIndexList *pPointList);
    inline void             Clone(FIndexList &pPointList){ Clone(&pPointList); }
    
    void                    Save(FFile *pFile);
    void                    Load(FFile *pFile);
    
    int                     GetPrintLineCount();
    FString                 GetPrintLine(int pLineNumber);
    FString                 GetPrintString(const char *pVariableName);
    
    
};

#endif

