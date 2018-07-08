//
//  TowerPickerMenuButton.h
//  Mustache
//
//  Created by Nick Raptis on 6/16/13.
//  Copyright (c) 2013 Scott Shuptrine Interiors. All rights reserved.
//

#ifndef Mustache_TowerPickerMenuButton_h
#define Mustache_TowerPickerMenuButton_h

#include "GLApp.h"

class TowerPickerMenuButton
{
public:
    
    TowerPickerMenuButton();
    virtual ~TowerPickerMenuButton();
    
    virtual void                        Update();
    virtual void                        Draw();
    
    bool                                Contains(int x, int y);
    
    GLApp                               *mApp;
    
    float                               mX;
    float                               mY;
    
    bool                                mSelected;
    
    float                               mWidth;
    float                               mHeight;
    
};


#endif
