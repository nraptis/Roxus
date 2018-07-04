//
//  GameStoreScreen.cpp
//  Digplex
//
//  Created by Nick Raptis on 11/26/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "GameStoreScreen.h"
#include "MainApp.h"

#include "GameMenu.h"


GameStoreScreenCell::GameStoreScreenCell()
{
    //SetFrame(0.0f, 0.0f, gApp->mTitleScreenBack.mWidth, gApp->mTitleScreenBack.mHeight);
    mClipsContent = false;
}

GameStoreScreenCell::~GameStoreScreenCell()
{
    
}

void GameStoreScreenCell::Update()
{
    
    
    
    
    
}

void GameStoreScreenCell::Draw()
{
    //gApp->mTitleScreenBack.Draw(0.0f, 0.0f);
}

void GameStoreScreenCell::Notify(void *pSender)
{
    
}

GameStoreScreen::GameStoreScreen()
{
    //mClipsContent = true;
    
    SetFrame(100.0f, 100.0f, 480.0f, 700.0f);
    SetTransformAnchor(0.5f, 0.5f);
    
    mName = "Store Screen";
    
    mViewTop.mName = "Store Screen Slice - Top";
    mScrollViewContent.mName = "Store Screen Slice - Middle Scroller";
    mViewBottom.mName = "Store Screen Slice - Top";
    
    
    //mViewTop.mDrawManual = true;
    //mScrollViewContent.mDrawManual = true;
    //mViewBottom.mDrawManual = true;
    
    AddSubview(mViewTop);
    AddSubview(mScrollViewContent);
    AddSubview(mViewBottom);
    
    
    
    float aPaddingH = 32.0f;
    float aPaddingV = 60.0f;
    
    float aHeightTop = 160.0f;
    float aHeightBottom = 70.0f;
    
    mViewTop.SetFrame(aPaddingH, aPaddingV, GetWidth() - aPaddingH * 2.0f, aHeightTop);
    
    
    float aScrollHeight = GetHeight() - (aHeightTop + aHeightBottom + aPaddingV * 4.0f);
    
    mScrollViewContent.SetFrame(aPaddingH, mViewTop.GetBottom() + aPaddingH, GetWidth() - aPaddingH * 2.0f, aScrollHeight);
    
    
    mViewBottom.SetFrame(aPaddingH, mScrollViewContent.GetBottom() + aPaddingV, GetWidth() - aPaddingH * 2.0f, aHeightBottom);
    
    
    float aCellX = 0.0f;
    float aCellY = 0.0f;
    
    GameStoreScreenCell *aCell = new GameStoreScreenCell();
    aCell->SetPos(aCellX, aCellY);
    
    mScrollViewContent.AddSubview(aCell);
    
    
    //mScrollViewContent.SetContentSize(aCell->GetWidth(), aCell->GetHeight());
    
    mScrollViewContent.SetContentSize(mScrollViewContent.GetWidth(), aCell->GetHeight());
    //mScrollViewContent.
    
    mScrollViewContent.mScrollHorizontalEnabled = false;
    
    
    //mViewTop.SetFrame(<#float pX#>, <#float pY#>, <#float pWidth#>, <#float pHeight#>)
    
    
    mViewTop.mDrawManual = true;
    
    //mScrollViewContent.mDrawManual = true;
    
    mViewBottom.mDrawManual = true;
    
    
    
    
    mButtonClose.SetUp(gApp->mGIPaperMenuCloseButton, mWidth - (gApp->mGIPaperMenuCloseButton.mWidth + 10.0f), 14.0f);
    AddSubview(mButtonClose);
    
    
    mButtonZone.SetUp(gApp->mMIBigButton[1], 50.0f, 580.0f);
    AddSubview(mButtonZone);
    
    
    SetCenter();
}

GameStoreScreen::~GameStoreScreen()
{
    
}



void GameStoreScreen::Update()
{
    //SetTransformRotation(GetTransformRotation() + 0.05f);
    
}

void GameStoreScreen::Draw()
{
    gApp->mGIPaperMenuBack.Center(GetWidth() / 2.0f, GetHeight() / 2.0f);
    
    
    //mViewTop.DrawManualTest();
    //mScrollViewContent.DrawManualTest();
    
    //.mDrawManual = true;
    //mViewBottom.mDrawManual = true;
    
}

void GameStoreScreen::TouchDown(float pX, float pY, void *pData)
{
    
}

void GameStoreScreen::TouchMove(float pX, float pY, void *pData)
{
    
}

void GameStoreScreen::TouchUp(float pX, float pY, void *pData)
{
    
}

void GameStoreScreen::TouchFlush()
{
    
}

void GameStoreScreen::Notify(void *pSender)
{
    if(pSender == &mButtonClose)
    {
        gApp->ClosePopup();
    }
    
    if(pSender == &mButtonZone)
    {
        gApp->PopupGameMenu();
    }
}



