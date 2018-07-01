//
//  FButton.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/23/13.
//  Copyright (c) 2013 Nick Raptis. All rights reserved.
//

#ifndef FRAMEWORK_BUTTON_H
#define FRAMEWORK_BUTTON_H

#include "FView.h"
#include "FSprite.h"
#include "FColor.h"

class FButtonLayer;

class FButton : public FView
{
public:
    
    FButton();
    virtual ~FButton();
    
    
    void                                    SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown, float pX, float pY);
    inline void                             SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown, FVec2 pPos){SetUp(pSpriteUp, pSpriteOver, pSpriteDown, pPos.mX, pPos.mY);}
    inline void                             SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown){SetUp(pSpriteUp, pSpriteOver, pSpriteDown, mX, mY);}
    
    inline void                             SetUp(FSprite *pSpriteUp, FSprite *pSpriteDown, float pX, float pY){SetUp(pSpriteUp, 0, pSpriteDown, pX, pY);}
    inline void                             SetUp(FSprite *pSpriteUp, FSprite *pSpriteDown, FVec2 pPos){SetUp(pSpriteUp, 0, pSpriteDown, pPos.mX, pPos.mY);}
    inline void                             SetUp(FSprite *pSpriteUp, FSprite *pSpriteDown){SetUp(pSpriteUp, 0, pSpriteDown, mX, mY);}
    
    inline void                             SetUp(FSprite *pSpriteUp, float pX, float pY){SetUp(pSpriteUp, 0, 0, pX, pY);}
    inline void                             SetUp(FSprite *pSpriteUp, FVec2 pPos){SetUp(pSpriteUp, 0, 0, pPos.mX, pPos.mY);}
    inline void                             SetUp(FSprite *pSpriteUp){SetUp(pSpriteUp, 0, 0, mX, mY);}
    
    
    
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteOver, FSprite &pSpriteDown, float pX, float pY){SetUp(&pSpriteUp, &pSpriteOver, &pSpriteDown, pX, pY);}
    
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteOver, FSprite &pSpriteDown, FVec2 pPos){SetUp(&pSpriteUp, &pSpriteOver, &pSpriteDown, pPos.mX, pPos.mY);}
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteOver, FSprite &pSpriteDown){SetUp(&pSpriteUp, &pSpriteOver, &pSpriteDown, mX, mY);}
    
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteDown, float pX, float pY){SetUp(&pSpriteUp, 0, &pSpriteDown, pX, pY);}
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteDown, FVec2 pPos){SetUp(&pSpriteUp, 0, &pSpriteDown, pPos.mX, pPos.mY);}
    inline void                             SetUp(FSprite &pSpriteUp, FSprite &pSpriteDown){SetUp(&pSpriteUp, 0, &pSpriteDown, mX, mY);}
    
    inline void                             SetUp(FSprite &pSpriteUp, float pX, float pY){SetUp(&pSpriteUp, 0, 0, pX, pY);}
    inline void                             SetUp(FSprite &pSpriteUp, FVec2 pPos){SetUp(&pSpriteUp, 0, 0, pPos.mX, pPos.mY);}
    inline void                             SetUp(FSprite &pSpriteUp){SetUp(&pSpriteUp, 0, 0, mX, mY);}
    
    
    
    void                                    SetUp(const char *pPathUp, const char *pPathOver, const char *pPathDown, float pX, float pY);
    inline void                             SetUp(const char *pPathUp, const char *pPathOver, const char *pPathDown, FVec2 pPos){SetUp(pPathUp, pPathOver, pPathDown, pPos.mX, pPos.mY);}
    inline void                             SetUp(const char *pPathUp, const char *pPathOver, const char *pPathDown){SetUp(pPathUp, pPathOver, pPathDown, mX, mY);}
    
    void                                    AddOverlay(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown);
    inline void                             AddOverlay(FSprite *pSpriteUp, FSprite *pSpriteDown){AddOverlay(pSpriteUp, 0, pSpriteDown);}
    inline void                             AddOverlay(FSprite *pSpriteUp){AddOverlay(pSpriteUp, 0, 0);}
    inline void                             AddOverlay(FSprite &pSpriteUp, FSprite &pSpriteOver, FSprite &pSpriteDown){AddOverlay(&pSpriteUp, &pSpriteOver, &pSpriteDown);}
    inline void                             AddOverlay(FSprite &pSpriteUp, FSprite &pSpriteDown){AddOverlay(&pSpriteUp, 0, &pSpriteDown);}
    inline void                             AddOverlay(FSprite &pSpriteUp){AddOverlay(&pSpriteUp, 0, 0);}
    
    void                                    AddUnderlay(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown);
    inline void                             AddUnderlay(FSprite *pSpriteUp, FSprite *pSpriteDown){AddUnderlay(pSpriteUp, 0, pSpriteDown);}
    inline void                             AddUnderlay(FSprite *pSpriteUp){AddUnderlay(pSpriteUp, 0, 0);}
    inline void                             AddUnderlay(FSprite &pSpriteUp, FSprite &pSpriteOver, FSprite &pSpriteDown){AddUnderlay(&pSpriteUp, &pSpriteOver, &pSpriteDown);}
    inline void                             AddUnderlay(FSprite &pSpriteUp, FSprite &pSpriteDown){AddUnderlay(&pSpriteUp, 0, &pSpriteDown);}
    inline void                             AddUnderlay(FSprite &pSpriteUp){AddUnderlay(&pSpriteUp, 0, 0);}
    
    
    virtual void                            Update();
    virtual void                            Draw();
    
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    
    //virtual void                            BaseTouchDown(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
    //virtual void                            BaseTouchMove(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
    //virtual void                            BaseTouchUp(float pX, float pY, float pOriginalX, float pOriginalY, void *pData);
    //virtual void                            BaseTouchFlush();
    
    FList                                   mButtonLayersUnder;
    FButtonLayer                            *mButtonLayer;
    FList                                   mButtonLayersOver;
    
    
    virtual void                            SetListener(FView *pListener);
    FView                                   *mListener;
    
    //void                                  *mClickData;
    
    //bool                                  mIsDown;
    //bool                                  mIsOver;
    
    //bool                                    mDrawManual;
    
    
    bool                                    mTriggerOnDown;
    bool                                    mTriggerOnUp;
    
    
    bool                                    mDrawRectIfSpriteIsNull;
    
    //FSprite                                 *mSpriteUp;
    //FSprite                                 *mSpriteOver;
    //FSprite                                 *mSpriteDown;
    
    //FSprite                                 *mSpriteOverlayUp;
    //FSprite                                 *mSpriteOverlayOver;
    //FSprite                                 *mSpriteOverlayDown;
    
    //FColor                                  mColorUp;
    //FColor                                  mColorOver;
    //FColor                                  mColorDown;
    
    
    //These are for PC only.. Ignore for now..
    
    //FSprite                                 *GetButtonImage();
    //FSprite                                 *GetOverlayImage();
    
    
    
    
    
    /*
    
    //Legacy.. Deprecated..
    void                                    Setup(int x, int y, int pWidth, int pHeight, FView *pListener);
    void                                    Setup(int x, int y, FSprite *pSpriteArray, int pSpriteCount, FView *pListener);
    void                                    Setup(int x, int y, FSprite *pSprite, FView *pListener);
    void                                    Setup(int x, int y, FSprite *pSprite);
    void                                    Setup(float pX, float pY, float pWidth, float pHeight);
    
    void                                    SetUpTopLeft(float pX, float pY, FView *pListener, bool pAutoSize=true);
    void                                    SetUpCentered(float pX, float pY, FView *pListener, bool pAutoSize=true);
     
    */
    
};

class FButtonLayer
{
public:
    FButtonLayer();
    virtual ~FButtonLayer();
    
    void                                    SetUp(FSprite *pSpriteUp, FSprite *pSpriteOver, FSprite *pSpriteDown);
    void                                    SetUp(FSprite *pSpriteUp, FSprite *pSpriteDown){SetUp(pSpriteUp, 0, pSpriteDown);}
    void                                    SetUp(FSprite *pSpriteUp){SetUp(pSpriteUp, 0, 0);}
    
    
    void                                    Draw(FButton *pButton, bool pActive, bool pIsOver, bool pIsDown);
    
    float                                   mWidth;
    float                                   mHeight;
    
    float                                   mOffsetX;
    float                                   mOffsetY;
    
    float                                   mRotation;
    
    float                                   mScale;
    
    FSprite                                 *mSpriteUp;
    FSprite                                 *mSpriteOver;
    FSprite                                 *mSpriteDown;
    
    FColor                                  mColorUp;
    FColor                                  mColorOver;
    FColor                                  mColorDown;
    
    bool                                    mActive;
    
};

#endif
