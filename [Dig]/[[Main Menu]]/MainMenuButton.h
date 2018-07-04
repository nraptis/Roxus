//
//  MainMenuButton.h
//  DigMMMac
//
//  Created by Nicholas Raptis on 2/26/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#ifndef __DigMMMac__MainMenuButton__
#define __DigMMMac__MainMenuButton__

#include "FButton.h"
#include "FObject.h"
#include "MainMenuTwinkle.h"

class MainMenuButtonGem
{
public:
    MainMenuButtonGem();
    virtual ~MainMenuButtonGem();
    
    virtual void                            Update(float pX, float pY, float pScale);
    virtual void                            Draw(float pX, float pY, float pScale);
    
    float                                   mWobbleRotSin;
    
    MainMenuTwinkle                         mTwinkle;
    
    float                                   mX;
    float                                   mY;
    
};

class MainMenuButton : public FButton
{
public:
    
    MainMenuButton();
    virtual ~MainMenuButton();
    
    
    void                                    SetSprites(FSprite *pSprite, FSprite *pSpriteShadow);
    FSprite                                 *mButtonSprite;
    FSprite                                 *mButtonSpriteShadow;
    
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            ButtonActionRollOver();
    virtual void                            ButtonActionRollOff();
    
    virtual void                            ButtonActionDragOver();
    virtual void                            ButtonActionDragOff();
    
    virtual void                            ButtonActionReleaseOver();
    virtual void                            ButtonActionReleaseOff();
    
    
    
    
    
    float                                   mScaleAdd;
    
    float                                   mBumpSinRotate;
    float                                   mBumpSinSpeedRotate;
    
    float                                   mBumpSinShift;
    float                                   mBumpSinSpeedShift;
    
    float                                   mBumpSinScale;
    float                                   mBumpSinSpeedScale;
    
    float                                   mBumpAmountRotate;
    float                                   mBumpAmountShift;
    float                                   mBumpAmountScale;
    
    float                                   mShiftDirX;
    float                                   mShiftDirY;
    
    void                                    Bump();
    
    
    
    MainMenuButtonGem                       *mGem;
    
    
    
    void                                    AddLeavesRight(float pOffset);
    void                                    AddLeavesLeft(float pOffset);
    
    void                                    LeavesRuffle();
    bool                                    mLeavesRuffle;
    float                                   mLeavesRuffleAmount;
    float                                   mLeavesRuffleFadeIn;
    float                                   mLeavesRuffleSin;
    int                                     mLeavesRuffleTimer;
    
    
    FList                                   mLeavesRight;
    FList                                   mLeavesLeft;
    
    
    void                                    AddLetter(FSprite *pSprite, float pX, float pY);
    void                                    LetterBounce();
    bool                                    mLetterBounce;
    int                                     mLetterBounceIndex;
    int                                     mLetterBounceTimer;
    float                                   mLetterBounceScale;
    FList                                   mLetters;
    
    
};


class MainMenuButtonLetter// : public Object
{
public:
    
    MainMenuButtonLetter();
    virtual ~MainMenuButtonLetter();
    
    virtual void                    Update();
    virtual void                    Draw(float pX, float pY, float pScale);
    
    FSprite                         *mSprite;
    
    float                           mX;
    float                           mY;
    
    
    void                            Bounce();
    
    float                           mBounceAmount;
    
    int                             mBounceTimer;
    
    float                           mBounceSin;
    float                           mBounceSinSpeed;
    
    float                           mBounceScale;
};

class MainMenuButtonLeaf// : public Object
{
public:
    
    MainMenuButtonLeaf();
    virtual ~MainMenuButtonLeaf();
    
    virtual void                    Update();
    
    
    void                            DrawShadow(float pX, float pY, float pScale);
    void                            DrawLeaf(float pX, float pY, float pScale);
    
    void                            Draw(FSprite *pSprite, float pX, float pY, float pScale);
    
    
    float                           mX;
    float                           mY;
    
    float                           mBaseArmRot;
    float                           mBaseArmLength;
    float                           mBaseScale;
    
    float                           mButtonOffset;
    
    float                           mRuffleOffset;
    float                           mRuffleRot;
    
    bool                            mLeft;
    
    FWobbler                        mWobblerRot;
    FWobbler                        mWobblerExtend;
    
};

#endif /* defined(__DigMMMac__MainMenuButton__) */
