//
//  AnimationAffine.h
//  Digplex
//
//  Created by Nick Raptis on 10/4/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__AnimationAffine__
#define __Digplex__AnimationAffine__

#include "FObject.h"
#include "FSpline.h"
#include "MotionPath.h"

class AnimationAffine : public FObject
{
public:
    
    AnimationAffine();
    virtual ~AnimationAffine();
    
    void                                SetStartAffine(float pX, float pY, float pScale);
    
    float                               mAffineStartX;
    float                               mAffineStartY;
    
    float                               mAffineStartScale;

    float                               mX;
    float                               mY;
    
    float                               mScale;
    
    float                               mRotation;
    
    
    MotionPath                          mMotionPath;
    MotionPathCalibrationSpline         *mCalibrationSpline;
    FSpline                             *mSpline;
    
    
};


#endif /* defined(__Digplex__AnimationAffine__) */
