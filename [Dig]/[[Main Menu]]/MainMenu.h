//
//  MainMenu.h
//  CoreDemo
//
//  Created by Nick Raptis on 10/25/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#ifndef __CoreDemo__MainMenu__
#define __CoreDemo__MainMenu__

#include "MainApp.h"
#include "MainMenuLetter.h"
#include "MainMenuButton.h"
#include "MainMenuSceneItem.h"
#include "Rex.h"
#include "HeroStego.h"

class MainMenuSun;
class MainMenu : public FView
{
public:
    
    MainMenu();
    virtual ~MainMenu();
    
    virtual void                            PositionContent();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    virtual void                            TouchDown(float pX, float pY, void *pData);
	virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchFlush();
    
    virtual void                            Notify(void *pSender);
    
    MainMenuButton                          *mButtonPlay;
    MainMenuButton                          *mButtonLogIn;
    MainMenuButton                          *mButtonStore;
    
    FView                                   *mButtonContainer;
    
    FView                                   *mTitleContainer;
    
    
    //WiggleButton                            *mButtonPickLevel;
    
    //WiggleButton                            mButtonStore;
    //WiggleButton                            mButtonOptions;
    
    bool                                    mDidClick;
    
    int                                     mDidClickTimer;
    
    int                                     mDidClickActionIndex;
    
    //float                                   mTitleTextCenterX;
    //float                                   mTitleTextCenterY;
    
    //float                                   mTitleTextRotationSin;
    //float                                   mTitleTextShiftSin;
    
    
    FList                                   mLetters;
    //FList                                   mLettersRow2;
    
    
    FList                                   mSceneItemListBottom;
    FList                                   mSceneItemListMiddle;
    FList                                   mSceneItemListTop;
    
    float                                   mLetterOffsetBaseX[26];
    float                                   mLetterOffsetBaseY[26];
    
    
    void                                    *mTouch;
    
    MainMenuLetter                          *mLastClicked;
    
    MainMenuSun                             *mSun;
    
    
    //FObjectList                             mStars;
    
    
    
    
    float                                   mFloorX;
    float                                   mFloorY;
    float                                   mFloorCenterX;
    float                                   mFloorCenterY;
    
    float                                   mFloorWidth;
    float                                   mFloorHeight;
    
    float                                   mFloorScale;
    
    
    
    FRect                                   mTopInterfaceFrame;
    
    FRect                                   mTopInterfaceTitleFrame;
    FRect                                   mTopInterfaceButtonFrame;
    
    
    HeroStego                               *mStego;
    
};

class MainMenuSun
{
public:
    MainMenuSun();
    virtual ~MainMenuSun();
    
    virtual void                            Update();
    virtual void                            Draw();
    
    float                                   mX;
    float                                   mY;
    
    float                                   mScale;
    
    
    float                                   mSin[4];
    float                                   mSinSpeed[4];
    
    float                                   mRot[4];
    float                                   mRotSpeed[4];
    
};

#endif
