//
//  Game.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/11/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#include "Game.h"
#include "GLApp.h"

Game *gGame = 0;

Game::Game()
{
    gGame = this;
    
    mBoard = 0;
    mInterfaceTop = 0;
    mInterfaceBottom = 0;
    
    //core_sound_musicPlay("music_game_loop.mp3", true);
    
    mBoardContainer = new BoardContainer();
    AddSubview(mBoardContainer);
    mBoard = mBoardContainer->mBoard;
    
    mInterfaceTop = new InterfaceTop();
    AddSubview(mInterfaceTop);
    
    mInterfaceBottom = new InterfaceBottom();
    AddSubview(mInterfaceBottom);
}

Game::~Game()
{
    gGame = 0;
    
}


void Game::Layout(float pX, float pY, float pWidth, float pHeight)
{
    SetFrame(pX, pY, pWidth, pHeight);
    
    mBoard->Load();
    
    float aTopHeight = pHeight / 8.0f;
    if(aTopHeight < 76.0f)aTopHeight = 76.0f;
    if(aTopHeight > 140.0f)aTopHeight = 140.0f;
    mInterfaceTop->Layout(0.0f, 0.0f, pWidth, aTopHeight);
    
    float aBottomHeight = pHeight / 8.0f;
    if(aBottomHeight < 68.0f)aBottomHeight = 68.0f;
    if(aBottomHeight > 108.0f)aBottomHeight = 108.0f;
    mInterfaceBottom->Layout(0.0f, pHeight - aBottomHeight, pWidth, aBottomHeight);
    
    float aBoardHeight = pHeight - (aTopHeight + aBottomHeight);
    if(aBoardHeight < 240.0f)aBoardHeight = 240.0f;
    mBoardContainer->Layout(0.0f, aTopHeight, pWidth, aBoardHeight);
    
}

void Game::Update()
{
    
}

void Game::Draw()
{
    Graphics::SetColor(0.05f, 0.05f, 0.15f, 1.0f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    Graphics::SetColor();
    
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

void Game::Notify(void *pSender)
{
    
}



