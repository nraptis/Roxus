//
//  ItemBuzzDrill.cpp
//  Digplex
//
//  Created by Nick Raptis on 12/5/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.
//

#include "ItemBuzzDrill.h"
#include "MainApp.h"

ItemBuzzDrill::ItemBuzzDrill()
{
    mName = "Buzz Drill";
    SetSize(gApp->mGIItemBack);
    SetClickable();
}

ItemBuzzDrill::~ItemBuzzDrill()
{
    
}

void ItemBuzzDrill::Update()
{
    ActionProcItem::Update();
}

void ItemBuzzDrill::Draw()
{
    ActionProcItem::Draw();
    ActionProcItem::DrawCircle();
    
    
    if(mIsClicked)
    {
        Graphics::SetColor(0.75f, 0.75f, 0.75f);
    }
    else
    {
        Graphics::SetColor();
    }
    
    
    gApp->mGameTileBone.Draw(mWidth2, mHeight2, 1.0f, 0.0f);
    Graphics::SetColor();
    
}

void ItemBuzzDrill::DrawEffects()
{
    
}

void ItemBuzzDrill::DrawFocus(float pX, float pY)
{
    
}

void ItemBuzzDrill::StartTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus)
{
    
}

void ItemBuzzDrill::UpdateTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus)
{
    
}



