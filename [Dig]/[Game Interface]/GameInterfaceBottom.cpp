//
//  GameInterfaceBottom.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/26/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "GameInterfaceBottom.h"
#include "MainMenu.h"
#include "Board.h"
#include "Game.h"

GameInterfaceBottom::GameInterfaceBottom()
{
    mName = "[GIB]";

 
    //mClipsContent = false;
    mDrawManual = true;
    //mDrawManual = false;
    
    
    mContentLeft.mName = "Bottom Content Left";
    mContentRight.mName = "Bottom Content Right";
    
    mContentLeft.mDrawManual = true;
    mContentRight.mDrawManual = true;
    
    AddSubview(mContentLeft);
    AddSubview(mContentRight);
    
    
    //mProgressBar1.SetSpriteShadow(&(gApp->mGIProgressBarShadow));
    //mProgressBar1.SetSprite(&(gApp->mGIProgressBarBack));
    
    
    //mProgressBar2.SetSpriteShadow(&(gApp->mGIProgressBarShadow));
    //mProgressBar2.SetSprite(&(gApp->mGIProgressBarBack));

    //for(int i=0;i<4;i++)
    //{
    //    mChaosEgg[i] = new ChaosEgg();
    //    mContentLeft.AddSubview(mChaosEgg[i]);
    //    mChaosEgg[i]->mItemID = i + 4;
    //    gGame->mActionProcItems += mChaosEgg[i];
    //    mChaosEgg[i]->SetX(i * 130);
    //}
    
    float aItemSize = 160.0f;
    float aItemX = 0.0f;
    float aItemY = 0.0f;
    
    mBlaster = new ItemBlaster();
    mBlaster->mItemID = 3;
    mContentRight.AddSubview(mBlaster);
    gGame->mActionProcItems += mBlaster;
    mBlaster->SetX(0.0f);
    mBlaster->SetY(aItemY);
    
    
    mBuzzDrill = new ItemBuzzDrill();
    mBuzzDrill->mItemID = 2;
    mContentLeft.AddSubview(mBuzzDrill);
    mBuzzDrill->SetX(aItemX);
    mBuzzDrill->SetY(aItemY);
    aItemX += aItemSize;
    
    mRockHammer1 = new RockHammer();
    mRockHammer1->mItemID = 1;
    mContentLeft.AddSubview(mRockHammer1);
    mRockHammer1->SetX(aItemX);
    mRockHammer1->SetY(aItemY);
    aItemX += aItemSize;
    
    /*
    mRockHammer1 = new RockHammer();
    mRockHammer1->mItemID = 1;
    mContentLeft.AddSubview(mRockHammer1);
    mRockHammer1->SetX(aItemX);
    mRockHammer1->SetY(aItemY);
    aItemX += aItemSize;
    
    mRockHammer2 = new RockHammer();
    mRockHammer2->mItemID = 1;
    mContentLeft.AddSubview(mRockHammer2);
    mRockHammer2->SetX(aItemX);
    mRockHammer2->SetY(aItemY);
    aItemX += aItemSize;
    */
    
    
    mContentLeft.SizeToFitChildren();
    mContentRight.SizeToFitChildren();
    
}

GameInterfaceBottom::~GameInterfaceBottom()
{
    
}

void GameInterfaceBottom::SetUp(float pY, float pHeight)
{
    float aTargetWidth = 768.0f;
	float aWidthRatio = aTargetWidth / gAppWidth;
    
    float aScale = 1.0f / aWidthRatio;
    float aWidth = 660.0f / aScale;
    float aHeight = pHeight / aScale;
    
    SetTransformScale(aScale);
    SetFrame(0.0f, pY, aWidth, aHeight);
    
    mContentLeft.SetFrame(8.0f, -4.0f, mContentLeft.GetWidth(), mContentLeft.GetHeight());
    mContentRight.SetFrame(GetWidth() - (mContentRight.GetWidth() + 4.0f), -4.0f, mContentRight.GetWidth(), mContentRight.GetHeight());
}

void GameInterfaceBottom::Update()
{
    
}

void GameInterfaceBottom::Draw()
{
    Graphics::SetColor();
    
    //Graphics::SetColor(0.75f);
    
    gApp->mInterfaceBottomBack.Center(GetWidth() / 2.0f, (gApp->mInterfaceBottomBack.mHeight / 2.0f) - 4.0f);
    
    Graphics::SetColor();
    
    mContentLeft.DrawManual();
    mContentRight.DrawManual();
    
    DrawTransform();
    
    Graphics::SetColor();
    
}
