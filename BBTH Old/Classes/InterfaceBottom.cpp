//
//  InterfaceBottom.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/11/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#include "InterfaceBottom.h"
#include "GLApp.h"

InterfaceBottom::InterfaceBottom()
{
    
}

InterfaceBottom::~InterfaceBottom()
{
    
}


void InterfaceBottom::Layout(float pX, float pY, float pWidth, float pHeight)
{
    SetFrame(pX, pY, pWidth, pHeight);
}

void InterfaceBottom::Update()
{
    
}

void InterfaceBottom::Draw()
{
    Graphics::SetColor(0.38f, 0.38f, 0.38f, 1.0f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    Graphics::SetColor();
}


