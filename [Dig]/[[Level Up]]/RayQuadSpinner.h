//
//  RayQuadSpinner.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/15/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__RayQuadSpinner__
#define __DigMMMac__RayQuadSpinner__

#include "FColor.h"
#include "FMotionObject.h"
#include "FDrawQuad.h"
#include "GeoQuad.h"

class RayQuadSpinnerSpoke
{
public:
    RayQuadSpinnerSpoke();
    
    FDrawQuad                       mQuadBase;
    FDrawQuad                       mQuad;
    
    void                            Transform(float pX, float pY, float pScale, float pRotation, float pAlpha);
    void                            Draw();
    
};

class RayQuadSpinner : public FMotionObject
{
public:
    RayQuadSpinner();
    virtual ~RayQuadSpinner();
    
    
    virtual void                    Update();
    virtual void                    Draw();
    
    void                            Transform(float pX, float pY, float pScale, float pRotation, float pAlpha);
    
    void                            SetSpokeCount(int pCount);
    int                             mSpokeCount;
    
    void                            SetColorInner(FColor pColorInner);
    FColor                          mColorInner;
    
    void                            SetColorOuter(FColor pColorOuter);
    FColor                          mColorOuter;
    
    
    void                            SetRayDist(float pRayDist);
    float                           mRayDist;
    
    void                            SetRayLength(float pRayLength);
    float                           mRayLength;
    
    void                            SetRayWidthInner(float pWidth);
    float                           mRayWidthInner;
    
    void                            SetRayWidthOuter(float pWidth);
    float                           mRayWidthOuter;
    
    void                            SetRayWidth(float pWidthInner, float pWidthOuter);
    
    
    void                            Generate();
    bool                            mGenerate;
    
    
    FList                           mBaseQuadList;
    
    //FDrawQuad
    
    
};

#endif /* defined(__DigMMMac__RayQuadSpinner__) */
