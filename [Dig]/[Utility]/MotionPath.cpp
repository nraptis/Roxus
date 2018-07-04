//
//  MotionPath.cpp
//  Digplex
//
//  Created by Nick Raptis on 10/4/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "MotionPath.h"


MotionPathCalibrationSpline::MotionPathCalibrationSpline()
{
    mLength = 0;
    
}

MotionPathCalibrationSpline::~MotionPathCalibrationSpline()
{
    
}


    //FSpline                                         mSpline;
    //float                                           mNodeX[CAL_SPLINE_SIZE];
    //float                                           mNodeY[CAL_SPLINE_SIZE];
    //float                                           mNodeRotation[CAL_SPLINE_SIZE];
    //float                                           mNodeLength[CAL_SPLINE_SIZE];



MotionPath::MotionPath()
{
    mCalibrationSpline = 0;
}

MotionPath::~MotionPath()
{
    
}


void MotionPath::AddCalibrationSpline(float pStartX, float pStartY, float pStartSpeedX, float pStartSpeedY, float pEndX, float pEndY, float pEndSpeedX, float pEndSpeedY)
{
    MotionPathCalibrationSpline *aCSpline = new MotionPathCalibrationSpline();
    
    aCSpline->mSpline.Add(pStartX, pStartY);
    aCSpline->mSpline.Add(pEndX, pEndY);
    
    
    aCSpline->mSpline.SetTangent(0, pStartSpeedX, pStartSpeedY);
    aCSpline->mSpline.SetTangent(1, pEndSpeedX, pEndSpeedY);
    
    
    if(mCalibrationSpline == 0)
    {
        mCalibrationSpline = aCSpline;
    }
    
    
    //mCalibrationSplines
}

MotionPathCalibrationSpline *MotionPath::GetBest(float pClosestDistance)
{
    MotionPathCalibrationSpline *aReturn = mCalibrationSpline;
    
    
    return aReturn;
}

