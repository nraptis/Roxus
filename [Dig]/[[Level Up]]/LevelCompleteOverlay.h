//
//  LevelCompleteOverlay.h
//  CrossBone
//
//  Created by Nick Raptis on 7/24/14.
//  Copyright (c) 2014 Department of Homeland Security. All rights reserved.
//

#ifndef __CrossBone__LevelCompleteOverlay__
#define __CrossBone__LevelCompleteOverlay__

#include "MainApp.h"
#include "LevelCompleteMenu.h"
#include "LevelCompleteText.h"
#include "PrizeChestDialog.h"
#include "FPointList.h"
#include "Rex.h"

class LevelCompleteOverlay : public FView
{
public:
    
    LevelCompleteOverlay();
    virtual ~LevelCompleteOverlay();
    
    virtual void                            PositionContent();
    void                                    SetUp(float pScale, FVec2 pCenter, bool pDidWin);
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
	virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    

    int                                     mMode;
    int                                     mModeTimer;
    
    int                                     mFadeInTimer;
    float                                   mFadeBackgroundAlpha;

    bool                                    mWin;
    
    
    PrizeChestDialog                        *mPrizeChest;
    
    
    LevelCompleteText                       *mText;
    LevelCompleteText                       *mTextLose;
    
    
    int                                     mTextAnimationMode;
    int                                     mTextAnimationTime;
    int                                     mTextAnimationTimer;
    float                                   mTextAnimationPercent;
};




#endif /* defined(__CrossBone__LevelCompleteOverlay__) */
