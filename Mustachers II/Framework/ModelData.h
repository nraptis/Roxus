//
//  ModelData.h
//  Chrysler300Reloaded
//
//  Created by Nick Raptis on 1/18/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef MODEL_DATA_H
#define MODEL_DATA_H

#include "Sprite.h"
#include "FString.h"
#include "Buffer.h"
#include "Graphics.h"


//90 z clockwise (10,8,2)  ==> (

class ModelData
{
public:
    
    ModelData();
    virtual ~ModelData();
    
    float               *mXYZ;
    float               *mUVW;
    float               *mNormal;
    
    unsigned int        mProperties;
    
    virtual void        Save(Buffer *pBuffer);
    virtual void        Save(const char *pFile);
    
    virtual void        LoadData(Buffer *pBuffer);
    virtual void        LoadData(const char *pFile);
    
    void                SetSprite(Sprite *pSprite, bool pFixUVW=true);
    
    void                DiscardXYZ();
    void                DiscardUVW();
    void                DiscardNormal();
    
    
    void                FitUVW(float pStartU, float pEndU, float pStartV, float pEndV);
    
    ModelData           *Clone();
    
    virtual void        GetCentroid(float &pCentroidX, float &pCentroidY, float &pCentroidZ);
    
    void                AddXYZ(float pX, float pY, float pZ);
    void                SizeXYZ(int pSize);
    
    void                AddUVW(float pU, float pV, float pW);
    void                SizeUVW(int pSize);
    
    void                AddNormal(float pNormX, float pNormY, float pNormZ);
    void                SizeNormal(int pSize);
    
    inline float        *ResizeTriple(float *pData, int pCount, int pSize);
    inline void         SetTriple(unsigned int pIndex, float *pArray, float pValue1, float pValue2, float pValue3);
    
    void                CopyXYZ(float *pXYZ, int pCount);
    void                CopyUVW(float *pUVW, int pCount);
    void                CopyNorm(float *pNorm, int pCount);
    
    void                InvertU();
    void                InvertV();
    void                InvertW();
    
    void                FlipXY();
    void                FlipYZ();
    void                FlipZX();
    
    
    void                NegateX();
    void                NegateY();
    void                NegateZ();
    
    
    float               GetX(int pIndex);
    float               GetY(int pIndex);
    float               GetZ(int pIndex);
    
    float               GetU(int pIndex);
    float               GetV(int pIndex);
    float               GetW(int pIndex);
    
    float               GetNormX(int pIndex);
    float               GetNormY(int pIndex);
    float               GetNormZ(int pIndex);
    
    int                 mBindIndex;
    
    int                 mXYZCount;
    int                 mXYZSize;
    
    int                 mUVWCount;
    int                 mUVWSize;
    
    int                 mNormalCount;
    int                 mNormalSize;
    
    virtual void        Print();
    virtual void        PrintOverview();
    
    virtual void        Draw();
    virtual void        Draw(int pBindIndex);
    
    virtual void        DrawEfficient();
    virtual void        DrawEfficientSetup();
    
    virtual void        Free();
};

class ModelDataIndexed : public ModelData
{
public:
    
    ModelDataIndexed();
    virtual ~ModelDataIndexed();
    
    float               *mUVWShifted;
    
    virtual void        Save(Buffer *pBuffer);
    virtual void        Save(const char *pFile);
    
    virtual void        LoadData(Buffer *pBuffer);
    virtual void        LoadData(const char *pFile);
    
    void                Load(const char *pFile);
    inline void         Load(char *pFile){Load((const char *)pFile);}
    inline void         Load(FString pFile){Load((const char *)(pFile.c()));}
    
    
    
    void                Load(const char *pFile, Sprite &pSprite);
    inline void         Load(char *pFile, Sprite &pSprite){Load((const char *)pFile, pSprite);}
    inline void         Load(FString pFile, Sprite &pSprite){Load((const char *)(pFile.c()), pSprite);}
    
    
    
    void                Load(const char *pFileStart, int pIndex, const char *pFileEnd=0);
    void                Load(const char *pFileStart, int pIndex, const char *pFileEnd, Sprite &pSprite);
    
    
    
    ModelData           *GetData();
    void                DiscardIndeces();
    
    virtual void        GetCentroid(float &pCentroidX, float &pCentroidY, float &pCentroidZ);
    
    void                CopyIndex(GRAPHICS_MODEL_TYPE *pIndex, int pCount);
    
    ModelDataIndexed    *Clone();
    
    void                Clone(ModelDataIndexed *pTarget);
    
    void                PrintCode();
    
    GRAPHICS_MODEL_TYPE *mIndex;
    
    int                 mIndexCount;
    int                 mIndexSize;
    
    void                AddIndex(GRAPHICS_MODEL_TYPE pIndex);
    void                SizeIndex(int pSize);
    
    virtual void        Draw();
    
    virtual void        DrawShifted(float pUShift, float pVShift);
    virtual void        DrawShifted(ModelDataIndexed *pReference, float pUShift, float pVShift);
    virtual void        Draw(int pBindIndex);
    
    virtual void        DrawEfficient();
    virtual void        DrawEfficientSetup();
    
    virtual void        Free();
};

#endif
