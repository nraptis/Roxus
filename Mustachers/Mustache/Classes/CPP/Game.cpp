//
//  Game.cpp
//  GoldDigger
//
//  Created by Nick Raptis on 1/23/13.
//  Copyright (c) 2013 Chrysler Group LLC. All rights reserved.
//

#include "Game.h"

float gTileWidth=40.0f;
float gTileHeight=46.0f;

Game::Game()
{
    mApp = GAPP;
    gGame = this;
    
    gTileWidth = 72.0f;
    gTileHeight = 72.0f;
    
    if(gIsIpad == false)
    {
        gTileWidth /= 2.0f;
        gTileHeight /= 2.0f;
    }
    
    mCenterX = 0.0f;
    mCenterY = 0.0f;
    mZoomScale = 0.66f;
    
    mArena = new EditorGameArena();//GameArena();//GameArena();
    
    mCenterX = -mArena->mArenaWidth / 2.0f;
    mCenterY = -mArena->mArenaHeight / 2.0f;
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
    if(mArena)
    {
        mArena->Update();
    }
}

void Game::Draw()
{
    SetColor();
    DrawRect(0.0f, 0.0f, gAppWidth, gAppHeight);
    
    if(mArena)
    {
        Graphics::MatrixPush();
        
        
        Graphics::Translate(gAppWidth2, gAppHeight2, 1.0f);
        Graphics::Scale(mZoomScale);
        Graphics::Translate(mCenterX, mCenterY, 0.0f);
        
        mArena->Draw();
        
        Graphics::MatrixPop();
        
    }
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

void Game::MultiTouch(int x, int y, void *pData)
{
    //mBoard->MultiTouch(x, y, pData);
    
    if(mArena)
    {
        mArena->Click(TransformX(x), TransformY(y));
    }
}

void Game::MultiRelease(int x, int y, void *pData)
{
    //mBoard->MultiRelease(x, y, pData);
}

void Game::MultiDrag(int x, int y, void *pData)
{
    //mBoard->MultiDrag(x, y, pData);
}

void Game::FlushMultiTouch()
{
    //mBoard->FlushMultiTouch();
    
    
}

float Game::TransformX(float pX)
{
    return ((pX - gAppWidth2) / mZoomScale) - mCenterX;
    //float aReturn = pX;
    //aReturn = gAppWidth2 + ((aReturn - gAppWidth2) / mZoomScale);
    //aReturn -= (gAppWidth2 + mCenterX);
    //return aReturn;
}

float Game::TransformY(float pY)
{
    return ((pY - gAppHeight2) / mZoomScale) - mCenterY;
    //float aReturn = pY;
    //aReturn = gAppHeight2 + ((aReturn - gAppHeight2) / mZoomScale);
    //aReturn -= (gAppHeight2 + mCenterY);
    //return aReturn;
}
