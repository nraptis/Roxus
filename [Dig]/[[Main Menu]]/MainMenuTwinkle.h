//
//  MainMenuTwinkle.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/8/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__MainMenuTwinkle__
#define __DigMMMac__MainMenuTwinkle__

#include "MainMenuSceneItem.h"
#include "WiggleBoyPart.h"

class MainMenuTwinkle : public WiggleBoyPart
{
public:
    MainMenuTwinkle();
    virtual ~MainMenuTwinkle();
    
    //virtual void                            Update();
    virtual void                            Update(float pX, float pY, float pScale, float pRotation);
    virtual void                            Draw();
    
    float                                   mTwinkleScale;
    float                                   mTwinkleScaleSpeed;
    float                                   mTwinkleRotation;
    
    bool                                    mTwinkleOn;
    
    FRTimer                                 mTimer;
    
};

#endif /* defined(__DigMMMac__MainMenuTwinkle__) */
