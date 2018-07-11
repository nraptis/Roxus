//
//  Game.cpp
//  GoldDigger
//
//  Created by Nick Raptis on 1/23/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#include "Game.h"

float gTileWidth=46.0f;
float gTileHeight=46.0f;

Game::Game()
{
    mApp = GAPP;
    gGame = this;
    
    gTileWidth = 72.0f;
    gTileHeight = 72.0f;
    
    if(gIsLargeScreen == false)
    {
        gTileWidth /= 2.0f;
        gTileHeight /= 2.0f;
    }
    
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    mZoomScale = 1.0f;
    
    //mArena = new EditorGameArena();//GameArena();
    mArena = new GameArena();
    
    
    mCenterX = gAppWidth2;
    mCenterY = gAppHeight2;
    
    mPanning = false;
    
    mTapMode = false;
    
    mTapStartX = 0;
    mTapStartY = 0;
    
    
    mTouchCenterX = 0.0f;
    mTouchCenterY = 0.0f;
    
    mDragCenterX = 0.0f;
    mDragCenterY = 0.0f;
    
    mTouchCenterAdjustmentDirX = 0.0f;
    mTouchCenterAdjustmentDirY = 0.0f;
    
    mTouchStartCenterX = 0.0f;
    mTouchStartCenterY = 0.0f;
    
    mTouchStartDistance = 0.0f;
    mTouchStartScale = 0.0f;
    
    FitArenaOnScreen();
    
    mTestRotation = 0.0f;
    mTestFrame = 0.0f;
    
    mZoomScaleMin = (float)gAppWidth / gArenaWidth;
    mZoomScaleMax = 2.25f;
    
    
    mTestMode = TEST_MODE_UNIT_SPAWN;
    
    mTestUnitSpawnCount = 4;
    mTestUnitSpawnRandom = 8;
    
}

Game::~Game()
{
    delete mArena;
    mArena = 0;
    //delete mBoard;
    //mBoard = 0;
}

void Game::Update()
{
    
    if(mTapMode)
    {
        
    }
    
    if(mArena)
    {
        /*
        if(mApp->mTouchDownCount > 0)
        {
            float aWorldX = TransformX(mApp->mTouchDownX[0]);
            float aWorldY = TransformY(mApp->mTouchDownY[0]);
            
            mArena->RefreshGridCursor(aWorldX, aWorldY);
        }
        */
        
        mArena->Update();
        
    }
    
    mTestFrame += 0.25f;
    if(mTestFrame >= 20.0f)mTestFrame -= 20.0f;
    
    mTowerDetailMenu.Update();
    
    mTowerPickerMenu.Update();
    
}

void Game::Draw()
{

    Graphics::SetColor();
    Graphics::DrawRect(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    if(mArena)
    {
        Graphics::MatrixPush();
        Graphics::Translate(mCenterX, mCenterY, 0.0f);
        Graphics::Scale(mZoomScale);
        Graphics::Translate(-gArenaWidth2, -gArenaHeight2, 0.0f);
        
        mArena->Draw();
        
        if(mTowerPickerMenu.mCurrentTower)
        {
            mArena->DrawGridOverlay();
            mArena->DrawGridSelection();
        }
        
        Graphics::MatrixPop();
        
    }
    
    
    /*
    
    SetColor();
    float aDrawX = gAppWidth2;
    float aDrawY = gAppHeight2 / 2.0f;
    
    mApp->mRobot.Center(aDrawX, aDrawY, mTestRotation, mTestFrame);
    
    SetColor(1.0f, 0.0f, 0.0f);
    DrawLine(aDrawX, aDrawY, aDrawX + Sin(180.0f - mTestRotation) * 50, aDrawY + Cos(180.0f - mTestRotation) * 50);
    
    */
    
    mTowerDetailMenu.Draw();
    
    mTowerPickerMenu.Draw();
    
}

void Game::GoInactive()
{

}

void Game::GoActive()
{
    
}

void Game::Notify(void *pData)
{
    
}

void Game::KillPanning()
{
    mPanning = false;
}

void Game::FitArenaOnScreen()
{
    
    float aArenaWidth = gArenaWidth * mZoomScale;
    float aArenaHeight = gArenaHeight * mZoomScale;
    
    float aArenaLeft = mCenterX - (aArenaWidth / 2.0f);
    float aArenaRight = mCenterX + (aArenaWidth / 2.0f);
    
    float aArenaTop = mCenterY - (aArenaHeight / 2.0f);
    float aArenaBottom = mCenterY + (aArenaHeight / 2.0f);
    
    if(aArenaLeft > 0)
    {
        mCenterX -= aArenaLeft;
    }
    
    if(aArenaRight < gAppWidth)
    {
        mCenterX += (gAppWidth - aArenaRight);
    }
    
    if(aArenaWidth < gAppWidth)
    {
        mCenterX = gAppWidth2;
    }
    
    
    if(aArenaTop > 0)
    {
        mCenterY -= aArenaTop;
    }
    
    if(aArenaBottom < gAppHeight)
    {
        mCenterY += (gAppHeight - aArenaBottom);
    }
    
    if(aArenaHeight < gAppHeight)
    {
        mCenterY = gAppHeight2;
    }
    
}

void Game::ComputeTouches()
{
    mTouchStartCenterX = mCenterX;
    mTouchStartCenterY = mCenterY;
    
    mTouchStartScale = mZoomScale;


    /*
    if(mApp->mTouchDownCount <= 0)
    {
        mTouchCenterX = 0.0f;
        mTouchCenterY = 0.0f;
        
        mDragCenterX = 0.0f;
        mDragCenterY = 0.0f;
        
        mTouchStartDistance = 100.0f;
    }
    else
    {
        mTouchCenterX = mApp->mTouchDownX[0];
        mTouchCenterY = mApp->mTouchDownY[0];
        
        if(mApp->mTouchDownCount > 1)
        {
            for(int i=1;i<mApp->mTouchDownCount;i++)
            {
                mTouchCenterX += mApp->mTouchDownX[i];
                mTouchCenterY += mApp->mTouchDownY[i];
            }
            
            mTouchCenterX /= ((float)mApp->mTouchDownCount);
            mTouchCenterY /= ((float)mApp->mTouchDownCount);
            
            float aDiffX = mApp->mTouchDownX[1] - mApp->mTouchDownX[0];
            float aDiffY = mApp->mTouchDownY[1] - mApp->mTouchDownY[0];
            
            mTouchStartDistance = aDiffX * aDiffX + aDiffY * aDiffY;
            
            if(mTouchStartDistance >= 1.0f)mTouchStartDistance = sqrtf(mTouchStartDistance);
     
        }
        
        mDragCenterX = mTouchCenterX;
        mDragCenterY = mTouchCenterY;
        
        mTouchCenterAdjustmentDirX = (mCenterX - mTouchCenterX) / mZoomScale;
        mTouchCenterAdjustmentDirY = (mCenterY - mTouchCenterY) / mZoomScale;

    }

    */
    
}


void Game::TouchDown(int x, int y, void *pData) {
    mTapMode = false;

    if (mTowerDetailMenu.mAnimating) {
        mTowerPickerMenu.Deselect();
        KillPanning();
        return;
    }

    if (mTowerDetailMenu.mHidden == false) {
        if (mTowerDetailMenu.TouchHitsButton(x, y)) {
            printf("We Did Hit The Button!!\n");
        }
        else
        {
            mTowerDetailMenu.AnimateOut();
        }
        
        mTowerPickerMenu.Deselect();
        KillPanning();
    }
    else
    {
        mTowerPickerMenu.TouchDown(x, y, pData);
        if(mTowerPickerMenu.mCurrentTower)
        {
            KillPanning();
        }
        else
        {
            mPanning = true;
            ComputeTouches();

            /*
            if(mApp->mTouchDownCount == 1)
            {
                mTapMode = true;
                
                mTapStartX = x;
                mTapStartY = y;
            }
            */
            
        }
    }
}

void Game::TouchUp(int x, int y, void *pData)
{
    
    if(gEditor)
    {
        if(mTapMode)
        {
            gEditor->Click(TransformX(x), TransformY(y));
            mTapMode = false;
            return;
        }
        
    }
    
    if(mTowerDetailMenu.mHidden == false)
    {
        int aReleaseAction = mTowerDetailMenu.ReleaseAction(x, y);
        
        printf("RELEASE ACTION [%d]\n", aReleaseAction);
        
        if(aReleaseAction != -1)
        {
            Tower *aTower = mTowerDetailMenu.mTower;
            
            if(aTower && mArena)
            {
                mArena->RemoveTower(aTower->mGridX, aTower->mGridY);
            }
            
            mTowerDetailMenu.AnimateOut();
        }
        
    }
    else if(mTowerPickerMenu.mCurrentTower)
    {
        if(mTowerPickerMenu.IsHoveringOverSelectedButton(x, y))
        {
            
        }
        else
        {
            if(mArena)
            {
                if(mArena->CanPlaceTower())
                {
                    mArena->PlaceTower(mTowerPickerMenu.mCurrentTower);
                    mTowerPickerMenu.mCurrentTower = 0;
                }
            }
        }
        
        mTowerPickerMenu.Deselect();
    }
    else
    {
        ComputeTouches();
        
        if(mTapMode)
        {
            if(mArena)
            {
                Tower *aTower = mArena->GetTower(mArena->mCursorGridX, mArena->mCursorGridY);
                
                if(aTower)
                {
                    float aTowerX = CX(aTower->mGridX);
                    float aTowerY = CX(aTower->mGridY);
                    
                    
                    float aMenuX = UntransformX(aTowerX);
                    float aMenuY = UntransformY(aTowerY);
                    
                    mTowerDetailMenu.AnimateIn(aMenuX, aMenuY, mZoomScale, aTower);
                    
                }
                
                //mArena->RemoveTower(mArena->mCursorGridX, mArena->mCursorGridY);
            }
        }
    }
    
    if(mArena)
    {
        mArena->mCursorGridX = -1;
        mArena->mCursorGridY = -1;
    }
}

void Game::TouchMove(int x, int y, void *pData)
{
    
    if(mTowerDetailMenu.mHidden == false || mTowerDetailMenu.mAnimating == true)
    {
        KillPanning();
        mTapMode = false;
        return;
    }
    
    if(mTapMode)
    {
        int aDeltaTapX = (mTapStartX - x);
        if(aDeltaTapX < 0)aDeltaTapX=-aDeltaTapX;
        
        int aDeltaTapY = (mTapStartY - x);
        if(aDeltaTapY < 0)aDeltaTapY=-aDeltaTapY;
        
        int aTapMaxShift = gAppWidth / 50;
        if(aTapMaxShift < 10)aTapMaxShift = 10;
        
        if(aDeltaTapX > aTapMaxShift || aDeltaTapY > aTapMaxShift)
        {
            mTapMode = false;
        }
    }
    
    if(mTowerPickerMenu.mCurrentTower)
    {
        KillPanning();
    }
    
    if(mPanning)
    {
        mDragCenterX = x;
        mDragCenterY = y;

        /*
        if(mApp->mTouchDownCount > 0)
        {
            mDragCenterX = mApp->mTouchDownX[0];
            mDragCenterY = mApp->mTouchDownY[0];
            
            if(mApp->mTouchDownCount > 1)
            {
                for(int i=1;i<mApp->mTouchDownCount;i++)
                {
                    mDragCenterX += mApp->mTouchDownX[i];
                    mDragCenterY += mApp->mTouchDownY[i];
                }
                
                mDragCenterX /= ((float)mApp->mTouchDownCount);
                mDragCenterY /= ((float)mApp->mTouchDownCount);
                
                float aDiffX = mApp->mTouchDownX[1] - mApp->mTouchDownX[0];
                float aDiffY = mApp->mTouchDownY[1] - mApp->mTouchDownY[0];
                
                float aDist = aDiffX * aDiffX + aDiffY * aDiffY;
                if(aDist >= 1.0f)aDist = sqrtf(aDist);
                
                mZoomScale = mTouchStartScale + (aDist - mTouchStartDistance) / (300.0f);
                
                if(mZoomScale < mZoomScaleMin)mZoomScale = mZoomScaleMin;
                if(mZoomScale > mZoomScaleMax)mZoomScale = mZoomScaleMax;
            }
        }
        */
        
        float aPanX = (mDragCenterX - mTouchCenterX);
        float aPanY = (mDragCenterY - mTouchCenterY);
        
        mCenterX = (mTouchStartCenterX + aPanX) + ((mZoomScale - mTouchStartScale) * mTouchCenterAdjustmentDirX);
        mCenterY = (mTouchStartCenterY + aPanY) + ((mZoomScale - mTouchStartScale) * mTouchCenterAdjustmentDirY);
        
        FitArenaOnScreen();
    }
    
}

void Game::TouchFlush()
{
    mTowerPickerMenu.Deselect();
}

float Game::UntransformX(float pX)
{
    return mCenterX + (pX - gArenaWidth2) * mZoomScale;
}

float Game::UntransformY(float pY)
{
    return mCenterY + (pY - gArenaHeight2) * mZoomScale;
}

float Game::TransformX(float pX)
{
    return gArenaWidth2 + (pX - mCenterX) / mZoomScale;
}

float Game::TransformY(float pY)
{
    return gArenaHeight2 + (pY - mCenterY) / mZoomScale;
}

