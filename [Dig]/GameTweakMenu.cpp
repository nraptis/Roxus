//
//  GameTweakMenu.cpp
//  DigMMMac
//
//  Created by Nicholas Raptis on 3/13/15.
//  Copyright (c) 2015 Darkswarm LLC. All rights reserved.
//

#include "GameTweakMenu.h"
#include "Game.h"
#include "Board.h"
#include "MainMenu.h"

GameTweakMenu::GameTweakMenu()
{
    mButtonReset = new UButton("Reset");
    mButtonLevelUp = new UButton("L-U");
    mButtonMainMenu = new UButton("MainM");
    mButtonGame = new UButton("Game");
    
    AddLine(mButtonReset, mButtonLevelUp, mButtonMainMenu, mButtonGame);
    
    SetText("Game Stuff");
    
    LayoutSubviews();
    
    DisableCloseButton();
    
    mGimpTimer = 0;
    
    SetPos(100, 330);
}

GameTweakMenu::~GameTweakMenu()
{
    
}



void GameTweakMenu::Notify(void *pSender)
{
    if(gBoard == 0)return;
    if(gGame == 0)return;
    
    if(pSender == mButtonLevelUp)
    {
        gBoard->LevelUp();
    }
    
    if(pSender == mButtonMainMenu)
    {
        if(gApp->TransitionInProgress() == false)
        {
            gApp->TransitionTo(new MainMenu(), 0, new Transition());
        }
        
    }
    
    if(pSender == mButtonGame)
    {
        if(gApp->TransitionInProgress() == false)
        {
            gApp->TransitionTo(new Game(0), 0, new Transition());
        }
    }
    
}

//UButton                                 *mButtonReset;
