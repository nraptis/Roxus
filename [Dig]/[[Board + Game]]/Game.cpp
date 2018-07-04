//
//  Game.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/12/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "MainApp.h"
#include "UMainCanvas.h"

#include "Game.h"
#include "MainMenu.h"
#include "Board.h"
#include "FParticle.h"

#include "AnimationDiscoveredStar.h"
#include "AnimationDiscoveredTreasure.h"
#include "CollectedEssence.h"

#include "GameInterfaceTop.h"
#include "GameInterfaceBottom.h"

#include "ActionProcItem.h"
#include "ItemBuzzDrill.h"

#ifdef EDITOR_MODE
#include "EditorBoard.h"
#endif

Game *gGame = 0;
Game::Game(int pLevelIndex)
{
    
    #ifndef DISABLE_SOUNDS
    core_sound_musicCrossFade("music_game_loop.mp3", 45, true);
    #endif
    
    //if(gUtils)gUtils->SetReferenceView(this);
    
    mRecievesConsumedTouches = true;
    mRecievesOutsideTouches = true;
    
    gGame = this;
    mName = "Game";
    
    mInterfaceTop = 0;
    mInterfaceBottom = 0;
    
    mDidSetupBoard = false;
    
    mInterfaceTopHeight = 130;
    
    mEssenceTargetX = 300.0f;
    mEssenceTargetY = 440.0f;
    
    if(gIsLargeScreen)
    {
        mInterfaceBottomHeight = (90 + 90);
        mInterfaceTileSize = 55;
    }
    else
    {
        mInterfaceBottomHeight = (90 + 90);
        mInterfaceTileSize = 55;
    }
    
    for(int i=0;i<4;i++)
    {
        mScoreAnimationNodeX[i] = 0.0f;
        mScoreAnimationNodeY[i] = 0.0f;
    }
    
    mGameMenu = 0;
    
    SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    mFlashColor = FColor(1.0f, 0.0f, 1.0f, 0.0f);
    
    mWarning = false;
    mWarningAlertTimer = 0;
    
    mWarningSoundTickTockTimer = 0;
    mWarningSoundTick = false;
    
    mCollectionTypeCount = 0;
    
    for(int i=0;i<8;i++)
    {
        mCollectionTypeAnimationTargetX[i] = 100.0f;
        mCollectionTypeAnimationTargetY[i] = 40.0f;
        
        mCollectionType[i] = COLLECTION_TYPE_TILE;
        mCollectionTypeIndex[i] = 0;
        
        mCollectionCount[i] = 0;
        mCollectionCountTotal[i] = 0;
        
        mCollectionComplete[i] = false;
    }
    
    mLevelComplete = false;
    mLevelCompleteOverlay = 0;
    mLoadLevelIndex = pLevelIndex;
    
    mAnimationScreenFade = 0.0f;
    
    mStartAnimation = false;
    
    mStartAnimationTimer = 20;
    mStartAnimationIndex = 0;
    mStartAnimationNumbarScale = 1.0f;;
    mStartAnimationNumbarScaleSpeed = 0.0f;
    mStartAnimationGoFade = 1.0f;
    mStartAnimationNumberScalePauseTimer = 0;
    
    mStartAnimationGoRotationSin = 120.0f;
    mStartAnimationGoScaleSin = 0.0f;
    mStartAnimationGoScale = 1.0f;
    mStartAnimationGoScaleSpeed = 0.0f;
    
    mDarkenFade = 0.0f;
    
    mDiscoverStarCount = 0;
    mDiscoverStarTotal = 3;
    
    mMainItem = 0;
    

    
    
    
#ifdef EDITOR_MODE
    
    mEditorCanvas = new EditorUCanvas();
    AddSubview(mEditorCanvas);
    
    
    mBoard = new EditorBoard();
    AddSubview(mBoard);
    
#else
    mBoard = new Board();
    AddSubview(mBoard);
    SetUpForLevel(mLoadLevelIndex);
#endif
    
    
    
    
}

Game::~Game()
{
    
    if(gUtils)
    {
        //if(gUtils->mReferenceView == this)
        //{
        //    gUtils->SetReferenceView(0);
        //}
    }
    
    gGame = 0;
    
    //delete mLevelEggAnimation;
    //mLevelEggAnimation = 0;
    
    mAnimations.Free();
    mAnimationsTop.Free();
    mAnimationsTopAdditive.Free();
    mCollectedEssences.Free();
}

void Game::SetUpForLevel(int pLevelIndex)
{
    
#ifdef EDITOR_MODE
    
    mLoadLevel = "editor_level.xml";
    
    //gEditor->Load("editor_level.xml");
    //mBoard->Load("editor_level.xml");
    //mBoard->Load("editor_level.xml");
    
    
#else
    
    //mBoard->SizeGrid(9, 72);
    //mBoard->GenerateTiles(9, 72);
    //mBoard->Load("level_item_test");
    
    if(pLevelIndex == 1)
    {
        mLoadLevel = "level_test_7w_dense_i_t";
        
        //CollectionTypeAddTile(0, 20);
        //CollectionTypeAddTile(1, 12);
        //CollectionTypeAddTile(2, 4);
    }
    else if(pLevelIndex == 2)
    {
        mLoadLevel = "level_chain_mode_7_try";
        
        //CollectionTypeAddTile(0, 10);
        //CollectionTypeAddTile(1, 24);
    }
    else
    {
        //level_easy_basic_exploration
        //level_learn_rocks_n_treasures
        
        //mLoadLevel = "level_intro";
        //mLoadLevel = "level_test_fast";
        //mLoadLevel = "level_metal_n_stone";
        mLoadLevel = "level_thanksgiving";
        
        //mLoadLevel = "level_learn_rocks_n_treasures";
        
        
        
        mBoard->SetStartMoveCount(30);
    }
    
    
    
    //level_easy_powerup_explore
    //level_easy_treasure_explore
    
    
    CollectionTypeSetUp();
    
#endif
    
    
    
#ifdef EDITOR_MODE
    
    mInterfaceTop = 0;
    mInterfaceBottom = 0;
    
    mStartAnimation = false;
    
#else
    
    float aInterfaceScale = 1.0f;
    if(gIsLargeScreen == false)aInterfaceScale = 0.5f;
    
    
    mInterfaceTop = new GameInterfaceTop();
    AddSubview(mInterfaceTop);//, 5);
    
    mInterfaceBottom = new GameInterfaceBottom();
    AddSubview(mInterfaceBottom);//, 87);
    
#endif
    
}

int aHax = 0;




void Game::PositionContent()
{
    SetFrame(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    float aTargetInterfaceWidth = 768.0f;
    
    
    if((gAppWidth / gAppHeight) >= 0.7f)
    {
        aTargetInterfaceWidth = 640.0f;
    }
    
    //float aInterfaceScale = (aTargetInterfaceWidth / gAppWidth);
    //float aInterfaceWidth = aTargetInterfaceWidth * aInterfaceScale;
    
    if(mInterfaceTop)
    {
        //mInterfaceTop->SetUpWithWidth(aInterfaceWidth);
        mInterfaceTop->SetUp();
        
    }
    
    float aInterfaceTopHeight = 0.0f;
    
    if(mInterfaceTop)
    {
        aInterfaceTopHeight = mInterfaceTop->GetHeight() * mInterfaceTop->GetTransformScale();
    }
    
    if(mDidSetupBoard == false)
    {
        if(gIsLargeScreen)
        {
            mBoard->SetUpToFitInterface(gTileWidth, aInterfaceTopHeight, 160.0f);
        }
        else
        {
            mBoard->SetUpToFitInterface(gTileWidth, aInterfaceTopHeight, 180.0f);
        }
        
        mBoard->Load(mLoadLevel.c());
        mBoard->StartAnimation();
        
        //mDidSetupBoard = true;
        
        
        //mBoard->SetUpToFitInterface(gTileWidth, aInterfaceTopHeight, 100.0f);
        //mBoard->Load(mLoadLevel.c());
        //mBoard->StartAnimation();
        
        
        if(mInterfaceTop)
        {
            mInterfaceTop->SetDisplayScore(gApp->mMeta.mScore);
            mInterfaceTop->SetDisplayMoves(mBoard->mStats->mMoveCount, mBoard->mStats->mMoveCountTotal);
            
        }
        
        
        mDidSetupBoard = true;
    }
    
    //mBoard->SetUpToFitInterface(gTileWidth, aInterfaceTopHeight, 140.0f);
    //mBoard->SetUpToFitInterface(gTileWidth, aInterfaceTopHeight, 140.0f);
    
    aHax++;
    //if(aHax < 300)
    //{
    if(mInterfaceBottom)
    {
        float aBottomY = mBoard->GetY() + mBoard->GetTransformScale() * mBoard->GetHeight();
        
        mInterfaceBottom->SetUp(aBottomY, GetHeight() - aBottomY);
        
        if(mMainItem == 0)
        {
            mMainItem = mInterfaceBottom->mBlaster;
        }
        
        if(mMainItem)
        {
            FVec2 aConverted = Convert(mMainItem->mWidth2, mMainItem->mHeight2, mMainItem, this);
            
            
            mEssenceTargetX = aConverted.mX;
            mEssenceTargetY = aConverted.mY;
        }
    }
    //}
}

void Game::Update()
{
    //if(gUtils)gUtils->SetReferenceView(this);
    
    
#ifdef EDITOR_MODE
    mFlashColor.mAlpha = 0.0f;
    return;
#endif
    
    if(mInterfaceTop)
    {
        mScoreAnimationNodeX[0] = 10.0f;//mInterfaceTop->mBoxScore.GetX();
        mScoreAnimationNodeY[0] = 11.25f;//mInterfaceTop->mBoxScore.GetY();
        
        mScoreAnimationNodeX[1] = 100.0f;//mInterfaceTop->mBoxGem1.GetX();
        mScoreAnimationNodeY[1] = 80.0f;//mInterfaceTop->mBoxGem1.GetY();
        
        mScoreAnimationNodeX[2] = 200.0f;//mInterfaceTop->mBoxGem2.GetX();
        mScoreAnimationNodeY[2] = 90.0f;//mInterfaceTop->mBoxGem2.GetY();
        
        mScoreAnimationNodeX[3] = 320.0f;//mInterfaceTop->mBoxGem3.GetX();
        mScoreAnimationNodeY[3] = 65.0f;//mInterfaceTop->mBoxGem3.GetY();
        
        for(int i=0;i<4;i++)
        {
            
            mScoreAnimationNodeX[i] *= mInterfaceTop->GetTransformScale() + mInterfaceTop->GetX();
            mScoreAnimationNodeY[i] *= mInterfaceTop->GetTransformScale() + mInterfaceTop->GetY();
            
            mScoreAnimationNodeX[i] += mInterfaceTop->GetTransformScale() * 30.0f;
            mScoreAnimationNodeY[i] += mInterfaceTop->GetTransformScale() * 27.0f;
        }
    }
    
    if(mFlashColor.mAlpha > 0.0f)
    {
        mFlashColor.mAlpha -= 0.075f;
        if(mFlashColor.mAlpha <= 0.0f)
        {
            mFlashColor.mAlpha = 0.0f;
        }
    }
    
    
    //mDarkenFade
    if(gApp->IsPaused())
    {
        mDarkenFade+= 0.01f;
        if(mDarkenFade >= 1.0f)mDarkenFade = 1.0f;
        
        return;
    }
    else
    {
        if(mDarkenFade > 0.0f)
        {
            mDarkenFade -= 0.01f;
            if(mDarkenFade <= 0.0f)
            {
                mDarkenFade = 0.0f;
            }
        }
    }
    
    
    /*
     
     if((mBoard != 0) && (mJarHeatBeam != 0))
     {
     
     if(mBoard->mJarTriggering == true)
     {
     float aCenterX = gBoard->GetTileCenterX(mBoard->mJarTargetGridX);
     float aCenterY = gBoard->GetTileCenterY(mBoard->mJarTargetGridY);
     
     float aScale = UntransformScale();
     
     aCenterX = UntransformX(aCenterX);
     aCenterY = UntransformY(aCenterY);
     
     //Graphics::SetColor(1.0f, 0.0f, 1.0f, 1.0f);
     //Graphics::DrawLine(mEssenceTargetX, mEssenceTargetY, aCenterX, aCenterY, 4.0f);
     //Graphics::SetColor();
     
     mJarHeatBeam->Focus(mEssenceTargetX, mEssenceTargetY, aCenterX, aCenterY);
     }
     }
     
     */
    
    
    if(mLevelComplete)
    {
        //TODO:
        
        //if(gApp->mPopoverViews.mCount == 0)
        //{
        
        
    }
    else
    {
        if(mStartAnimation)
        {
            if(mStartAnimationIndex <= 0)
            {
                mStartAnimationTimer--;
                
                
                if(mStartAnimationTimer <= 0)
                {
                    mStartAnimationNumbarScale = 0.05f;
                    mStartAnimationNumbarScaleSpeed = 0.220f;
                    
                    mStartAnimationNumberScalePauseTimer = 19;
                    
                    mStartAnimationIndex = 1;
                    
                    gApp->mSoundStartAnimationBeep.Play();
                }
                
            }
            else
            {
                
                
                
                if(mStartAnimationIndex <= 3)
                {
                    
                    mStartAnimationGoRotationSin += 5.0f;
                    if(mStartAnimationGoRotationSin >= 360.0f)mStartAnimationGoRotationSin -= 360.0f;
                    
                    mStartAnimationGoScaleSin += 14.0f;
                    if(mStartAnimationGoScaleSin >= 360.0f)mStartAnimationGoScaleSin -= 360.0f;
                    
                    
                    mStartAnimationNumbarScale += mStartAnimationNumbarScaleSpeed;
                    
                    if(mStartAnimationNumbarScaleSpeed <= 0.0f)
                    {
                        if(mStartAnimationNumberScalePauseTimer > 0)
                        {
                            mStartAnimationNumberScalePauseTimer--;
                            mStartAnimationNumbarScaleSpeed = 0;
                        }
                        else
                        {
                            mStartAnimationNumbarScaleSpeed -= 0.0075f;
                        }
                    }
                    else
                    {
                        mStartAnimationNumbarScaleSpeed -= 0.0195f;
                    }
                    
                    if(mStartAnimationNumbarScale <= 0.0f)
                    {
                        mStartAnimationNumbarScale = 0.05f;
                        mStartAnimationNumbarScaleSpeed = 0.220f;
                        
                        
                        mStartAnimationIndex++;
                        
                        if(mStartAnimationIndex > 3)
                        {
                            gApp->mSoundStartAnimationGo.Play();
                            
                            mStartAnimationGoScale = 0.025f;
                            mStartAnimationGoScaleSpeed = 0.15f;
                            
                            
                        }
                        else
                        {
                            gApp->mSoundStartAnimationBeep.Play();
                            
                            mStartAnimationTimer = 90;
                            mStartAnimationNumberScalePauseTimer = 19;
                        }
                    }
                }
                else
                {
                    
                    mStartAnimationGoRotationSin += 12.0f;
                    if(mStartAnimationGoRotationSin >= 360.0f)mStartAnimationGoRotationSin -= 360.0f;
                    
                    mStartAnimationGoScaleSin += 6.0f;
                    if(mStartAnimationGoScaleSin >= 360.0f)mStartAnimationGoScaleSin -= 360.0f;
                    
                    
                    mStartAnimationTimer--;
                    
                    mStartAnimationGoScale += mStartAnimationGoScaleSpeed;
                    mStartAnimationGoScaleSpeed -= 0.0115f;
                    
                    
                    if(mStartAnimationGoScaleSpeed < 0)
                    {
                        if(mStartAnimationGoScaleSpeed < -1)mStartAnimationGoScaleSpeed = -1;
                        
                        if(mStartAnimationGoScale < 1.0f)mStartAnimationGoScale = 1.0f;
                    }
                    
                    
                    
                    
                    
                    if(mStartAnimationTimer <= 5)
                    {
                        mStartAnimationTimer = 5;
                        
                        mStartAnimationGoFade -= 0.0685f;
                        
                        if(mStartAnimationGoFade <= 0)
                        {
                            mStartAnimationTimer = 0;
                            mStartAnimation = false;
                        }
                    }
                }
            }
            
            
        }
        else
        {
            
        }
    }
    
    mAnimations.Update();
    mAnimationsAdditive.Update();
    
    mAnimationsTop.Update();
    mAnimationsTopAdditive.Update();
    
    mCollectedEssences.Update();
    
}

void Game::Draw()
{
    
    if(mBoard) mBoard->DrawManual();
    
    DrawTransform();
    
    mAnimations.Draw();
    Graphics::BlendSetAdditive();Graphics::SetColor();
    mAnimationsAdditive.Draw();
    Graphics::BlendSetAlpha();Graphics::SetColor();
    
    if(mFlashColor.mAlpha > 0.0f)
    {
        Graphics::SetColor(mFlashColor);
        
        Graphics::DrawRect(mX, mY, mWidth, mHeight);
        
        Graphics::SetColor();
    }
    
    
    
    //mPopoverShowing = false;
    // = 0.0f;
    
    if(gApp->mPopoverFade > 0.0f)
    {
        Graphics::SetColor(0.0f, 0.0f, 0.0f, gApp->mPopoverFade);
        Graphics::DrawRect(mX, mY, mWidth, mHeight);
        Graphics::SetColor();
    }
    
    if(mInterfaceTop)mInterfaceTop->DrawManual();
    if(mInterfaceBottom)mInterfaceBottom->DrawManual();
    
    DrawTransform();
    
    float aBottomY = mBoard->GetY() + mBoard->GetTransformScale() * mBoard->GetHeight();
    
    if(mInterfaceBottom)
    {
        mInterfaceBottom->SetUp(aBottomY, GetHeight() - aBottomY);
    }
    
    float aX = 0.0f;
    float aY = 0.0f;
    
    EnumList(ActionProcItem, aItem, mActionProcItems)
    {
        if(aItem->mTriggering)
        {
            aX = aItem->mWidth2;
            aY = aItem->mHeight2;
            
            FVec2 aConverted = Convert(aX, aY, aItem, this);
            
            aX = aConverted.mX;
            aY = aConverted.mY;
            
            
            aItem->DrawFocus(aX, aY);
        }
    }
    
    
    mAnimationsTop.Draw();
    
    Graphics::BlendSetAdditive();
    Graphics::SetColor();
    
    mCollectedEssences.Draw();
    mAnimationsTopAdditive.Draw();
    
    Graphics::BlendSetAlpha();
    Graphics::SetColor();
    
    if(false)
    {
        float aAdScale = 1.0f;
        if(gIsLargeScreen == false)aAdScale = 0.5f;
        float aBannerHeight = gApp->mAdBannerDemo.mHeight * aAdScale;
        gApp->mAdBannerDemo.DrawScaled(gAppWidth2, gAppHeight - (aBannerHeight / 2.0f), aAdScale);
    }
    
    Graphics::SetColor();
    
    
    /*
     Graphics::BlendSetAdditive();
     
     float aX = 32.0f;
     float aY = 150.0f;
     
     for(int i=0;i<4;i++)
     {
     gApp->mEffectParticleFlare[0][i].Draw(aX, aY);
     gApp->mEffectParticleFlare[1][i].Draw(aX, aY + 60.0f);
     
     gApp->mEffectParticleFlareLarge[0][i].Draw(aX, aY + 140.0f);
     gApp->mEffectParticleFlareLarge[1][i].Draw(aX, aY + 260.0f);
     
     
     
     
     aX += 100.0f;
     }
     
     aY += 440.0f;
     
     
     aX = 40.0f;
     
     for(int i=0;i<8;i++)
     {
     gApp->mEffectTwinkleYellow[i].Draw(aX, aY);
     gApp->mEffectTwinkleYellowLarge[i].Draw(aX, aY + 80.0f);
     
     aX += 80.0f;
     
     }
     
     */
    
    
}

bool Game::IsPaused()
{
    
    bool aReturn = false;
    
    return aReturn;
}

void Game::TouchDown(float pX, float pY, void *pData)
{
    
}

void Game::TouchMove(float pX, float pY, void *pData)
{
    
}

void Game::TouchUp(float pX, float pY, void *pData)
{
    
}

void Game::TouchFlush()
{
    
}


void Game::SetDisplayScore(int pScore)
{
    if(mInterfaceTop)
    {
        
        mInterfaceTop->SetDisplayScore(pScore);
        
    }
}


void Game::Flash(FColor pColor)
{
    mFlashColor = pColor;
}

float Game::UntransformScale()
{
    float aReturn = 1.0f;
    
    if(gBoard)
    {
        float aScale = gBoard->GetTransformScale();
        
        aReturn = aScale;
    }
    
    return aReturn;
    
    //return UntransformScale(1.0f);
}

float Game::UntransformScale(float pScale)
{
    return (UntransformScale() * pScale);
}

float Game::UntransformX(float pX)
{
    float aReturn = pX;
    
    if(gBoard)
    {
        aReturn = gBoard->GetFrame().mX + gBoard->GetTransformScale() * pX;
    }
    
    return aReturn;
}

float Game::UntransformY(float pY)
{
    float aReturn = pY;
    
    if(gBoard)
    {
        aReturn = mBoard->GetFrame().mY + gBoard->GetTransformScale() * (pY - mBoard->mOffsetY);
    }
    
    return aReturn;
}







void Game::DiscoverStar(GameTileStar *pStar, float pCenterX, float pCenterY)
{
    //Log("DiscoverStar()\n");
    
    float aScale = UntransformScale();
    
    float aX = UntransformX(pCenterX);
    float aY = UntransformY(pCenterY);
    
    mDiscoverStarCount++;
    //mDiscoverStarTotal
    
    AnimationDiscoveredStar *aDiscoverStar = new AnimationDiscoveredStar();
    
    aDiscoverStar->SetStartAffine(aX, aY, aScale);
    aDiscoverStar->SetStartDiscoverNumber(1, 3);
    
    mAnimations.Add(aDiscoverStar);
    
    if(mInterfaceTop)
    {
        mInterfaceTop->DiscoverStar();
    }
    
}

void Game::DiscoverTreasure(GameTileTreasure *pTreasure, float pCenterX, float pCenterY)
{
    float aScale = UntransformScale();
    
    float aX = UntransformX(pCenterX);
    float aY = UntransformY(pCenterY);
    
    int aTreasureType = 0;
    
    if(pTreasure != 0)
    {
        aTreasureType = pTreasure->mSpecialIndex;
    }
    
    if((aTreasureType % 2) == 0)
    {
        gApp->mMeta.mCurrencyGem1++;
    }
    else
    {
        gApp->mMeta.mCurrencyGem2++;
    }
    
    
    for(int i=0;i<7;i++)
    {
        FParticle *aCoin = new FParticle(gApp->mSequenceCoinSpin[gRand.Get(5)], true);
        aCoin->mFrame = gRand.GetFloat(aCoin->mSpriteSequence->GetMaxFrame());
        aCoin->SetPos(aX + gRand.F(-8.0f, 8.0f), aY + gRand.F(-8.0f, 8.0f));
        aCoin->mGravityY = 0.3f;
        aCoin->mFrameSpeed = gRand.F(0.6f, 0.70f);
        aCoin->SetSpeed(gRand.GetFloat(-3.0f, 3.0f), gRand.F(-14.0f, -6.0f));
        mAnimations.Add(aCoin);
    }
    
    
    
    AnimationDiscoveredTreasure *aDiscoverTreasure = new AnimationDiscoveredTreasure();
    
    aDiscoverTreasure->mTreasureType = aTreasureType;
    aDiscoverTreasure->SetStartAffine(aX, aY, aScale);
    
    //aDiscoverTreasure->SetStartDiscoverNumber(1, 3);
    
    mAnimations.Add(aDiscoverTreasure);
}

void Game::CollectEssence(float pCenterX, float pCenterY, int pEssenceCount, int pFlag)
{
    CollectedEssence *aEssence = new CollectedEssence();
    aEssence->SetStartAffine(pCenterX, pCenterY, 1.3f);
    aEssence->mRotation = gRand.GetFloat(200.0f);
    mCollectedEssences.Add(aEssence);
    
    
    //FVec2 aConverted = Convert(mInterfaceBottom->mCharger.GetCenterX(), mInterfaceBottom->mCharger.GetCenterY(), mInterfaceBottom->mCharger, this);
    //mEssenceTargetX = aConverted.mX;
    //mEssenceTargetY = aConverted.mY;
    
    aEssence->ShootTowardsJar(mEssenceTargetX, mEssenceTargetY);
    
    
    if(mMainItem)
    {
        mMainItem->WillCollectItem(aEssence);
        aEssence->mTarget = mMainItem;
        
    }
    
    //FObjectList                             mAnimationsTop;
    //FObjectList                             mAnimationsTopAdditive;
    
    //mEffectYellowGlowBomb
    
}

bool Game::CollectedEssenceReachedInterface(CollectedEssence *pEssence)
{
    bool aReturn = false;
    
    if(mMainItem)
    {
        mMainItem->CollectItem(pEssence);
        
    }
    
    if(mInterfaceBottom)
    {
        //mMainItem
        
        //mInterfaceBottom->mCharger.CollectEssence(pEssence);
    }
    
    return aReturn;
}

int Game::CollectedEssencesCount(void *pTarget)
{
    int aReturn = 0;
    
    EnumList(CollectedEssence, aEssence, mCollectedEssences)
    {
        if(aEssence->mComplete == false)
        {
            if(aEssence->mTarget == pTarget)
            {
                aReturn++;
            }
        }
    }
    
    return aReturn;
}

//


void Game::ActionProcItemWillBeReady()
{
    if(mBoard)
    {
        if(mBoard->mFinished == false)
        {
            mBoard->ActionProcItemCheck();
        }
    }
}

void Game::ActionProcItemTriggerStop()
{
    if(mBoard)
    {
        mBoard->ActionProcItemTriggerStop();
    }
}


bool Game::AnyActionProcItemReady()
{
    bool aReturn = false;
    
    EnumList(ActionProcItem, aItem, mActionProcItems)
    {
        if(aItem->IsReady())aReturn = true;
    }
    
    return aReturn;
}

bool Game::AnyActionProcItemWillBeReady()
{
    bool aReturn = false;
    
    EnumList(ActionProcItem, aItem, mActionProcItems)
    {
        if(aItem->WillBeReady())aReturn = true;
    }
    
    return aReturn;
}

int Game::ActionProcItemSelect()
{
    int aReturn = -1;
    
    FList aPossibleCandidates;
    
    EnumList(ActionProcItem, aItem, mActionProcItems)
    {
        if(aItem->IsReady())
        {
            aPossibleCandidates.Add(aItem);
        }
    }
    
    
    ActionProcItem *aTriggerItem = (ActionProcItem *)(aPossibleCandidates.FetchRandom());
    
    if(aTriggerItem)
    {
        aReturn = aTriggerItem->mItemID;
    }
    
    return aReturn;
}

void Game::ComputeFocus(ActionProcItemFocus *pFocus)
{
    if((pFocus != 0) && (gBoard != 0))
    {
        float aX = 0.0f;
        float aY = 0.0f;
        
        for(int i=0;i<3;i++)
        {
            if(pFocus->mMatch[i])
            {
                aX = gBoard->GetTileCenterX(pFocus->mMatchGridX[i]);
                aY = gBoard->GetTileCenterY(pFocus->mMatchGridY[i]);
                
                pFocus->mMatchCenterX[i] = UntransformX(aX);
                pFocus->mMatchCenterY[i] = UntransformY(aY);
                
            }
            
            if(pFocus->mObstacle[i])
            {
                aX = gBoard->GetTileCenterX(pFocus->mObstacleGridX[i]);
                aY = gBoard->GetTileCenterY(pFocus->mObstacleGridY[i]);
                
                pFocus->mObstacleCenterX[i] = UntransformX(aX);
                pFocus->mObstacleCenterY[i] = UntransformY(aY);
                
            }
        }
    }
}

void Game::ActionProcItemStartTrigger(int pItemID, ActionProcItemFocus *pFocus)
{
    ComputeFocus(pFocus);
    
    ActionProcItem *aActiveItem = 0;
    EnumList(ActionProcItem, aItem, mActionProcItems)if(aItem->mItemID == pItemID)aActiveItem = aItem;
    if(aActiveItem)
    {
        float aX = 0.0f;
        float aY = 0.0f;
        
        aX = aActiveItem->mWidth2;
        aY = aActiveItem->mHeight2;
        
        FVec2 aConverted = Convert(aX, aY, aActiveItem, this);
        
        aX = aConverted.mX;
        aY = aConverted.mY;
        
        aActiveItem->StartTrigger(aX, aY, pFocus);
    }
}

void Game::ActionProcItemUpdateTrigger(int pItemID, ActionProcItemFocus *pFocus)
{
    ComputeFocus(pFocus);
    
    ActionProcItem *aActiveItem = 0;
    EnumList(ActionProcItem, aItem, mActionProcItems)if(aItem->mItemID == pItemID)aActiveItem = aItem;
    
    if(aActiveItem)
    {
        float aX = 0.0f;
        float aY = 0.0f;
        
        aX = aActiveItem->mWidth2;
        aY = aActiveItem->mHeight2;
        
        FVec2 aConverted = Convert(aX, aY, aActiveItem, this);
        
        aX = aConverted.mX;
        aY = aConverted.mY;
        
        aActiveItem->UpdateTrigger(aX, aY, pFocus);
    }
    
    
}

int Game::ActionProcItemTriggerChargeTime(int pItemID)
{
    ActionProcItem *aActiveItem = 0;
    EnumList(ActionProcItem, aItem, mActionProcItems)if(aItem->mItemID == pItemID)aActiveItem = aItem;
    
    int aReturn = 10;
    
    if(aActiveItem)aReturn = aActiveItem->GetTriggerChargeTime();
    
    return aReturn;
}

void Game::CircleBurst(float pX, float pY, FSprite *pSprite, int pCount, float pSpeed)
{
    
}

void Game::CircleBurst(float pX, float pY)
{
    CircleBurst(pX, pY, &(gApp->mEffectParticleStar[3]), 8, 6.0f);
}

void Game::LevelCompleteDialogShow(bool pDidWin)
{
    mLevelComplete = true;
    if(mLevelCompleteOverlay == 0)
    {
        mLevelCompleteOverlay = new LevelCompleteOverlay();
        
        float aScale = 1.0f;
        if(gIsLargeScreen == false)aScale = 0.5f;
        
        mLevelCompleteOverlay->SetUp(aScale, FVec2(gAppWidth, gAppHeight), pDidWin);
        
        AddSubview(mLevelCompleteOverlay);
    }
}

void Game::CollectionTypeSetUp()
{
    if(mInterfaceTop)
    {
        
    }
}

void Game::CollectionTypeAddTile(int pTileType, int pCount)
{
    mCollectionType[mCollectionTypeCount] = COLLECTION_TYPE_TILE;
    mCollectionTypeIndex[mCollectionTypeCount] = pTileType;
    mCollectionCount[mCollectionTypeCount] = pCount;
    mCollectionCountTotal[mCollectionTypeCount] = pCount;
    mCollectionComplete[mCollectionTypeCount] = false;
    mCollectionTypeCount++;
}

void Game::CollectionTypeAddStar(int pNumber)
{
    mCollectionType[mCollectionTypeCount] = COLLECTION_TYPE_STAR;
    mCollectionTypeIndex[mCollectionTypeCount] = 0;
    mCollectionCount[mCollectionTypeCount] = pNumber;
    mCollectionCountTotal[mCollectionTypeCount] = pNumber;
    mCollectionComplete[mCollectionTypeCount] = false;
    mCollectionTypeCount++;
}


void Game::CollectionTypeUpdateTile(int pTileType, int pCount)
{
    
    for(int i=0;i<mCollectionTypeCount;i++)
    {
        if(mCollectionType[i] == COLLECTION_TYPE_TILE)
        {
            if(mCollectionTypeIndex[i] == pTileType)
            {
                mCollectionCount[i] -= pCount;
                
                if(mCollectionCount[i] <= 0)
                {
                    mCollectionComplete[i] = true;
                    mCollectionCount[i] = 0;
                }
                
                if(mInterfaceTop)
                {
                    
                }
            }
        }
    }
    CollectionTypeCheckCompletion();
}

void Game::CollectionTypeCheckCompletion()
{
    bool aAnyIncomplete = false;
    
    for(int i=0;i<mCollectionTypeCount;i++)
    {
        if(mCollectionComplete[i] == false)
        {
            aAnyIncomplete = true;
        }
    }
    
    if(aAnyIncomplete == false)
    {
        
    }
}
