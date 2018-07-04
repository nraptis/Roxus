//
//  GameMenu.cpp
//  CoreDemo
//
//  Created by Nick Raptis on 10/25/13.
//  Copyright (c) 2013 Nick Raptis Inc. All rights reserved.
//

#include "GameMenu.h"
#include "MainMenu.h"

GameMenu::GameMenu()
{
    float aScale = 1.0f;
    if(gIsLargeScreen == false)aScale = 0.5f;
    
    SetSize(gApp->mGIPaperMenuBack);
    SetTransformAnchor(0.5f, 0.5f);
    
    //SetUp(&(gApp->mGameMenuBack), FVec2(gAppWidth2, gAppHeight2), aScale);
    //SetUp(&(gApp->mGIPaperMenuBack));
    
    mButtonClose.SetUp(gApp->mGIPaperMenuCloseButton, mWidth - (gApp->mGIPaperMenuCloseButton.mWidth + 10.0f), 14.0f);
    AddSubview(mButtonClose);
    
    
    float aButtonWidth = gApp->mMIBigButton[0].mWidth;
    float aButtonHeight = gApp->mMIBigButton[0].mHeight;
    
    float aY = mHeight - (aButtonHeight + 90.0f);
    
    
    //mButtonMainMenu = new MenuButton();
    mButtonMainMenu.SetUp(gApp->mMIBigButton[2], mWidth2 - (aButtonWidth / 2.0f), aY);
    mButtonMainMenu.AddOverlay(&(gApp->mMIBigButtonTextQuit), 0);
    mButtonMainMenu.AddUnderlay(gApp->mMIBigButtonShadow[2]);
    AddSubview(mButtonMainMenu);
    aY -= (aButtonHeight - 22.0f);
    
    mButtonStore.SetUp(gApp->mMIBigButton[1], mWidth2 - (aButtonWidth / 2.0f), aY);
    mButtonStore.AddOverlay(&(gApp->mMIBigButtonTextStore), 0);
    mButtonStore.AddUnderlay(gApp->mMIBigButtonShadow[1]);
    AddSubview(mButtonStore);
    aY -= (aButtonHeight - 22.0f);
    
    mButtonOptions.SetUp(gApp->mMIBigButton[0], mWidth / 2.0f - (aButtonWidth / 2.0f), aY);
    mButtonOptions.AddOverlay(gApp->mMIBigButtonTextOptions);
    mButtonOptions.AddUnderlay(gApp->mMIBigButtonShadow[0]);
    
    AddSubview(mButtonOptions);
    aY -= (aButtonHeight - 22.0f);
    
    
    SetCenter();
    
}

GameMenu::~GameMenu()
{
    Log("Game Menu Dealloc!");
}

void GameMenu::Update()
{
    //MenuModal::Update();
    
}

void GameMenu::Draw()
{
	Graphics::SetColor();
    
    gApp->mGIPaperMenuBack.Draw(0.0f, 0.0f);
    
	Graphics::SetColor();
    
    //DrawBorders();
    //MenuModal::Draw();
}

//void GameMenu::ButtonClick(FButton *pButton)
void GameMenu::Notify(void *pSender)
{
    if(IsAnimating() == true)return;
    
    
    if(pSender == &mButtonOptions)
    {
        //gViewController.ModalViewAdd(new GameStoreScreen());
        
        gApp->PopupStoreMenu();
    }
    
    
    if(pSender == &mButtonClose)
    {
        
        gApp->ClosePopup();
        
        /*
        FView *aNext = gViewController.mRoot.ModalViewGetNextExcluding(this);
        
        if(aNext)
        {
            AnimationSetX(-400);
            
            AnimationSetID(2);
            AnimationCommit(70);
            
            
            aNext->SetCenter();
            aNext->AnimationSetX(0.0f);
            aNext->AnimationSetYFrom(aNext->GetY() + 30.0f);
            aNext->AnimationSetID(1);
            aNext->AnimationCommit(24);
        }
        
        //if(gViewController.ModalViewCount() <= 1)
        else
        {
            //GameMenu
            
            AnimationSetY(-200);
            AnimationSetID(2);
            AnimationSetScaleX(0.45f);
            AnimationSetScaleY(0.5f);
            AnimationCommit(24);
            
            //AnimateOut();
        }
        
        //gApp->PopoverKill(true);
        */
        
        return;
    }
    
    if(pSender == &mButtonMainMenu)
    {
        if(gApp->TransitionInProgress() == false)
        {
            gApp->TransitionTo(new MainMenu(), 0, new Transition());
        }
    }
}

void GameMenu::AnimationComplete(FViewAnimation *pAnimation, int pID)
{
    /*
    Log("[[GM - Animation Complete]] (%d)\n", pID);
    
    
    if(pID == 2)
    {
        Log("MVC1 - [%d]\n", gViewController.mRoot.ModalViewCount());
        
        Kill();
        
        Log("MVC2 - [%d]\n", gViewController.mRoot.ModalViewCount());
    }
    */
}
