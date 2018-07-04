//
//  ItemBlaster.h
//  Digplex
//
//  Created by Nick Raptis on 12/5/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#ifndef __Digplex__ItemBlaster__
#define __Digplex__ItemBlaster__

#include "ActionProcItem.h"
#include "FParticle.h"
#include "FObject.h"
#include "FSpline.h"

class ItemBlaster : public ActionProcItem
{
public:
    ItemBlaster();
    virtual ~ItemBlaster();
    
    virtual void                            Update();
    virtual void                            Draw();
    virtual void                            DrawEffects();
    virtual void                            DrawFocus(float pX, float pY);
    
    virtual void                            StartTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus);
    virtual void                            UpdateTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus);
    virtual void                            EndTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus);
    
    //virtual int                             GetTriggerChargeTime(){return 3;}
    
    virtual void                            WillCollectItem(void *pItem);
    virtual void                            CollectItem(void *pItem);
    
    virtual bool                            IsReady();
    virtual bool                            WillBeReady();
    
    bool                                    mCoolDownFadeIsHappening;
    FTimer                                  mCoolDownFadeTimer;
    
    int                                     mCollectedEssenceCount;
    int                                     mCollectedEssenceMax;
    float                                   mCollectedEssenceBounceAmount;
    
    
    
    
    
    
    float                                   mChargerGemSpinner1;
    float                                   mChargerGemSpinner2;
    
    
    int                                     mCollectedEssenceOverflow;
    
    bool                                    mCollectEssenceEnqueued;
    
    float                                   mStartX;
    float                                   mStartY;
    
    float                                   mEndX;
    float                                   mEndY;
    
    float                                   mBeamWidth;
    float                                   mBeamWidthSin;
    
    float                                   mContactNodeRot[2];
    float                                   mContactNodeScale[2];
    float                                   mContactNodeScaleSin[2];
    float                                   mContactNodeRotation[2];
    
    float                                   mFrameSpinner;
    
    FSpline                                 mSpline;
    
    FDrawQuadSnake                              mQuadSnake;
    
    FWobbler                                mWobblerCollectRotationShake;
    FWobbler                                mWobblerCollectShiftShake;
    float                                   mHitWobbleAmount;
    
    FWobbler                                mWobblerAlwaysRotate;
    
    
    float                                   mLaserFrame;
    float                                   mLaserFrameMax;
    
    float                                   mTwinkleFrame[2];
    float                                   mGlowBallFrame[2];
    
    float                                   mDirX;
    float                                   mDirY;
    
    float                                   mNormX;
    float                                   mNormY;
    
    int                                     mKnotCount;
    
    float                                   *mKnotControlX;
    float                                   *mKnotControlY;
    
    float                                   *mKnotSin;
    float                                   *mKnotSinSpeed;
    
    float                                   *mKnotShiftMagnitude;
    
    float                                   *mKnotShiftDirX;
    float                                   *mKnotShiftDirY;
    
    int                                     mStartIndex;
    int                                     mEndIndex;
};



#endif /* defined(__Digplex__ItemBlaster__) */
