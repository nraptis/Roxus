//
//  FParticleTemplate.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/8/15.
//  Copyright (c) 2015 Nick Raptis. All rights reserved.
//

#ifndef __DigMMMac__FParticleTemplate__
#define __DigMMMac__FParticleTemplate__

#include "FRandomizer.h"
#include "FObject.h"
#include "FSprite.h"
#include "FSpriteSequence.h"
#include "FColor.h"
#include "FFile.h"
#include "FXML.h"
#include "FPointList.h"
#include "FParticleSource.h"

class FParticle;

class FParticleTemplate
{
public:
    FParticleTemplate();
    virtual ~FParticleTemplate();
    
    void										SetParent(FParticleTemplate *pParent);
    FParticleTemplate							*mSpawnSourceParent;
    
    int                                         mSpawnParticleCount;
    int                                         mSpawnParticleCountRandom;
    
    int                                         mSpawnWaveCount;
    int                                         mSpawnWaveCountRandom;
    
    int                                         mSpawnWaveInterval;
    int                                         mSpawnWaveIntervalRandom;
    
    int                                         mSpawnParticleStartDelayRandom;
    int                                         mSpawnSourceType;
    
    float                                       mSpawnSourceRadius;
    float                                       mSpawnSourceWidth;
    float                                       mSpawnSourceHeight;
    
    FList                                       mSpawnSourcePolygonList;
    FList                                       mSpawnSourcePointCloudList;
    
    float                                       mSpawnOffsetX;
    float                                       mSpawnOffsetY;
    float                                       mSpawnOffsetXRandom;
    float                                       mSpawnOffsetYRandom;
    
    float										mSpawnFrameSpeed;
    float										mSpawnFrameSpeedRandom;
    bool										mSpawnFrameStartRandom;
    bool										mSpawnFrameLoop;
    
    FColor                                      mSpawnColor;
    FColor                                      mSpawnColorExtra;
    FColor                                      mSpawnColorRandom;
    FColor                                      mSpawnColorSpeed;
    FColor                                      mSpawnColorSpeedRandom;
    
    float                                       mSpawnScale;
    float                                       mSpawnScaleRandom;
    float                                       mSpawnScaleSpeed;
    float										mSpawnScaleSpeedAdd;
    float                                       mSpawnScaleSpeedRandom;
    float                                       mSpawnScaleSpeedAccel;
    
    
    
    float                                       mSpawnRotation;
    float                                       mSpawnRotationRandom;
    
    float                                       mSpawnRotationSpeed;
    float                                       mSpawnRotationSpeedRandom;
    float                                       mSpawnRotationSpeedAccel;
    bool                                        mSpawnRotationSpeedNegativeRandom;
    
    float										mSpawnSpeedX;
    float										mSpawnSpeedY;
    float										mSpawnSpeedXRandom;
    float										mSpawnSpeedYRandom;
    float										mSpawnSpeedAccel;
    float										mSpawnSpeedGravityX;
    float										mSpawnSpeedGravityY;
    float										mSpawnSpeedGravityYAdd;
    
    float										mSpawnDirectionalAngle;
    float										mSpawnDirectionalAngleRandom;
    float										mSpawnDirectionalMagnitude;
    float										mSpawnDirectionalMagnitudeRandom;
    float										mSpawnDirectionalPush;
    float										mSpawnDirectionalPushRandom;
    
    int                                         mSpawnDelayAlphaSpeedAddTime;
    float                                       mSpawnDelayAlphaSpeedAdd;
    int                                         mSpawnDelayScaleSpeedAddTime;
    float                                       mSpawnDelayScaleSpeedAdd;
    
    
    void										ResetSpawnAll();
    void										ResetSpawnPosition();
    void										ResetSpawnSpeedAll();
    void										ResetSpawnSpeedBase();
    void										ResetSpawnSpeedDirectional();
    
    void										ResetSpawnColorAll();
    void										ResetSpawnColorBase();
    void										ResetSpawnColorRandom();
    void										ResetSpawnColorSpeed();
    
    void										ResetSpawnScaleAll();
    void										ResetSpawnScaleBase();
    void										ResetSpawnScaleSpeed();
    
    void										ResetSpawnRotationAll();
    void										ResetSpawnRotationBase();
    void										ResetSpawnRotationSpeed();
    
    void										ResetSpawnDelayedTriggers();
    
    
    
    //...
    void                                        QuickSingleton();
    void                                        QuickBlast();
    void                                        QuickBlizzard();
    
    
    void                                        RandomRotAll(int pLevel);
    void                                        RandomRotBase(int pLevel);
    void                                        RandomRotSpeed(int pLevel);
    
    
    
    
    
    
    
    FRandomizer                                 *mRand;
    
    void										TimeTrialReset();
    void										TimeTrialPrepareUpdate();
    void										TimeTrialUpdate(int pTime);
    void										TimeTrialSetPos(float pX, float pY);
    void										TimeTrialDraw();
    
    int											mTimeTrialTick;
    int											mTimeTrialPreviousTick;
    float										mTimeTrialX;
    float										mTimeTrialY;
    //mSource
    
    
    void                                        Clear();
    void                                        Reset();
    
    void                                        Seed(int pSeed);
    void                                        Seed();
    int											mSeed;
    
    
    
    FString										ExportString(const char *pName);
    FString										ExportGeometry(const char *pName);
    FXMLTag										*SaveXML();
    
    void										LoadXML(FXMLTag *pTag);
    void                                        SetSpawnSource(int pSourceType);
    void                                        Clone(FParticleTemplate *pParticleTemplate);
    
    FPointList                                  mSpawnPointList;
    
    FSprite                                     *mSprite;
    FSpriteSequence                             *mSpriteSequence;
    
    
    FParticleSource                             mSource;
};

#endif
