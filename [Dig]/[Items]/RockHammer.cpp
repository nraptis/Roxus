//  RockHammer.cpp
//  Digplex
//
//  Created by Nick Raptis on 11/30/14.
//  Copyright (c) 2014 Froggy Studios LLC. All rights reserved.

#include "MainApp.h"
#include "RockHammer.h"


RockHammer::RockHammer()
{
    mName = "Rock Hammer";
 
    SetSize(gApp->mGIItemBack);
    
    SetClickable();
}

RockHammer::~RockHammer()
{
    
}

void RockHammer::Update()
{
    ActionProcItem::Update();
}

void RockHammer::Draw()
{
    ActionProcItem::Draw();
    ActionProcItem::DrawCircle();
    
    if(mIsClicked)Graphics::SetColor(0.75f, 0.75f, 0.75f);
    else Graphics::SetColor();
    
    gApp->mGIRockHammerBack.Draw(mWidth2, mHeight2, 1.0f, 0.0f);
    Graphics::SetColor();
}

void RockHammer::DrawEffects()
{
    
}

void RockHammer::DrawFocus(float pX, float pY)
{
    
}

void RockHammer::StartTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus)
{
    
}

void RockHammer::UpdateTrigger(float pFromX, float pFromY, ActionProcItemFocus *pFocus)
{
    
}


