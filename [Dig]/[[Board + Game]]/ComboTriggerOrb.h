//
//  ComboTriggerOrb.h
//  2015 Jeep Arcon
//
//  Created by Nick Raptis on 9/7/14.
//  Copyright (c) 2014 Chrysler Group LLC. All rights reserved.
//

//So basically while these little specks are floating around,

#ifndef ___015_Jeep_Arcon__ComboTriggerOrb__
#define ___015_Jeep_Arcon__ComboTriggerOrb__

#include "FObject.h"
#include "FView.h"
#include "FSpline.h"
#include "FAnimation.h"

class BoardGenericMatch;

class ComboTriggerOrb : public FObject
{
public:
    
    ComboTriggerOrb();
    virtual ~ComboTriggerOrb();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    FView                               *mListener;
    
    bool                                IsActive(){return ((mMode <= 2) && (mDidFizzle == false));}
    
    void                                StartSwirl(int pGridX, int pGridY, float pCenterX, float pCenterY);
    
    void                                Trigger(int pGridX, int pGridY, float pTargetX, float pTargetY);
    void                                Trigger(BoardGenericMatch *pMatch);
    void                                TriggerFizzle();
    
    void                                PhaseOut();
    
    //StepAnimationLayerParticleGroup     mLayerSparkles;
    //StepAnimationLayer                  mLayerSparkles;
    
    float                               mFrame;
    float                               mFrameSpeed;
    
    FObjectList                         mSparkles;
    FObjectList                         mAnimations;
    
    
    BoardGenericMatch                   *mMatch;
    
    //StepAnimationLayerBlast             *mStartBlastLayer;
    //StepAnimationLayerParticleGroup     *mStartParticleLayer;
    
    //StepAnimationLayerBlast             *mExplodeBlastLayer;
    //StepAnimationLayerParticleGroup     *mExplodeParticleLayer;
    
    FSpline                             mSpline;
    
    FAnimation                          mAnimation;
    
    int                                 mSparkleGenerationTimer;
    
    bool                                mAttachedToTile;
    //int
    
    bool                                mReadyToTrigger;
    
    bool                                mDidFizzle;
    
    int                                 mTriggerTick;
    int                                 mTriggerTickTotal;
    
    float                               mOrbitCenterX;
    float                               mOrbitCenterY;
    
    float                               mOrbitTargetCenterX;
    float                               mOrbitTargetCenterY;
    
    float                               mOrbitSpeedX;
    float                               mOrbitSpeedY;
    
    float                               mOrbitRadius;
    
    float                               mOrbitRotationAngle;
    
    float                               mOrbitRotationAxis;
    float                               mOrbitRotationSpeed;
    
    float                               mOrbitScale;
    
    float                               mOrbitRotation;
    
    float                               mOrbitX;
    float                               mOrbitY;
    
    
    //int                                 mStartGridX;
    //int                                 mStartGridY;
    
    
    int                                 mTargetGridX;
    int                                 mTargetGridY;
    
    //float                               mBoltTargetX;
    //float                               mBoltTargetY;
    
    //float                               mStartX;
    //float                               mStartY;
    
    float                               mFade;
    
    //float                               mBoltX;
    //float                               mBoltY;
    
    //float                               mBoltRotation;
    
    //bool                                mBoltShowing;
    
    
    float                               mSpinnerRotation1;
    float                               mSpinnerRotationSpeed1;
    
    float                               mSpinnerRotation2;
    float                               mSpinnerRotationSpeed2;
    
    float                               mScaleSin;
    
    
    int                                 mMode;
    int                                 mModeTimer;
    
};


#endif /* defined(___015_Jeep_Arcon__ComboTriggerOrb__) */
