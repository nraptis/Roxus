//
//  TowerPickerMenu.cpp
//  Mustache
//
//  Created by Nick Raptis on 6/16/13.
//  Copyright (c) 2013 Darkswarm LLC. All rights reserved.
//

#include "TowerPickerMenu.h"
#include "EditorMapArena.hpp"
#include "GLApp.hpp"

TowerPickerMenu::TowerPickerMenu() {
    mApp = GAPP;

    mSelectedButton = 0;
    mCurrentTower = 0;
    
    float aButtonWidth = mApp->mTowerMenuButtonBack[0].mWidth;
    float aButtonHeight = mApp->mTowerMenuButtonBack[0].mHeight;

    for (int i=0;i<5;i++) {
        TowerPickerMenuButton *aButton = new TowerPickerMenuButton();
        
        aButton->mWidth = aButtonWidth;
        aButton->mHeight = aButtonHeight;
        
        mButtons += aButton;
    }
}

TowerPickerMenu::~TowerPickerMenu()
{
    
}

void TowerPickerMenu::Update()
{
    
    float aSpacing = 0.0f;
    
    float aButtonWidth = mApp->mTowerMenuButtonBack[0].mWidth;
    float aButtonHeight = mApp->mTowerMenuButtonBack[0].mHeight;
    
    float aX = gAppWidth - aButtonWidth;
    float aY = (gAppHeight) - (aButtonHeight + 5.0f);
    
    EnumList(TowerPickerMenuButton, aButton, mButtons)
    {
        aButton->mX = aX;
        aButton->mY = aY;
        
        aX -= (aButtonWidth + aSpacing);
    }    
}

void TowerPickerMenu::Draw() {
    Graphics::SetColor();
    
    EnumList(TowerPickerMenuButton, aButton, mButtons)
    {
        aButton->Draw();
    }
}

void TowerPickerMenu::Deselect()
{
    EnumList(TowerPickerMenuButton, aButton, mButtons)
    {
        aButton->mSelected = false;
    }
    
    mSelectedButton = 0;
}

bool TowerPickerMenu::IsHoveringOverSelectedButton(int x, int y) {
    bool aResult = false;
    if (mSelectedButton) {
        if (mSelectedButton->Contains(x, y)) {
            aResult = true;
        }
    }
    
    return aResult;
}

void TowerPickerMenu::TouchDown(int x, int y, void *pData) {
    if (mSelectedButton || (gEditor != 0)) {
        return;
    }
    
    mCurrentTower = 0;
    
    EnumList (TowerPickerMenuButton, aButton, mButtons) {
        if(aButton->Contains(x, y))
        {
            mSelectedButton = aButton;
        }
    }

    if (mSelectedButton) {
        mSelectedButton->mSelected = true;
        
        mCurrentTower = new Tower();
    }
}
