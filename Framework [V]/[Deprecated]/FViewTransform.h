//
//  FViewTransform.h
//  RaptisGame
//
//  Created by Nick Raptis on 3/13/14.
//  Copyright (c) 2014 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_VIEW_TRANSFORM_H
#define FRAMEWORK_VIEW_TRANSFORM_H

#include "FRect.h"

class FView;
class FViewTransform
{
public:
    FViewTransform();
    ~FViewTransform();
    
    void                                        Transform(float &pX, float &pY);
    void                                        Untransform(float &pX, float &pY);
    
    void                                        Transform(float &pX, float &pY, float pWidth, float pHeight);
    void                                        Untransform(float &pX, float &pY, float pWidth, float pHeight);
    
    bool                                        ApplyAbsoluteTransformation(FViewTransform *pParentTransform, float pParentX, float pParentY, float pParentWidth, float pParentHeight, FViewTransform *pTransform, float pX, float pY, float pWidth, float pHeight);
    
    bool                                        ApplyAbsoluteTransformation(FViewTransform *pTransform, float pX, float pY, float pWidth, float pHeight);
    
    bool                                        ContainsPoint(float pX, float pY);
    
    float                                       mX;
    float                                       mY;
    
    float                                       mScale;
    
    float                                       mScaleX;
    float                                       mScaleY;
    
    float                                       mRotation;
    
    float                                       mAnchorX;
    float                                       mAnchorY;
    
    float                                       mCornerX[4];
    float                                       mCornerY[4];
};

#endif /* defined(__RaptisGame__FViewTransform__) */
