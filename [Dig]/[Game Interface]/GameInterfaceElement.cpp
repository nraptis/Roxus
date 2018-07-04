//
//  GameInterfaceElement.cpp
//  Digplex
//
//  Created by Nick Raptis on 9/19/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "GameInterfaceElement.h"
#include "core_includes.h"

#define GAME_INTERFACE_ELEMENT 34719

GameInterfaceElement::GameInterfaceElement()
{
    mName = "GameInterfaceElement";
    mViewType = GAME_INTERFACE_ELEMENT;
    
    
    mSprite = 0;
    mSpriteShadow = 0;
    
    SetFrame(0.0f, 0.0f, 16.0f, 16.0f);
}

GameInterfaceElement::~GameInterfaceElement()
{
    
}


void GameInterfaceElement::SetSprite(FSprite *pSprite, bool pAutoSize)
{
    mSprite = pSprite;
    if((mSprite != 0) && (pAutoSize == true))
    {
        if((mSprite->mWidth > GetWidth()) && (mSprite->mHeight > GetHeight()))
        {
            SetFrame(GetX(), GetY(), mSprite->mWidth, mSprite->mHeight);
        }
    }
}

void GameInterfaceElement::SetSpriteShadow(FSprite *pSprite, bool pAutoSize)
{
    mSpriteShadow = pSprite;
    if((mSpriteShadow != 0) && (pAutoSize == true))
    {
        if((mSpriteShadow->mWidth > GetWidth()) && (mSpriteShadow->mHeight > GetHeight()))
        {
            SetFrame(GetX(), GetY(), mSpriteShadow->mWidth, mSpriteShadow->mHeight);
        }
    }
}

void GameInterfaceElement::Draw()
{
    if(mSprite)
    {
        Graphics::SetColor();
        mSprite->Center(GetWidth() / 2.0f, GetHeight() / 2.0f);
    }
}

void GameInterfaceElement::DrawShadow()
{
    if(mSpriteShadow)
    {
        Graphics::SetColor();
        mSpriteShadow->Center(GetWidth() / 2.0f, GetHeight() / 2.0f);
    }
}

void GameInterfaceElement::DrawOverlay()
{
    
    Graphics::SetColor(0.8f + gRand.F(0.05f), 0.2f, 0.6f, 0.4f);
    Graphics::OutlineRect(0.0f, 0.0f, mWidth, mHeight, 2.0f);

}



GameInterfaceContainer::GameInterfaceContainer()
{
    mDrawManual = true;
}

void GameInterfaceContainer::Draw()
{
    //DrawManualBegin();
    
    EnumList(FView, aView, mSubviews)
    {
        aView->DrawManualBegin();
        
        if(aView->mViewType == GAME_INTERFACE_ELEMENT)
        {
            ((GameInterfaceElement *)aView)->Draw();
            
        }
        else
        {
            aView->Draw();
        }
        
        aView->DrawManualSubviews();
        
        aView->DrawManualEnd();
    }
    
    Graphics::SetColor();
    
    //DrawManualEnd();
}

void GameInterfaceContainer::DrawShadow()
{
    DrawManualBegin();
    
    EnumList(FView, aView, mSubviews)
    {
        if(aView->mViewType == GAME_INTERFACE_ELEMENT)
        {
            ((GameInterfaceElement *)aView)->DrawShadow();
            
        }
    }
    
    DrawManualEnd();
}

void GameInterfaceContainer::DrawOverlay()
{
    DrawManualBegin();
    
    EnumList(FView, aView, mSubviews)
    {
        if(aView->mViewType == GAME_INTERFACE_ELEMENT)
        {
            ((GameInterfaceElement *)aView)->DrawOverlay();
        }
    }
    DrawManualEnd();
    
    
    
    DrawManualBegin();
    
    Graphics::SetColor(0.08f, 0.8f + gRand.F(0.05f), 0.6f, 0.6f);
    Graphics::OutlineRect(0.0f, 0.0f, mWidth, mHeight, 2.0f);
    
    DrawManualEnd();
    
    Graphics::SetColor();
}




