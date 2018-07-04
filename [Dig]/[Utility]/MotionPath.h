//
//  MotionPath.h
//  Digplex
//
//  Created by Nick Raptis on 10/4/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__MotionPath__
#define __Digplex__MotionPath__

#include "FSpline.h"
#include "FList.h"

#define CAL_SPLINE_SIZE 256

class MotionPathCalibrationSpline
{
public:
    
    MotionPathCalibrationSpline();
    virtual ~MotionPathCalibrationSpline();
    
    FSpline                                         mSpline;
    
    float                                           mNodeX[CAL_SPLINE_SIZE];
    float                                           mNodeY[CAL_SPLINE_SIZE];
    float                                           mNodeRotation[CAL_SPLINE_SIZE];
    float                                           mNodeLength[CAL_SPLINE_SIZE];
    
    float                                           mLength;
    
    
};

class MotionPath
{
public:
    
    MotionPath();
    virtual ~MotionPath();
    
    
    
    void                                            AddCalibrationSpline(float pStartX, float pStartY, float pStartSpeedX, float pStartSpeedY, float pEndX, float pEndY, float pEndSpeedX, float pEndSpeedY);
    MotionPathCalibrationSpline                     *mCalibrationSpline;
    
    
    MotionPathCalibrationSpline                     *GetBest(float pClosestDistance);
    
    
    FList                                           mCalibrationSplines;
    
    
    
};

#endif /* defined(__Digplex__MotionPath__) */
