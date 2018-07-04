//
//  GameInterfaceTop.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/26/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#ifndef __CoreDemo__GameInterfaceTop__
#define __CoreDemo__GameInterfaceTop__

#include "MainApp.h"
#include "FView.h"
#include "GameInterfaceElement.h"
#include "FSprite.h"
#include "FTexture.h"

class GameInterfaceStarIndicator : public GameInterfaceElement
{
public:
    
    GameInterfaceStarIndicator();
    virtual ~GameInterfaceStarIndicator();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    void                                    DiscoverStar();
    
    float                                   mStarIndicatorX[3];
    float                                   mStarIndicatorY[3];
    
    bool                                    mStarEarned[3];
    
    int                                     mEarnedCount;
};

class GameInterfaceScoreBar : public GameInterfaceElement
{
public:
    GameInterfaceScoreBar();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    void                                    SetValue(int pValue);
    
    int                                     mScoreDisplay;
    FString                                 mScoreString;
};

class GameInterfaceProgressbar : public GameInterfaceElement
{
public:
    GameInterfaceProgressbar();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    float                                   mProgress;
    
    FTextureRect                            mTextureRect;
    
    void                                    ReceivedEssence(int pCount);
    
    int                                     mValueMax;
    int                                     mValue;
    
    int                                     mHitTimer;
    float                                   mHitShake;
};

class GameInterfaceMovesBox : public GameInterfaceElement
{
public:
    GameInterfaceMovesBox();
    virtual ~GameInterfaceMovesBox();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    int                                     mDisplayMoves;
    int                                     mDisplayMovesTotal;
    
    FString                                 mStringMoves;
    FString                                 mStringMovesTotal;
    
    void                                    SetMoves(int pMovesCount);
    void                                    SetMovesTotal(int pMovesCount);
    
    
};

class GameInterfaceBox : public GameInterfaceElement
{
    
public:
    
    GameInterfaceBox();
    virtual ~GameInterfaceBox();
    
    void                                    SetUp(FSprite *pSpriteItem, FSprite *pSpriteBar, FFont *pFont, float pX, float pY, float pOffsetX, float pOffsetY);
    
    virtual void                            Update();
    virtual void                            Draw();
    
    int                                     mValue;
    
    bool                                    mValueTotalShow;
    int                                     mValueTotal;
    
    void                                    SetValue(int pValue, bool pForceValue);
    
    FString                                 mText;
    
    FSprite                                 *mSpriteItem;
    FSprite                                 *mSpriteBar;
    
    FFont                                   *mFont;
    
    float                                   mOffsetX;
    float                                   mOffsetY;
    
    float                                   mItemCenterX;
    float                                   mItemCenterY;
    
    float                                   mRotationSin;
    
    bool                                    mCenterText;
    
};

class GameInterfaceTop : public FView
{
public:
    
    GameInterfaceTop();
    virtual ~GameInterfaceTop();
    
    void                                    SetUp();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
	virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    virtual void                            Notify(void *pSender);
    
    void                                    SetDisplayScore(int pScore);
    void                                    SetDisplayMoves(int pMoves, int pMovesTotal);
    
    void                                    SetDisplayCurrency(int pValue);
    
    
    
    
    void                                    DiscoverStar();
    
    GameInterfaceContainer                  mContentLeft;
    GameInterfaceContainer                  mContentMiddle;
    GameInterfaceContainer                  mContentRight;
    
    FButton                                 mButtonMenu;

    GameInterfaceStarIndicator              mStarIndicator;
    GameInterfaceMovesBox                   mMovesBox;
    GameInterfaceProgressbar                mProgressBar;
    GameInterfaceScoreBar                   mScoreBar;
    
    //GameInterfaceBox                        mBoxCurrency;
    //GameInterfaceBox                        mBoxGem1;
    //GameInterfaceBox                        mBoxGem2;
    
    
};

#endif
