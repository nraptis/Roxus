//
//  WiggleButton.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/25/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#ifndef __CoreDemo__WiggleButton__
#define __CoreDemo__WiggleButton__

#include "FButton.h"
#include "core_includes.h"

class WiggleButton : public FButton
{
public:
    
    WiggleButton();
    virtual ~WiggleButton();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            ButtonActionRollOver();
    virtual void                            ButtonActionRollOff();
    
    virtual void                            ButtonActionDragOver();
    virtual void                            ButtonActionDragOff();
    
    virtual void                            ButtonActionReleaseOver();
    virtual void                            ButtonActionReleaseOff();
    
    float                                   mScaleAdd;
    
    float                                   mBumpSinRotate;
    float                                   mBumpSinSpeedRotate;
    
    float                                   mBumpSinShift;
    float                                   mBumpSinSpeedShift;
    
    float                                   mBumpSinScale;
    float                                   mBumpSinSpeedScale;
    
    float                                   mBumpAmountRotate;
    float                                   mBumpAmountShift;
    float                                   mBumpAmountScale;
    
    float                                   mShiftDirX;
    float                                   mShiftDirY;
    
    void                                    Bump();
};



#endif /* defined(__CoreDemo__WiggleButton__) */
