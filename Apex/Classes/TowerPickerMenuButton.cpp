//
//  TowerPickerMenuButton.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/16/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#include "TowerPickerMenuButton.h"
#include "GLApp.h"

TowerPickerMenuButton::TowerPickerMenuButton()
{
    mApp = GAPP;
    
    mX = 0.0f;
    mY = 0.0f;
    
    mSelected = false;
    
    if(gIsLargeScreen)
    {
        mWidth = 90.0f;
        mHeight = 140.0f;
    }
    else
    {
        mWidth = 40.0f;
        mHeight = 500.0f;
    }
}

TowerPickerMenuButton::~TowerPickerMenuButton()
{
    
}

void TowerPickerMenuButton::Update()
{
    
}

void TowerPickerMenuButton::Draw()
{
    
    float aCenterX = mX + mWidth / 2.0f;
    float aCenterY = mY + mHeight / 2.0f;
    
    if(mSelected)
    {
        mApp->mTowerMenuButtonBack[1].Center(aCenterX, aCenterY);
    }
    else
    {
        mApp->mTowerMenuButtonBack[0].Center(aCenterX, aCenterY);
    }
    
}

bool TowerPickerMenuButton::Contains(int x, int y)
{
    return (x >= mX && y >= mY && x < (mX + mWidth) && (y < mY + mHeight));
}
