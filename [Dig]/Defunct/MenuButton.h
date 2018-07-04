//
//  MenuButton.h
//  CoreDemo
//
//  Created by Nick Raptis on 11/8/13.
//  Copyright (c) 2013 Union AdWorks Inc. All rights reserved.
//

#ifndef __CoreDemo__MenuButton__
#define __CoreDemo__MenuButton__


#include "FButton.h"
#include "core_includes.h"

class MenuButton : public FButton
{
public:
    
    MenuButton();
    virtual ~MenuButton();
    
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



#endif /* defined(__CoreDemo__MenuButton__) */
