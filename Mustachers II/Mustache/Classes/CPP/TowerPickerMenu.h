//
//  TowerPickerMenu.h
//  Mustache
//
//  Created by Nick Raptis on 6/16/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_TowerPickerMenu_h
#define Mustache_TowerPickerMenu_h

#include "GLApp.h"
#include "TowerPickerMenuButton.h"
#include "Tower.h"

class TowerPickerMenu
{
public:
    
    TowerPickerMenu();
    virtual ~TowerPickerMenu();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    virtual void                        MultiTouch(int x, int y, void *pData);
    
    void                                Deselect();
    
    bool                                IsHoveringOverSelectedButton(int x, int y);
    
    GLApp                               *mApp;

    List                                mButtons;
    
    TowerPickerMenuButton               *mSelectedButton;
    
    Tower                               *mCurrentTower;
};

#endif
