//
//  TowerDetailMenu.h
//  Mustache
//
//  Created by Nick Raptis on 9/6/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_TowerDetailMenu_h
#define Mustache_TowerDetailMenu_h

#include "GLApp.h"
#import "Tower.h"

class TowerDetailMenu
{
public:
    
    TowerDetailMenu();
    virtual ~TowerDetailMenu();
    
    GLApp                               *mApp;
    
    Tower                               *mTower;
    
    virtual void                        Update();
    virtual void                        Draw();
    
    bool                                mHidden;
    bool                                mAnimating;
    
    bool                                mAnimatingIn;
    
    float                               mCenterX;
    float                               mCenterY;
    
    float                               mWidth;
    float                               mHeight;
    
    float                               mScale;
    
    float                               mButtonWidth;
    float                               mButtonHeight;
    
    float                               mButtonX[3];
    float                               mButtonY[3];
    
    int                                 mButtonClickedIndex;
    
    bool                                TouchHitsButton(float x, float y);
    int                                 ReleaseAction(float x, float y);
    
    
    void                                AnimateIn(float x, float y, float pZoomScale, Tower *pTower);
    void                                AnimateOut();
    
};

#endif
