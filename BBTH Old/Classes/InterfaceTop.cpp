//
//  InterfaceTop.cpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 5/11/16.
//  Copyright © 2016 Darkswarm LLC. All rights reserved.
//

#include "InterfaceTop.h"
#include "GLApp.h"

InterfaceTop::InterfaceTop()
{
    
}

InterfaceTop::~InterfaceTop()
{
    
}


void InterfaceTop::Layout(float pX, float pY, float pWidth, float pHeight)
{
    SetFrame(pX, pY, pWidth, pHeight);
    
}

void InterfaceTop::Update()
{
    
}

void InterfaceTop::Draw()
{
    Graphics::SetColor(0.34f, 0.34f, 0.37f, 1.0f);
    Graphics::DrawRect(0.0f, 0.0f, mWidth, mHeight);
    
    Graphics::SetColor();
}


