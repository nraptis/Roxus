//
//  HeroStego.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__HeroStego__
#define __DigMMMac__HeroStego__

#include "WiggleBoy.h"
#include "FObject.h"

class HeroStego : public WiggleBoy
{
public:
    
    //sleep for between 60 and 150 updates
    //flang from  [12-16] to [18-23] between 2 and 4 times,
    //with smoothing function..
    
    
    HeroStego();
    virtual ~HeroStego();
    
    virtual void                            Update();
    
    //WiggleBoyPart                           *mPartReference;
    
    WiggleBoyPart                           *mPartBody;
    WiggleBoyPart                           *mPartBelly;
    
    WiggleBoyPart                           *mPartSpike1;
    WiggleBoyPart                           *mPartSpike2;
    WiggleBoyPart                           *mPartSpike3;
    
    WiggleBoyPart                           *mPartHeadNub;
    WiggleBoyPart                           *mPartHead;
    
    WiggleBoyPart                           *mPartTail;
    
    
    WiggleBoyPart                           *mPartFootFront1;
    WiggleBoyPart                           *mPartFootFront2;
    
    WiggleBoyPart                           *mPartEye;
    WiggleBoyPart                           *mPartNostril;
    
    
    WiggleBoyPart                           *mPartTailSpike1;
    WiggleBoyPart                           *mPartTailSpike2;
    WiggleBoyPart                           *mPartTailSpike3;
    WiggleBoyPart                           *mPartTailSpike4;

    
    
    
    
    
    FRTimer                                 mAnimBounceTimer;
    FStepper3                               mAnimBounceStepper;
    int                                     mAnimBounceCount;
    int                                     mAnimBounceMode;
    
    
    FRTimer                                 mAnimSpikeTimer;
    FStepper3                               mAnimSpikeStepper;
    int                                     mAnimSpikeCount;
    int                                     mAnimSpikeMode;
    
    FRTimer                                 mAnimTailWagTimer;
    FWobbler                                mAnimTailWagWobbler;
    int                                     mAnimTailWagCount;
    int                                     mAnimTailWagMode;
    
    
    FWobbler                                mAnimSwaySpikeWobbler1;
    FWobbler                                mAnimSwaySpikeWobbler2;
    FWobbler                                mAnimSwaySpikeWobbler3;
    
    
    
    FRTimer                                 mAnimTailSpikeTimer;
    FStepper3                               mAnimTailSpikeStepper;
    int                                     mAnimTailSpikeCount;
    int                                     mAnimTailSpikeMode;
    
    FRTimer                                 mAnimNoseTimer;
    FStepper3                               mAnimNoseStepper;
    int                                     mAnimNoseCount;
    int                                     mAnimNoseMode;
    
    
    FRTimer                                 mAnimCraneNeckTimer;
    FStepper3                               mAnimCraneNeckStepper;
    int                                     mAnimCraneNeckCount;
    int                                     mAnimCraneNeckMode;
    
};

#endif /* defined(__DigMMMac__HeroStego__) */



