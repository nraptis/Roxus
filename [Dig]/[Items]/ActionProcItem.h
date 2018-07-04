//
//  ActionProcItem.h
//  Digplex
//
//  Created by Nick Raptis on 11/30/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef ACTION_PROC__ITEM_H
#define ACTION_PROC__ITEM_H

#include "FView.h"
#include "FObject.h"

class ActionProcItemFocus
{
public:
    ActionProcItemFocus();
    ~ActionProcItemFocus();
    
    int                                 mMatchGridX[3];
    int                                 mMatchGridY[3];
    float                               mMatchCenterX[3];
    float                               mMatchCenterY[3];
    bool                                mMatch[3];
    
    int                                 mObstacleGridX[3];
    int                                 mObstacleGridY[3];
    float                               mObstacleCenterX[3];
    float                               mObstacleCenterY[3];
    bool                                mObstacle[3];
};

class ActionProcItem : public FView
{
public:
    
    ActionProcItem();
    virtual ~ActionProcItem();
    
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            DrawEffects();
    virtual void                            DrawFocus(float pX, float pY);
    
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    
    virtual void                            Notify(void *pSender);
    
    
    
    virtual void                            DrawProgressBars();
    

    virtual void                            SpawnParticle(int pIndex);
    
    virtual void                            WillCollectItem(void *pItem){}
    virtual void                            CollectItem(void *pItem){}
    
    virtual bool                            IsReady();
    virtual bool                            WillBeReady();
    
    
    virtual void                            StartTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus);
    virtual void                            UpdateTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus);
    virtual void                            EndTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus);
    
    virtual int                             GetTriggerChargeTime();
    
    
    
        
    void                                    SetClickable();
    
    
    bool                                    mIsClickable;
    bool                                    mIsClicked;
    //bool                                    mButtonClicked;
    
    
    void                                    SetDragable();
    bool                                    mDragable;
    
    

    float                                   mShakeX;
    float                                   mShakeY;
    
    float                                   mChargePercent;
    float                                   mChargePercentTarget;
    float                                   mChargePercentDrawBlinkSin;
    
    
    float                                   mSelectionHaloRotation1;
    float                                   mSelectionHaloRotation2;
    
    FWobbler                                mSelectionHaloWobbler;
    
    
    
    bool                                    mChargePercentDraw;
    virtual void                            DrawCircle();
    //void                                    Backg
    
    
    
    bool                                    mDelayWait;
    FRTimer                                 mDelayWaitTimer;
    
    bool                                    mDelayReady;
    FRTimer                                 mDelayReadyTimer;
    
    
    
    
    int                                     mItemID;
    int                                     mCharging;
    
    //Possibly a "channeling" and a "triggering".
    virtual bool                            IsTriggering(){return mTriggering;}
    
    //virtual void                            Trigger
    
    bool                                    mTriggering;
    //int                                     mTriggerTime;
    //int                                     mTriggeringTimerTick;
    //int                                     mTriggerChargeTime;
    
    FStepper3                               mTriggerStepper;
    
    float                                   mTriggerBeamWidth[3];
    float                                   mTriggerObstacleBeamWidth[3];
    ActionProcItemFocus                     *mTriggerFocus;
    
    
    
    
    FTimer                                  mTimerSpawnParticle1;
    FTimer                                  mTimerSpawnParticle2;
    FTimer                                  mTimerSpawnParticle3;
    FTimer                                  mTimerSpawnParticle4;
    
    
    virtual bool                            IsCoolingDown(){return mCoolingDown;}
    bool                                    mCoolingDown;
    
    FTimer                                  mCoolDownTimer;
    
    FObjectList                             mAnimations;
    FObjectList                             mAnimationsAdditive;
    FObjectList                             mAnimationsRelative;
    
};


#endif



