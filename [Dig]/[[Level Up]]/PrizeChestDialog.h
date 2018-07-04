//
//  PrizeChestDialog.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/15/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__PrizeChestDialog__
#define __DigMMMac__PrizeChestDialog__

#include "FView.h"
#include "RayQuadSpinner.h"

class PrizeChestDialog : public FView
{
public:
    PrizeChestDialog();
    virtual ~PrizeChestDialog();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            Notify(void *pSender);
    
    
    bool                                    mChest;
    bool                                    mChestOpen;
    float                                   mChestX;
    float                                   mChestY;
    float                                   mChestScale;
    float                                   mChestScaleX;
    float                                   mChestScaleY;
    float                                   mChestRotation;
    
    
    RayQuadSpinner                          mChestSpinner1;
    
    float                                   mAnimationEnterPercent;
    bool                                    mAnimationEnter;
    int                                     mAnimationEnterMode;
    int                                     mAnimationEnterTimer;
    int                                     mAnimationEnterTime;
    
    float                                   mBackScale;
    float                                   mBackScaleX;
    float                                   mBackScaleY;
    
    
};

#endif /* defined(__DigMMMac__PrizeChestDialog__) */
