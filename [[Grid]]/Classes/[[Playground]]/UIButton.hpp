//
//  UIButton.hpp
//  DigMMMac
//
//  Created by Raptis, Nicholas on 7/3/18.
//  Copyright © 2018 Darkswarm LLC. All rights reserved.
//

#ifndef UI_BUTTON_HPP
#define UI_BUTTON_HPP

#include "FButton.h"
#include "UIRoundedRect.hpp"

class UIButton : public FButton {
public:
    UIButton();
    virtual ~UIButton();

    virtual void                            Update();
    virtual void                            Draw();

    virtual void                            Layout();

    virtual void                            TouchDown(float pX, float pY, void *pData);
    virtual void                            TouchMove(float pX, float pY, void *pData);
    virtual void                            TouchUp(float pX, float pY, void *pData);
    virtual void                            TouchFlush();

    void                                    SetTransparentBackground();

    UIRoundedRect                           mButtonBackground;
    UIRoundedRect                           mButtonOutline;

    UIRoundedRect                           mButtonBackgroundDown;
    UIRoundedRect                           mButtonOutlineDown;

    bool                                    mDrawCloseX;
    bool                                    mDrawMinimize;
    bool                                    mDrawMaximize;

    FString                                 mText;


};

#endif /* UIButton_hpp */
