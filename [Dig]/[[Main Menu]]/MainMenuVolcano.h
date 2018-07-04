//
//  MainMenuVolcano.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/5/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__MainMenuVolcano__
#define __DigMMMac__MainMenuVolcano__

#include "MainMenuSceneItem.h"

#include "GeoQuad.h"
#include "FParticle.h"

class MainMenuVolcano : public MainMenuSceneItem
{
public:
    MainMenuVolcano(FSprite *pSprite);
    virtual ~MainMenuVolcano();
    
    virtual void                                Update();
    virtual void                                Draw();
    
    //float
    
    virtual void                                SetRelativePos(float pX, float pY);
    virtual void                                Place(float pCenterX, float pCenterY, float pScale);
    
    void                                        SetMouthPos(float pX, float pY);
    void                                        SetMouthDir(float pDegrees);
    void                                        SetMouthWidth(float pWidth);
    
    float                                       mBaseMouthX;
    float                                       mBaseMouthY;
    
    float                                       mBaseMouthDir;
    float                                       mBaseMouthWidth;
    
    
    GeoQuad                                     mQuadBase;
    GeoQuad                                     mQuadOffset;
    GeoQuad                                     mQuadDraw;
    
    
    float                                       mCornerWobbleSin1;
    float                                       mCornerWobbleSin2;
    
    
    FObjectList                                 mSmokeList;
    float                                       mSmokeBaseDriftSin;
    float                                       mSmokeBaseDriftSinSpeed;
    
    
    int                                         mPuffCount;
    int                                         mPuffMode;
    int                                         mPuffTimer;
    int                                         mPuffBlastCount;
    
    int                                         mPuffBlastDelay;
    
    
    float                                       mPuffBounce;
    float                                       mPuffBounceSpeed;
    
    
    int                                         mWaitTimer;
    int                                         mMode;
    
    
    float                                       mBounceFactor;
    
    //Alright, we're gonna fudge with it on these cocksuckers
    //There's really no 'right' way to jello-ify everything on the screen.
    
    
    
    
    
    
    //FSprite *pSprite
    
    //
    //-34.5f, -56.5f
    
};

class MainMenuVolcanoSmoke : public FParticle
{
public:
    
    MainMenuVolcanoSmoke();
    virtual ~MainMenuVolcanoSmoke();
    
    virtual void                        Update();
    
    
    
    void                                Draw(float pX, float pY, float pScale);
    void                                DrawShadow(float pX, float pY, float pScale);
    void                                Draw(FSprite *pSprite, float pX, float pY, float pScale, bool pShadow);
    
    
    
    
    int                                 mSmokeIndex;
    
    float                               mDriftSin;
    float                               mDriftSinSpeed;
    
    float                               mDriftOffsetX;
    float                               mDriftOffsetY;
    
    float                               mBirthFade;
    
    bool                                mDrawShadow;
    
    
    
    float                               mScatterDirX;
    float                               mScatterDirY;
    
    float                               mScatterMagnitude;
    float                               mScatterFade;
    
    float                               mScatterRotSpeed;
    
    int                                 mScatterTimer;
    
    
};

#endif /* defined(__DigMMMac__MainMenuVolcano__) */


