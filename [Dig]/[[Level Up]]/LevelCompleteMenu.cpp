//
//  LevelCompleteMenu.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/25/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "LevelCompleteMenu.h"
#include "MainMenu.h"

LevelCompleteMenu::LevelCompleteMenu(bool pDidWin) : FView()
{
    Log("LevelCompleteMenu::LevelCompleteMenu()\n");
    
    mDidWin = pDidWin;
    
    SetSize(gApp->mGIPaperMenuBack);
    
    float aButtonWidth = gApp->mGIPaperMenuCloseButton.mWidth;
    float aButtonHeight = gApp->mGIPaperMenuCloseButton.mHeight;
    
    mButtonDone = new MenuButton();
    mButtonDone->SetUp(&(gApp->mGIPaperMenuCloseButton), 0, 0, FVec2(GetWidth() - (aButtonWidth + 18.0f), 20.0f));
    AddSubview(mButtonDone);
    
    //if(pDidWin)
    //{
    //    SetUp(&(gApp->mLevelCompleteMenuBackWin), FVec2(gAppWidth2, gAppHeight2), aScale);
    //}
    //else
    //{
    //    SetUp(&(gApp->mLevelCompleteMenuBackLose), FVec2(gAppWidth2, gAppHeight2), aScale);
    //}
    
    
    
    
    
    
    //aButtonWidth = gApp->mButtonMenuDone[0].mWidth;
    //aButtonHeight = gApp->mButtonMenuDone[0].mHeight;
    
    
    //mButtonDone = new MenuButton();
    //mButtonDone->SetUp(&(gApp->mButtonMenuDone[0]), 0, &(gApp->mButtonMenuDone[2]), FVec2(mFrame.mWidth / 2.0f - (aButtonWidth / 2.0f), mFrame.mHeight - (aButtonHeight + 62)));
    //AddSubview(mButtonDone);
    
    mStarEarnedDisplay[0] = false;
    mStarEarnedDisplay[1] = false;
    mStarEarnedDisplay[2] = false;
    
    
    mStarEarned[0] = true;
    mStarEarned[1] = true;//gRand.GetBool();
    mStarEarned[2] = true;//gRand.GetBool();
    
    mStarAnimationTimer = 50;
    mStarAnimationIndex = 0;
    mStarAnimation = true;
    
    
    mStarPos[0].mX = mWidth2;
    mStarPos[0].mY = 136;
    
    mStarPos[1].mX = mWidth2 - 166.0f;
    mStarPos[1].mY = 173;
    
    mStarPos[2].mX = mWidth2 + 171.0f;
    mStarPos[2].mY = 175;
    
    mStarShake[0] = 0.0f;
    mStarShake[1] = 0.0f;
    mStarShake[2] = 0.0f;
    
}

LevelCompleteMenu::~LevelCompleteMenu()
{
    Log("LevelCompleteMenu Dealloc!");
}

void LevelCompleteMenu::Update()
{
    
    if(IsAnimating() == false)
    {
        if(mStarAnimation)
        {
            mStarAnimationTimer--;
            
            if(mStarAnimationTimer <= 0)
            {
                if(mStarAnimationIndex >= 0 && mStarAnimationIndex < 3)
                {
                    if(mStarEarned[mStarAnimationIndex])
                    {
                        mStarEarnedDisplay[mStarAnimationIndex] = true;
                        gApp->mSoundMenuStarEarn.Play();
                        mStarShake[mStarAnimationIndex] = 4.0f;
                    }
                }
                mStarAnimationTimer = 30;
                mStarAnimationIndex++;
            }
            
            
        }
        
        
        for(int i=0;i<3;i++)
        {
            if(mStarShake[i] > 0)
            {
                mStarShake[i] -= 0.45f;
                if(mStarShake[i] <= 0.0f)
                {
                    mStarShake[i] = 0.0f;
                }
            }
        }
        
    }
    
}

void LevelCompleteMenu::Draw()
{
    
	Graphics::SetColor();
    
    gApp->mGIPaperMenuBack.Draw(0.0f, 0.0f);
    
	Graphics::SetColor();
    
    DrawBorders();
    
    
    for(int i=0;i<3;i++)
    {
        
        if(mStarEarnedDisplay[i])
        {
            float aDrawX = mStarPos[i].mX;
            float aDrawY = mStarPos[i].mY;
            
            float aDrawScale = 1.0f;
            float aDrawRotation = 0.0f;
            
            float aShake = mStarShake[i];
            
            if(aShake > 0.0f)
            {
                
                aDrawX += gRand.GetFloat(-aShake, aShake);
                aDrawY += gRand.GetFloat(-aShake, aShake);
                
                aDrawScale += gRand.GetFloat(-(aShake * 0.05f), (aShake * 0.05f));
                
                aDrawRotation += gRand.GetFloat(-aShake, aShake);
            }
            
            gApp->mTimeOverMenuStar[i].Draw(aDrawX, aDrawY, aDrawScale, aDrawRotation);
        }
    }
    
    
    //SetColor(0.0f, 1.0f, 0.0f);
    //DrawRect(mButtonDone->GetX(), mButtonDone->GetY(), mButtonDone->GetWidth(), mButtonDone->GetHeight());
    
	Graphics::SetColor();
}

//void LevelCompleteMenu::ButtonClick(FButton *pButton)

void LevelCompleteMenu::Notify(void *pSender)
{    
    if(pSender == mButtonDone)
    {
        if(gApp->TransitionInProgress() == false)
        {
            gApp->TransitionTo(new MainMenu(), 0, new Transition());
        }
    }
    
}
