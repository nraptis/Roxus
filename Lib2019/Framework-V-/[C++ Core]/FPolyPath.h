//
//  FPolyPath.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/30/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef __DigMMMac__FPolyPath__
#define __DigMMMac__FPolyPath__

#include "FPointList.h"

class FPolyPathInterp
{
public:
    FPolyPathInterp();
    virtual ~FPolyPathInterp();
    
    bool                            mValid;
    
    int                             mIndexStart;
    int                             mIndexEnd;
    
    float                           mPercentInterp;
    
    float                           mX;
    float                           mY;
    
    float                           mNormX;
    float                           mNormY;
    
    float                           mWidth;
    float                           mRotation;
    
    
    float                           mLineX1;
    float                           mLineY1;
    float                           mLineX2;
    float                           mLineY2;
    
    float                           mLineRotation;
    
    float                           mFaceCenterX;
    float                           mFaceCenterY;
    float                           mFaceCenterRotation;
};

class FPolyPath
{
public:
    
    FPolyPath();
    virtual ~FPolyPath();
    
    void                            Clear();
    void                            Reset();
    
    void                            Add(FPointList *pList);
    void                            Add(float pX, float pY);
    void                            Set(int pIndex, float pX, float pY);

    
    void                            AddValues(int pCount, float pX1, float pY1, float pX2=0.0f, float pY2=0.0f, float pX3=0.0f, float pY3=0.0f, float pX4=0.0f, float pY4=0.0f, float pX5=0.0f, float pY5=0.0f, float pX6=0.0f, float pY6=0.0f, float pX7=0.0f, float pY7=0.0f, float pX8=0.0f, float pY8=0.0f);
    void                            AddValuesReset(int pCount, float pX1, float pY1, float pX2=0.0f, float pY2=0.0f, float pX3=0.0f, float pY3=0.0f, float pX4=0.0f, float pY4=0.0f, float pX5=0.0f, float pY5=0.0f, float pX6=0.0f, float pY6=0.0f, float pX7=0.0f, float pY7=0.0f, float pX8=0.0f, float pY8=0.0f);
    
    void                            Size(int pSize);
    inline void                     SetSize(int pSize){Size(pSize);}

    void                            Generate();
    bool                            mRefresh;
    
    void                            Draw();
    void                            DrawPoints();
    void                            DrawEdges();
    void                            DrawNormals();
    void                            DrawLerps();
    void                            DrawOffset(float pOffset);
    void                            DrawRay(float pPercent, float pLength=36.0f);
    
    
    bool                            Interpolate(float pLength);
    bool                            Interpolate(FPolyPathInterp *pInterp, float pLength);
    
    //float                           Interpolate(float *pArray, float pLength, bool pWrap);
    //bool                            Interpolate(float pLength, bool pWrap, int &pStartIndex, int &pEndIndex);
    FPolyPathInterp                 mInterpolater;
    //float                           GetX(float pLength, bool pWrap=true);
    //float                           GetY(float pLength, bool pWrap=true);
    
    
    void                            GetWithDist(float pDistance, float &pX, float &pY);
    void                            GetWithPercent(float pPercent, float &pX, float &pY);
    void                            GetRandom(float &pX, float &pY);
    
    
    bool                            mClosed;
    bool                            mFlipNormals;
    
    bool                            mWrap;
    
    int                             mCount;
    int                             mSize;
    
    float                           mLength;
    
    float                           mCenterX;
    float                           mCenterY;
    
    float                           *mX;
    float                           *mY;
    
    //float                           *mU;
    //float                           *mV;
    float                           *mDistance;
    float                           *mPercent;
    float                           *mDirX;
    float                           *mDirY;
    float                           *mNormX;
    float                           *mNormY;
    float                           *mLerpX;
    float                           *mLerpY;
    
    float                           *mFaceCenterX;
    float                           *mFaceCenterY;
    float                           *mFaceCenterRotation;
    
    
    float                           *mWidth;
    float                           *mRotation;
    
    void                            Save(FFile *pFile);
    void                            Load(FFile *pFile);
    
};

#endif /* defined(__DigMMMac__FPolyPath__) */
