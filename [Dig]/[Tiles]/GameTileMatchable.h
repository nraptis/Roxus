//
//  GameTileMatchable.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 8/9/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

#ifndef ___015_Jeep_Arcon__GameTileMatchable__
#define ___015_Jeep_Arcon__GameTileMatchable__

#include "GameTile.h"
#include "ComboTriggerOrb.h"
#include "FParticle.h"

class GameTileMatchable : public GameTile
{
public:
    
    GameTileMatchable();
    virtual ~GameTileMatchable();
    
    virtual void                            Update();
    
    virtual void                            DrawBottom();
    virtual void                            DrawBottomBuried();
    
    virtual void                            Draw();
    virtual void                            DrawBuried();
    
    virtual void                            DrawSkipAccessoryBottom();
    virtual void                            DrawSkipAccessory();
    virtual void                            DrawSkipAccessoryTop();
    
    virtual void                            DrawTop();
    virtual void                            DrawTopBuried();
    
    virtual void                            FallingComplete();
    
    virtual void                            Destroy(int pDestroyType, int pDestroyTime);
    
    virtual void                            SetUp(int pGridX, int pGridY, float pTileWidth, float pTileHeight);
    
    
    void                                    Shimmer();
    float                                   mShimmerPercent;
    bool                                    mShimmer;
    
    
    void                                    SetUpFreshlySpawned();
    
    void                                    GenerateComboTrigger();
    
    void                                    Select();
    void                                    Deselect();
    
    bool                                    mSelected;
    
    bool                                    mSpecial;
    int                                     mSpecialIndex;
    
    
    
    
    ComboTriggerOrb                         *mComboTrigger;
    
    float                                   mSkipAnimFrame1;
    float                                   mSkipAnimFrameSpeed1;
    float                                   mSkipAnimFrameMax1;
    
    float                                   mSkipAnimFrame2;
    float                                   mSkipAnimFrameSpeed2;
    float                                   mSkipAnimFrameMax2;
    
    int                                     mSkipTimer;
    int                                     mSkipTimerMode;
    
    float                                   mSkipScale;
    
    float                                   mDestroyRumbleShakeX;
    float                                   mDestroyRumbleShakeY;
    float                                   mDestroyRumbleShakeAmount;
    
    float                                   mSquishShiftBounce1;
    float                                   mSquishShiftBounce2;
    
    bool                                    mLandedAnimation;
    
    int                                     mLandedAnimationBounces;
    
    float                                   mLandedAnimationSin;
    float                                   mLandedAnimationSinSpeed;
    
    float                                   mLandedAnimationShiftX;
    float                                   mLandedAnimationShiftY;
    
    
    FRTimer                                 mSparkleTimer;
    FObjectList                             mTwinkleList;
    
};


#endif /* defined(___015_Jeep_Arcon__GameTileMatchable__) */
