//
//  GameInterfaceTop.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/26/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "core_includes.h"

#include "GameInterfaceTop.h"
#include "MainMenu.h"
#include "GameMenu.h"
#include "Game.h"
#include "Board.h"
#include "MainApp.h"

GameInterfaceTop::GameInterfaceTop()
{
    mName = "GameInterfaceTop";
    
    mDrawManual = true;
    //mClipsContent = false;
    
    //mLeft = 0.0f;
    //mRight = 0.0f;
    
    //mMovesBlockCenterX = 256.0f;
    //mMovesBlockCenterY = 50.0f;
    
    
    for(int i=0;i<8;i++)
    {
        //mCollectionBox[i] = 0;
    }
    
    mContentLeft.mName = "Top Content Left";
    mContentMiddle.mName = "Top Content Middle";
    mContentRight.mName = "Top Content Right";
    
    AddSubview(mContentLeft);
    AddSubview(mContentMiddle);
    AddSubview(mContentRight);
    
    mButtonMenu.SetUp(&(gApp->mGIButtonPause), 0, 0, FVec2(0.0f, 0.0f));
    mButtonMenu.SetListener(this);
    
    
    //mBoxCurrency.SetUp(&(gApp->mInterfaceTopScoreBarGem[0]), &(gApp->mInterfaceTopScoreBarSmall), &(gApp->mFontMovesRemaining), 40, 62, 26.0f, 7.0f);
    
    //mBoxGem2.SetUp(&(gApp->mInterfaceTopScoreBarGem[0]), &(gApp->mInterfaceTopScoreBarSmall), &(gApp->mFontMovesRemaining), 40, 156.0f, 26.0f, 7.0f);
    
    
    //mBoxScore.SetUp(&(gApp->mInterfaceTopScoreBarGem[2]), &(gApp->mInterfaceTopScoreBarLarge), &(gApp->mFontScore), 500, 40, 26.0f, 7.0f);
    //mBoxScore.SetUp(0, &(gApp->mGIScoreBarMockup), &(gApp->mFontScoreBar), 500, 40, 26.0f, 7.0f);
    //mBoxScore
    
    mProgressBar.SetSprite(&(gApp->mGIProgressBarShadow));
    mProgressBar.SetSpriteShadow(&(gApp->mGIProgressBarShadow));
    mProgressBar.SetSprite(&(gApp->mGIProgressBarBack));
    
    //FSprite                                                 mGIProgressBarBack;
    //FSprite                                                 mGIProgressBarShadow;
    //FSprite                                                 mGIProgressBarFill;
    //FSprite                                                 mGIProgressBarMockup;
    
    
    
    mScoreBar.SetSpriteShadow(&(gApp->mGIScoreBarShadow));
    mScoreBar.SetSprite(&(gApp->mGIScoreBarBack));
    
    
    
    //mSampleBar.SetSprite(&(gApp->mGIScoreBarBack));
    //mSampleBar2.SetSprite(&(gApp->mGIScoreBarBack));
    
    
    
    //mMovesBox.SetSprite(&(gApp->mGIMovesBox));
    
    
    //mBoxGem1.SetUp(&(gApp->mInterfaceTopScoreBarGem[0]), &(gApp->mInterfaceTopScoreBarSmall), &(gApp->mFontScore), 0.0f, 0.0f, 22.0f, 7.0f);
    //mBoxGem2.SetUp(&(gApp->mInterfaceTopScoreBarGem[1]), &(gApp->mInterfaceTopScoreBarSmall), &(gApp->mFontScore), 0.0f, 0.0f, 22.0f, 7.0f);
    //mBoxGem3.SetUp(&(gApp->mInterfaceTopScoreBarGem[2]), &(gApp->mInterfaceTopScoreBarSmall), &(gApp->mFontScore), 0.0f, 0.0f, 22.0f, 7.0f);
    
    //mBoxGem1.mCenterText = true;
    //mBoxGem2.mCenterText = true;
    //mBoxGem3.mCenterText = true;
    
    //mBoxGem1.SetValue(gRand.Get(25));
    //mBoxGem2.SetValue(gRand.Get(25));
    //mBoxGem3.SetValue(gRand.Get(25));
    
    //AddSubview(mBoxGem1);
    //AddSubview(mBoxGem2);
    //AddSubview(mBoxGem3);
    
    
    float aSliceWidth[3];
    float aSliceHeight[3];
    
   
    
    float aContentMiddleWidth = 160.0f;
    
    //mContentLeft.mColor = FColor(1.0f, 0.0f, 0.0f, 0.25f);
    //mContentMiddle.mColor = FColor(0.0f, 1.0f, 0.0f, 0.25f);
    //mContentRight.mColor = FColor(0.0f, 0.0f, 1.0f, 0.25f);
    
    mContentRight.AddSubview(mScoreBar);
    mContentRight.AddSubview(mProgressBar);
    
    //mScoreBar.SetX(80.0f);
    //mProgressBar.SetX(80.0f);
    
    mProgressBar.SetFrame(mScoreBar.GetX(), mScoreBar.GetY() + mScoreBar.GetHeight() - 12.0f, mScoreBar.GetWidth(), mScoreBar.GetHeight());
    
    
    
    mContentMiddle.AddSubview(mStarIndicator);
    mContentMiddle.AddSubview(mMovesBox);
    
    mMovesBox.SetFrame(mStarIndicator.GetWidth() / 2.0f - mMovesBox.GetWidth() / 2.0f, 5.0f, mMovesBox.GetWidth(), mMovesBox.GetHeight());
    
    mStarIndicator.SetFrame(mMovesBox.GetCenterX() - mStarIndicator.GetWidth() / 2.0f, 75, mStarIndicator.GetWidth(), mStarIndicator.GetHeight());
    
    
    mContentLeft.AddSubview(mButtonMenu);
    
    //mContentLeft.AddSubview(mBoxCurrency);
    //mContentLeft.AddSubview(mBoxGem1);
    //mContentLeft.AddSubview(mBoxGem2);
    
    
    
    //mContentLeft.AddSubview(mSampleBar);
    //mContentLeft.AddSubview(mSampleBar2);
    
    //GameInterfaceElement                    mSampleBar;
    //GameInterfaceElement                    mSampleBar2;
    
    //mSampleBar2.SetFrame(mSampleBar.GetRight(), mSampleBar.GetY(), mSampleBar2.GetWidth(), mSampleBar2.GetHeight());
    
    mButtonMenu.SetFrame(0.0f, 0.0f, mButtonMenu.GetWidth(), mButtonMenu.GetHeight());
    
    //mSampleBar.SetFrame(2.0f, mButtonMenu.GetBottom() - 6.0f, mSampleBar.GetWidth(), mSampleBar.GetHeight());
    
    
    //mSampleBar.SetFrame(mButtonMenu.GetX(), mButtonMenu.GetY() + mButtonMenu.GetHeight() + 9.0f, mSampleBar.GetWidth(), mSampleBar.GetHeight());
    
    
    
    mContentLeft.SizeToFitChildren();
    mContentRight.SizeToFitChildren();
    mContentMiddle.SizeToFitChildren();
    
    //mContentLeft.PrintFrame();
    //mContentMiddle.PrintFrame();
    //mContentRight.PrintFrame();
    
}

GameInterfaceTop::~GameInterfaceTop()
{
    
}

//void GameInterfaceTop::SetUpWithScale(float pScale, float pBaseHeight)

void GameInterfaceTop::SetUp()
{
    float aTargetWidth = 768.0f;
	float aWidthRatio = aTargetWidth / gAppWidth;
    
    
    //gAdjustmentScale
    
    float aScale = 1.0f / aWidthRatio;
    float aWidth = 660.0f / aScale;
    //float aHeight = 128.0f / aScale;
    //float aHeight = 128.0f / aScale;
    float aHeight = 128.0f / aScale;
    
    
    
    SetFrame(0.0f, 0.0f, aWidth, aHeight);// * GetTransformScale());
    SetTransformScale(aScale);
    
    
    mContentLeft.SetFrame(0.0f, -2.0f, mContentLeft.GetWidth(), mContentLeft.GetHeight());
    mContentMiddle.SetFrame(mWidth2 - mContentMiddle.GetWidth() / 2.0f, -2.0f, mContentMiddle.GetWidth(), mContentMiddle.GetHeight());
    mContentRight.SetFrame(mWidth - mContentRight.GetWidth(), -2.0f, mContentRight.GetWidth(), mContentRight.GetHeight());
    
    
    
    //Log("BoxC[%f %f] BoxG2[%f %f]\n\n", mBoxCurrency.mX, mBoxCurrency.mY, mBoxCurrency.mWidth, mBoxCurrency.mHeight);
    
    
    /*
    if(gGame)
    {
        for(int i=0;i<gGame->mCollectionTypeCount;i++)
        {
            
            if(gGame->mCollectionType[i] == COLLECTION_TYPE_TILE)
            {
                
                mCollectionBox[i] = new GameInterfaceBox();
                mCollectionBox[i]->SetUp(&(gApp->mTileEggFront[gGame->mCollectionTypeIndex[i]]), &(gApp->mInterfaceTopScoreBarSmall), &(gApp->mFontScore), 0.0f, 0.0f, 22.0f, 7.0f);
                mCollectionBox[i]->SetFrame(aX, aY, mCollectionBox[i]->GetWidth(), mCollectionBox[i]->GetHeight());
                
                mCollectionBox[i]->mValueTotalShow = true;
                mCollectionBox[i]->mValueTotal = gGame->mCollectionCountTotal[i];
                mCollectionBox[i]->SetValue(gGame->mCollectionCount[i], true);
                
                AddSubview(mCollectionBox[i]);
                
                aX += mCollectionBox[i]->GetWidth() + aSpacePadding;
            }
        }
    }
    */

    
}


void GameInterfaceTop::Update()
{
    if(gApp->IsPaused())
    {
        return;
    }
}

void GameInterfaceTop::Draw()
{
    
    Graphics::SetColor(0.80f);
    Graphics::SetColor();
    
    //gApp->mInterfaceTopBack.Draw(0.0f, 0.0f);
    //gApp->mInterfaceTopBack.Center(mFrame.mWidth / 2.0f, mFrame.mHeight + (gApp->mInterfaceTopBack.mHeight / 2.0f) - 134.0f);
    
    
    Graphics::SetColor();
    
    
    
    mContentLeft.DrawShadow();
    mContentMiddle.DrawShadow();
    mContentRight.DrawShadow();
    
    mContentLeft.Draw();
    mContentMiddle.Draw();
    mContentRight.Draw();
    
    //mContentLeft.DrawOverlay();
    //mContentMiddle.DrawOverlay();
    //mContentRight.DrawOverlay();
}

void GameInterfaceTop::TouchDown(float pX, float pY, void *pData)
{
    
}

void GameInterfaceTop::TouchUp(float pX, float pY, void *pData)
{
    
}

void GameInterfaceTop::TouchMove(float pX, float pY, void *pData)
{
    
}

void GameInterfaceTop::TouchFlush()
{
    
}

void GameInterfaceTop::DiscoverStar()
{
    mStarIndicator.DiscoverStar();
}

void GameInterfaceTop::Notify(void *pSender)
{
    if(gGame)
    {
        if(gGame->mLevelComplete)
        {
            return;
        }
    }
    
    if(pSender == &mButtonMenu)
    {
        gApp->PopupGameMenu();
        //gApp->PopoverShow(aMenu, FColor(0.0f, 0.0f, 0.0f, 0.85f));
    }
}

void GameInterfaceTop::SetDisplayScore(int pScore)
{
    mScoreBar.SetValue(pScore);
}

void GameInterfaceTop::SetDisplayMoves(int pMoves, int pMovesTotal)
{
    mMovesBox.SetMoves(pMoves);
    mMovesBox.SetMovesTotal(pMovesTotal);
}

void GameInterfaceTop::SetDisplayCurrency(int pValue)
{
    
}

GameInterfaceBox::GameInterfaceBox()
{
    mName = "GameInterfaceBox";
    
    mValue = 0;
    
    mValueTotalShow = false;
    mValueTotal = 0;
    
    
    
    mSpriteItem = 0;
    mSpriteBar = 0;
    
    mFont = 0;
    
    mOffsetX = 0.0f;
    mOffsetY = 0.0f;
    
    mRotationSin = gRand.Get(360.0f);
    
    mCenterText = false;
    
    mText = "0";
}

GameInterfaceBox::~GameInterfaceBox()
{
    
}

//void GameInterfaceBox::SetUp(FSprite *pSprite, float pX, float pY)
//void GameInterfaceBox::SetUp(FSprite *pSprite, FFont *pFont, float pX, float pY)

void GameInterfaceBox::SetUp(FSprite *pSpriteItem, FSprite *pSpriteBar, FFont *pFont, float pX, float pY, float pOffsetX, float pOffsetY)
{
    mSpriteItem = pSpriteItem;
    mSpriteBar = pSpriteBar;
    
    mFont = pFont;
    
    float aSlotWidth = gApp->mInterfaceTopScoreBarItemSlot.mWidth;
    float aSlotHeight = gApp->mInterfaceTopScoreBarItemSlot.mHeight;
    
    if(aSlotHeight < 6.0f)aSlotHeight = 40.0f;
    if(aSlotWidth < 24.0f)aSlotWidth = 24.0f;
    
    
    float aBarWidth = pSpriteBar->mWidth;
    float aBarHeight = pSpriteBar->mHeight;
    
    
    //mInterfaceTopScoreBarItemSlot
    
    SetFrame(pX, pY, aBarWidth + aSlotWidth, aSlotHeight);
    
    
    mOffsetX = pOffsetX;
    mOffsetY = pOffsetY;
    
}

void GameInterfaceBox::Update()
{
    
    mRotationSin += 4.0f;
    if(mRotationSin >= 360.0f)
    {
        mRotationSin -= 360.0f;
    }
    
    
}

void GameInterfaceBox::Draw()
{
    Graphics::SetColor();
    
    mSpriteBar->Draw(mOffsetX, mOffsetY);
    
    
    
    
    
    float aItemX = gApp->mInterfaceTopScoreBarItemSlot.mWidth / 2.0f;
    float aItemY = gApp->mInterfaceTopScoreBarItemSlot.mHeight / 2.0f;
    
    gApp->mInterfaceTopScoreBarItemSlot.Center(aItemX, aItemY);
    
    float aRotation = Sin(mRotationSin) * 8.0f;
    
    if(mSpriteItem)mSpriteItem->Draw(aItemX, aItemY, 1.0f, aRotation);
    
    //mSprite->Center(mFrame.mWidth / 2.0f, mFrame.mHeight / 2.0f);
    
    if(mCenterText == false)mFont->Draw(mText.c(), 84.0f, 10.0f);
    else mFont->Center(mText.c(), 76.0f, 13.0f);
    
}

void GameInterfaceBox::SetValue(int pValue, bool pForceValue)
{
    if((mValue != pValue) || (pForceValue == true))
    {
        mValue = pValue;
        
        mText = FString((mValueTotal - mValue));
        
        if(mValueTotalShow == true)
        {
            mText = FString(mText + FString(",") + FString(mValueTotal));
        }
        
    }
}


GameInterfaceMovesBox::GameInterfaceMovesBox()
{
    mDisplayMoves = -1;
    mDisplayMovesTotal = -1;
    
    mStringMoves = FString(mDisplayMoves);
    mStringMovesTotal = FString(mDisplayMovesTotal);
    
    SetSprite(&(gApp->mGIMovesBox));
}

GameInterfaceMovesBox::~GameInterfaceMovesBox()
{
    
}



void GameInterfaceMovesBox::SetMoves(int pMovesCount)
{
    mDisplayMoves = pMovesCount;
    mStringMoves = FString(mDisplayMoves);
}

void GameInterfaceMovesBox::SetMovesTotal(int pMovesCount)
{
    if(mDisplayMovesTotal != pMovesCount)
    {
        mDisplayMovesTotal = pMovesCount;
        mStringMovesTotal = FString(mDisplayMovesTotal);
    }
}

void GameInterfaceMovesBox::Update()
{
    GameInterfaceElement::Update();
}

void GameInterfaceMovesBox::Draw()
{
    GameInterfaceElement::Draw();
    
    //gApp->mFontMovesRemaining.Center(mStringMoves.c(), mWidth2 - 18.0f, mHeight2 - 12.0f);
    //gApp->mFontMovesRemaining.Center(mStringMovesTotal.c(), mWidth2 + 18.0f, mHeight2 - 12.0f);
    
    gApp->mFontMovesRemaining.Center(mStringMoves.c(), mWidth2, mHeight2 - 12.0f);
}

GameInterfaceScoreBar::GameInterfaceScoreBar()
{
    mName = "GameInterfaceScoreBar";
    
    mScoreString = "0";
    mScoreDisplay = 0;
    
}

void GameInterfaceScoreBar::Update()
{
    
}

void GameInterfaceScoreBar::Draw()
{
    GameInterfaceElement::Draw();
    Graphics::SetColor();
    
    
    //mScoreString
    
    gApp->mFontMovesRemaining.Right(mScoreString.c(), mWidth - 10.0f, 20.0f);
    gApp->mFontMovesRemaining.Center(mScoreString.c(), mWidth2, 90.0f);
    
    
    //gApp->mFontScoreBar.Right(mScoreString.c(), GetWidth() - 18.0f, 24.0f);
}

void GameInterfaceScoreBar::SetValue(int pValue)
{
    if(mScoreDisplay != pValue)
    {
        mScoreDisplay = pValue;
        mScoreString = FString(pValue, true);
    }
}

GameInterfaceProgressbar::GameInterfaceProgressbar()
{
    mProgress = 0.0f;
    
    //SetFrame(GetX(), GetY(), gApp->mGIProgressBarBack.mWidth, gApp->mGIProgressBarBack.mHeight);
    
    
    
    
    mValueMax = 30;
    mValue = 0;
    
    
    mHitTimer = 0;
    
    mHitShake = 0;
    
    
}

void GameInterfaceProgressbar::Update()
{
    
    if(mHitShake > 0.0f)
    {
        mHitShake *= 0.9835f;
        mHitShake -= 0.03f;
        if(mHitShake <= 0.0f)
        {
            mHitShake = 0.0f;
        }
    }
    
    mProgress += 0.0033f;
    if(mProgress >= 1.4f)
    {
        mProgress = 0.0f;
    }
}


void GameInterfaceProgressbar::ReceivedEssence(int pCount)
{
    mHitShake = 4.5f;
    
    if(mHitShake <= 0.0f)
    {
        
    }
    
    if(mValue > (mValueMax + 5))
    {
        mValue = 0;
    }
    
    mValue += pCount;
    
    mProgress = ((float)mValue) / ((float)mValueMax);
    
}

void GameInterfaceProgressbar::Draw()
{
    if(mHitShake > 0.0f)
    {
        
        float aCenterX = GetWidth() / 2.0f;
        float aCenterY = GetHeight() / 2.0f;
        
        aCenterX += gRand.GetFloat(-mHitShake, mHitShake);
        aCenterY += gRand.GetFloat(-mHitShake, mHitShake);
        
        float aScaleHighlight = (mHitShake / 50.0f) + 1.0f;
        
        float aRotate = gRand.GetFloat(-(mHitShake / 2.0f), (mHitShake / 2.0f));
        
        Graphics::SetColor();
        
        if(mSpriteShadow)
        {
            Graphics::SetColor();
            mSpriteShadow->Draw(aCenterX, aCenterY, 1.0f, aRotate);
            
        }
        if(mSprite)
        {
            Graphics::BlendSetAlpha();
            //Graphics::SetColor(0.45f);
            Graphics::SetColor();
            
            
            mSprite->Draw(aCenterX, aCenterY, aScaleHighlight, aRotate);
            Graphics::BlendSetAlpha();
            
            Graphics::SetColor();
            mSprite->Draw(aCenterX, aCenterY, 1.0f, aRotate);
        }
    }
    else
    {
        GameInterfaceElement::Draw();
    }
    
    float aImageWidth = gApp->mGIProgressBarFill.mWidth;
    float aImageHeight = gApp->mGIProgressBarFill.mHeight;
    
    float aStartU[3];
    float aStartV[3];
    
    float aEndU[3];
    float aEndV[3];
    
    float aImageStartX[3];
    float aImageStartY[3];
    
    float aImageEndX[3];
    float aImageEndY[3];
    
    aImageStartX[0] = 0.0f;
    aImageStartY[0] = 0.0f;
    aImageEndX[0] = 12.0f;
    aImageEndY[0] = 32.0f;
    
    aImageStartX[1] = 12.0f;
    aImageStartY[1] = 0.0f;
    aImageEndX[1] = 24.0f;
    aImageEndY[1] = 32.0f;
    
    aImageStartX[2] = 24.0f;
    aImageStartY[2] = 0.0f;
    aImageEndX[2] = 32.0f;
    aImageEndY[2] = 32.0f;
    
    for(int i=0;i<3;i++)
    {
        aStartU[i] = (float)(aImageStartX[i]) / aImageWidth;
        aStartV[i] = (float)(aImageStartY[i]) / aImageHeight;
        
        aEndU[i] = (float)(aImageEndX[i]) / aImageWidth;
        aEndV[i] = (float)(aImageEndY[i]) / aImageHeight;
    }
    
    float aRefStartX = 0.0f;
    float aRefStartY = 0.0f;
    float aRefEndX = 12.0f;
    float aRefEndY = 32.0f;
    
    Graphics::SetColor(0.5f);
    
    float aDrawStartX = 32.0f;
    float aDrawStartY = 24.0f;
    float aDrawEndX = aDrawStartX + 12.0f;
    float aDrawEndY = aDrawStartY + 32.0f;
    
    gApp->mGIProgressBarFill.DrawSliceTo(aRefStartX, aRefStartY, aRefEndX, aRefEndY, aDrawStartX, aDrawStartY, aDrawEndX, aDrawEndY);
    
    aRefStartX = 12.0f;
    aRefEndX = 20.0f;
    
    aDrawStartX = aDrawEndX;
    aDrawEndX = aDrawStartX + Trim(mProgress, 0, 1) * 166.0f;
    
    gApp->mGIProgressBarFill.DrawSliceTo(aRefStartX, aRefStartY, aRefEndX, aRefEndY, aDrawStartX, aDrawStartY, aDrawEndX, aDrawEndY);
    
    aRefStartX = 20.0f;
    aRefEndX = 32.0f;
    
    aDrawStartX = aDrawEndX;
    aDrawEndX = aDrawStartX + 12.0f;
    
    gApp->mGIProgressBarFill.DrawSliceTo(aRefStartX, aRefStartY, aRefEndX, aRefEndY, aDrawStartX, aDrawStartY, aDrawEndX, aDrawEndY);
    
    Graphics::SetColor();
    
}

GameInterfaceStarIndicator::GameInterfaceStarIndicator()
{
    SetFrame(0.0f, 0.0f, 188.0f, 72.0f);
    
    mStarIndicatorX[0] = 38.0f;
    mStarIndicatorY[0] = 36.0f;
    
    mStarIndicatorX[1] = 96.0f;
    mStarIndicatorY[1] = 36.0f;
    
    mStarIndicatorX[2] = 152.0f;
    mStarIndicatorY[2] = 36.0f;
    
    mStarEarned[0] = false;
    mStarEarned[1] = false;
    mStarEarned[2] = false;
    
    mEarnedCount = 0;
    
}

GameInterfaceStarIndicator::~GameInterfaceStarIndicator()
{
    
}

void GameInterfaceStarIndicator::Update()
{
    
    for(int i=0;i<3;i++)
    {
        //float mStarIndicatorX = mStarIndicatorX
    }
}

void GameInterfaceStarIndicator::Draw()
{
    GameInterfaceElement::Draw();
    
    //mStarIndicator
    
    for(int i=0;i<3;i++)
    {
        gApp->mGIStarBarShadow[i].Center(mStarIndicatorX[i], mStarIndicatorY[i]);
    }
    
    Graphics::SetColor();
    
    for(int i=0;i<3;i++)
    {
        gApp->mGIStarBarBack[i].Center(mStarIndicatorX[i], mStarIndicatorY[i]);
    }
    
    for(int i=0;i<3;i++)
    {
        if(mStarEarned[i])
        {
            gApp->mGIStarBarComplete[i].Center(mStarIndicatorX[i], mStarIndicatorY[i]);
        }
    }
}

void GameInterfaceStarIndicator::DiscoverStar()
{
    mName = "GameInterfaceStarIndicator";
    
    if(mEarnedCount < 3)mEarnedCount++;
    
    if(mStarEarned[0] == false)
    {
        mStarEarned[0] = true;
    }
    else if(mStarEarned[1] == false)
    {
        mStarEarned[1] = true;
    }
    else
    {
        mStarEarned[2] = true;
    }
}

