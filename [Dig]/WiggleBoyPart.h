//
//  WiggleBoyPart.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__WiggleBoyPart__
#define __DigMMMac__WiggleBoyPart__

#include "FSprite.h"
#include "FMotionObject.h"
#include "GeoQuad.h"

class WiggleBoyAnim;
class WiggleBoyPart : public FMotionObject
{
public:
    
    
    WiggleBoyPart(FSprite *pSprite, WiggleBoyPart *pParent, float pParentOffsetX, float pParentOffsetY, bool pFront=true);
    WiggleBoyPart(FSprite *pSprite, float pOffsetX, float pOffsetY);
    WiggleBoyPart(FSprite *pSprite);
    WiggleBoyPart();
    virtual ~WiggleBoyPart();
    
    
    virtual void                            Update(float pX, float pY, float pScale, float pRotation);
    virtual void                            Draw();
    
    
    //virtual void                            Compute();
    
    void                                    SetSprite(FSprite *pSprite);
    
    void                                    AddPart(WiggleBoyPart *pPart, bool pFront);
    void                                    AddAnim(WiggleBoyAnim *pAnim);
    
    
    void                                    SetParentOffset(float pX, float pY);
    void                                    SetPivotOffset(float pX, float pY);
    void                                    SetOffset(float pX, float pY);
    
    
    
    
    //mParentOffsetX
    
    
    WiggleBoyPart                           *mParent;
    FSprite                                 *mSprite;
    
    //GeoQuad                                 mQuadBase;
    GeoQuad                                 mQuadDraw;
    
    //GeoQuad                                 mQuadTest;
    
    
    float                                   mCornerOffsetX[4];
    float                                   mCornerOffsetY[4];
    
    FList                                   mPartListFront;
    FList                                   mPartListBack;
    
    FList                                   mAnimationList;
    
    //float                                   mX;
    //float                                   mY;
    
    float                                   mOffsetX;
    float                                   mOffsetY;
    
    //float                                   mRotation;
    //float                                   mScale;
    
    float                                   mOffsetRotation;
    float                                   mOffsetScale;
    
    float                                   mPivotOffsetX;
    float                                   mPivotOffsetY;
    
    float                                   mParentOffsetX;
    float                                   mParentOffsetY;
    
    //float                                   mWidth;
    //float                                   mHeight;
    
    
    
    //float                                   mA
    //float                                   mDrawOffsetX;
    //float                                   mDrawOffsetY;
    
    
    float                                   mDrawRotation;
    float                                   mDrawScale;
    
    
};




class WiggleBoyAnim
{
public:
    
    WiggleBoyAnim();
    virtual ~WiggleBoyAnim();
    
    virtual void                            Update(WiggleBoyPart *pPart);
    virtual bool                            IsReady(WiggleBoyPart *pPart);
    
    virtual void                            Activate(WiggleBoyPart *pPart);
    virtual void                            Finish(WiggleBoyPart *pPart);
    
    
    void                                    WillActivate();
    void                                    WillFinish();
    
    
    
    bool                                    mBlockSimul;
    
    int                                     mProcRandom;
    
    int                                     mTimeSleep;
    int                                     mTimeSleepRandom;
    
    int                                     mTimeCooldown;
    int                                     mTimeCooldownRandom;
    
    int                                     mTimeDuration;
    int                                     mTimeDurationRandom;
    
    bool                                    mActive;
    
    
    int                                     mCycleTimerSleep;
    int                                     mCycleTimeSleep;
    
    int                                     mCycleTimerCoolDown;
    int                                     mCycleTimeCoolDown;
    
    int                                     mCycleTimerDuration;
    int                                     mCycleTimeDuration;
};

class WiggleBoyAnimTest : public WiggleBoyAnim
{
public:
    
    WiggleBoyAnimTest();
    virtual ~WiggleBoyAnimTest();
    
    virtual void                            Update(WiggleBoyPart *pPart);
    virtual void                            Activate(WiggleBoyPart *pPart);
    
    int                                     mTestMode;
    
    int                                     mTestActionType;
    
    float                                   mTestValueStart1;
    float                                   mTestValueEnd1;
    
    float                                   mTestValueStart2;
    float                                   mTestValueEnd2;
    
    float                                   mTestDirX;
    float                                   mTestDirY;
    
    int                                     mTestCornerIndex;
};


#endif /* defined(__DigMMMac__WiggleBoyPart__) */
